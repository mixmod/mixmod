/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphic2DQuantitative.cpp  description
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
#include "mixmod/Clustering/ClusteringInput.h"

#include "GUIMGraphic2DQuantitative.h"
#include <QButtonGroup>
#include <QLabel>

GUIMGraphic2DQuantitative::GUIMGraphic2DQuantitative(QMainWindow* mainWindow, XEM::ClusteringMain* cmain):GUIMGraphic(mainWindow, cmain) {
	_layout = new QHBoxLayout();
	_graphic = NULL;
	_displayButton = new QPushButton(tr("Display"));
	_diplayNumberCheckBox = new QCheckBox(tr("Display number of individuals"));
	_diplayNumberCheckBox->setCheckState(Qt::Unchecked);
	_indexResult = 0;
}

GUIMGraphic2DQuantitative::~GUIMGraphic2DQuantitative() {
}


//-------
// create
//-------
void GUIMGraphic2DQuantitative::create(int64_t indexResult) {
	_indexResult = indexResult;
	QWidget * wi = new QWidget();

	QWidget * settingsWidget = new QWidget();
	// Settings layout
	//----------------
	QVBoxLayout * settingsLayout = new QVBoxLayout();
	settingsWidget->setLayout(settingsLayout);

	// Display or not number of individuals
	settingsLayout->addWidget(_diplayNumberCheckBox);
	connect(_diplayNumberCheckBox, SIGNAL(toggled(bool)), this, SLOT(display()));

	// séparateur
	settingsLayout->addSpacing(5);
	QFrame * line = new QFrame();
	line->setFrameShape(QFrame::HLine);
// line->setFrameShadow(QFrame::Sunken);
	settingsLayout->addWidget(line);

	// Variable selection
	//-------------------
	QLabel * labelSettings = new QLabel(tr("Choose variables"));
	settingsLayout->addWidget(labelSettings);

	//display the variables

	int64_t nbVariables = _cMain->getInput()->getPbDimension();

	for (int64_t i = 0; i<nbVariables; ++i) {
		QCheckBox * cBox = new QCheckBox(QString::number(i+1));
		_checkBoxes.append(cBox);
		connect(_checkBoxes[i], SIGNAL(toggled(bool)), this, SLOT(variableSelectionChecked()));

		settingsLayout->addWidget(cBox,Qt::AlignTop);
		if (i==0 || i==1) {
			cBox->setCheckState(Qt::Checked);
		}
		else {
			cBox->setCheckState(Qt::Unchecked);
		}
	}
	_displayButton->setShortcut(Qt::Key_Return);
	connect( _displayButton, SIGNAL( released() ), this , SLOT( display()));
	settingsLayout->addWidget(_displayButton);
	_layout->insertWidget(1,settingsWidget,1);

	//Graphic
	//-------
	_graphic = createGraphic(_indexResult);
	_dock = createGraphicDocWidget();
	connect(_dock, SIGNAL( dockToClose()), this, SLOT( throwGraphicToDelete()));
	//_dock->setWidget(_graphic );
	_layout->insertWidget(0,_graphic,10);

	wi->setLayout(_layout);

	connect(_dock, SIGNAL( dockToClose()), this, SLOT( throwGraphicToDelete()));
	_dock->setWidget(wi);
	getMainWindow()->addDockWidget( Qt::RightDockWidgetArea, _dock );
}


//--------
// Display
//--------
void GUIMGraphic2DQuantitative::display() {

	int numXCoord = 0;
	int numYCoord = 1;
	int count=0;
	int i=0;
	for( QVector<QCheckBox*>::iterator it = _checkBoxes.begin() ; it != _checkBoxes.end() ; ++it ) {
		if ((*it)->isChecked()) {
			if (count==0) {
				numXCoord = i;
			}
			else {
				numYCoord = i;
			}
			count++;
		}
		i++;
	}

	_graphic->detachItems();
	delete _graphic;
	_graphic =  createGraphic(_indexResult, numXCoord, numYCoord, _diplayNumberCheckBox->isChecked());
	_layout->insertWidget(0,_graphic,4);
}

int GUIMGraphic2DQuantitative::getNbCheckedBoxes() {
	int count=0;
	for( QVector<QCheckBox*>::iterator it = _checkBoxes.begin() ; it != _checkBoxes.end() ; ++it ) {
		if ((*it)->isChecked()) {
			count++;
		}
	}
	return count;
}


//----------------
// checkBoxChecked
//----------------
void GUIMGraphic2DQuantitative::variableSelectionChecked() {
	if (getNbCheckedBoxes()==2) {
		_displayButton->setEnabled(true);
	}
	else {
		_displayButton->setEnabled(false);
	}
}
