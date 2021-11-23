/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicQualitativeDiagram.cpp  description
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

#include "GUIMGraphicQualitativeDiagram.h"
#include <QLabel>
#include <QListWidget>
//#include "qwt_legend_item.h"
#include <qwt_plot_layout.h>
#include "mixmod/Kernel/IO/BinarySample.h"
#include "mixmod/Kernel/IO/BinaryData.h"

GUIMGraphicQualitativeDiagram::GUIMGraphicQualitativeDiagram(QMainWindow* mainWindow, XEM::ClusteringMain* cmain): GUIMGraphic(mainWindow, cmain) {
	_layout = NULL;
	_graphic = NULL;
	_diagram = NULL;
	_indexResult = 0;
	_diagram = NULL;
}

GUIMGraphicQualitativeDiagram::~GUIMGraphicQualitativeDiagram() {
	if (_diagram) {
		delete _diagram;
	}
}

void GUIMGraphicQualitativeDiagram::create(int64_t indexResult) {
	_indexResult = indexResult;
	_displayedVariable = 1;
	QWidget * wi = new QWidget();
	_layout = new QHBoxLayout();

	_settings = new QVBoxLayout();
	QLabel * labelSettings = new QLabel(tr("Choose variable diagram"));
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


	createGraphic(_indexResult);
	_layout->addWidget(_graphic,4);
	_layout->addLayout(_settings,1);

	wi->setLayout(_layout);

	_dock = new GUIMGraphicDockWidget( tr("Diagram"), getMainWindow() );
	connect(_dock, SIGNAL( dockToClose()), this, SLOT( throwGraphicToDelete()));
	_dock->setWidget(wi);
	getMainWindow()->addDockWidget( Qt::BottomDockWidgetArea, _dock );
}

void GUIMGraphicQualitativeDiagram::createGraphic(int64_t indexResult) {
	if (!_graphic) {
		_graphic = new QwtPlot();


		_graphic->setCanvasBackground(QColor(Qt::lightGray));
		_graphic->plotLayout()->setAlignCanvasToScales(true);
		_graphic->installEventFilter(this);

		_graphic->setAxisTitle(QwtPlot::yLeft, tr("Frequencies"));
		_graphic->setAxisTitle(QwtPlot::xBottom, tr("Variable values"));
	}

	setDiagram();

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

void GUIMGraphicQualitativeDiagram::setDiagram() {
	if(_diagram) {
		delete _diagram;
		_graphic->detachItems();
	}

	_graphic->setTitle(tr("Diagram for the variable ") + QString::number(_displayedVariable));
	_diagram = new Diagram(tr("Diagram ")+QString::number(_displayedVariable), Qt::GlobalColor(6+_displayedVariable), _graphic);

	XEM::Sample ** samples = const_cast<XEM::Sample**>(_cMain->getInput()->getData()->getData());
	QVector< int64_t > vSample;
	int64_t nbModality = static_cast<const XEM::BinaryData* >( _cMain->getInput()->getData() )->getTabNbModality()[_displayedVariable-1];
	for (int64_t i = 0; i<_cMain->getInput()->getNbSample(); ++i) {
		vSample.push_back( static_cast<XEM::BinarySample *>(samples[i])->getDataValue(_displayedVariable-1));
	}
	_graphic->setAxisScale( QwtPlot::xBottom, 0, nbModality + 1 );
	_graphic->setAxisAutoScale( QwtPlot::yLeft );
	static_cast<Diagram *>( _diagram)->setValues(vSample, nbModality);

	_graphic->replot();

	_graphic->setAutoReplot(true);
}

void GUIMGraphicQualitativeDiagram::changeVariableToDisplay(int indexVar) {
	_displayedVariable = indexVar+1;
	createGraphic(_indexResult);
}


Diagram::Diagram(const QString& title, const QColor& symbolColor, QwtPlot* parent) {
	_parent = parent;
	_color = symbolColor;
}

Diagram::~Diagram() {
}

void Diagram::setValues(QVector< int64_t > &sample, int64_t nbModality) {
	if (!_vCurve.isEmpty()) {
		_vCurve.clear();
	}

	QVector<int> occurences(nbModality);
	for (int64_t i = 0; i<nbModality; i++) {
		int occ = sample.count(i+1);
		occurences[i] = occ;
	}

	for (int64_t i = 0; i<nbModality; ++i) {
		QVector<double> xDat(2, i+1);
		QVector<double> yDat(2);
		QwtPlotCurve *curve = new QwtPlotCurve(QObject::tr("Curve ") + QString::number(i + 1) );

		yDat[0] = 0;
		yDat[1] = occurences[i];

		curve->setSamples(xDat, yDat);
		curve->setPen(QPen(_color));
		curve->setRenderHint(QwtPlotItem::RenderAntialiased);
		curve->attach(_parent);

		QPen pen = curve->pen();
		pen.setWidth(5);
		curve->setPen(pen);

		QwtPlotMarker* 	mark = new QwtPlotMarker();
		mark->setValue(xDat[1], yDat[1]);
		mark->setLabel(QString::number(yDat[1]));
		mark->setLabelAlignment( Qt::AlignTop );
		mark->attach(_parent);

		_vCurve.push_back(curve);
	}
}
