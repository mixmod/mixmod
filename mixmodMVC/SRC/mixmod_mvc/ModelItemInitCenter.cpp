/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitCenter.cpp  description
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
#include "mixmod_mvc/ModelItemInitCenter.h"
#include "mixmod_mvc/EventMixmodSetInitName.h"
#include "mixmod_mvc/EventMixmodDisplayCenter.h"

namespace XEM {
namespace MVC {


ModelItem<TreeInitCenterChild, double>::ModelItem( Input* iInput, double* iTabCenterI, int64_t iPosition) {
	_tabCenterI = iTabCenterI;
	_input = iInput;
	_position = iPosition;
}

ModelItem<TreeInitCenterChild, double> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitCenterChild, double> ::setValue( int64_t /*position*/) {
	return NULL ;
}

Event* ModelItem<TreeInitCenterChild, double> ::insertChild( int64_t /*position*/) {
	Event* eventDisplay = new EventMixmodDisplayCenter(_tabCenterI,_input->getPbDimension());

	return eventDisplay ;
}

Event* ModelItem<TreeInitCenterChild, double> ::removeChild(int64_t /*position*/) {
	return NULL ;
}




ModelItem<TreeInitCenterChild, int64_t>::ModelItem( Input* iInput, int64_t* iTabCenterI, int64_t iPosition) {
	_tabCenterI = iTabCenterI;
	_input = iInput;
	_position = iPosition;
}

ModelItem<TreeInitCenterChild, int64_t> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitCenterChild, int64_t> ::setValue( int64_t /*position*/) {
	return NULL ;
}

Event* ModelItem<TreeInitCenterChild, int64_t> ::insertChild( int64_t /*position*/) {
	Event* eventDisplay = new EventMixmodDisplayCenterB(_tabCenterI,_input->getPbDimension());

	return eventDisplay ;
}

Event* ModelItem<TreeInitCenterChild, int64_t> ::removeChild(int64_t /*position*/) {
	return NULL ;
}
}
}
