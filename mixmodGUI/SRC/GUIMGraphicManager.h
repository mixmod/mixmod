/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicManager.h  description
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

#ifndef GUIMGRAPHICMANAGER_H
#define GUIMGRAPHICMANAGER_H

#include <QObject>
#include <QMainWindow>

#include "qwt_plot_marker.h"
#include "qwt_text.h"
#include "qwt_plot_grid.h"
#include "qwt_symbol.h"

#include "GUIMGraphicQuantitativeClass.h"
#include "GUIMGraphicQuantitativePoint.h"
#include "GUIMGraphicQuantitativeHist.h"
#include "GUIMGraphicQualitativeDiagram.h"
#include "mixmod/Kernel/IO/Input.h"
#include "MVCRootTreeItem.h"

class GUIMGraphicManager : public QObject {
	Q_OBJECT

public :

	GUIMGraphicManager(QMainWindow* parent);
	virtual ~GUIMGraphicManager();

	void close();
	void setClusteringMain(XEM::ClusteringMain* main);
	void createAll(XEM::MVC::RootTreeItem::DataType dataType);
	void create(XEM::MVC::RootTreeItem::DataType dataType, int index, int64_t indexResult);
	const bool hasMain() const;
	const bool hasGraphics() const;
	void init();
	void deleteGraphic(int indexGraphic);
	GUIMGraphic * getGraphic(int index) {
		return _vGraphics[index];
	};

private slots:

	void deleteGraphic(GUIMGraphic *);

private :

	QVector<GUIMGraphic *> _vGraphics;
	QMainWindow* _parent;
	XEM::ClusteringMain * _cMain;
	int64_t _indexResult;

	enum QuantitativeGraphics {
	    QuantitativePoint = 0,
	    QuantitativeClass,
	    QuantitativeHistogram
	};
	enum QualitativeGraphics {
	    QualitativeDiagram = 0,
	    QualitativePointBoxes
	};
};

#endif // GUIMGRAPHICMANAGER_H
