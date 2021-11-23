/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphic2DQuantitative.h  description
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

#ifndef GUIMGRAPHIC2DQUANTITATIVE_H
#define GUIMGRAPHIC2DQUANTITATIVE_H

#include "GUIMGraphic.h"
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>

class GUIMGraphic2DQuantitative : public GUIMGraphic {
	Q_OBJECT

public :

	GUIMGraphic2DQuantitative(QMainWindow* , XEM::ClusteringMain * cmain);
	virtual ~GUIMGraphic2DQuantitative();

	virtual void create(int64_t indexResult);

protected :

	virtual QwtPlot * createGraphic(int64_t indexResult, int numXCoord=0, int numYCoord=1, bool displayNumberOfIndividuals=false)=0;
	virtual GUIMGraphicDockWidget * createGraphicDocWidget()=0;

	int64_t _indexResult;

protected slots :

	//void display(int64_t indexResult);
	void display();
	void variableSelectionChecked();

private :

	QBoxLayout * _layout;
	QwtPlot * _graphic;
	QVector<QCheckBox*> _checkBoxes;
	int getNbCheckedBoxes();
	QPushButton * _displayButton;
	QCheckBox * _diplayNumberCheckBox;
};

#endif // GUIMGRAPHIC2DQUANTITATIVE_H
