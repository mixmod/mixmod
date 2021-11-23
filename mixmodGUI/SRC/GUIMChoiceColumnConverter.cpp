/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMChoiceColumnConverter.cpp  description
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

#include "GUIMChoiceColumnConverter.h"

GUIMChoiceColumnConverter::GUIMChoiceColumnConverter() {
	_atLeastOneColumnIsUsed = false;

	setStyleSheet("background-color:white");
	_mainLayout = new QGridLayout();

	//first line (header)
	int64_t vPos = 0;
	_mainLayout->addWidget(new QLabel(tr("Column")), 0, vPos++  );

	for (int i=0; i<static_cast<int>(NBCOLUMNTYPE); ++i) {
		GUIMLabel * title = new GUIMLabel(ColumnTypetoString(static_cast<ColumnTypeForRadioButton>(i)));
		title->setId(i);
		connect(title, SIGNAL(clickedOn(int)), this, SLOT(checkAll(int)));
		_mainLayout->addWidget(title, 0, vPos++  );
	}

	_mainLayout->addWidget(new QLabel(tr("Factor")), 0, vPos  );
	setLayout(_mainLayout);
}

GUIMChoiceColumnConverter::~GUIMChoiceColumnConverter() {
}

void GUIMChoiceColumnConverter::updateChoiceColumnConverter(int64_t nbColumn) {
	int64_t oldNbColumn = _vButtonGroup.size();

	//new Column(s) to add
	if (oldNbColumn<nbColumn) {
		for (int64_t i = oldNbColumn+1; i <= nbColumn; ++i) {

			QLabel * label = new QLabel( tr("C") + QString::number(i));
			_vLabel.push_back(label);

			//add the row i
			addRow(i);
		}
	}

	//remove row(s)
	if (oldNbColumn>nbColumn) {
		for (int64_t i = oldNbColumn-1; i>= nbColumn ; --i) {

			delete _vLabel[i];
			_vLabel.pop_back();

			delete _vFactor[i];
			_vFactor.pop_back();

			//delete the radio button
			qDeleteAll(_vButtonGroup[i]->buttons());
			_vButtonGroup[i]->buttons().clear();

			//delete the button group
			delete _vButtonGroup[i];
			_vButtonGroup.pop_back();

		}
	}

	//if oldNbColumn == nbColumn, converter doesn't change
}

void GUIMChoiceColumnConverter::addRow(int64_t row) {
	int64_t vPos = 0;

	//creation of radiobouton groupBox
	QButtonGroup *buttonGroup = new QButtonGroup(this);
	connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(verifyButton(QAbstractButton*)));
	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(oneColumnIsChanged(int)));
	buttonGroup->setObjectName(QString::number(row));

	QRadioButton *rUseless = new QRadioButton("");
	//connect(rUseless, SIGNAL(clicked(bool)), this, SLOT(oneColumnIsChanged(int)));
	QRadioButton *rQuantitative = new QRadioButton("");
	QRadioButton *rQualitative = new QRadioButton("");
	QRadioButton *rWeight = new QRadioButton("");
	QRadioButton *rName = new QRadioButton("");

	buttonGroup->addButton(rUseless);
	buttonGroup->setId(rUseless, static_cast<int>(USELESS));
	buttonGroup->addButton(rQuantitative);
	buttonGroup->setId(rQuantitative,static_cast<int>(QUANTITATIVE));
	buttonGroup->addButton(rQualitative);
	buttonGroup->setId(rQualitative, static_cast<int>(QUALITATIVE));//use to known if qualitative or not
	buttonGroup->addButton(rWeight);
	buttonGroup->setId(rWeight, static_cast<int>(WEIGHT));
	buttonGroup->addButton(rName);
	buttonGroup->setId(rName, static_cast<int>(NAME));
	rUseless->setChecked(true);

	_vButtonGroup.push_back(buttonGroup);

	//display the line in the window of the converter
	_mainLayout->addWidget(_vLabel[row-1], row+1, vPos++);
	_mainLayout->addWidget(rUseless, row+1, vPos++);
	_mainLayout->addWidget(rQuantitative, row+1, vPos++);
	_mainLayout->addWidget(rQualitative, row+1, vPos++);
	_mainLayout->addWidget(rWeight, row+1, vPos++);
	_mainLayout->addWidget(rName, row+1, vPos++);

	//creation of factor spinBox
	QSpinBox * sbFactor = new QSpinBox();
	sbFactor->setEnabled(false);
	sbFactor->setMinimum(1);
	_mainLayout->addWidget(sbFactor, row+1, vPos);

//  int64_t indexSpinBox = _vFactor.size();
	_vFactor.push_back(sbFactor);
}

void GUIMChoiceColumnConverter::verifyButton(QAbstractButton * button) {
	//to enabled factor or not
	QButtonGroup * bGroup = button->group();
	int64_t row = bGroup->objectName().toLongLong();//row where nbfactor need to be changed or not
	int64_t id = bGroup->id(button);

	//qualitative
	_vFactor[row-1]->setEnabled(id == static_cast<int>(QUALITATIVE));
}

void GUIMChoiceColumnConverter::oneColumnIsChanged(int ) {
	_atLeastOneColumnIsUsed = false ;
	for (int64_t i = 0; i<_vButtonGroup.size(); ++i) {
		_atLeastOneColumnIsUsed = _atLeastOneColumnIsUsed | (_vButtonGroup[i]->checkedId() != static_cast<int>(USELESS));//to know if at least one column is chosen
	}
}

void GUIMChoiceColumnConverter::checkAll(int num) {
	for (int i = 0; i<_vButtonGroup.size(); i++) {
		QAbstractButton* button = _vButtonGroup[i]->button(num);
		button->setChecked(true);
		verifyButton(button);
		oneColumnIsChanged(num);
	}
}


int64_t GUIMChoiceColumnConverter::getNbFactor(int64_t index) {
	return _vFactor.at(index)->value();
}

bool GUIMChoiceColumnConverter::goodColumnConfiguration() const {
	bool res = true ;

	int64_t nbQualitative = 0;
	int64_t nbQuantitative = 0;
	int64_t nbWeight = 0;
	int64_t nbName = 0;

	//-----------------
	//count column type
	//-----------------
	for (int64_t i = 0; i<_vButtonGroup.size(); ++i) {
		if(_vButtonGroup[i]->checkedId() == static_cast<int>(QUALITATIVE)) {
			nbQualitative++;
		}
		else if (_vButtonGroup[i]->checkedId() == static_cast<int>(QUANTITATIVE)) {
			nbQuantitative++;
		}
		else if (_vButtonGroup[i]->checkedId() == static_cast<int>(WEIGHT)) {
			nbWeight++;
		}
		else if (_vButtonGroup[i]->checkedId() == static_cast<int>(NAME)) {
			nbName++;
		}
	}

	//----------
	//mixed data
	//----------
	if (nbQualitative != 0 && nbQuantitative != 0)//2 types => impossible
		return false;

	//-------------------
	//only name or weight
	//-------------------
	if (nbQualitative == 0 && nbQuantitative == 0 && ((nbName >= 1 && nbWeight >= 1) || (nbName == 0 && nbWeight >= 1) || (nbName >= 1 && nbWeight == 0)))
		return false;

	return res;
}

GUIMLabel::GUIMLabel( QWidget* parent )
	: QLabel( parent ) {

}

GUIMLabel::GUIMLabel( const QString & text, QWidget * parent, Qt::WindowFlags f): QLabel(text, parent, f) {

}

GUIMLabel::~GUIMLabel() {

}

void GUIMLabel::setId(int num) {
	_id = num;
}

void GUIMLabel::mousePressEvent(QMouseEvent* event) {
	emit(clickedOn(_id));
	QLabel::mousePressEvent(event);
}

QString ColumnTypetoString(ColumnTypeForRadioButton columnType) {
	switch (columnType) {
	case USELESS :
		return QObject::tr("Useless");
		break;
	case QUANTITATIVE :
		return QObject::tr("Quantitative");
		break;
	case QUALITATIVE :
		return QObject::tr("Qualitative");
		break;
	case WEIGHT :
		return QObject::tr("Weight");
		break;
	case NAME :
		return QObject::tr("Name");
		break;
	default :
		break;
	}
}
