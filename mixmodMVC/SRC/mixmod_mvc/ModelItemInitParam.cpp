/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitParam.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2013
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
#include "mixmod_mvc/ModelItemInitParam.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodInsertInitParamChild.h"
#include "mixmod_mvc/EventMixmodInsertInitParamBinary.h"
#include "mixmod_mvc/EventMixmodInsertInitParamHD.h"
#include "mixmod_mvc/EventMixmodDisplayInitParam.h"
#include "mixmod_mvc/Util.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Kernel/Model/ModelType.h"

namespace XEM {
namespace MVC {

//#include "GaussianParameter.h"

ModelItem<TreeInitParameter, string>::ModelItem( Input* iInput, string iFilename) {
	_filename = iFilename;
	_input = iInput;
}


ModelItem<TreeInitParameter, string> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeInitParameter, string> ::setValue( int64_t position) {


	if (_filename.compare("") != 0) {
		ifstream partitionFile(_filename.c_str(), ios::in);
		if (! partitionFile.is_open()) {
			throw wrongParamFileName;
		}
		else {
			ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
			cStrategy->setInitParam(_filename, position);
			Event* event;
			ModelType * modelType = _input->getModelType()[0];
			if (isBinary(modelType->getModelName()) ) {
				event = new EventMixmodInsertInitParamBinary(_filename,_input->getNbCluster(position), _input->getPbDimension(),position);
			}
			else if (isHD(modelType->getModelName())) {
				event = new EventMixmodInsertInitParamHD(_filename,_input->getNbCluster(position), _input->getPbDimension(),position);
			}
			else if ( (!isBinary(modelType->getModelName())) && (!isHD(modelType->getModelName())) ) {
				event = new EventMixmodInsertInitParamChild(_filename, _input->getNbCluster(position), _input->getPbDimension(),position);
			}
			return event;
		}
	}
	else {
		throw wrongParamFileName;
	}

}


Event* ModelItem<TreeInitParameter, string> ::insertChild( int64_t /*position*/) {
	Event* event = new EventMixmodDisplayInitParam( _filename );

	return event;
}

Event* ModelItem<TreeInitParameter, string> ::removeChild(int64_t /*position*/) {
	return new NoEvent();
}





}
}
