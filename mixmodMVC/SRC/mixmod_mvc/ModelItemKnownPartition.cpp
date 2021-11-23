/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemKnownPartition.cpp  description
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
#include "mixmod_mvc/ModelItemKnownPartition.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/EventMixmodInsertKnownPartition.h"
#include "mixmod_mvc/EventMixmodInsertInitPartitionSample.h"
#include "mixmod_mvc/EventMixmodDisplayKnownPartition.h"
#include "mixmod_mvc/EventMixmodErrorKnownPartition.h"
#include "mixmod_mvc/Model.h"

namespace XEM {
namespace MVC {


ModelItem<TreeKnownPartition, string>::ModelItem( Input* iInput, string iFilename) {
	_filename = iFilename;
	_input = iInput;
}


ModelItem<TreeKnownPartition, string> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeKnownPartition, string> ::setValue( int64_t position) {
	Event* event=NULL;

	if (_filename.compare(Model::DEFAULTFILENAME) ==0) {
		_input->removeKnownLabelDescription();
		event = new EventMixmodDisplay<std::string>(_filename);
	}
	else {
		try {
			DomLabel domLabel;
			_input->setKnownLabelDescription(*domLabel.readLabel(_filename));
			event = new EventMixmodDisplayKnownPartition(_filename);
		}
		catch (Exception* e) {
			string defaultName = Model::DEFAULTFILENAME ;
			_filename = defaultName ;
			_input->removeKnownLabelDescription();
			return new EventMixmodErrorKnownPartition(_filename, e);
		}
		catch (IOStreamErrorType& e) {
			string defaultName = Model::DEFAULTFILENAME ;
			_filename = defaultName ;
			_input->removeKnownLabelDescription();
			return new EventMixmodErrorKnownPartition(_filename, e);
		}

	}
	return event;


}

}
}
