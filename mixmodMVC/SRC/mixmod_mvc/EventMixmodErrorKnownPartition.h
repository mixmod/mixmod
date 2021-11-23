/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodErrorKnownPartition.h  description
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
#ifndef __EVENTMIXMODERRORKNOWNPARTITION_H__
#define __EVENTMIXMODERRORKNOWNPARTITION_H__

#include "mixmod_mvc/EventMixmodError.h"

namespace XEM {
namespace MVC {



class EventMixmodErrorKnownPartition :public EventMixmodError<string> {

public :
	EventMixmodErrorKnownPartition(string iFilename, Exception* e);
	EventMixmodErrorKnownPartition(string iFilename, IOStreamErrorType e);
	~EventMixmodErrorKnownPartition();
	virtual bool launchError() const;
	TreeKeyword getKeyword() const;
	Exception* getError() const;
	Exception* _error;
};

inline bool EventMixmodErrorKnownPartition::launchError() const {
	return true;
}

inline Exception* EventMixmodErrorKnownPartition::getError() const {
	return _error;
}

}
}

#endif
