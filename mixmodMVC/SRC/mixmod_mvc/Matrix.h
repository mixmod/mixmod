/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/Matrix.h  description
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
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cstddef>
#include <string>
#include <ostream>
#include <stdint.h>

namespace XEM {
namespace MVC {


template < class T>
class Matrix {

public:
	Matrix();
	Matrix(T** iTabValue, int64_t iPbDimension);
	virtual ~Matrix();

	virtual std::ostream& edit( std::ostream& ) const ;

protected:
	// data
	T** _tabValue;
	int64_t _pbDimension;
};
// using operator << with matrix
std::ostream & operator<<( std::ostream&, const Matrix<int64_t>& );
std::ostream & operator<<( std::ostream&, const Matrix<double>& );


template < class T>
Matrix<T>::Matrix() {
	_tabValue= NULL;
	_pbDimension = 0;
}

template < class T>
Matrix<T>::Matrix(T** iTabValue, int64_t iPbDimension) {
	_tabValue = iTabValue;
	_pbDimension = iPbDimension;
}

template < class T>
Matrix<T>::~Matrix() {
	if (_tabValue) {
		_tabValue = NULL;
	}
}

template < class T>
std::ostream & Matrix<T>::edit(std::ostream & flux) const {
	for( int64_t i = 0 ; i < _pbDimension ; ++i ) {
		for( int64_t j = 0 ; j < _pbDimension ; ++j ) {
			flux << _tabValue[i][j] << " ";
		}
		flux << "\n \t " ;
	}
	//flux << std::endl ;

	return flux ;
}


}
}

#endif
