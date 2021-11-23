/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicQualitativeDiagram.h  description
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

#ifndef GUIMGRAPHICQUALITATIVEDIAGRAM_H
#define GUIMGRAPHICQUALITATIVEDIAGRAM_H

#include "GUIMGraphic.h"
#include <QHBoxLayout>
#include "qwt_plot_curve.h"

class Diagram;

class GUIMGraphicQualitativeDiagram : public GUIMGraphic {

	Q_OBJECT

public :

	GUIMGraphicQualitativeDiagram(QMainWindow* mainWindow, XEM::ClusteringMain * cmain);
	virtual ~GUIMGraphicQualitativeDiagram();
	virtual void create(int64_t indexResult);

private :

	void createGraphic(int64_t indexResult);
	int64_t _indexResult;
	int _displayedVariable;
	QBoxLayout * _layout;
	QVBoxLayout * _settings;
	QwtPlot* _graphic;
	Diagram * _diagram;

private slots :

	void setDiagram();
	void changeVariableToDisplay(int indexVar);
};


class Diagram {

public:

	Diagram(const QString& title, const QColor& symbolColor, QwtPlot* parent);
	virtual ~Diagram();

	//void setColor(const QColor &);
	void setValues(QVector< int64_t >& sample, int64_t nbModality);

private :

	QVector<QwtPlotCurve *> _vCurve;
	QwtPlot * _parent;
	QColor _color;
};

#endif // GUIMGRAPHICQUALITATIVEDIAGRAM_H
