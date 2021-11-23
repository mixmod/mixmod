/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMProcessModifier.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2015
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
#include "GUIMProcessModifier.h"

GUIMProcessModifier::GUIMProcessModifier( GUIMAbstractModifier* parent )
	: QObject( (QObject*)(parent) ) { /*, _modifier(parent)*/}

GUIMProcessModifier::~GUIMProcessModifier() {
	//_modifier = NULL ;
}

void GUIMProcessModifier::addAction(GUIMAction newAction ) {
	//if( _actions.size() != _values.size() || _values.size() != _positions.size() || _positions.size() != _indexes.size() )
	//throw ;
	//_indexes.append( index );
	_actions.append( newAction );
// _values.append( newValue );
//  _positions.append( pos );

	emit actionAdded( _actions.size() );
}

void GUIMProcessModifier::removeAll() {
	_actions.clear();
}
