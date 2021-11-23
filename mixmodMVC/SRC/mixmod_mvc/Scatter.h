/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/Scatter.h  description
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
#ifndef __SCATTER_H__
#define __SCATTER_H__

#include <cstddef>
#include <string>
#include <ostream>
#include "mixmod_mvc/Matrix.h"
#include <stdint.h>

namespace XEM {
namespace MVC {

template < class T> // avec T = U**
class Scatter:public Matrix<T> {

public :
	Scatter();
	Scatter(T** iTabScatter, int64_t * iTabModality, int64_t iPbDimension);
	~Scatter();

	virtual std::ostream & edit( std::ostream & flux ) const ;

private :
	// data
	int64_t * _tabModality;
};


template < class T >
Scatter<T>::Scatter():Matrix<T>() {
	_tabModality = NULL;
}


template < class T >
Scatter<T>::Scatter(T** iTabScatter, int64_t * iTabModality, int64_t iPbDimension):Matrix<T>(iTabScatter,iPbDimension) {
	_tabModality = iTabModality;
}


template < class T >
Scatter<T>::~Scatter() {
	if (_tabModality) {
		_tabModality = NULL;
	}

}


template < class T >
std::ostream & Scatter<T>::edit( std::ostream & flux ) const {
	for( int64_t j = 0 ; j < this->_pbDimension ; ++j ) {
		for( int64_t h = 0 ; h < this->_tabModality[j] ; ++h ) {
			flux << this->_tabValue[j][h] << " " ;
		}
		flux << "\n" ;
	}

	flux << std::endl ;

	return flux ;
}

}
}

#endif
