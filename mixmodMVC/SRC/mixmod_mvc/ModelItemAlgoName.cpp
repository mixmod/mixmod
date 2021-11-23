/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemAlgoName.cpp  description
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
#include "mixmod_mvc/ModelItemAlgo.h"
#include "mixmod_mvc/ModelItemAlgoName.h"
#include "mixmod_mvc/EventMixmodInsertAlgo.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodDisplayInsertedAlgoName.h"
#include "mixmod/Clustering/ClusteringStrategy.h"

namespace XEM {
namespace MVC {



ModelItem<TreeNbAlgoChild, AlgoName>::ModelItem( Input* iInput, AlgoName iAlgoName, int64_t iParentPosition) {
	_algoName = iAlgoName;
	_input = iInput;
	_position = iParentPosition;
}


ModelItem<TreeNbAlgoChild, AlgoName> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeNbAlgoChild, AlgoName> ::setValue( int64_t /*position*/) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setAlgo(_algoName, _position);

	Event* eventMixmodSetAlgo = new EventMixmodDisplay<AlgoName>(_algoName);
	return eventMixmodSetAlgo;
}


Event* ModelItem<TreeNbAlgoChild, AlgoName> ::insertChild( int64_t /*position*/) {
// Event* eventMixmodInsertAlgo = new EventMixmodDisplay<TypeAlgo>(_algoName);
	Event* eventMixmodInsertAlgo = new EventMixmodDisplayInsertedAlgoName(_algoName);
	return eventMixmodInsertAlgo;
}

Event* ModelItem<TreeNbAlgoChild, AlgoName> ::removeChild(int64_t /*position*/) {
	return NULL ;
}


}
}
