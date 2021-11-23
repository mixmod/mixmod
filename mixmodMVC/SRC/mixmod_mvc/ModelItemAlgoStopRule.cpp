/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemAlgoStopRule.cpp  description
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
#include "mixmod_mvc/ModelItemAlgoStopRule.h"
#include "mixmod_mvc/EventMixmodInsertStopRuleValue.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodDisplayEpsilon.h"
#include "mixmod_mvc/EventMixmodDisplayIteration.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Kernel/Algo/Algo.h"

namespace XEM {
namespace MVC {



ModelItem<TreeNbAlgoChild, AlgoStopName>::ModelItem( Input* iInput, AlgoStopName iStopName, int64_t iParentPosition) {
	_stopName = iStopName;
	_input = iInput;
	_position = iParentPosition;
}


ModelItem<TreeNbAlgoChild, AlgoStopName> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeNbAlgoChild, AlgoStopName> ::insertChild( int64_t positionRule) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	AlgoStopName oldStopName = cStrategy->getAlgo(_position)->getAlgoStopName();
	Event* eventMixmodSetAlgoStop ;
	if ( (oldStopName == NBITERATION)  || (_stopName == EPSILON ) ) {
		eventMixmodSetAlgoStop = new EventMixmodDisplayEpsilon(cStrategy->getAlgo(_position)->Algo::getEpsilon());
	}
	else if ( (oldStopName == EPSILON) || (_stopName == NBITERATION ) ) {
		eventMixmodSetAlgoStop = new EventMixmodDisplayIteration(cStrategy->getAlgo(_position)->getNbIteration());
	}
	else if( oldStopName == NO_STOP_NAME ) {
		eventMixmodSetAlgoStop = new EventMixmodInsertStopRuleValue(_stopName,cStrategy->getAlgo(_position)->getEpsilon(),cStrategy->getAlgo(_position)->getNbIteration());
	}
	else if( oldStopName == NBITERATION_EPSILON && _stopName == NBITERATION_EPSILON ) {//case new algo, nbiteration to insert at the beginning
		cStrategy->setAlgoStopRule(NBITERATION_EPSILON, _position);
		if (positionRule==0) {
			return new EventMixmodDisplayIteration(cStrategy->getAlgo(_position)->getNbIteration());
		}
		else if (positionRule==1) {
			return new EventMixmodDisplayEpsilon(cStrategy->getAlgo(_position)->Algo::getEpsilon());
		}
	}
	else	{
		return NULL;
	}
	cStrategy->setAlgoStopRule(_stopName, _position);
	return eventMixmodSetAlgoStop;
}



Event* ModelItem<TreeNbAlgoChild, AlgoStopName> ::removeChild(int64_t /*position*/) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setAlgoStopRule(_stopName, _position);
	return new NoEvent();
}

}
}
