/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemWeight.cpp  description
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
#include "mixmod_mvc/ModelItemWeight.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodDisplayWeight.h"
#include "mixmod_mvc/EventMixmodDisplayWeightChild.h"
#include "mixmod_mvc/EventMixmodErrorWeight.h"
#include "mixmod_mvc/Model.h"

namespace XEM {
namespace MVC {

ModelItem<TreeDataWeight, string>::ModelItem( Input* iInput, string iFilename) {
	_filename = iFilename;
	_input = iInput;
}


ModelItem<TreeDataWeight, string> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeDataWeight, string> ::setValue( int64_t position) {
	Event* event=NULL;
	if (_filename.compare(Model::DEFAULTFILENAME) ==0) {
		string name = "";
		_input->setWeight(name);
		event = new EventMixmodDisplay<std::string>(_filename);
	}
	else {
		try {
			_input->setWeight( _filename);
			event = new EventMixmodDisplayWeight(_filename);
		}
		catch (Exception* e) {
			string defaultName = Model::DEFAULTFILENAME ;
			_filename = defaultName ;
			string name="";
			_input->setWeight(name);
			return new EventMixmodErrorWeight(_filename, e);
		}
	}
	return event;
}


ModelItem<TreeDataWeightChild, double>::ModelItem( Input* iInput, double iWeight ) {
	_input = iInput;
	_weight = iWeight;
}


ModelItem<TreeDataWeightChild, double> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeDataWeightChild, double> ::setValue( int64_t /*position*/) {
	return NULL ;
}


Event* ModelItem<TreeDataWeightChild, double> ::insertChild( int64_t position) {
	Event* eventDisplay = new EventMixmodDisplayWeightChild(_weight);

	return eventDisplay ;
}

Event* ModelItem<TreeDataWeightChild, double> ::removeChild(int64_t /*position*/) {
	return new NoEvent();
}

}
}
