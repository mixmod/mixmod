/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodDisplay.cpp  description
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
#include "mixmod_mvc/EventMixmodDisplay.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {


EventMixmodDisplay<CriterionName>::EventMixmodDisplay(CriterionName iCriterionName):_criterionName(iCriterionName) {
}


EventMixmodDisplay<CriterionName>::~EventMixmodDisplay() {
}


string EventMixmodDisplay<CriterionName>::getDisplay()const {

	string criterion = CriterionNameToString(_criterionName);
	return criterion;
}

TreeKeyword EventMixmodDisplay<CriterionName>::getKeyword() const {
	return TreeCriterionChild;
}


void EventMixmodDisplay<CriterionName>::process(TreeItem* treeItem /*id*/) {
}


bool EventMixmodDisplay<CriterionName>::launchNewEvent()const {
	return false;
}



EventMixmodDisplay<ModelName>::EventMixmodDisplay(ModelName iModelName):_modelName(iModelName) {
}


EventMixmodDisplay<ModelName>::~EventMixmodDisplay() {
}


string EventMixmodDisplay<ModelName>::getDisplay()const {

	string modelName = ModelNameToString(_modelName);
	return modelName;
}

void EventMixmodDisplay<ModelName>::process(const TreeItem& treeItem /*id*/) {
}

bool EventMixmodDisplay<ModelName>::launchNewEvent()const {
	if (isHD(_modelName)) {
		return true;
	}
	else {
		return false;
	}
}

TreeKeyword EventMixmodDisplay<ModelName>::getKeyword() const {
	return TreeModelChild;
}




EventMixmodDisplay<StrategyInitName>::EventMixmodDisplay(StrategyInitName iStrategyInitName):_strategyInitName(iStrategyInitName) {
}


EventMixmodDisplay<StrategyInitName>::~EventMixmodDisplay() {
}


string EventMixmodDisplay<StrategyInitName>::getDisplay()const {

	string strategyInitName = StrategyInitNameToString(_strategyInitName);
	return strategyInitName;
}

void EventMixmodDisplay<StrategyInitName>::process( TreeItem * treeItem /*id*/) {
}

bool EventMixmodDisplay<StrategyInitName>::launchNewEvent()const {
	return false;
}

TreeKeyword EventMixmodDisplay<StrategyInitName>::getKeyword() const {
	return TreeInitType;
}






EventMixmodDisplay<AlgoStopName>::EventMixmodDisplay(AlgoStopName iAlgoStopName, TreeKeyword iTreeKeyword):_algoStopName(iAlgoStopName), _treeKeyword(iTreeKeyword) {
}


EventMixmodDisplay<AlgoStopName>::~EventMixmodDisplay() {
}


string EventMixmodDisplay<AlgoStopName>::getDisplay()const {

	//string algoStopName = AlgoStopNameToString(_algoStopName);
	return string();
}

void EventMixmodDisplay<AlgoStopName>::process(TreeItem* treeItem /*id*/) {
}

bool EventMixmodDisplay<AlgoStopName>::launchNewEvent()const {
	return false;
}

TreeKeyword EventMixmodDisplay<AlgoStopName>::getKeyword() const {
	return _treeKeyword;
}



EventMixmodDisplay<AlgoName>::EventMixmodDisplay(AlgoName iAlgoName):_algoName(iAlgoName) {
}


EventMixmodDisplay<AlgoName>::~EventMixmodDisplay() {
}


string EventMixmodDisplay<AlgoName>::getDisplay()const {

	string algoName = AlgoNameToString(_algoName);
	return algoName;
}

void EventMixmodDisplay<AlgoName>::process(TreeItem * treeItem) {
}

bool EventMixmodDisplay<AlgoName>::launchNewEvent()const {
	bool res = false;
	/*if ((_typeAlgo==SEM) || (_typeAlgo==M) || (_typeAlgo==MAP)){
	  res = true;
	}*/
	return res;
}

TreeKeyword EventMixmodDisplay<AlgoName>::getKeyword() const {
	return TreeAlgoName;
}




}
}
