/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventUserInsertParamInInit.cpp  description
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
#include "mixmod_mvc/EventUserInsertParamInInit.h"
#include "mixmod_mvc/Controller.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {



EventUserInsertParamInInit::EventUserInsertParamInInit(int64_t iPosition) {
	_position = iPosition;
}

EventUserInsertParamInInit::~EventUserInsertParamInInit() {
}

std::string EventUserInsertParamInInit::getDisplay() const {
	return string();
}

bool EventUserInsertParamInInit::launchNewEvent() const {
	return true;
}

void EventUserInsertParamInInit::process(TreeItem * treeItem) {
	const StrategyInitName initName = dynamic_cast<ClusteringStrategy*>(_controller->getModel()->getInput()->getStrategy())->getStrategyInit()->getStrategyInitName();
	if (initName == RANDOM) {
		_controller->insertChild(treeItem, View::NB_TRY_INIT_RANDOM, _position);
	}
	if (initName == CEM_INIT) {
		_controller->insertChild(treeItem, View::NB_TRY_INIT_CEM, _position);
	}
	if (initName == SEM_MAX) {
		_controller->insertChild(treeItem, View::NB_ITERATION_SEM_MAX, _position);
	}
	if (initName == SMALL_EM) {
		_controller->insertChild(treeItem, View::NB_TRY_INIT_SMALL_EM, _position);
		_controller->insertChild(treeItem, View::STOP_RULE_SMALL_EM, ++_position);
	}
}



TreeKeyword EventUserInsertParamInInit::getKeyword() const {
	return TreeInitType;
}
}
}
