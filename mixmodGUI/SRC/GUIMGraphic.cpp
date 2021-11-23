/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphic.cpp  description
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
#include "GUIMGraphic.h"
#include "mixmod/Kernel/IO/Data.h"
#include "mixmod/Kernel/IO/GaussianSample.h"
#include "mixmod/Clustering/ClusteringOutput.h"
#include "mixmod/Clustering/ClusteringInput.h"
#include <qcoreevent.h>

GUIMGraphic::GUIMGraphic( QMainWindow*parent, XEM::ClusteringMain* cmain ):QObject(parent), _cMain(cmain), _dock(NULL) {
	d_zoomer = NULL;
}

GUIMGraphic::~GUIMGraphic() {
	// do not delete input & output
	close();
}

void GUIMGraphic::close() {
	if (_dock) {
		//disconnet puis close au lieuy de delete?
		delete _dock;
		_dock = NULL;
	}
}

QwtPointArrayData GUIMGraphic::addValues( int nbEle, int nbDim, int numXCoord, int numYCoord ) {
	if( nbDim <= numXCoord || nbDim <= numYCoord )
		throw ;

	QVector<double> x;
	QVector<double> y;

	const XEM::Data* data = _cMain->getInput()->getData();

	const double* weights = data->getWeight();
	const XEM::GaussianSample** samples = (const XEM::GaussianSample**) data->getData();

	for( int i = 0 ; i < nbEle ; ++i ) {
		for( int j = 0 ; j < weights[i] ; ++j ) {

			x.push_back(samples[i]->getDataValue(numXCoord));
			y.push_back(samples[i]->getDataValue(numYCoord));

		}
	}
	QwtPointArrayData coords(x,y);

#ifdef GUIM_DEBUG_MODE
	for( int i = 0 ; i < coords.size() ; ++i )
		cout << " (" << coords.xData()[i] << '\t' << coords.yData()[i] << ") " ;
	cout << endl ;
#endif
	return coords;
}

void GUIMGraphic::throwGraphicToDelete() {
	emit(graphicToDelete(this));
}
