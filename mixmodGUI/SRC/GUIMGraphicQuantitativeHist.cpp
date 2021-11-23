/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicQuantitativeHist.cpp  description
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
#include "mixmod/Clustering/ClusteringModelOutput.h"
#include "mixmod/Matrix/Matrix.h"
#include "mixmod/Kernel/IO/Data.h"
#include "mixmod/Kernel/IO/ParameterDescription.h"

#include "GUIMGraphicQuantitativeHist.h"
#include <QListWidgetItem>
#include "qwt_plot_layout.h"
#include "qwt_legend.h"
#include "mixmod/Kernel/IO/GaussianSample.h"
#include "mixmod/Kernel/Parameter/GaussianEDDAParameter.h"
#include <algorithm>
#include <qwt_legend.h>
#ifdef QWT_6_1_X
#include <qwt_legend_label.h>
#else
#include <qwt_legend_item.h>
#endif
GUIMGraphicQuantitativeHist::GUIMGraphicQuantitativeHist(QMainWindow* mainWindow, XEM::ClusteringMain* cmain): GUIMGraphic(mainWindow, cmain) {
	xMin = 0;
	xMax = 0;
	_layout = NULL;
	_graphic = NULL;
	_histogram = NULL;
	_indexResult = 0;
}

GUIMGraphicQuantitativeHist::~GUIMGraphicQuantitativeHist() {
}

void GUIMGraphicQuantitativeHist::create(int64_t indexResult) {
	_indexResult = indexResult;
	_displayedVariable = 1;
	QWidget * wi = new QWidget();
	_layout = new QHBoxLayout();

	_settings = new QVBoxLayout();

	QLabel * labelSettings = new QLabel(tr("Choose variable histogram"));
	_settings->addWidget(labelSettings);

	//listWidget to display the variables
	QListWidget * listWidget = new QListWidget(_dock);
	listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

	int64_t nbVariables = _cMain->getInput()->getPbDimension();

	for (int64_t i = 0; i<nbVariables; ++i) {
		new QListWidgetItem( QString::number(i+1) ,listWidget);
	}
	listWidget->setCurrentRow(0);
	connect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT (changeVariableToDisplay(int)));
	_settings->addWidget(listWidget);

	//QSlider
	_slider = new QSlider(_dock);
	_slider->setMinimum(1);
	int max = 30;
	if (_cMain->getInput()->getNbSample()/5 < max) {
		max =  _cMain->getInput()->getNbSample()/5;
	}
	_slider->setMaximum(max);
	_nbClusterInHistogram = max/2;
	_slider->setValue(_nbClusterInHistogram);
	_slider->setOrientation(Qt::Horizontal);
	_settings->addWidget(_slider);

	_labelSlider = new QLabel(tr("Clusters in Histogram : ") + QString::number(_slider->value()));
	_settings->addWidget(_labelSlider);
	connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(setHistogram(int)));

	createGraphic(_indexResult);
	_layout->addLayout(_settings,1);
	_layout->insertWidget(0,_graphic,4);

	wi->setLayout(_layout);

	_dock = new GUIMGraphicDockWidget( tr("Histogram"), getMainWindow() );
	connect(_dock, SIGNAL( dockToClose()), this, SLOT( throwGraphicToDelete()));
	_dock->setWidget(wi);
	getMainWindow()->addDockWidget( Qt::BottomDockWidgetArea, _dock );
}

void GUIMGraphicQuantitativeHist::createGraphic(int64_t indexResult) {
	if (!_graphic) {
		_histogram = NULL;
		d_zoomer = NULL;
		_graphic = new QwtPlot();
		QwtPlotGrid *grid = new QwtPlotGrid();
		grid->enableX(false);
		grid->enableY(true);
		grid->enableXMin(false);
		grid->enableYMin(false);
#ifdef QWT_6_1_X        
		grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
#else
		grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));        
#endif        
		grid->attach(_graphic);

		_graphic->setCanvasBackground(QColor(Qt::gray));
		_graphic->plotLayout()->setAlignCanvasToScales(true);
		_graphic->installEventFilter(this);

		_graphic->setAxisTitle(QwtPlot::yLeft, tr("Frequencies"));
		_graphic->setAxisTitle(QwtPlot::xBottom, tr("Variable values"));

		QwtLegend *legend = new QwtLegend();
#ifdef QWT_6_1_X        
		legend->setDefaultItemMode(QwtLegendData::Checkable);
		_graphic->insertLegend(legend, QwtPlot::RightLegend);
		connect(legend, SIGNAL(checked(const QVariant&, bool, int)),this, SLOT(legendChecked(const QVariant&, bool)));
#else
		legend->setItemMode(QwtLegend::CheckableItem);        
		_graphic->insertLegend(legend, QwtPlot::RightLegend);
		connect(_graphic, SIGNAL(legendChecked(QwtPlotItem *, bool)),this, SLOT(showItem(QwtPlotItem *, bool)));        
#endif
	}

	setHistogram(_nbClusterInHistogram);

	XEM::ClusteringModelOutput * cMOutput = _cMain->getOutput()->getClusteringModelOutput(indexResult);
	int64_t nbCluster = cMOutput->getNbCluster();

	if (!_vPlotCurve.isEmpty()) {
		_vPlotCurve.clear();
	}
	for (int64_t i = 0; i<nbCluster+1; ++i) {
		traceCurve(i);
	}

	if (d_zoomer)
		delete d_zoomer;

	d_zoomer = new QwtPlotZoomer( QwtPlot::xBottom, QwtPlot::yLeft, _graphic->canvas());
	d_zoomer->setRubberBand(QwtPicker::RectRubberBand);
	d_zoomer->setRubberBandPen(QColor(Qt::green));
	d_zoomer->setTrackerMode(QwtPicker::AlwaysOn);
	d_zoomer->setTrackerPen(QColor(Qt::white));
	d_zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
	d_zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton);
}

#ifdef QWT_6_1_X
QwtLegendLabel *GUIMGraphicQuantitativeHist::getLegendLabelOfItem(QwtPlotItem *item){
  QwtLegend *lgd = qobject_cast<QwtLegend *>( _graphic->legend() );

    QList<QWidget *> legendWidgets = 
        lgd->legendWidgets( _graphic->itemToInfo( item ) );

    if ( legendWidgets.size() == 1 )
    {
        QwtLegendLabel *legendLabel =
            qobject_cast<QwtLegendLabel *>( legendWidgets[0] );
        return legendLabel;
    }
    return NULL;

}
#endif

void GUIMGraphicQuantitativeHist::setHistogram(int NbCluster) {
	if(_histogram) {
		_histogram->detach();
		delete _histogram;
	}
	_labelSlider->setText("Clusters in Histogram : " + QString::number(NbCluster));
	if(NbCluster!=_nbClusterInHistogram) {
		_nbClusterInHistogram = NbCluster;
	}
	_graphic->setTitle(tr("Histogram for the variable ") + QString::number(_displayedVariable));
	_histogram = new Histogram(tr("Histogram ")+QString::number(_displayedVariable), Qt::GlobalColor(9), this);

	XEM::Sample ** samples = const_cast<XEM::Sample**>(_cMain->getInput()->getData()->getData());
	vector< double > vSample;
	for (int64_t i = 0; i<_cMain->getInput()->getNbSample(); ++i) {
		vSample.push_back( static_cast<XEM::GaussianSample *>(samples[i])->getDataValue(_displayedVariable-1) );
	}
	xMin = *min_element(vSample.begin(), vSample.end());
	xMax = *max_element(vSample.begin(), vSample.end());

	_graphic->setAxisScale( QwtPlot::xBottom, xMin , xMax );
	static_cast<Histogram *>( _histogram)->setValues(vSample, _slider->value());
	_histogram->attach(_graphic);

	_graphic->replot();
#ifdef QWT_6_1_X
	QwtLegendLabel *legendLabel = getLegendLabelOfItem(_histogram);    
	if ( legendLabel )
		legendLabel->setChecked(true);
#else
	QwtLegendItem *legendItem = static_cast<QwtLegendItem *>(_graphic->legend()->find(_histogram));
	if ( legendItem )
		legendItem->setChecked(true);    
#endif    
	_graphic->setAutoReplot(true);
}

void GUIMGraphicQuantitativeHist::traceCurve(int64_t indexNbCluster) {
	double variance = 1;
	double mean = 0;
	double value=xMin;
	double proportion = 0;
	double h = (xMax-xMin)/1000;

	QVector<double> xDat;
	QVector<double> yDat;
	QwtPlotCurve *curve = NULL;

	if (_cMain->getOutput()->getClusteringModelOutput(_indexResult)->getNbCluster()!=indexNbCluster) {
		XEM::GaussianEDDAParameter * param = static_cast<XEM::GaussianEDDAParameter *>(_cMain->getOutput()->getClusteringModelOutput(_indexResult)->getParameterDescription()->getParameter());
		curve = new QwtPlotCurve(tr("Component ") + QString::number(indexNbCluster + 1) );
		mean = param->getTabMean()[indexNbCluster][_displayedVariable-1];
		variance = param->getTabSigma()[indexNbCluster]->storeToArray()[_displayedVariable-1][_displayedVariable-1];
		proportion = param->getTabProportion()[indexNbCluster];
		int64_t nbSample = _cMain->getInput()->getNbSample();
		while(value<(xMax+h)) {
			xDat.push_back(value);
			double denominator = sqrt(2*M_PI*variance);
			double numerator = proportion*nbSample*exp(-((value-mean)*(value-mean)/(variance*2)));
			yDat.push_back(numerator/denominator);
			value = value + h;
		}
		int color = indexNbCluster+7;
		if (color>=9)
			color++;

		curve->setPen(QPen(Qt::GlobalColor(color)));
		curve->setSamples(xDat, yDat);
		curve->setRenderHint(QwtPlotItem::RenderAntialiased);
		curve->attach(_graphic);
		_vPlotCurve.push_back(curve);

	}
	else {//sum of gaussian
		curve = new QwtPlotCurve(tr("Mixture"));
		double sumY = 0;
		for (int64_t j = 0; j<_vPlotCurve[0]->dataSize(); ++j) {
			sumY = _vPlotCurve[0]->sample(j).y();
			for (int64_t i=1; i<_vPlotCurve.size(); ++i) {
				sumY = sumY + _vPlotCurve[i]->sample(j).y();
			}
			xDat.push_back(_vPlotCurve[0]->sample(j).x());
			yDat.push_back(sumY);
		}
		curve->setPen(QPen(Qt::GlobalColor(2)));
		curve->setSamples(xDat, yDat);
		curve->setRenderHint(QwtPlotItem::RenderAntialiased);
		curve->attach(_graphic);
		_vPlotCurve.push_back(curve);
	}
#ifdef QWT_6_1_X
    QwtLegendLabel *legendLabel = getLegendLabelOfItem(_vPlotCurve.last());    
	if ( legendLabel ) {
		legendLabel->setVisible(true);
		legendLabel->setChecked(true);
	}    
#else
	QwtLegendItem *legendItem = static_cast<QwtLegendItem *>(_graphic->legend()->find(_vPlotCurve.last()));
	if ( legendItem ) {
		legendItem->setVisible(true);
		legendItem->setChecked(true);
	}
#endif    
	_graphic->replot();
}

#ifdef QWT_6_1_X
void GUIMGraphicQuantitativeHist::legendChecked(const QVariant& itemInfo, bool value)
{
    QwtPlotItem *item = _graphic->infoToItem(itemInfo);
    if (item)
        showItem(item, value);
}
#endif

void GUIMGraphicQuantitativeHist::showItem(QwtPlotItem* item, bool on) {
	item->setVisible(on);
	_graphic->replot();
}


void GUIMGraphicQuantitativeHist::changeVariableToDisplay(int indexVar) {
	_displayedVariable = indexVar+1;
	_graphic->detachItems();
	delete _graphic;
	_graphic = NULL;
	createGraphic(_indexResult);
	_layout->insertWidget(0,_graphic,4);
}

bool GUIMGraphicQuantitativeHist::eventFilter(QObject* obj, QEvent* event) {
	if (obj == _graphic) {
		if(event->type() == QEvent::MouseButtonPress) {
			QMouseEvent * mouseEvent = static_cast<QMouseEvent *>(event);
			if (mouseEvent->button() == Qt::RightButton) {
				_graphic->setAxisScale( QwtPlot::xBottom, xMin , xMax );
				_graphic->setAxisAutoScale(QwtPlot::yLeft);
				d_zoomer->setZoomBase();

			}
		}
	}

	return QObject::eventFilter(obj, event);
}


Histogram::Histogram(const QString &title, const QColor &symbolColor, GUIMGraphicQuantitativeHist * parent):
	QwtPlotHistogram(title) {
	setStyle(QwtPlotHistogram::Columns);
	_parent = parent;
	setColor(symbolColor);
}

void Histogram::setColor(const QColor &symbolColor) {
	QColor color = symbolColor;
	color.setAlpha(160);

	setPen(QPen(Qt::black));
	setBrush(QBrush(color));

	QwtColumnSymbol *symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
	symbol->setFrameStyle(QwtColumnSymbol::Raised);
	symbol->setLineWidth(2);
	symbol->setPalette(QPalette(color));
	setSymbol(symbol);
}

void Histogram::setValues(std::vector< double > sample, int nbInterval) {
	double h = (_parent->getxMax()-_parent->getxMin())/(nbInterval);//interval
	double Min = _parent->getxMin();
	//creation of intervals
	QVector<QwtInterval> vInterval(nbInterval);
	for ( uint i = 0; i < nbInterval; i++ ) { //put ionterval instaead ofnbSamples
		QwtInterval interval(Min, Min + h);
		interval.setBorderFlags(QwtInterval::ExcludeMaximum);
		vInterval[i] = interval;
		Min = Min+h;
	}

	//frequences in intervall
	QVector<int> nbSamplesByInterval(nbInterval, 0);
	int nbSamplesInEachInterval = 0;

	//number of sample by interval
	for (int64_t i = 0; i<sample.size(); ++i) {
		for (int64_t j = 0; j<nbInterval; ++j) {
			if ( vInterval[j].contains(sample[i])) {
				nbSamplesByInterval[j]++;
				j=nbInterval;
			}
		}
	}

	//filling of histogram
	QVector<QwtIntervalSample> vsamples(nbInterval);
	for ( uint i = 0; i < nbInterval; i++ ) {
		vsamples[i] = QwtIntervalSample(nbSamplesByInterval[i], vInterval[i]);
	}
	setData(new QwtIntervalSeriesData(vsamples));
}
