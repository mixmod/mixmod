/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitPartition.cpp  description
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
#include "mixmod_mvc/ModelItemInitPartition.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod_mvc/Model.h"
#include "mixmod_mvc/EventMixmodDisplayInitPart.h"
#include "mixmod_mvc/EventMixmodErrorInitPart.h"
#include "mixmod/Clustering/ClusteringStrategy.h"

namespace XEM {
namespace MVC {


ModelItem<TreeInitPartition, string>::ModelItem( Input* iInput, string iFilename) {
	_filename = iFilename;
	_input = iInput;
}


ModelItem<TreeInitPartition, string> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeInitPartition, string> ::setValue( int64_t position) {
	Event* event = NULL;
	if (_filename.compare("") != 0) {
		ifstream partitionFile(_filename.c_str(), ios::in);
		if (! partitionFile.is_open()) {
			throw wrongPartitionFileName;
		}
		else {
			try {
				ClusteringStrategy * cStrategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
				cStrategy->setInitPartition(_filename, position);
				event = new EventMixmodDisplayInitPart(_filename);
			}
			catch(Exception* e) {
				string defaultName = Model::DEFAULTFILENAME ;
				_filename = defaultName ;
				return new EventMixmodErrorInitPart(_filename, e);
			}

			return event;
		}
	}
	else {
		throw wrongPartitionFileName;
	}
}


Event* ModelItem<TreeInitPartition, string> ::insertChild( int64_t /*position*/) {

	Event* event = new EventMixmodDisplayInitPart( _filename );

	return event;
}

Event* ModelItem<TreeInitPartition, string> ::removeChild(int64_t /*position*/) {
	return NULL ;
}





}
}
