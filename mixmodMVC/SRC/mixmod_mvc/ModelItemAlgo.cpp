/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemAlgo.cpp  description
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
#include "mixmod_mvc/ModelItemAlgoName.h"
#include "mixmod_mvc/EventMixmodInsertAlgo.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/ModelItemAlgo.h"
#include "mixmod/Kernel/Algo/Algo.h"
#include "mixmod/Clustering/ClusteringStrategy.h"

namespace XEM {
namespace MVC {


ModelItem<TreeNbAlgo, AlgoName>::ModelItem( Input* iInput, AlgoName iAlgoName) {
	_input = iInput;
}


ModelItem<TreeNbAlgo, AlgoName> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeNbAlgo, AlgoName> ::setValue( int64_t /*position*/) {
	return NULL ;
}


Event* ModelItem<TreeNbAlgo, AlgoName> ::insertChild( int64_t position) {
	// 0=strategyPosition  une unique strategy
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
//  Algo * algo = createDefaultClusteringAlgo();
	cStrategy->insertAlgo(defaultClusteringAlgoName , position);//insert l'algorithme par défaut
	cStrategy->setAlgoStopRule( NO_STOP_NAME, position);
	Event* eventMixmodInsertAlgo = new EventMixmodInsertAlgo(defaultAlgoName, position, defaultAlgoStopName);

	return eventMixmodInsertAlgo;
}

Event* ModelItem<TreeNbAlgo, AlgoName> ::removeChild(int64_t position) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->removeAlgo(position);

	return new NoEvent();
}


}
}
