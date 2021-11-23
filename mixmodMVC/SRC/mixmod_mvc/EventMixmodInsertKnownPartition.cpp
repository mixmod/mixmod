/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertKnownPartition.cpp  description
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
#include "mixmod_mvc/EventMixmodInsertKnownPartition.h"
//#include "mixmod_mvc/Identifier.h"
#include "mixmod_mvc/Controller.h"
#include "mixmod_mvc/Model.h"

namespace XEM {
namespace MVC {



EventMixmodInsertKnownPartition::EventMixmodInsertKnownPartition(string iFilename, int64_t iNbCluster, int64_t iNbSample, int64_t position) {
	_nbCluster = iNbCluster;
	_filename = iFilename;
	_nbSample = iNbSample;
	_position = position;
}

EventMixmodInsertKnownPartition::~EventMixmodInsertKnownPartition() {
}

std::string EventMixmodInsertKnownPartition::getDisplay() const {
	return _filename;
}

bool EventMixmodInsertKnownPartition::launchNewEvent() const {
	bool res = false;
	/*bool res = true;
	if (  (_filename.compare(Model::WRONGFILENAME)==0) || (_filename.compare(Model::DEFAULTFILENAME)==0) ){
	  res = false;
	}*/
	return res;
}

void EventMixmodInsertKnownPartition::process(const TreeItem& treeItem) {
	/* Identifier id2 (id,TreeKnownPartitionChild,_position);
	 for (int64_t i=0; i<_nbSample;++i){
	 _controler->insertChild(id2,i,(int64_t**) (NULL));
	     }
	*/
}


TreeKeyword EventMixmodInsertKnownPartition::getKeyword() const {
	return TreeKnownPartition;
}
}
}
