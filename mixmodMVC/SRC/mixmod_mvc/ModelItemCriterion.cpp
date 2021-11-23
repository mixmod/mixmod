/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemCriterion.cpp  description
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
#include "mixmod_mvc/ModelItemCriterion.h"
#include "mixmod_mvc/NoEvent.h"

namespace XEM {
namespace MVC {



ModelItem<TreeCriterionChild, CriterionName>::ModelItem( Input* iInput, CriterionName iCriterionName) {
	_criterionName = iCriterionName;
	_input = iInput;
}

ModelItem<TreeCriterionChild, CriterionName> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeCriterionChild, CriterionName> ::setValue( int64_t position) {
	Event *event = NULL;
	int64_t nbCriterionName = _input->getNbCriterion();
	if ((position>(nbCriterionName-1))
	        ||(position<0) ) {
		event = NULL;
	}
	else {
		_input->setCriterion( _criterionName, position);
		event = new EventMixmodDisplay<CriterionName>(_criterionName);
	}
	return event;
}


Event* ModelItem<TreeCriterionChild, CriterionName> ::insertChild( int64_t position) {
	Event *event = NULL;
	int64_t nbCriterionName = _input->getNbCriterion();
	if((position>nbCriterionName)
	        || (position<0)) {
		event = NULL;
	}
	else {
		_input->insertCriterion( _criterionName, position);
		event = new EventMixmodDisplay<CriterionName>(_criterionName);
	}
	return event;
}

Event* ModelItem<TreeCriterionChild, CriterionName> ::removeChild(int64_t position) {


	Event* event = NULL;
	int64_t nbCriterionName = _input->getNbCriterion();
	if ((position>(nbCriterionName-1))
	        || ((position==0) && (nbCriterionName==1))
	        || (position<0)) {
		event = NULL;
	}
	else {
		_input->removeCriterion(position);
		event = new NoEvent();
	}
	return event;
}
}
}
