/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventUserSetStopRuleInit.cpp  description
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
#include "mixmod_mvc/EventUserSetStopRuleInit.h"
#include "mixmod_mvc/Controller.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {




EventUserSetStopRuleInit::EventUserSetStopRuleInit(AlgoStopName iStopName) {
	_stopName = iStopName;
}

EventUserSetStopRuleInit::~EventUserSetStopRuleInit() {
}

std::string EventUserSetStopRuleInit::getDisplay() const {
	return string();
}

bool EventUserSetStopRuleInit::launchNewEvent() const {
	return true;
}

void EventUserSetStopRuleInit::process(TreeItem * treeItem) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringStrategy*>(_controller->getModel()->getInput()->getStrategy());
	AlgoStopName oldName = cStrategy->getStopNameInInit();
	int64_t nbIterationInit = cStrategy->getNbIterationInInit();
	double epsilonInit = cStrategy->getEpsilonInInit();
	_controller->setValue(treeItem,_stopName);
	if (_stopName != oldName) {
		if (_stopName==NBITERATION && oldName == NBITERATION_EPSILON) {
			_controller->removeChild< double >(treeItem,1);
		}
		if (_stopName==EPSILON && oldName == NBITERATION_EPSILON) {
			_controller->removeChild< int64_t >(treeItem,0);
		}
		if (_stopName==NBITERATION_EPSILON && oldName == NBITERATION) {
			_controller->insertChild(treeItem,1,epsilonInit);
		}
		if (_stopName==EPSILON && oldName == NBITERATION) {
			_controller->insertChild(treeItem,1,epsilonInit);
			_controller->removeChild< int64_t >(treeItem,0);
		}
		if (_stopName==NBITERATION_EPSILON && oldName == EPSILON) {
			_controller->insertChild(treeItem,0,nbIterationInit);
		}
		if (_stopName==NBITERATION && oldName == EPSILON) {
			_controller->insertChild(treeItem,0,nbIterationInit);
			_controller->removeChild< double >(treeItem,1);
		}
	}
}

TreeKeyword EventUserSetStopRuleInit::getKeyword() const {
	return TreeInitStopRule;
}




}
}
