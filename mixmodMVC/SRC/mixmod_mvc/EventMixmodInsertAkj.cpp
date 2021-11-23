/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertAkj.cpp  description
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
#include "mixmod_mvc/EventMixmodInsertAkj.h"

namespace XEM {
namespace MVC {



EventMixmodInsertAkj::EventMixmodInsertAkj(int64_t iNbCluster, double** iTabA, int64_t iPosition) {
	_nbCluster = iNbCluster;
	_tabA = iTabA;
	_position = iPosition;
}


EventMixmodInsertAkj::~EventMixmodInsertAkj() {
}


std::string EventMixmodInsertAkj::getDisplay() const {
	return "tabAkj";
}


bool EventMixmodInsertAkj::launchNewEvent() const {
	return true;
}


void EventMixmodInsertAkj::process(TreeItem * treeItem) {
	//Identifier id2 (id,TreeInitParameterChildHD,_position);
	TreeItem * parameterItem = treeItem->getChild(_position);
	for (int64_t i=0; i<_nbCluster; ++i) {
		_controller->insertChild(parameterItem,i,_tabA[i]);
	}

}


TreeKeyword EventMixmodInsertAkj::getKeyword() const {
	return TreeInitParameterChild;
}

}
}
