/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertInitParamChild.cpp  description
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
#include "mixmod_mvc/EventMixmodInsertInitParamChild.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {




EventMixmodInsertInitParamChild::EventMixmodInsertInitParamChild(string iFilename, int64_t iNbCluster, int64_t iPbDimension, int64_t position) {
	_nbCluster = iNbCluster;
	_filename = iFilename;
	_pbDimension = iPbDimension;
	_position = position;
	_nbParamChild = 3;
}

EventMixmodInsertInitParamChild::~EventMixmodInsertInitParamChild() {
}

std::string EventMixmodInsertInitParamChild::getDisplay() const {
	return _filename;
}

bool EventMixmodInsertInitParamChild::launchNewEvent() const {
	return true;
}

void EventMixmodInsertInitParamChild::process(TreeItem* treeItem) {
	int64_t nbChild = treeItem->getNbChild();
	if (nbChild != 0) {
		for (int64_t i=0; i<nbChild ; ++i) {
			_controller->removeChild<StrategyInitName>(treeItem,i);
		}
	}
	for (int64_t i=0; i<_nbParamChild ; ++i) {
		int64_t value = 0;
		_controller->insertChild(treeItem,i, value);
	}
}


TreeKeyword EventMixmodInsertInitParamChild::getKeyword() const {
	return TreeInitParameterChild;
}
}
}
