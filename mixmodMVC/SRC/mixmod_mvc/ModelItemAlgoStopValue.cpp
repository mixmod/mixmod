/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemAlgoStopValue.cpp  description
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
#include "mixmod_mvc/ModelItemAlgoStopValue.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodDisplayIteration.h"
#include "mixmod_mvc/EventMixmodDisplayEpsilon.h"
#include "mixmod/Clustering/ClusteringStrategy.h"

namespace XEM {
namespace MVC {


ModelItem<TreeNbIteration, int64_t>::ModelItem( Input* iInput, int64_t iNbIteration, int64_t iParentPosition, int64_t iGParentPosition) {
	_nbIteration = iNbIteration;
	_input = iInput;
	_position = iParentPosition;
	_gPosition = iGParentPosition;
}

ModelItem<TreeNbIteration, int64_t> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeNbIteration, int64_t> ::setValue( int64_t /*position*/) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setAlgoIteration(_gPosition, _nbIteration);
	Event* eventMixmodSetAlgoStop = new EventMixmodDisplayIteration(_nbIteration);
	return eventMixmodSetAlgoStop;
}


ModelItem<TreeEpsilon, double>::ModelItem( Input* iInput, double iEpsilon, int64_t iParentPosition, int64_t iGparentPosition) {
	_epsilon = iEpsilon;
	_input = iInput;
	_position = iParentPosition;
	_gPosition = iGparentPosition;
}

ModelItem<TreeEpsilon, double> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeEpsilon, double> ::setValue( int64_t /*position*/) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	cStrategy->setAlgoEpsilon( _gPosition,_epsilon);
	Event* eventMixmodSetAlgoStop = new EventMixmodDisplayEpsilon(_epsilon);
	return eventMixmodSetAlgoStop;
}
}
}
