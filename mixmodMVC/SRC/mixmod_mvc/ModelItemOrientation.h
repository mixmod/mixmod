/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemOrientation.h  description
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
#ifndef __MODELITEMINITORIENTATION_H__
#define __MODELITEMINITORIENTATION_H__

#include "mixmod_mvc/ModelItem.h"
#include "mixmod_mvc/EventMixmodDisplay.h"

namespace XEM {
namespace MVC {

template< >
class ModelItem<TreeInitParameterOrientation, double> : public AbstractModelItem {

public :

	ModelItem();
	ModelItem( Input* iInput, double ** iTabValue, int64_t iPosition );
	~ModelItem();

	Event* setValue( int64_t position);
	Event* insertChild( int64_t position);
	Event* removeChild( int64_t position);


private :

	double** _tabValue;
	Input * _input;
	int64_t _position;
};

}
}

#endif
