/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodSetStopRuleValue.cpp  description
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
#include "mixmod_mvc/EventMixmodSetStopRuleValue.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {




EventMixmodSetStopRuleValue::EventMixmodSetStopRuleValue(AlgoStopName iStopName, double iEpsilon, int64_t iNbIteration, AlgoStopName iOldStopName) {
	_stopName = iStopName;
	_nbIteration = iNbIteration;
	_epsilon = iEpsilon;
	_oldStopName = iOldStopName;
}

EventMixmodSetStopRuleValue::~EventMixmodSetStopRuleValue() {
}

std::string EventMixmodSetStopRuleValue::getDisplay() const {
	string stopRuleValue = AlgoStopNameToString(_stopName);
	return stopRuleValue;
}

bool EventMixmodSetStopRuleValue::launchNewEvent() const {

	bool res = false;

	if ( ( ((_stopName == NBITERATION) || (_stopName == EPSILON)) && (_oldStopName ==  NBITERATION_EPSILON) ) ||
	        ( (_stopName == NBITERATION_EPSILON) && ( (_oldStopName ==  NBITERATION) || (_oldStopName ==  EPSILON) ) ) ) {
		res = true;
	}
	else if ( ((_stopName == NBITERATION) && (_oldStopName ==  EPSILON)) ||  ((_stopName == EPSILON) && (_oldStopName ==  NBITERATION)) ) {
		res = true;
	}
	else if(_nbIteration==1) {
		res = true;
	}
	return res;

}

void EventMixmodSetStopRuleValue::process(TreeItem * treeItem) {

	if ( (_oldStopName == NBITERATION) && (_stopName ==  EPSILON ) ) {
		_controller->removeChild<int64_t>(treeItem,0);
		_controller->insertChild(treeItem,0,_epsilon);
	}

	else if ( (_oldStopName == NBITERATION) && (_stopName ==  NBITERATION_EPSILON ) ) {
		_controller->removeChild<int64_t>(treeItem,0);
		_controller->insertChild(treeItem,0,_nbIteration);
		_controller->insertChild(treeItem,1,_epsilon);
	}

	else if ( (_oldStopName == NBITERATION_EPSILON) && (_stopName ==  NBITERATION ) ) {
		_controller->removeChild<int64_t>(treeItem,0);
		_controller->removeChild<double>(treeItem,0);
		_controller->insertChild(treeItem,0,_nbIteration);

	}
	else if ( (_oldStopName == NBITERATION_EPSILON) && (_stopName ==  EPSILON ) ) {
		_controller->removeChild<int64_t>(treeItem,0);
		_controller->removeChild<double>(treeItem,0);
		_controller->insertChild(treeItem,0,_epsilon);
	}
	else if ( (_oldStopName == EPSILON) && (_stopName ==  NBITERATION_EPSILON ) ) {
		_controller->removeChild<double>(treeItem,0);
		_controller->insertChild(treeItem,0,_nbIteration);
		_controller->insertChild(treeItem,1,_epsilon);
	}
	else if ( (_oldStopName == EPSILON) && (_stopName ==  NBITERATION ) ) {
		_controller->removeChild<double>(treeItem,0);
		_controller->insertChild(treeItem,0,_nbIteration);
	}
	else if((_stopName ==  NBITERATION) && (_oldStopName == NBITERATION ) && (_nbIteration==1)) {
		_controller->removeChild<int64_t>(treeItem,0);
		_controller->insertChild(treeItem,0,_nbIteration);
	}

}



TreeKeyword EventMixmodSetStopRuleValue::getKeyword() const {
	return TreeStopRuleValue;
}




}
}
