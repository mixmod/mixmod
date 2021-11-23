/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemNbStrategyTry.cpp  description
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
#include "mixmod_mvc/ModelItemNbStrategyTry.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodDisplayNbStrategyTry.h"
#include "mixmod/Clustering/ClusteringStrategy.h"

namespace XEM {
namespace MVC {

ModelItem<TreeNbStrategyTry, int64_t>::ModelItem( Input* iInput, int64_t iNbStrategyTry) {
	_nbStrategyTry = iNbStrategyTry;
	_input = iInput;
}

ModelItem<TreeNbStrategyTry, int64_t> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeNbStrategyTry, int64_t> ::setValue( int64_t /*position*/) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setNbTry(_nbStrategyTry);
	Event* eventMixmodSetNbStrategyTry = new EventMixmodDisplayNbStrategyTry(_nbStrategyTry);
	return eventMixmodSetNbStrategyTry;
}

Event* ModelItem<TreeNbStrategyTry, int64_t> ::removeChild( int64_t ) {
	return new NoEvent();
}

Event* ModelItem<TreeNbStrategyTry, int64_t> ::insertChild( int64_t ) {
	return new EventMixmodDisplayNbStrategyTry(_nbStrategyTry/*_input->getStrategy(0)->getNbTry()*/);
}

}
}
