/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitDispersion.cpp  description
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
#include "mixmod_mvc/ModelItemInitDispersion.h"
#include "mixmod_mvc/EventMixmodSetInitName.h"
#include "mixmod_mvc/EventMixmodDisplayDispersion.h"
#include "mixmod_mvc/EventMixmodDisplayDispersionData.h"
#include "mixmod_mvc/NoEvent.h"

namespace XEM {
namespace MVC {



ModelItem<TreeInitDispersionChild, double>::ModelItem( Input* iInput, double** iTabValue, int64_t iPosition) {
	_tabValue = iTabValue;
	_input = iInput;
	_position = iPosition;
}

ModelItem<TreeInitDispersionChild, double> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitDispersionChild, double> ::setValue( int64_t /*position*/) {
	return NULL ;
}

Event* ModelItem<TreeInitDispersionChild, double> ::insertChild( int64_t /*position*/) {
	Event* eventDisplay = new EventMixmodDisplayDispersion(_tabValue,_input->getPbDimension());
	return eventDisplay ;
}

Event* ModelItem<TreeInitDispersionChild, double> ::removeChild(int64_t /*position*/) {
	return NULL ;
}


ModelItem<TreeInitDispersionData, double>::ModelItem( Input* iInput, double * iValue ) {
	_input = iInput;
	_value = iValue;
}


ModelItem<TreeInitDispersionData, double> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeInitDispersionData, double> ::setValue( int64_t /*position*/) {
	return NULL ;
}


Event* ModelItem<TreeInitDispersionData, double> ::insertChild( int64_t position) {
	Event* eventDisplay = new EventMixmodDisplayDispersionData(_value,_input->getNbCluster(0));

	return eventDisplay ;
}

Event* ModelItem<TreeInitDispersionData, double> ::removeChild(int64_t /*position*/) {
	return new NoEvent();
}

}
}
