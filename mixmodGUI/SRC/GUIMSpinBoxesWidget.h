/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMSpinBoxesWidget.h  description
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
#ifndef __GUIM_SPIN_BOXES_WIDGET_H__
#define __GUIM_SPIN_BOXES_WIDGET_H__

#include <QWidget>
#include <QScrollArea>
#include <QWizardPage>
#include <QGridLayout>
#include <QSpinBox>

class GUIMProjectCreator ;

class SpinBoxesWidget : public QWidget {
	Q_OBJECT

public :

	SpinBoxesWidget( QWidget* = 0, Qt::WindowFlags = 0 );
	virtual ~SpinBoxesWidget();

	virtual QSize sizeHint() const ;

	int getNbSpinBox() const {
		return vSpinBox.size() ;
	}
	int getSpinBoxValue( int i ) const {
		return vSpinBox[i]->value() ;
	}
	//QVector getSpinValue() const {return vSpinBox;}
	void move (int nb);

public slots :

	void updateTab(int);

private :

	QVector<QSpinBox*> vSpinBox ;
	QGridLayout* grid ;

	static const int FIRST_SPACE_H = 10 ;
	static const int FIRST_SPACE_V = 5 ;
	static const int LAST_SPACE_H = 20 ;
	static const int LAST_SPACE_V = 15 ;
	static const int SPACE_BETWEEN = 5 ;
	static const int SPIN_BOX_WIDTH = 50 ;
	static const int SPIN_BOX_HEIGHT = 35 ;
};
#endif