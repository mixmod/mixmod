/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitName.cpp  description
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
#include "mixmod_mvc/ModelItemInitName.h"
#include "mixmod_mvc/EventMixmodSetInitName.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {


ModelItem<TreeInitTypeName, StrategyInitName>::ModelItem( Input* iInput, StrategyInitName iInitName) {
	_initName = iInitName;
	_input = iInput;
}

ModelItem<TreeInitTypeName, StrategyInitName> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitTypeName, StrategyInitName> ::setValue( int64_t position) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	StrategyInitName oldInitName =  cStrategy->getStrategyInit()->getStrategyInitName();
	cStrategy->setStrategyInitName( _initName);

	Event* eventMixmodSetInitName = new EventMixmodSetInitName(_initName,oldInitName, (_input->getNbCluster()).size() );
	return eventMixmodSetInitName;
}

Event* ModelItem<TreeInitTypeName, StrategyInitName> ::insertChild( int64_t /*position*/) {
	return NULL ;
}

Event* ModelItem<TreeInitTypeName, StrategyInitName> ::removeChild(int64_t /*position*/) {
	return new NoEvent();
}
}
}
