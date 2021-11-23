/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemScatter.cpp  description
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
#include "mixmod_mvc/ModelItemScatter.h"
#include "mixmod_mvc/EventMixmodSetInitName.h"
#include "mixmod_mvc/EventMixmodDisplayScatter.h"
#include "mixmod_mvc/Util.h"
//#include "BinaryData.h"

namespace XEM {
namespace MVC {

ModelItem<TreeInitScatterChild, double>::ModelItem( Input* iInput, double** iTabValue, int64_t iPosition) {
	_tabValue = iTabValue;
	_input = iInput;
	_position = iPosition;
}

ModelItem<TreeInitScatterChild, double> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitScatterChild, double> ::setValue( int64_t /*position*/) {
	return NULL ;
}

Event* ModelItem<TreeInitScatterChild, double> ::insertChild( int64_t /*position*/) {
	int64_t * tabModality = ((BinaryData*) _input->getData())->getTabNbModality();
	Event* eventDisplay = new EventMixmodDisplayScatter(_tabValue,_input->getPbDimension(),tabModality);

	return eventDisplay ;
}

Event* ModelItem<TreeInitScatterChild, double> ::removeChild(int64_t /*position*/) {
	return NULL ;
}

}
}
