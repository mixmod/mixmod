/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemInitDimension.cpp  description
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
#include "mixmod_mvc/ModelItemInitDimension.h"
#include "mixmod_mvc/EventMixmodInsertSubDim.h"
#include "mixmod_mvc/EventMixmodSetModelChild.h"
#include "mixmod_mvc/EventMixmodDisplaySubDim.h"
#include "mixmod_mvc/NoEvent.h"

namespace XEM {
namespace MVC {



ModelItem<TreeInitParameterDimension, int64_t>::ModelItem( Input* iInput, int64_t iSubDim) {
	_subDim = iSubDim;
	_input = iInput;
}


ModelItem<TreeInitParameterDimension, int64_t> ::~ModelItem() {
	_input = NULL ;
}


Event* ModelItem<TreeInitParameterDimension, int64_t> ::setValue( int64_t /*position*/) {
	return NULL ;
}


Event* ModelItem<TreeInitParameterDimension, int64_t> ::insertChild( int64_t /*position*/) {
	Event* eventMixmodInsertSubDim= new EventMixmodDisplaySubDim(_subDim);

	return eventMixmodInsertSubDim ;
}

Event* ModelItem<TreeInitParameterDimension, int64_t> ::removeChild(int64_t /*position*/) {
	return NULL ;
}


}
}
