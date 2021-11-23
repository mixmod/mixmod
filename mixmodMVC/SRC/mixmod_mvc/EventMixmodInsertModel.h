/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertModel.h  description
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
#ifndef __EVENTMIXMODINSERTMODEL_H__
#define __EVENTMIXMODINSERTMODEL_H__


//#include "mixmod_mvc/Identifier.h"
#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {


class EventMixmodInsertModel : public Event {

public :
	EventMixmodInsertModel(ModelName iModelName, int64_t iNbCluster, int64_t iSubDim, int64_t iPosition);
	~EventMixmodInsertModel();
	std::string getDisplay() const;
	bool launchNewEvent() const;
	void process(TreeItem* treeItem);
	TreeKeyword getKeyword() const;
private :
	ModelName _modelName;
	int64_t _nbCluster;
	int64_t _subDim;
	int64_t _position;
};


}
}

#endif
