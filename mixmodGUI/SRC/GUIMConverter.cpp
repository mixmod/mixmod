/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMConverter.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2015
    email                : contact@mixmod.org
 ***************************************************************************/

/***************************************************************************
    This file is part of MIXMOD

    MIXMOD is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MIXMOD is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

    All informations available on : http://www.mixmod.org
***************************************************************************/
#include "mixmod/Kernel/IO/IndividualColumnDescription.h"
#include "mixmod/Kernel/IO/QualitativeColumnDescription.h"
#include "mixmod/Kernel/IO/QuantitativeColumnDescription.h"
#include "mixmod/Kernel/IO/WeightColumnDescription.h"

#include "GUIMConverter.h"
#include "GUIMFilenameValidator.h"
#include "mixmod_iostream/DomData.h"

GUIMConverter::GUIMConverter(): _validateInput(false), _validateNumericMixmod(false), _validateXMLMixmod(false) {
	init();

	QVBoxLayout *mainLayout = new QVBoxLayout();
	_gridInput = new QGridLayout;
	_gridOutput = new QGridLayout;

	_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	_buttonBox->setStyleSheet("QPushButton {background:white}");

	layout = new QGridLayout();
	layout->setVerticalSpacing(15);

	createNbColumnBox();
	createNbSampleBox();
	createChoiceColumn();
	createFilenameBox();
	createFormatBox();
	createMixmodFilenameBox();

	connect(_buttonBox, SIGNAL(accepted()), this, SLOT(ok()));
	connect(_buttonBox, SIGNAL(rejected()), this, SLOT(discard()));

	mainLayout->addLayout(layout);
	mainLayout->addSpacing(20);
	mainLayout->addWidget(_buttonBox);
	setLayout(mainLayout);
	resize(this->width(), this->height()*0.9);
}

GUIMConverter::~GUIMConverter() {
}

void GUIMConverter::init() {

	setWindowTitle( tr("Converter") );

	//working Directory
	if ( !GUISettings::workDirectory.exists() ) {
		GUISettings::workDirectory.setPath(".");
	}

	_numericFilename = "";
	_XMLFilename = "";
	TEXT_VALIDATOR = tr("Not a valid File") ;
	DIR_VALIDATOR = tr("Not a valid Directory") ;
	FILE_VALIDATOR = tr("File already exists") ;
	_hPos = 0;

	QRegExp rxNumeric("*.dat");
	rxNumeric.setPatternSyntax(QRegExp::Wildcard);
	_validatorNumeric = new QRegExpValidator(rxNumeric, 0);

	QRegExp rxXML("*.mxd");
	rxXML.setPatternSyntax(QRegExp::Wildcard);
	_validatorXML = new QRegExpValidator(rxXML, 0);

	QLinearGradient gradient(QPointF(0,200), QPointF(400,300));
	gradient.setColorAt(1, QColor(140,180,250,240));
	gradient.setColorAt(0, Qt::white);
	QBrush back = QBrush(gradient);

	QPalette pal = palette();
	pal.setBrush(QPalette::Background, back);
	pal.setBrush(QPalette::Base, back);

	setPalette(pal);
	setStyleSheet("QPushButton {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff)};");
	setWindowIcon(QPixmap(":/logo.png"));

	setAttribute( Qt::WA_DeleteOnClose );
	setWindowModality (Qt::ApplicationModal);
}

void GUIMConverter::createNbColumnBox() {
	QLabel * nbColumnLabel = new QLabel(tr("Number of columns"));

	_nbColumnSpinBox = new QSpinBox();
	_nbColumnSpinBox->setMinimum( 1 );
	_nbColumnSpinBox->setMaximum( XEM::maxPbDimension + 2 );//2 for Name & Weight
	_nbColumnSpinBox->setValue(1);

	connect(_nbColumnSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateChoiceColumn(int)));

	groupBoxInput = new QGroupBox(tr("Input"));
	_hPosInput = 0;

	layout->addWidget(groupBoxInput, _hPos++, 0, 2, 4);

	_gridInput->addWidget(nbColumnLabel, _hPosInput, 0, 1, 1);
	_gridInput->addWidget(_nbColumnSpinBox, _hPosInput++, 2, 1, 2);
}

void GUIMConverter::createNbSampleBox() {
	QLabel * nbSampleLabel = new QLabel(tr("Number of samples (optional)"));

	_nbSampleSpinBox = new QSpinBox();
	_nbSampleSpinBox->setMinimum( 0 );
	_nbSampleSpinBox->setMaximum( XEM::maxNbSample );
	_nbSampleSpinBox->setValue(0);

	_gridInput->addWidget(nbSampleLabel,_hPosInput,0,1,1);
	_gridInput->addWidget(_nbSampleSpinBox, _hPosInput++, 2, 1, 2);
}

void GUIMConverter::createChoiceColumn() {
	sa = new QScrollArea();
	int64_t widthArea = 8;
	sa->setStyleSheet("background:white;");
	sa->setWidgetResizable( true );

	_choiceColumnConverter = new GUIMChoiceColumnConverter();
	_choiceColumnConverter->updateChoiceColumnConverter(1);
	sa->setWidget(_choiceColumnConverter);
	sa->setMinimumHeight(sa->sizeHint().height()*1.5);

	sa->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QLabel * columnLabel = new QLabel(tr("Selection of columns"));
	_gridInput->addWidget(columnLabel, _hPosInput++,0,1,1);
	_gridInput->addWidget(sa, _hPosInput, 0, widthArea, 4);
	_hPosInput = _hPosInput + widthArea;
}


void GUIMConverter::createFilenameBox() {

	QLabel * filenameLabel = new QLabel(tr("Filename"));
	_filenameEdit = new QLineEdit();
	connect(_filenameEdit, SIGNAL(textChanged(QString)), this, SLOT(verifyTextInput(QString)));
	connect(_filenameEdit, SIGNAL(textChanged(QString)), this, SLOT(updateOutput(QString)));
	_filenameButton = new QPushButton(tr("..."));
	connect(_filenameButton, SIGNAL( released()), this, SLOT(setFilename()));
	_validatorlabel = new QLabel(TEXT_VALIDATOR);

	_gridInput->addWidget(filenameLabel, _hPosInput, 0, 1, 1);
	_gridInput->addWidget(_filenameEdit, _hPosInput, 1, 1, 2);
	_gridInput->addWidget(_filenameButton, _hPosInput++, 3 );
	_gridInput->addWidget(_validatorlabel, _hPosInput++, 1 , 1, 2);
	groupBoxInput->setLayout(_gridInput);
}

void GUIMConverter::createFormatBox() {
	_indexFormat = 0;
	QLabel * formatLabel = new QLabel(tr("Format"));
	_formatComboBox = new QComboBox();

	for (int64_t i = 0; i < XEM::nbFormatNumeric; ++i) {
		_formatVector.push_back(QString::fromStdString(XEM::FormatNumericFileToString(static_cast<XEM::FormatNumeric::FormatNumericFile>(i))));

		//TODO condition a enlever
		if (static_cast<XEM::FormatNumeric::FormatNumericFile>(i) == XEM::FormatNumeric::defaultFormatNumericFile)
			_formatComboBox->addItem(_formatVector[i]);

	}
	_formatComboBox->setStyleSheet("background:qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 1 #82aae6, stop: 0 #ffffff);");

	_gridInput->addWidget(formatLabel, _hPosInput, 0, 1, 1);
	_gridInput->addWidget(_formatComboBox, _hPosInput, 3, 1, 1);
}

void GUIMConverter::createMixmodFilenameBox() {
	QGroupBox *groupBox = new QGroupBox(tr("Output"));
	QLabel * filenameNumericMixmodLabel = new QLabel(tr("New numeric filename"));
	_filenameNumericMixmodEdit = new QLineEdit();

	connect(_filenameNumericMixmodEdit, SIGNAL(textChanged(QString)), this, SLOT(verifyTextNumericMixmod(QString)));
	_filenameNumericMixmodButton = new QPushButton(tr("Change Directory"));//change directory
	_filenameNumericMixmodButton->setEnabled(false);
	connect(_filenameNumericMixmodButton, SIGNAL( released()), this, SLOT(setDirectoryNumericFile()));
	_validatorNumericlabel = new QLabel(TEXT_VALIDATOR);

	_hPosOutput = 0;
	layout->addWidget(groupBox, _hPosInput + _hPos++, 0, 2, 4);

	_gridOutput->addWidget(filenameNumericMixmodLabel, _hPosOutput, 0, 1, 1);
	_gridOutput->addWidget(_filenameNumericMixmodEdit, _hPosOutput, 1, 1, 2);
	_gridOutput->addWidget(_filenameNumericMixmodButton, _hPosOutput++, 3 );
	_gridOutput->addWidget(_validatorNumericlabel, _hPosOutput++, 1 , 1, 2);

	QLabel * filenameXMLMixmodLabel = new QLabel(tr("New XML filename"));
	_filenameXMLMixmodEdit = new QLineEdit();

	connect(_filenameXMLMixmodEdit, SIGNAL(textChanged(QString)), this, SLOT(verifyTextXMLMixmod(QString)));
	_filenameXMLMixmodButton = new QPushButton(tr("Change Directory"));//change directory
	_filenameXMLMixmodButton->setEnabled(false);
	connect(_filenameXMLMixmodButton, SIGNAL( released()), this, SLOT(setDirectoryXMLFile()));
	_validatorXMLlabel = new QLabel(TEXT_VALIDATOR);

	_gridOutput->addWidget(filenameXMLMixmodLabel, _hPosOutput, 0, 1, 1);
	_gridOutput->addWidget(_filenameXMLMixmodEdit, _hPosOutput, 1, 1, 2);
	_gridOutput->addWidget(_filenameXMLMixmodButton, _hPosOutput++, 3 );
	_gridOutput->addWidget(_validatorXMLlabel, _hPosOutput++, 1 , 1, 2);

	groupBox->setLayout(_gridOutput);
}


void GUIMConverter::setFilename() {
	QString fileName = QFileDialog::getOpenFileName( this, tr("Open Data"),GUISettings::workDirectory.absolutePath(), tr("All files (*)") );
	if (QFileInfo(fileName).exists())
		_filenameEdit->setText( fileName );
}

void GUIMConverter::setDirectoryNumericFile() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),GUISettings::workDirectory.absolutePath(),QFileDialog::ShowDirsOnly);
	if (!dir.isEmpty())
		_filenameNumericMixmodEdit->setText( dir + QDir::separator() + _numericFilename);

}

void GUIMConverter::setDirectoryXMLFile() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),GUISettings::workDirectory.absolutePath(),QFileDialog::ShowDirsOnly);
	if (!dir.isEmpty())
		_filenameXMLMixmodEdit->setText(dir + QDir::separator() + _XMLFilename);
}


void GUIMConverter::verifyTextInput(QString text ) {
	int cursor = 0;
	GUIMFilenameValidator * _validatorFilename = new GUIMFilenameValidator(this);
	if( _validatorFilename->validate( text, cursor ) == QValidator::Acceptable ) {
		_validatorlabel->setText("");
		_validateInput = true;
	}
	else {
		_validatorlabel->setText(TEXT_VALIDATOR);
		_validateInput = false;
	}
	_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(_validateInput && _validateNumericMixmod && _validateXMLMixmod);
	_filenameNumericMixmodButton->setEnabled(_validateInput);
	_filenameXMLMixmodButton->setEnabled(_validateInput);
}


void GUIMConverter::verifyTextNumericMixmod(QString text) {
	if (!_filenameNumericMixmodEdit->text().isEmpty()) {
		int cursor = 0;
		QFileInfo infoNumericMixmod(_filenameNumericMixmodEdit->text());
		QDir dirNumericMixmod(infoNumericMixmod.absoluteDir());
		if (!dirNumericMixmod.exists()) { //directory doesn't exist
			_validateNumericMixmod = false;
			_validatorNumericlabel->setText(DIR_VALIDATOR);
		}
		else if (infoNumericMixmod.exists() && !infoNumericMixmod.isDir()) {//file exists
			_validateNumericMixmod = false;
			_validatorNumericlabel->setText(FILE_VALIDATOR);
		}
		else if (_validatorNumeric->validate( text, cursor ) != QValidator::Acceptable) {//bad extension
			_validateNumericMixmod = false;
			_validatorNumericlabel->setText(TEXT_VALIDATOR);
		}
		else {
			_validateNumericMixmod = true;
			_validatorNumericlabel->setText("");
		}
	}
	else {
		_validateNumericMixmod = false;
		_validatorNumericlabel->setText(TEXT_VALIDATOR);
	}
	_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(_validateInput && _validateNumericMixmod && _validateXMLMixmod);
}


void GUIMConverter::verifyTextXMLMixmod(QString text) {
	if (!_filenameXMLMixmodEdit->text().isEmpty()) {
		int cursor = 0;
		QFileInfo infoXMLMixmod(_filenameXMLMixmodEdit->text());
		QDir dirXMLMixmod(infoXMLMixmod.absoluteDir());
		if (!dirXMLMixmod.exists()) { //directory doesn't exist
			_validateXMLMixmod = false;
			_validatorXMLlabel->setText(DIR_VALIDATOR);
		}
		else if (infoXMLMixmod.exists() && !infoXMLMixmod.isDir()) {//file exists
			_validateXMLMixmod = false;
			_validatorXMLlabel->setText(FILE_VALIDATOR);
		}
		else if (_validatorXML->validate( text, cursor ) != QValidator::Acceptable) {//bad extension
			_validateXMLMixmod = false;
			_validatorXMLlabel->setText(TEXT_VALIDATOR);
		}
		else {
			_validateXMLMixmod = true;
			_validatorXMLlabel->setText("");
		}
	}
	else {
		_validateXMLMixmod = false;
		_validatorXMLlabel->setText(TEXT_VALIDATOR);
	}
	_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(_validateInput && _validateNumericMixmod && _validateXMLMixmod);
}


void GUIMConverter::updateOutput(QString text) {
	QFileInfo info( text );
	_numericFilename ="mixmod_" + info.baseName() + ".dat";
	QString mixmodDataFileName = GUISettings::workDirectory.absolutePath() + QDir::separator() + _numericFilename;//our numeric filename

	//-------------------------------
	//case if our numeric File exists
	//-------------------------------
	QFileInfo infoMixmodFilenameTmp( mixmodDataFileName);
	int64_t comptMixmodFilename = 2;
	QFileInfo infoMixmodFilename =  infoMixmodFilenameTmp;

	while (infoMixmodFilename.exists()) { //if exists, we have to choose an other filename
		_numericFilename = infoMixmodFilenameTmp.baseName() + QString::number(comptMixmodFilename++)+ "." + infoMixmodFilenameTmp.completeSuffix();
		mixmodDataFileName = infoMixmodFilenameTmp.absolutePath() + QDir::separator() + _numericFilename;
		infoMixmodFilename.setFile(mixmodDataFileName);
	}

	_filenameNumericMixmodEdit->setText(mixmodDataFileName);
	_XMLFilename = infoMixmodFilename.baseName() + ".mxd";
	_filenameXMLMixmodEdit->setText(infoMixmodFilename.absolutePath() + QDir::separator() +  _XMLFilename);
}


void GUIMConverter::updateChoiceColumn(int nbColumn) {
	_choiceColumnConverter->updateChoiceColumnConverter(nbColumn);
}

void GUIMConverter::ok() {
	//---------------------------------------
	//check if at least one column is chosen
	//---------------------------------------
	if (_choiceColumnConverter->getAtLeastOneColumnIsUsed() == false) {
		QMessageBox msgBox(QMessageBox::Warning, tr("Warning"), tr("At least one column must be chosen !"),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
		return;
	}

	//----------------------------------------------
	//check if the chosen configuration is possible
	//----------------------------------------------
	if (!_choiceColumnConverter->goodColumnConfiguration()) {
		QMessageBox msgBox(QMessageBox::Warning, tr("Warning"), tr("Chosen type is invalid ! \n Possible causes : \n 1) Mixed data are not usuable. \n 2) Weight or name can't be alone."),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
		return;
	}

	if(_validateInput && _validateNumericMixmod && _validateXMLMixmod) {

		vector<bool> columnUsed;
		bool individualNameMustBeGenerated = true;//if one column is chosen as Name,  individualNameMustBeGenerated is false
		QVector <QButtonGroup* > vButtonGroup = _choiceColumnConverter->getVButtonGroup();//vButtonGroup contains all the button displayed in the converter window

		for (int64_t i = 0; i<vButtonGroup.size(); ++i) {
			//The column (i+1) is chosen if "useless" not chosen
			columnUsed.push_back(vButtonGroup[i]->checkedId() != static_cast<int>(USELESS));

			//if Column is name (last choice in list)
			if (vButtonGroup[i]->checkedId() == static_cast<int>(NAME)) {
				individualNameMustBeGenerated = false;
			}
		}

		XEM::FormatNumeric::FormatNumericFile format = XEM::StringToFormatNumericFile(_formatComboBox->currentText().toStdString());

		QFileInfo info( _filenameEdit->text() ) ;
		string userDataFileName = info.absoluteFilePath().toStdString();
		int64_t nbSample = _nbSampleSpinBox->value();

		try {
			//--------------------------------
			//copy of user's numeric data file
			//--------------------------------
			string mixmodDataFileName = _filenameNumericMixmodEdit->text().toStdString();
			XEM::createMixmodDataFileFromUserDataFile(userDataFileName, mixmodDataFileName, columnUsed, format, individualNameMustBeGenerated, nbSample);

			//-------------------------------------
			//creation of column Description vector
			//-------------------------------------
			vector<XEM::ColumnDescription *> columnDescription;
			int64_t compt = 0;//this is the num of the column for our numeric data
			for (int64_t i = 0; i<columnUsed.size(); ++i) {

				XEM::ColumnDescription * column;

				if (compt == 0 && individualNameMustBeGenerated == true) { //if column generated
					column = new XEM::IndividualColumnDescription(compt);
					columnDescription.push_back(column);
					compt++;
				}

				if (columnUsed[i]) {
					switch(vButtonGroup[i]->checkedId()) {
					case static_cast<int>(QUANTITATIVE):
						column = new XEM::QuantitativeColumnDescription(compt);
						compt++;
						break;
					case static_cast<int>(QUALITATIVE):
						column = new XEM::QualitativeColumnDescription(compt, _choiceColumnConverter->getNbFactor(i));
						compt++;
						break;
					case static_cast<int>(WEIGHT):
						column = new XEM::WeightColumnDescription(compt);
						compt++;
						break;
					case static_cast<int>(NAME):
						column = new XEM::IndividualColumnDescription(compt);
						compt++;
					default :
						break;
					}
					columnDescription.push_back(column);
				}
			}

			//-------------------
			//create the XML file
			//-------------------
			QFileInfo infoMixmodFilename( QString::fromStdString(mixmodDataFileName));
			XEM::DataDescription data(nbSample, columnDescription.size(), columnDescription, format, mixmodDataFileName, "");
			string sMXDFilename = QString(infoMixmodFilename.absolutePath() + QDir::separator() + infoMixmodFilename.baseName()).toStdString();
			XEM::DomData doc(data, sMXDFilename);

			QMessageBox msgBox(QMessageBox::Information, tr("Information"), tr("Your data are created !"),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();

			close();

		}
		catch(XEM::Exception* e) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( e->what() ) +"\n"+ tr("Your data aren't created !"),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
			close();
		}
		catch(XEM::IOStreamErrorType errorType) {
			QMessageBox msgBox(QMessageBox::Warning, QObject::tr("Warning"), QObject::tr( XEM::IOStreamErrorTypeToString(errorType).c_str() ) +"\n"+ tr("Your data aren't created !"),QMessageBox::Ok );
			msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
			msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
			msgBox.exec();
			close();
		}
	}
}

void GUIMConverter::discard() {
	close();
}
