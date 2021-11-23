/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemParamInInit.cpp  description
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
#include "mixmod_mvc/ModelItemParamInInit.h"
#include "mixmod_mvc/EventMixmodInsertStopRuleInit.h"
#include "mixmod_mvc/EventMixmodDisplayNbTryInit.h"
#include "mixmod_mvc/EventMixmodDisplayNbIterationInit.h"
#include "mixmod_mvc/EventMixmodDisplayEpsilonInit.h"
#include "mixmod_mvc/View.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {

ModelItem<TreeInitType, int64_t>::ModelItem( Input* iInput, int64_t iPosition) {
	_input = iInput;
	_position = iPosition;
}

ModelItem<TreeInitType, int64_t> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitType, int64_t> ::insertChild( int64_t ) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	const StrategyInitName initName = cStrategy->getStrategyInit()->getStrategyInitName();
	if (initName == CEM_INIT || initName == RANDOM) {
		return new EventMixmodDisplayNbTryInit(cStrategy->getNbTryInInit());
	}
	if (initName == SEM_MAX) {
		return new EventMixmodDisplayNbIterationInit(cStrategy->getNbIterationInInit());
	}
	if (initName == SMALL_EM) {
		if (_position == View::NB_TRY_INIT_SMALL_EM) {
			return new EventMixmodDisplayNbTryInit(cStrategy->getNbTryInInit());
		}
		else if (_position == View::STOP_RULE_SMALL_EM) {
			cStrategy->setStopNameInInit(defaultAlgoStopName);
			return new EventMixmodInsertStopRuleInit(defaultAlgoStopName,cStrategy->getEpsilonInInit(), cStrategy->getNbIterationInInit());
		}
	}
}

Event* ModelItem<TreeInitType, int64_t> ::removeChild( int64_t ) {
	return new NoEvent();
}

ModelItem<TreeInitNbTry, int64_t>::ModelItem( Input* iInput, int64_t iNbTryInit) {
	_input = iInput;
	_nbTryInit = iNbTryInit;
}

ModelItem<TreeInitNbTry, int64_t> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitNbTry, int64_t> ::setValue( int64_t ) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setNbTryInInit(_nbTryInit);
	return new EventMixmodDisplayNbTryInit(_nbTryInit);
}


ModelItem<TreeInitNbIteration, int64_t>::ModelItem( Input* iInput, int64_t iNbIterationInit) {
	_input = iInput;
	_nbIterationInit = iNbIterationInit;
}

ModelItem<TreeInitNbIteration, int64_t> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitNbIteration, int64_t> ::setValue( int64_t ) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setNbIterationInInit(_nbIterationInit);
	return new EventMixmodDisplayNbIterationInit(_nbIterationInit);
}

Event* ModelItem<TreeInitNbIteration, int64_t> ::insertChild( int64_t ) {
	return new EventMixmodDisplayNbIterationInit(_nbIterationInit);
}

Event* ModelItem<TreeInitNbIteration, int64_t> ::removeChild( int64_t ) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setStopNameInInit(EPSILON);
	return new NoEvent();
}

ModelItem<TreeInitEpsilon, double>::ModelItem( Input* iInput, double iEpsilon) {
	_input = iInput;
	_epsilon = iEpsilon;
}


ModelItem<TreeInitEpsilon, double> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitEpsilon, double>::setValue( int64_t ) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setEpsilonInInit(EPSILON);
	return new EventMixmodDisplayEpsilonInit(_epsilon);
}

Event* ModelItem<TreeInitEpsilon, double> ::insertChild( int64_t ) {
	return new EventMixmodDisplayEpsilonInit(_epsilon);
}

Event* ModelItem<TreeInitEpsilon, double> ::removeChild( int64_t ) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setStopNameInInit(NBITERATION);
	return new NoEvent();
}

}
}
