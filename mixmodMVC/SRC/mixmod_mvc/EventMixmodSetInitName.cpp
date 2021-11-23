/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodSetInitName.cpp  description
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
#include "mixmod_mvc/EventMixmodSetInitName.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {




EventMixmodSetInitName::EventMixmodSetInitName(StrategyInitName iInitName, StrategyInitName iOldInitName, int64_t iNbNbCluster) {
	_initName = iInitName;
	_oldInitName = iOldInitName;
	_defaultFilename = "NONE";
	_nbNbCluster = iNbNbCluster;
}

EventMixmodSetInitName::~EventMixmodSetInitName() {
}

std::string EventMixmodSetInitName::getDisplay() const {

	string initName = StrategyInitNameToString(_initName);
	return initName;
}

bool EventMixmodSetInitName::launchNewEvent() const {

	bool res = false;

	if ( (_oldInitName == USER_PARTITION) && ( (_initName == USER) || (_initName == RANDOM) ||
	        (_initName == SEM_MAX) || (_initName == SMALL_EM) || (_initName == CEM_INIT) ) ) {
		res = true;
	}
	else if ( (_oldInitName == USER) && ( (_initName == USER_PARTITION) || (_initName == RANDOM) ||
	                                      (_initName == SEM_MAX) || (_initName == SMALL_EM) || (_initName == CEM_INIT) ) ) {
		res = true;
	}
	else if ( ((_oldInitName == RANDOM) || (_oldInitName == SEM_MAX) || (_oldInitName == SMALL_EM) || (_oldInitName == CEM_INIT)) && ( (_initName == USER_PARTITION) || (_initName == USER)) ) {
		res = true;
	}
	else if (_oldInitName == USER &&  _initName == USER) {
		res = true;
	}

	return res;

}

void EventMixmodSetInitName::process(TreeItem * treeItem) {

	int64_t k;
//   Identifier id2;
//   if (_initName==USER_PARTITION){
//     id2 = Identifier(id, TreeInitTypeNameUserPartition);
//   }
//   else if (_initName==USER){
//    id2 = Identifier(id, TreeInitTypeNameUser);
//   }
//   else if  ( ( (_oldInitName == USER) || (_oldInitName == USER_PARTITION)) && ((_initName!=USER) || (_initName!=USER_PARTITION) ) ) {
//     id2 = Identifier(id, TreeInitTypeName);
//   }


	if (_oldInitName == CEM_INIT) {
		_controller->removeChild<int64_t>(treeItem,View::NB_TRY_INIT_CEM);
	}


	if ( ((_oldInitName == RANDOM) || (_oldInitName == SEM_MAX) || (_oldInitName == SMALL_EM) || (_oldInitName == CEM_INIT)) && ( _initName == USER_PARTITION) ) {

		for (k=0 ; k< _nbNbCluster ; ++k) {
			_controller->insertChild(treeItem,k,_defaultFilename);
		}
	}
	else if ( ((_oldInitName == RANDOM) || (_oldInitName == SEM_MAX) || (_oldInitName == SMALL_EM) || (_oldInitName == CEM_INIT)) && (_initName == USER) ) {
		for (k=0 ; k< _nbNbCluster ; ++k) {
			_controller->insertChild(treeItem,k,_defaultFilename);
		}
	}
	else if  ((_oldInitName == USER) /*&& ( (_initName == USER_PARTITION) || (_initName == RANDOM) ||
                                              (_initName == SEM_MAX) || (_initName == SMALL_EM) || (_initName == CEM_INIT) ) ) */||
	          ( (_oldInitName == USER_PARTITION) && ( (_initName == USER) || (_initName == RANDOM) ||
	                  (_initName == SEM_MAX) || (_initName == SMALL_EM) || (_initName == CEM_INIT) ) )) {
		for (k=0 ; k< _nbNbCluster ; ++k) {
			_controller->removeChild<StrategyInitName>(treeItem,k);
			if ((_initName == USER_PARTITION) || (_initName == USER) ) {
				_controller->insertChild(treeItem,k,_defaultFilename);
			}
		}
	}


}


TreeKeyword EventMixmodSetInitName::getKeyword() const {
	return TreeInitTypeName;
}




}
}
