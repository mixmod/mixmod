/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertModel.cpp  description
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
#include "mixmod_mvc/EventMixmodInsertModel.h"
//#include "mixmod_mvc/Identifier.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {




EventMixmodInsertModel::EventMixmodInsertModel(ModelName iModelName, int64_t iNbCluster, int64_t iSubDim, int64_t iPosition) {
	_modelName = iModelName;
	_nbCluster = iNbCluster;
	_subDim = iSubDim;
	_position = iPosition;
}

EventMixmodInsertModel::~EventMixmodInsertModel() {
}


std::string EventMixmodInsertModel::getDisplay() const {
	string modelName = ModelNameToString(_modelName);
	return modelName;
}

bool EventMixmodInsertModel::launchNewEvent() const {
	bool res = false;
	if (isHD(_modelName)) {
		res = true;
	}
	return res;
}

void EventMixmodInsertModel::process(TreeItem * treeItem) {
//Identifier id2 (id,TreeModelChild,_position);
	TreeItem * modelChildItem = treeItem->getChild(_position);

	if ( !isFreeSubDimension(_modelName)) {
		_nbCluster = 1;
	}
	for (int64_t i=0; i<_nbCluster; ++i) {
		_controller->insertChild(modelChildItem,i,_subDim);
	}
}

TreeKeyword EventMixmodInsertModel::getKeyword() const {
	return TreeModelChild;
}
}
}
