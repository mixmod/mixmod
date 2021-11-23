/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodSetModelChild.cpp  description
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
#include "mixmod_mvc/EventMixmodSetModelChild.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {




EventMixmodSetModelChild::EventMixmodSetModelChild(ModelName iModelName,ModelName iOldModelName, int64_t iNbCluster,int64_t iSubDim) {
	_modelName = iModelName;
	_oldModelName = iOldModelName;
	_nbCluster = iNbCluster;
	_subDim = iSubDim;
}

EventMixmodSetModelChild::~EventMixmodSetModelChild() {
}

std::string EventMixmodSetModelChild::getDisplay() const {
	string modelName = ModelNameToString(_modelName);
	return modelName;
}

bool EventMixmodSetModelChild::launchNewEvent() const {
	bool res = false;
	if (isHD(_modelName) && (!isHD(_oldModelName)) ||
	        isHD(_oldModelName) && (!isHD(_modelName)) ||
	        isHD(_oldModelName) && (isHD(_modelName)) ) {
		res = true;
	}
	return res;
}

void EventMixmodSetModelChild::process( TreeItem * treeItem) {

	if (isHD(_oldModelName)) {
		int64_t nbCluster = 1;
		if (isFreeSubDimension(_oldModelName)) {
			nbCluster = _nbCluster;
		}
		for (int64_t i=0; i<nbCluster; ++i) {
			_controller->removeChild<int64_t>(treeItem,i);
		}
	}
	if (isHD(_modelName)) {

		if (!isFreeSubDimension(_modelName)) {
			_nbCluster = 1;
		}

		for (int64_t i=0; i<_nbCluster; ++i) {
			_controller->insertChild(treeItem,i,_subDim);
		}
	}
}
}
}
