/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/Store.h  description
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
#ifndef ___MVC_STORE_H__
#define ___MVC_STORE_H__

#include <string>
#include <sstream>
#include <iostream>

namespace XEM {
namespace MVC {

struct AbstractStore {
	AbstractStore();
	virtual ~AbstractStore();
	virtual std::string str() const = 0 ;
};

template< class T >
struct Store : public AbstractStore {
public :
	Store( const T& value );
	virtual ~Store();

	std::string str() const ;

private :
	T _value ;
};

template< class T >
Store<T>::Store( const T& value )
	: AbstractStore(), _value(value) {
}

template< class T >
Store<T>::~Store() {
}

template< class T >
inline std::string Store<T>::str() const {
	std::stringstream ss ;
	if( ss.good() )
		ss << _value ;

	return ss.str() ;
}

}
}

#endif
