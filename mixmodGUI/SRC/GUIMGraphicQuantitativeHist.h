/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicQuantitativeHist.h  description
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

#ifndef GUIMGRAPHICQUANTITATIVEHIST_H
#define GUIMGRAPHICQUANTITATIVEHIST_H

#include "GUIMGraphic.h"
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include "qwt_plot_histogram.h"
#include "qwt_plot_curve.h"
#ifdef QWT_6_1_X
#include <qwt_legend_label.h>
#endif

class GUIMGraphicQuantitativeHist : public GUIMGraphic {
	Q_OBJECT

public :

	GUIMGraphicQuantitativeHist(QMainWindow* mainWindow, XEM::ClusteringMain * cmain);
	virtual ~GUIMGraphicQuantitativeHist();
	virtual void create(int64_t indexResult);
	double getxMin() {
		return xMin;
	};
	double getxMax() {
		return xMax;
	};

private :

	void createGraphic(int64_t indexResult);

	QBoxLayout * _layout;
	QVBoxLayout * _settings;
	QwtPlot* _graphic;
	QSlider * _slider;
	int64_t _nbClusterInHistogram;
	QLabel * _labelSlider;
	int64_t _displayedVariable;
	QwtPlotHistogram* _histogram;
	QVector<QwtPlotCurve *> _vPlotCurve;
	double xMin,xMax;
	int64_t _indexResult;

private slots :
#ifdef QWT_6_1_X  
    QwtLegendLabel *getLegendLabelOfItem(QwtPlotItem *item);
    void legendChecked(const QVariant& itemInfo, bool value);
#endif
	void setHistogram(int NbCluster);
	void changeVariableToDisplay(int indexVar);
	void traceCurve(int64_t indexVar);
	void showItem(QwtPlotItem* item, bool on);

protected:

	bool eventFilter(QObject* obj, QEvent* event);
};

class Histogram: public QwtPlotHistogram {
public:
	Histogram(const QString& title, const QColor& symbolColor, GUIMGraphicQuantitativeHist* parent);

	void setColor(const QColor &);
	void setValues(vector< double > sample, int nbIterval);

private :
	GUIMGraphicQuantitativeHist * _parent;
};

#endif // GUIMGRAPHICQUANTITATIVEHIST_H
