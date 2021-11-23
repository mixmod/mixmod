/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemStopRuleInit.cpp  description
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
#include "mixmod_mvc/ModelItemStopRuleInit.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod/Clustering/ClusteringStrategy.h"

namespace XEM {
namespace MVC {

ModelItem<TreeInitStopRule, AlgoStopName>::ModelItem( Input* iInput, AlgoStopName iAlgoStopName) {
	_input = iInput;
	_algoStopName = iAlgoStopName;
}

ModelItem<TreeInitStopRule, AlgoStopName> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitStopRule, AlgoStopName> ::setValue( int64_t position) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setStopNameInInit(_algoStopName);
	return new EventMixmodDisplay<AlgoStopName>(_algoStopName, TreeInitStopRule);
}

}
}
