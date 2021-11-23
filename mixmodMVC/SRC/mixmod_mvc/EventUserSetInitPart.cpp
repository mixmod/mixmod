/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventUserSetInitPart.cpp  description
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
#include "mixmod_mvc/EventUserSetInitPart.h"
#include "mixmod_mvc/Controller.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {



EventUserSetInitPart::EventUserSetInitPart(string iFilename) {
	_filename = iFilename;
}


EventUserSetInitPart::~EventUserSetInitPart() {
}

void EventUserSetInitPart::process(TreeItem * treeItem) {
	ClusteringStrategy * cStrategy = dynamic_cast<ClusteringStrategy*>(_controller->getModel()->getInput()->getStrategy());
	if ( cStrategy->getStrategyInit()->getTabPartition() && cStrategy->getStrategyInit()->getPartition(treeItem->getPosition()) && cStrategy->getStrategyInit()->getPartition(treeItem->getPosition())->getTabValue()) {
		for (int64_t i=0; i< _controller->getModel()->getInput()->getNbSample(); ++i) {
			_controller->removeChild<int64_t**>(treeItem,0);
		}
	}
	_controller->setValue(treeItem,_filename);
	if (_filename.compare(Model::DEFAULTFILENAME)!=0) {

		for (int64_t i=0; i< _controller->getModel()->getInput()->getNbSample(); ++i) {
			_controller->insertChild(treeItem,i,(int64_t**) (NULL));
		}
	}
}

std::string EventUserSetInitPart::getDisplay() const {
	return string();
}

bool EventUserSetInitPart::launchNewEvent() const  {
	return false;
}
}
}
