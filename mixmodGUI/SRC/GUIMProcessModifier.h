/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMProcessModifier.h  description
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
#ifndef __GUIM_PROCESS_MODIFIER_H__
#define __GUIM_PROCESS_MODIFIER_H__

#include <QList>
#include <QObject>
#include <QVariant>
#include <QHash>
#include <QModelIndex>

#include "GUIMAction.h"

class GUIMAbstractModifier ;

class GUIMProcessModifier : public QObject {
	Q_OBJECT

public :

	GUIMProcessModifier( GUIMAbstractModifier* );
	~GUIMProcessModifier();

	GUIMAction getAction( int pos ) const {
		return _actions[pos] ;
	}
	//  const QVariant& getValue( int pos ) const { return _values[pos] ; }
	//  int getPosition( int pos ) const { return _positions[pos] ; }
	//  const QModelIndex& getIndex( int pos ) const { return _indexes[pos] ; }
	int getNbAction() const {
		return _actions.size() ;
	}

public slots :

	void addAction(GUIMAction);
	void removeAll();

signals :

	void actionAdded( int );

protected :

	//GUIMAbstractModifier* _modifier ;
//          QList<QModelIndex> _indexes;    // indexes on which the action occurs
	QList<GUIMAction> _actions ;    // action type
	//        QList<QVariant> _values ;       // values
	//      QList< int > _positions ;       // to remove and insert actions (-1 for set action)
	// Note : sizes of QList are equal

};

#endif // __GUIM_PROCESS_MODIFIER_H__
