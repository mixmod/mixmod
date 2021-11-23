/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAction.h  description
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
#ifndef __GUIM_ACTION_H__
#define __GUIM_ACTION_H__
#include <QModelIndex>
#include <QVariant>

enum GUIMActionType {
    GUIMNoAction,
    GUIMInsert,
//	GUIMInsertChild,
    GUIMRemove,
//	GUIMRemoveChild,
    GUIMSet,
//	GUIMSetChild,
//	GUIMSetChildAlgo
};

struct GUIMAction {
	GUIMActionType  _type;      //action type
	QModelIndex     _index;     // reference index
	QList<int>      _positions;  // List of positions
	QVariant        _value;     //not necessary
	int 		  _level;     //level's number to reach a parent
	GUIMAction():_level(0) {}
};

/**
notes :

if _type=GUIMInsert
  Insert a child from _index
  _positions is a list to reach the child to insert from _index
  if there is a third parameter (position), it is the level's number to reach a parent


if _type=GUIMRemove
  Remove a child from _index
  _positions is a list to reach the child to remove from _index
  if there is a third parameter (position), it is the level's number to reach a parent

if _type=GUIMSet
  if _positions is empty :
    Set _value at _index (in this cas the index is already created)
  else
    Set _value at 'position' from _index (this item is not yet created)
    in this case, _positions is a list to reach the good position from index
**/

/*
Examples :
- insert a child to index=i at position=p
  _type = GUIMInsert
  _index = i
  _postion = (p)

- insert a 1rst child of the second child of index=i (the second child of index=i is not yet created)
  _type = GUIMInsert
  _index = i
  _postion = (2;1)

- removet a child to index=i at position=p
  _type = GUIMRemove
  _index = i
  _postion = (p)

- remove the 3rd child of the 2nd child of index=i (the 2nd child of index=i is not yet created)
  _type = GUIMRemove
  _index = i
  _postion = (2;3)

- set value=v to index=i (index is already created)
  _type = GUIMSet
  _index = i
  _position = empty
  _value = v

- set value=v to the child c of index=i (the child c of index=i is not yet created)
  _type = GUIMSet
  _index = i
  _position = (c)
  _value = v

- set value=v to the 1rst child of the 2nd child of index=i (index is not created)
  _type = GUIMSet
  _index = i
  _position = (2;1)
  _value = v
*/

inline GUIMAction createInsertAction(QModelIndex index, int position) {
	GUIMAction insertAction;
	insertAction._type = GUIMInsert;
	insertAction._index = index;
	insertAction._positions.append(position);
	//insertAction._value : none;
	return insertAction;
}

inline GUIMAction createInsertAction(QModelIndex index, int position, int level) {
	GUIMAction insertAction;
	insertAction._type = GUIMInsert;
	insertAction._index = index;
	insertAction._positions.append(position);
	//insertAction._value
	insertAction._level = level;
	return insertAction;
}

inline GUIMAction createRemoveAction(QModelIndex index, int position) {
	GUIMAction removeAction;
	removeAction._type = GUIMRemove;
	removeAction._index = index;
	removeAction._positions.append(position);
	//removeAction._value : none;
	return removeAction;
}

inline GUIMAction createRemoveAction(QModelIndex index, QList<int> positions) {
	GUIMAction removeAction;
	removeAction._type = GUIMRemove;
	removeAction._index = index;
	removeAction._positions = positions;
	//removeAction._value : none;
	return removeAction;
}

inline GUIMAction createRemoveAction(QModelIndex index, QList<int> positions, int level) {
	GUIMAction removeAction;
	removeAction._type = GUIMRemove;
	removeAction._index = index;
	removeAction._positions = positions;
	//insertAction._value
	removeAction._level = level;
	return removeAction;
}

inline GUIMAction createSetAction(QModelIndex index, QList<int> positions, QVariant value) {
	GUIMAction setAction;
	setAction._type = GUIMSet;
	setAction._index = index;
	setAction._positions = positions;
	setAction._value = value;
	return setAction;
}

inline GUIMAction createSetAction(QModelIndex index, QList<int> positions, QVariant value, int level) {
	GUIMAction setAction;
	setAction._type = GUIMSet;
	setAction._index = index;
	setAction._positions = positions;
	setAction._value = value;
	setAction._level = level;
	return setAction;
}

inline GUIMAction createSetAction(QModelIndex index, QVariant value) {
	GUIMAction setAction;
	setAction._type = GUIMSet;
	setAction._index = index;
	//setAction._positions : empty;
	setAction._value = value;
	return setAction;
}

#endif // __GUIM_ACTION_H__
