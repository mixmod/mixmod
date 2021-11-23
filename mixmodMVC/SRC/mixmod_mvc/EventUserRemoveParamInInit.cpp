/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventUserRemoveParamInInit.cpp  description
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
#include "mixmod_mvc/EventUserRemoveParamInInit.h"
#include "mixmod_mvc/Controller.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {


EventUserRemoveParamInInit::EventUserRemoveParamInInit(int64_t position) {
	_position = position;
}


EventUserRemoveParamInInit::~EventUserRemoveParamInInit() {
}

void EventUserRemoveParamInInit::process(TreeItem * treeItem) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringStrategy*>(_controller->getModel()->getInput()->getStrategy());
	const StrategyInitName initName = cStrategy->getStrategyInit()->getStrategyInitName();
	if (initName == RANDOM || initName == CEM_INIT) {
		_controller->removeChild< int64_t >(treeItem,_position);
	}
	if (initName == SEM_MAX) {
		_controller->removeChild< int64_t >(treeItem,_position);
	}
	if (initName == SMALL_EM) {
		_controller->removeChild< int64_t >(treeItem,_position);
		_controller->removeChild< AlgoStopName >(treeItem,_position);
	}

}

std::string EventUserRemoveParamInInit::getDisplay() const {
	return string();
}

bool EventUserRemoveParamInInit::launchNewEvent() const  {
	return true ;
}
}
}
