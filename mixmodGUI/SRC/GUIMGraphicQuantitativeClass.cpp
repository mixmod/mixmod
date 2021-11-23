/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicQuantitativeClass.cpp  description
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
#include "mixmod/Kernel/IO/LabelDescription.h"
#include "mixmod/Kernel/IO/Label.h"
#include "GUIMGraphicQuantitativeClass.h"

GUIMGraphicQuantitativeClass::GUIMGraphicQuantitativeClass(QMainWindow* mainWindow, XEM::ClusteringMain* cmain):GUIMGraphic2DQuantitative(mainWindow, cmain) {
}

GUIMGraphicQuantitativeClass::~GUIMGraphicQuantitativeClass() {
}

QwtPlot * GUIMGraphicQuantitativeClass::createGraphic(int64_t indexResult, int numXCoord, int numYCoord, bool displayNumberOfIndividuals) {
	int   nbElement = _cMain->getInput()->getNbSample();
	int nbDimension = _cMain->getInput()->getPbDimension();
	// fill colors & labels
	// labels

	XEM::ClusteringModelOutput * cMOutput = _cMain->getOutput()->getClusteringModelOutput(indexResult);
	int64_t * labels = cMOutput->getLabelDescription()->getLabel()->getTabLabel() ;

	// colors
	int colorsSize = cMOutput->getNbCluster() ;
	QVector<Qt::GlobalColor> colors ;
	colors.reserve( colorsSize );
	int color;
	for( int i = 0 ; i < colorsSize ; ++i ) {
		color = i+7;
		if (color>=9)
			color++;
		colors.push_back( Qt::GlobalColor(color) );
	}
	// end fill colors & labels
	QwtPlot* myPlot = new QwtPlot( QwtText("Point Class") );
	myPlot->setCanvasBackground(QColor(Qt::white));

	QwtPlotGrid*  myGrid = new QwtPlotGrid();
	// can we see the grid ?
	myGrid->enableXMin( true );
	myGrid->enableYMin( true );
	// draw the grid (see exec)
#ifdef QWT_6_1_X
	myGrid->setMajorPen( QPen(Qt::black, 0, Qt::DotLine) );
	myGrid->setMinorPen( QPen(Qt::gray, 0 , Qt::DotLine) );
#else
	myGrid->setMajPen( QPen(Qt::black, 0, Qt::DotLine) );
	myGrid->setMinPen( QPen(Qt::gray, 0 , Qt::DotLine) );
#endif
	// fill coords tab
	QwtPointArrayData coords = addValues( nbElement, nbDimension, numXCoord, numYCoord );

	double xMin = std::numeric_limits<double>::max() ,
	       xMax = std::numeric_limits<double>::min() ,
	       yMin = std::numeric_limits<double>::max() ,
	       yMax = std::numeric_limits<double>::min() ;

	for( int i = 0 ; i < coords.size() ; ++i ) {
		// set marker : symbol (QwtSymbol), color (QBrush & QPen), size (QSize)
		QwtPlotMarker*  mark = NULL ;
		mark = new QwtPlotMarker();

		QwtSymbol * qwtSymbol = new QwtSymbol( QwtSymbol::XCross, QBrush( colors[ labels[i] - 1 ] ), // same label = same color
		                                       QPen( colors[ labels[i] - 1 ], // same label = same color
		                                               2,Qt::SolidLine), QSize(10,10) );
		mark->setSymbol( qwtSymbol);

		//set Marker Label : number of individual
		QwtText text(QString::number(i+1));
		text.setColor(colors[labels[i]-1]);
		if (displayNumberOfIndividuals) {
			mark->setLabelAlignment( Qt::AlignTop );
			mark->setLabel(text);
		}
		double x = coords.xData()[i];
		double y = coords.yData()[i] ;

		// define the box of the chart
		if( xMin > x ) xMin = x ;
		if( xMax < x ) xMax = x ;
		if( yMin > y ) yMin = y ;
		if( yMax < y ) yMax = y ;

		mark->setValue( x, y );

		mark->attach( myPlot );
	}
#ifdef GUIM_DEBUG_MODE
	cout << xMin << '\t' << xMax << '\t' << yMin << '\t' << yMax << endl ;
#endif
	myGrid->attach( myPlot );

	myPlot->setAxisScale( QwtPlot::yLeft, yMin - 0.1, yMax + 0.1 );
	myPlot->setAxisScale( QwtPlot::xBottom, xMin - 0.1, xMax + 0.1 );

	d_zoomer = new QwtPlotZoomer( QwtPlot::xBottom, QwtPlot::yLeft, myPlot->canvas());
	d_zoomer->setRubberBand(QwtPicker::RectRubberBand);
	d_zoomer->setRubberBandPen(QColor(Qt::green));
	d_zoomer->setTrackerMode(QwtPicker::AlwaysOn);
	d_zoomer->setTrackerPen(QColor(Qt::white));
	d_zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
	d_zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton);

	return myPlot ;
}
