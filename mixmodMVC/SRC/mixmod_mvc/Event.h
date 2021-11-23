/***************************************************************************
							 SRC/GUI/MIXMOD_MVC/Event.h  description
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

#ifndef ___MVC_EVENT_H__
#define ___MVC_EVENT_H__

#include <string>
#include "mixmod_mvc/Util.h"
#include "mixmod_mvc/TreeItem.h"

namespace XEM {
namespace MVC {


class Controller;

class Event {
public:
	Event();
	virtual ~Event();
	virtual TreeKeyword getKeyword() const;
	virtual std::string getDisplay() const = 0;
	virtual bool launchNewEvent() const = 0;
	virtual void process(TreeItem * treeItem) = 0;
	void setControler(Controller * controler);
	virtual bool launchError() const;
	virtual Exception* getError() const;
protected:
	Controller * _controller;
};

inline Event::Event()
	: _controller(NULL) {
}

inline void Event::setControler(Controller * controler) {
	_controller = controler;
}

inline bool Event::launchError() const {
	return false;
}

inline Exception* Event::getError() const {
	return &NOERROR;
}

}
}

#endif
