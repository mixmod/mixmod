/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodDisplayInsertedAlgoName.h  description
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
#ifndef __EVENTMIXMODDISPLAYINSEETEDALGONAME_H__
#define __EVENTMIXMODDISPLAYINSEETEDALGONAME_H__

#include <sstream>

#include "mixmod_mvc/Vector.h"
#include "mixmod_mvc/Matrix.h"
#include "mixmod_mvc/Scatter.h"

#include "mixmod_mvc/Util.h"
#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {

//#include "Identifier.h"


class EventMixmodDisplayInsertedAlgoName:public Event {

public :
	EventMixmodDisplayInsertedAlgoName(AlgoName iAlgoName);
	~EventMixmodDisplayInsertedAlgoName();
	string getDisplay()const ;
	bool launchNewEvent()const ;
	void process(TreeItem * treeItem);
	virtual TreeKeyword getKeyword() const;
private :
	AlgoName  _algoName;
};


}
}

#endif
