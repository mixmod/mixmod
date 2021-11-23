/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertCenter.h  description
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
#ifndef __EVENTMIXMODINSERTCENTER_H__
#define __EVENTMIXMODINSERTCENTER_H__


#include "mixmod_mvc/Controller.h"
#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {



template <class T>
class EventMixmodInsertCenter : public Event {

public :
	EventMixmodInsertCenter(int64_t iNbCluster, T** iTabCenter, int64_t iPbDimension,int64_t iPosition);
	~EventMixmodInsertCenter();
	std::string getDisplay() const;
	bool launchNewEvent() const;
	void process(TreeItem* treeItem);
	TreeKeyword getKeyword() const;

private :
	int64_t _nbCluster;
	T** _tabCenter;
	int64_t _position;
	int64_t _pbDimension;
};

template <class T>
EventMixmodInsertCenter<T>::EventMixmodInsertCenter(int64_t iNbCluster, T** iTabCenter, int64_t iPbDimension, int64_t iPosition) {
	_nbCluster = iNbCluster;
	_tabCenter = iTabCenter;
	_position = iPosition;
	_pbDimension = iPbDimension;

}


template <class T>
EventMixmodInsertCenter<T>::~EventMixmodInsertCenter() {
}


template <class T>
std::string EventMixmodInsertCenter<T>::getDisplay() const {
	return string();
}


template <class T>
bool EventMixmodInsertCenter<T>::launchNewEvent() const {
	return true;
}


template <class T>
void EventMixmodInsertCenter<T>::process(TreeItem * treeItem) {
	TreeItem * centerItem = treeItem->getChild(_position);
	for (int64_t i=0; i<_nbCluster; ++i) {
		_controller->insertChild(centerItem,i,_tabCenter[i]);
	}

}


template <class T>
TreeKeyword EventMixmodInsertCenter<T>::getKeyword() const {
	return TreeInitCenter;
}





}
}

#endif
