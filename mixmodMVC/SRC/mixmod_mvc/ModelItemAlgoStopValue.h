/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemAlgoStopValue.h  description
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
#ifndef __MODELITEMALGOSTOPVALUE_H__
#define __MODELITEMALGOSTOPVALUE_H__


#include "mixmod_mvc/ModelItem.h"
#include "mixmod_mvc/EventMixmodDisplay.h"

namespace XEM {
namespace MVC {


template< >
class ModelItem<TreeNbIteration, int64_t> : public AbstractModelItem {
public :

	ModelItem();
	ModelItem( Input* iInput, int64_t = defaultNbIteration, int64_t iParentPosition = 0, int64_t iGparentPosition = 0 );
	~ModelItem();

	Event* setValue( int64_t position);
	Event* insertChild( int64_t ) {
		return NULL ;
	}
	Event* removeChild( int64_t ) {
		return NULL ;
	}


private :
	int64_t _nbIteration;
	Input * _input;
	int64_t _position;
	int64_t _gPosition;
};


template< >
class ModelItem<TreeEpsilon, double> : public AbstractModelItem {
public :

	ModelItem();
	ModelItem( Input* iInput, double = defaultEpsilon, int64_t iParentPosition = 0, int64_t iGparentPosition = 0 );
	~ModelItem();

	Event* setValue( int64_t position);
	Event* insertChild( int64_t ) {
		return NULL ;
	}
	Event* removeChild( int64_t ) {
		return NULL ;
	}


private :
	double _epsilon;
	Input * _input;
	int64_t _position;
	int64_t _gPosition;
};




}
}

#endif
