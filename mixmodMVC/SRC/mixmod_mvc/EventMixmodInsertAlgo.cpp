/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertAlgo.cpp  description
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
#include "mixmod_mvc/EventMixmodInsertAlgo.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {



EventMixmodInsertAlgo::EventMixmodInsertAlgo(AlgoName iAlgoName, int64_t position, AlgoStopName iStopName) {
	_algoName = iAlgoName;
	_position = position;
	_stopName = iStopName;
}


EventMixmodInsertAlgo::~EventMixmodInsertAlgo() {
}

void EventMixmodInsertAlgo::process( TreeItem * treeItem) {
	//Identifier id2(identifier,TreeNbAlgoChild,_position);
	TreeItem * NbAlgoChildItem = treeItem->getChild(_position);
	_controller->insertChild(NbAlgoChildItem,0,_algoName);

	if (_algoName==SEM) {
		_stopName = NBITERATION;
	}
	_controller->insertChild(NbAlgoChildItem,1,_stopName);


}

std::string EventMixmodInsertAlgo::getDisplay() const {
	return string();
}

bool EventMixmodInsertAlgo::launchNewEvent() const  {
	return true ;
}

TreeKeyword EventMixmodInsertAlgo::getKeyword() const {
	return TreeNbAlgoChild;
}


}
}
