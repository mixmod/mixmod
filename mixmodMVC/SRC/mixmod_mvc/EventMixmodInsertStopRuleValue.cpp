/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertStopRuleValue.cpp  description
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
#include "mixmod_mvc/EventMixmodInsertStopRuleValue.h"
//#include "mixmod_mvc/Identifier.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {




EventMixmodInsertStopRuleValue::EventMixmodInsertStopRuleValue(AlgoStopName iStopName, double iEpsilon, int64_t iNbIteration) {
	_stopName = iStopName;
	_nbIteration = iNbIteration;
	_epsilon = iEpsilon;
}

EventMixmodInsertStopRuleValue::~EventMixmodInsertStopRuleValue() {
}

std::string EventMixmodInsertStopRuleValue::getDisplay() const {
	//string stopName = AlgoStopNameToString(_stopName);
	return string();
}

bool EventMixmodInsertStopRuleValue::launchNewEvent() const {
	return true;
}

void EventMixmodInsertStopRuleValue::process(TreeItem* treeItem) {
	//Identifier id2 (id, TreeStopRuleValue,1);
	TreeItem * stopRuleItem = treeItem->getChild(1);
	if (_stopName==NBITERATION) {
		_controller->insertChild(stopRuleItem,0,_nbIteration);
	}
	else if (_stopName==EPSILON) {
		_controller->insertChild(stopRuleItem,0,_epsilon);
	}
	else if (_stopName==NBITERATION_EPSILON) {
		_controller->insertChild(stopRuleItem,0,_nbIteration);
		//Identifier id3 (id.getPosition(), TreeStopRuleValue, 1, id.getParentPosition(), id.getNbChild()+1);
		_controller->insertChild(stopRuleItem,1,_epsilon);
	}
}



TreeKeyword EventMixmodInsertStopRuleValue::getKeyword() const {
	return TreeStopRuleValue;
}




}
}
