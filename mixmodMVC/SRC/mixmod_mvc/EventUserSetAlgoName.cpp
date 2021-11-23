/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventUserSetAlgoName.cpp  description
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
#include "mixmod_mvc/EventUserSetAlgoName.h"
#include "mixmod_mvc/Controller.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Kernel/Algo/Algo.h"

namespace XEM {
namespace MVC {



EventUserSetAlgoName::EventUserSetAlgoName(AlgoName iAlgoName) {
	_algoName= iAlgoName;
}


EventUserSetAlgoName::~EventUserSetAlgoName() {
}

void EventUserSetAlgoName::process(TreeItem * treeItem) {
	AlgoStopName oldAlgoStopName = dynamic_cast<ClusteringStrategy*>(_controller->getModel()->getInput()->getStrategy())->getAlgo(treeItem->getParentPosition())->getAlgoStopName();//stopRuleValue
	int64_t nbChild = 1;
	if (oldAlgoStopName == NBITERATION_EPSILON) {
		nbChild = 2;
	}

	//Identifier id2(identifier.getParentPosition(),TreeStopRuleValue,1, identifier.getGParentPosition(), nbChild);//id StopRuleValue
	TreeItem * stopRuleItem = treeItem->getParent()->getChild(View::STOP);
	if ( _algoName == SEM && oldAlgoStopName == EPSILON ) {
		_controller->insertChild(stopRuleItem,0, defaultNbIteration);
		//Identifier id2(identifier.getParentPosition(),TreeStopRuleValue,1, identifier.getGParentPosition(), ++nbChild);
		_controller->removeChild<double>(stopRuleItem,1);
	}
	_controller->setValue(treeItem,_algoName);

	if ( _algoName == SEM && oldAlgoStopName == NBITERATION_EPSILON ) {
		_controller->removeChild<double>(stopRuleItem,1);
	}
	else if( ( _algoName == EM || _algoName == CEM) && oldAlgoStopName == EPSILON) {
		_controller->insertChild(stopRuleItem,0, defaultNbIteration);
	}
	else if ( ( _algoName == EM || _algoName == CEM) && oldAlgoStopName == NBITERATION) {
		_controller->insertChild(stopRuleItem,1, defaultEpsilon);
	}
	//Identifier id3(id2, TreeNbIteration, 0);
	TreeItem * nbIterationItem = stopRuleItem->getChild(View::NB_ITERATION);
	_controller->setValue(nbIterationItem, defaultNbIteration);
	if (_algoName== EM || _algoName == CEM ) {
		//Identifier id4(id2, TreeEpsilon, 1);
		TreeItem * epsilonItem = stopRuleItem->getChild(View::EPSILON);
		_controller->setValue(epsilonItem, defaultEpsilon);
	}
	//TODO faire un set plutot qu'un insert pour la supervisée
	/*else if (( _algoName == MAP || _algoName == M ) && oldAlgoStopType == NBITERATION_EPSILON ){
	_controler->insertChild(id2,0, nbIteration);

	_controler->removeChild<double>(id2,0);
	int64_t nbIteration = 1;
	}else if (( _algoName == MAP || _algoName == M ) && oldAlgoStopType == EPSILON ){
	_controler->removeChild<double>(id2,0);
	int64_t nbIteration = 1;
	_controler->insertChild(id2,0, nbIteration);
	}else if (( _algoName == MAP || _algoName == M ) && oldAlgoStopType == NBITERATION ){
	_controler->removeChild<int64_t>(id2,0);
	int64_t nbIteration = 1;
	_controler->insertChild(id2,0, nbIteration);
	}*/
}

std::string EventUserSetAlgoName::getDisplay() const {
	return string();
}

bool EventUserSetAlgoName::launchNewEvent() const  {
	return true ;
}

}
}
