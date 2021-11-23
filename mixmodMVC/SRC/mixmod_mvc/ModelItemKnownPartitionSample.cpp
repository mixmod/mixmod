/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemKnownPartitionSample.cpp  description
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
#include "mixmod_mvc/ModelItemKnownPartitionSample.h"
#include "mixmod_mvc/EventMixmodSetModelChild.h"
#include "mixmod_mvc/EventMixmodDisplaySubDim.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod/Kernel/IO/LabelDescription.h"
#include "mixmod/Kernel/IO/Label.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {


ModelItem<TreeKnownPartitionSample, int64_t>::ModelItem( Input* iInput) {
	_input = iInput;
}


ModelItem<TreeKnownPartitionSample, int64_t> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeKnownPartitionSample, int64_t> ::setValue( int64_t /*position*/) {
	return NULL ;
}


Event* ModelItem<TreeKnownPartitionSample, int64_t> ::insertChild( int64_t position) {
	int64_t value = _input->getKnownLabelDescription()->getLabel()->getLabel().at(position);
	Event* eventDisplay = new EventMixmodDisplayKnownPartitionSample(value);

	return eventDisplay ;
}

Event* ModelItem<TreeKnownPartitionSample, int64_t> ::removeChild(int64_t /*position*/) {
	return new NoEvent();
}







// init partition


ModelItem<TreeInitPartitionSample, int64_t>::ModelItem( Input* iInput, int64_t iPosition ) {
	_input = iInput;
	_position = iPosition;
}


ModelItem<TreeInitPartitionSample, int64_t> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeInitPartitionSample, int64_t> ::setValue( int64_t /*position*/) {
	return NULL ;
}


Event* ModelItem<TreeInitPartitionSample, int64_t> ::insertChild( int64_t position) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	Event* eventDisplay = new EventMixmodDisplayInitKnownPartitionSample(cStrategy->getStrategyInit()->getPartition(_position)->getTabValueI(position),_input->getNbCluster(_position));

	return eventDisplay ;
}

Event* ModelItem<TreeInitPartitionSample, int64_t> ::removeChild(int64_t /*position*/) {
	return new NoEvent();
}
}
}
