/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphic.h  description
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
#ifndef __GUIM_GRAPHIC_H__
#define __GUIM_GRAPHIC_H__

#include <QObject>
#include <QMainWindow>
#include <limits>
#include <cmath>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_text.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#ifdef QWT_6_1_X
#include <qwt_point_data.h>
#else
#include <qwt_series_data.h>
#endif
#include "mixmod/Kernel/IO/Input.h"
#include "mixmod/Clustering/ClusteringMain.h"
#include "mixmod/Clustering/ClusteringOutput.h"
#include "GUIMGraphicDockWidget.h"
#include "qwt_plot_zoomer.h"

class GUIMGraphic : public QObject {
	Q_OBJECT

public :

	GUIMGraphic( QMainWindow* parent, XEM::ClusteringMain * cmain);
	~GUIMGraphic();

	void setClusteringMain(XEM::ClusteringMain * cMain);

	QMainWindow* getMainWindow() const {
		return qobject_cast<QMainWindow*>( parent() );
	}
	void close();
	GUIMGraphicDockWidget* getDock() {
		return _dock;
	};

	virtual void create(int64_t indexResult) = 0;

signals :

	void graphicToDelete(GUIMGraphic *);

protected :

	virtual QwtPointArrayData addValues( int nbEle, int nbDim, int numXCoord, int numYCoord );

	XEM::ClusteringMain * _cMain;
	GUIMGraphicDockWidget* _dock;
	QwtPlotZoomer * d_zoomer;

protected slots:

	void throwGraphicToDelete();
};

inline void GUIMGraphic::setClusteringMain(XEM::ClusteringMain* cMain) {
	_cMain = cMain;
}

#endif // __GUIM_GRAPHIC_H__
