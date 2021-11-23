/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItem.h  description
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
#ifndef ___MVC_MODEL_ITEM_H__
#define ___MVC_MODEL_ITEM_H__

#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {


struct no_model_item_exception : public std::exception {
	virtual const char* what() const throw() {
		return "Call bad model item (include missing)";
	}
};

class AbstractModelItem {
public :
	virtual ~AbstractModelItem() ;
	virtual Event* setValue(int64_t) {
		return NULL ;
	}
	virtual Event* insertChild( int64_t ) {
		return NULL ;
	}
	virtual Event* removeChild( int64_t ) {
		return NULL ;
	}
};

template< int64_t Keyword, class T >
class ModelItem : public AbstractModelItem {
public :
	ModelItem( Input* input, const T& value = T() ) : _input(input), _value(value) {
		throw no_model_item_exception() ;
	}

	Event* setValue(int64_t) {
		return NULL ;
	}
	Event* insertChild( int64_t ) {
		return NULL ;
	}
	Event* removeChild( int64_t ) {
		return NULL ;
	}

	Input* _input ;
	T _value ;
};


}
}

#endif
