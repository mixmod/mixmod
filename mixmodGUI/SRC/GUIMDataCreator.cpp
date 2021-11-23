/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMDataCreator.cpp  description
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
#include "GUIMDataCreator.h"
#include "GUIUtil.h"
#include <QDebug>
#include <sstream>

#include <QFileInfo>
#include <QRadioButton>
#include <QPushButton>
#include <QFileDialog>
#include <QScrollBar>

GUIMDataCreator::GUIMDataCreator( XEM::MVC::RootTreeItem::ProjectType _projectType, QWizard* parent  )
	: QWizardPage(parent)
{
	TEXT_VALIDATOR = tr("Not a valid File") ;
	setTitle( tr("Data ") );

	_labelFilename = new QLabel( QObject::tr("Data filename "), this );

	_grid = new QGridLayout( this );
	int hPos = 0 ;
	//nbnbcluster

	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		_labelNbNbCluster = new QLabel( QObject::tr("Different number of clusters "), this );
		_grid->addWidget(const_cast<QLabel*>(_labelNbNbCluster), hPos, 1);
		_sbNbNbCluster = new QSpinBox( this );
		_sbNbNbCluster->setMinimum( 1 );
		_sbNbNbCluster->setMaximum( XEM::maxNbNbCluster );
		_grid->addWidget( _sbNbNbCluster, hPos++, 2, 1, 4 );
		_sbNbNbCluster->setVisible(true);
		_plus = new QPushButton( "+", this );
		_plus->setFixedSize(_plus->height(), _plus->height());
		_minus = new QPushButton( "-", this );
		_minus->setFixedSize(_minus->height(), _minus->height());
		_nbCluster = new SpinBoxesWidget( this );

		connect(_plus, SIGNAL( released() ), this , SLOT( addToNbNbCluster() ));
		connect(_minus, SIGNAL( released() ), this , SLOT( removeToNbNbCluster() ));
		_nbClusterArea = new QScrollArea( this );

		// here the parent of _modality become _modalityArea
		_nbClusterArea->setWidget( _nbCluster );
		_grid->addWidget( _plus, hPos, 1,  Qt::AlignRight);
		_grid->addWidget( _nbClusterArea, hPos++, 2, 2, 4 );
		_grid->addWidget( _minus, hPos++, 1,  Qt::AlignRight);

	}
	else {
		_sbNbNbCluster = NULL;
		_labelNbNbCluster = new QLabel( QObject::tr("Number of clusters "), this );
		_grid->addWidget( const_cast<QLabel*>(_labelNbNbCluster), hPos, 1 );
		_sbNbClusterAD = new QSpinBox( this );
		_sbNbClusterAD->setMinimum( 1 );
		_grid->addWidget( _sbNbClusterAD, hPos++, 2, 1, 4 );
	}

	//file
	_filename = new QLineEdit( this );
	_validatorFilename = new GUIMFilenameValidator( this );

	QRegExp rxXML("*.mxd");
	rxXML.setPatternSyntax(QRegExp::Wildcard);
	_validatorXML = new QRegExpValidator(rxXML, 0);

	_bFilename = new QPushButton( "...", this );
	_labelValidator = new QLabel( TEXT_VALIDATOR );

	_grid->addWidget( const_cast<QLabel*>(_labelFilename), hPos, 1 );
	_grid->addWidget( _filename, hPos, 2, 1, 3 );
	_grid->addWidget( _bFilename, hPos++, 5 );
	_grid->addWidget( _labelValidator, hPos++, 2 );

	if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		_filenamePartition = new QLineEdit( this );
		_validatorFilenamePartition = new GUIMFilenameValidator( this );
		_bFilenamePartition = new QPushButton( "...", this );
		_labelValidatorPartition = new QLabel( TEXT_VALIDATOR );
		_labelFilenamePartition = new QLabel( QObject::tr("Data Partition"), this );
		_grid->addWidget( const_cast<QLabel*>(_labelFilenamePartition), hPos, 1 );
		_grid->addWidget( _filenamePartition, hPos, 2, 1, 3 );
		_grid->addWidget( _bFilenamePartition, hPos++, 5 );
		_grid->addWidget( _labelValidatorPartition, hPos++, 2 );

		_filenameReclassify = new QLineEdit( this );
		_validatorFilenameReclassify = new GUIMFilenameValidator( this );
		_bFilenameReclassify = new QPushButton( "...", this );
		_labelValidatorReclassify = new QLabel( TEXT_VALIDATOR );
		_labelFilenameReclassify = new QLabel( QObject::tr("Data filename to classify"), this );
		_grid->addWidget( const_cast<QLabel*>(_labelFilenameReclassify), hPos, 1 );
		_grid->addWidget( _filenameReclassify, hPos, 2, 1, 3 );
		_grid->addWidget( _bFilenameReclassify, hPos++, 5 );
		_grid->addWidget( _labelValidatorReclassify, hPos++, 2 );
	}

	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		updateNbNbCluster( _sbNbNbCluster->value() );
		connect( _sbNbNbCluster, SIGNAL( valueChanged(int) ), this, SLOT( updateNbNbCluster(int) ) );
		registerField("nbNbCluster", _sbNbNbCluster);
		registerField("nbCluster", _nbCluster);
	}
	else {
		connect( _filenamePartition, SIGNAL( textChanged(const QString &) ), this, SLOT( verifyTextPartition(const QString &) ) );
		connect( _filenameReclassify, SIGNAL( textChanged(const QString &) ), this, SLOT( verifyTextReclassify(const QString &) ) );
		connect( _bFilenameReclassify, SIGNAL( released() ), this, SLOT( setFilenameReclassify() ) );
		connect( _bFilenamePartition, SIGNAL( released() ), this, SLOT( setFilenamePartition() ) );
		registerField("nbCluster", _sbNbClusterAD);
		registerField("dataPartition*", _filenamePartition);
		registerField("dataFilenameReclassify*", _filenameReclassify);
	}

	connect( _bFilename, SIGNAL( released() ), this, SLOT( setFilename() ) );

	connect( _filename, SIGNAL( textChanged(const QString &) ), this, SLOT( verifyText(const QString &) ) );

	registerField("dataFilename*", _filename);
	adjustSize();
}

GUIMDataCreator::~GUIMDataCreator() {
}


void GUIMDataCreator::setFilename() {
	QString filename = QFileDialog::getOpenFileName( this, tr("Open Data"),GUISettings::workDirectory.absolutePath(), tr("Data files (*.mxd);;All files (*)") ) ;
	if (!filename.isEmpty())
		_filename->setText( filename );
}


void GUIMDataCreator::setFilenameReclassify() {
	QString filename = QFileDialog::getOpenFileName( this, tr("Open Data"),GUISettings::workDirectory.absolutePath(), tr("Data files (*.dat);;Text files (*.txt);;All files (*)") );
	if (!filename.isEmpty())
		_filenameReclassify->setText( filename );
}

void GUIMDataCreator::setFilenamePartition() {
	QString filename = QFileDialog::getOpenFileName( this, tr("Open Partition"), GUISettings::workDirectory.absolutePath(), tr("Partition files (*.part);;Text files (*.txt);;All files (*)") );
	if (!filename.isEmpty())
		_filenamePartition->setText( filename );
}


void GUIMDataCreator::updateNbNbCluster( int nb ) {
	_nbClusterArea->setVisible(false);
	_nbCluster->updateTab( nb );
	_nbClusterArea->setVisible(true);
}

void GUIMDataCreator::verifyText( const QString & text ) {
	QString tmpText = text ;
	int cursorPos = _filename->cursorPosition() ;

	if( _validatorFilename->validate( tmpText, cursorPos ) == QValidator::Acceptable && _validatorXML->validate( tmpText, cursorPos ) == QValidator::Acceptable) {
		_labelValidator->setText("");
	}
	else {
		_labelValidator->setText(TEXT_VALIDATOR);
	}
}

void GUIMDataCreator::verifyTextPartition( const QString & text ) {
	QString tmpText = text ;
	int cursorPos = _filenamePartition->cursorPosition() ;

	if( _validatorFilenamePartition->validate( tmpText, cursorPos ) == QValidator::Acceptable ) {
		_labelValidatorPartition->setText("");
	}
	else {
		_labelValidatorPartition->setText(TEXT_VALIDATOR);
	}
}

void GUIMDataCreator::verifyTextReclassify( const QString & text ) {
	QString tmpText = text ;
	int cursorPos = _filenameReclassify->cursorPosition() ;

	if( _validatorFilenameReclassify->validate( tmpText, cursorPos ) == QValidator::Acceptable ) {
		_labelValidatorReclassify->setText("");
	}
	else {
		_labelValidatorReclassify->setText(TEXT_VALIDATOR);
	}
}

void GUIMDataCreator::addToNbNbCluster() {
	_sbNbNbCluster->setValue(_sbNbNbCluster->value()+1);
	updateNbNbCluster( _sbNbNbCluster->value() );
}

void GUIMDataCreator::removeToNbNbCluster() {
	_sbNbNbCluster->setValue(_sbNbNbCluster->value()-1);
	updateNbNbCluster( _sbNbNbCluster->value() );
}

void GUIMDataCreator::resizeEvent( QResizeEvent* event ) {
	// no horizontal scroll bar
	if (_sbNbNbCluster) {
		_nbCluster->move(_sbNbNbCluster->value());
	}
	QWidget::resizeEvent( event );
}
