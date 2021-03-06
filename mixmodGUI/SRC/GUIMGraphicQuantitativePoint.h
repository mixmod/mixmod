/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicQuantitativePoint.h  description
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

#ifndef GUIMGRAPHICQUANTITATIVEPOINT_H
#define GUIMGRAPHICQUANTITATIVEPOINT_H

#include "GUIMGraphic2DQuantitative.h"

class GUIMGraphicQuantitativePoint : public GUIMGraphic2DQuantitative {
	Q_OBJECT

public :
	GUIMGraphicQuantitativePoint(QMainWindow* , XEM::ClusteringMain * cmain);
	virtual ~GUIMGraphicQuantitativePoint();

	QwtPlot* createGraphic(int64_t indexResult, int numXCoord=0, int numYCoord=1, bool displayNumberOfIndividuals=false);
	GUIMGraphicDockWidget * createGraphicDocWidget();
};

inline GUIMGraphicDockWidget* GUIMGraphicQuantitativePoint::createGraphicDocWidget() {
	return (new GUIMGraphicDockWidget( tr("Point"), getMainWindow() ));
}

#endif // GUIMGRAPHICQUANTITATIVEPOINT_H
