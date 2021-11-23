/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMSpinBoxesWidget.cpp  description
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
#include "GUIMSpinBoxesWidget.h"
#include <sstream>

#include <QFileInfo>
#include <QRadioButton>
#include <QPushButton>
#include <QFileDialog>
#include <QScrollBar>

SpinBoxesWidget::SpinBoxesWidget( QWidget* parent, Qt::WindowFlags flags )
	: QWidget(parent, flags) {
	grid = new QGridLayout(this);
}

SpinBoxesWidget::~SpinBoxesWidget() {
	if (grid) {
		delete grid;
		grid = NULL;
	}
}

void SpinBoxesWidget::updateTab( int nb ) {
	// clear all Spin Boxes
	qDeleteAll( vSpinBox );
	vSpinBox.clear();

	// calculate the number of Spin Box in 1 line thanks to the current size of the QScrollArea
	float d = parentWidget()->width() + (FIRST_SPACE_H - LAST_SPACE_H) ;
	float q = SPIN_BOX_WIDTH + SPACE_BETWEEN ;
	float f = d/q ;
	int nbSbPerLine = f ;

	// it is this number
	nbSbPerLine = nbSbPerLine?nbSbPerLine:1 ;

	// put the Spin Boxes on the good position
	for( int i = 0 ; i < nb ; ++i ) {
		int q = i/nbSbPerLine ;
		QSpinBox* tmp = new QSpinBox( this ) ;
		tmp->setFixedSize( SPIN_BOX_WIDTH, SPIN_BOX_HEIGHT );
		tmp->move( FIRST_SPACE_H + (i%nbSbPerLine)*(SPIN_BOX_WIDTH + SPACE_BETWEEN),
		           FIRST_SPACE_V + q*(SPIN_BOX_HEIGHT + SPACE_BETWEEN)
		         );
		tmp->setRange( 1, 150 );
		tmp->setValue( i + 2 );

		vSpinBox.push_back(tmp);
	}
	adjustSize();
}

void SpinBoxesWidget::move( int nb ) {
	float d = parentWidget()->width() + (FIRST_SPACE_H - LAST_SPACE_H) ;
	float q = SPIN_BOX_WIDTH + SPACE_BETWEEN ;
	float f = d/q ;
	int nbSbPerLine = f ;

	// it is this number
	nbSbPerLine = nbSbPerLine?nbSbPerLine:1 ;
	for( int i = 0 ; i < nb ; ++i ) {
		int q = i/nbSbPerLine ;
		vSpinBox[i]->move( FIRST_SPACE_H + (i%nbSbPerLine)*(SPIN_BOX_WIDTH + SPACE_BETWEEN),
		                   FIRST_SPACE_V + q*(SPIN_BOX_HEIGHT + SPACE_BETWEEN)
		                 );
	}
	adjustSize();
}

QSize SpinBoxesWidget::sizeHint() const {
	return childrenRect().size() + QSize( FIRST_SPACE_H, FIRST_SPACE_V );
}
