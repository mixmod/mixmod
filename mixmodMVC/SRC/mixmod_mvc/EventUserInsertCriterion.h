/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventUserInsertCriterion.h  description
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
#ifndef __EVENTUSERINSERTCRITERIONCHILD_H__
#define __EVENTUSERINSERTCRITERIONCHILD_H__

#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {


class EventUserInsertCriterion : public Event {

public :
	EventUserInsertCriterion();
	EventUserInsertCriterion(CriterionName iCriterion, int64_t position);
	~EventUserInsertCriterion();
	void process(TreeItem* treeItem);
	std::string getDisplay() const ;
	bool launchNewEvent() const  ;
private :
	CriterionName _criterionName;
	int64_t _position;

};




}
}

#endif
