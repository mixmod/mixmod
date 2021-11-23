/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitParamChild.cpp  description
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
#include "mixmod_mvc/ModelItemInitParamChild.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodInsertProportion.h"
#include "mixmod_mvc/EventMixmodInsertCenter.h"
#include "mixmod_mvc/EventMixmodInsertDispersion.h"
#include "mixmod_mvc/EventMixmodDisplayInitParam.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

/*#include "GaussianParameter.h"
#include "GaussianEDDAParameter.h"*/

namespace XEM {
namespace MVC {


ModelItem<TreeInitParameterChild, int64_t>::ModelItem( Input* iInput, int64_t iPosition) {
	_input = iInput;
	_position = iPosition;
}


ModelItem<TreeInitParameterChild, int64_t> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeInitParameterChild, int64_t> ::setValue( int64_t /*position*/) {
	return NULL ;
}


Event* ModelItem<TreeInitParameterChild, int64_t> ::insertChild( int64_t position) {
	Event*  event ;
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	if (position == 0) {
		event = new EventMixmodInsertProportion(_input->getNbCluster(_position), cStrategy->getStrategyInit()->getInitParameter(_position)->getTabProportion(),position);
	}
	else if (position == 1) {
		GaussianParameter * initParam = dynamic_cast<GaussianParameter*>(cStrategy->getStrategyInit()->getInitParameter(_position));
		double ** tabMean = initParam->getTabMean();
		event = new EventMixmodInsertCenter<double>(_input->getNbCluster(_position), tabMean,_input->getPbDimension(),position);
	}
	else if (position == 2) {
		GaussianEDDAParameter * initParam = dynamic_cast<GaussianEDDAParameter *>(cStrategy->getStrategyInit()->getInitParameter(_position));
		event = new EventMixmodInsertDispersion(_input->getNbCluster(_position), initParam->getTabSigma(),_input->getPbDimension(),position);
	}

	return event;
}

Event* ModelItem<TreeInitParameterChild, int64_t> ::removeChild(int64_t /*position*/) {
	return NULL ;
}





}
}
