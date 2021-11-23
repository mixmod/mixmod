/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/Vector.h  description
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
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstddef>
#include <string>
#include <ostream>
#include <stdint.h>

namespace XEM {
namespace MVC {

template< class T >
class Vector {

public :

	template< class U > friend std::ostream & operator<<(std::ostream & flux,Vector<U> valueVector);

	Vector();
	Vector(T* iValueVector, int64_t sizeVector);
	~Vector();

private :
	T* _valueVector;
	int64_t _sizeVector;
};


template< class T >
Vector<T>::Vector() {
	_sizeVector = 0;
	_valueVector = NULL;
}

template< class T >
Vector<T>::Vector(T* iValueVector,int64_t sizeVector) {
	_valueVector = iValueVector;
	_sizeVector = sizeVector;
}


template< class T >
Vector<T>:: ~Vector() {
	if (_valueVector) {
		//delete [] _valueVector;
		_valueVector = NULL;
	}
}

template< class T >
std::ostream & operator<<(std::ostream & flux,Vector<T> vector) {
	int64_t i;

	for (i=0; i<vector._sizeVector; ++i) {
		flux<<vector._valueVector[i]<<"\t";
	}
	return flux ;
}

}
}

#endif
