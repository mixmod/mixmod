/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitProportion.cpp  description
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
#include "mixmod_mvc/ModelItemInitProportion.h"
#include "mixmod_mvc/EventMixmodSetInitName.h"
#include "mixmod_mvc/EventMixmodDisplayProportion.h"
#include "mixmod_mvc/EventMixmodInsertProportion.h"

namespace XEM {
namespace MVC {


ModelItem<TreeInitProportionChild, double>::ModelItem(double iProportionI) {
	_proportionI = iProportionI;
}

ModelItem<TreeInitProportionChild, double> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitProportionChild, double> ::setValue( int64_t /*position*/) {
	return NULL ;
}

Event* ModelItem<TreeInitProportionChild, double> ::insertChild( int64_t /*position*/) {
	Event* eventDisplay = new EventMixmodDisplayProportion(_proportionI);

	return eventDisplay ;
}

Event* ModelItem<TreeInitProportionChild, double> ::removeChild(int64_t /*position*/) {
	return NULL ;
}
}
}
