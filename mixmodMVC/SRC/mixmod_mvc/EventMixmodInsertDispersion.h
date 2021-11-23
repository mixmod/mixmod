/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertDispersion.h  description
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
#ifndef __EVENTMIXMODINSERTDISPERSION_H__
#define __EVENTMIXMODINSERTDISPERSION_H__


#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {



class EventMixmodInsertDispersion : public Event {

public :
	EventMixmodInsertDispersion(int64_t iNbCluster, XEM::Matrix** iTabSigma, int64_t iPbDimension,int64_t iPosition);
	~EventMixmodInsertDispersion();
	std::string getDisplay() const;
	bool launchNewEvent() const;
	void process(TreeItem* treeItem);
	TreeKeyword getKeyword() const;

private :
	int64_t _nbCluster;
	XEM::Matrix** _tabSigma;
	int64_t _position;
	int64_t _pbDimension;
};


class EventMixmodInsertDispersionB : public Event {

public :
	EventMixmodInsertDispersionB(int64_t iNbCluster, double*** iTabScatter, int64_t iPbDimension,int64_t iPosition);
	~EventMixmodInsertDispersionB();
	std::string getDisplay() const;
	bool launchNewEvent() const;
	void process(TreeItem* treeItem);
	TreeKeyword getKeyword() const;

private :
	int64_t _nbCluster;
	double*** _tabScatter;
	int64_t _position;
	int64_t _pbDimension;
};








}
}

#endif
