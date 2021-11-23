/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertAlgo.h  description
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
#ifndef __EVENTMIXMODINSERTALGO_H__
#define __EVENTMIXMODINSERTALGO_H__

#include "mixmod_mvc/Util.h"
#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {


class EventMixmodInsertAlgo : public Event {

public :
	EventMixmodInsertAlgo(AlgoName iAlgoName, int64_t position, AlgoStopName iStopName);
	~EventMixmodInsertAlgo();
	void process(TreeItem* treeItem);
	std::string getDisplay() const ;
	bool launchNewEvent() const  ;
	TreeKeyword getKeyword() const;
private :
	AlgoName _algoName;
	int64_t _position;
	AlgoStopName _stopName;
};




}
}

#endif
