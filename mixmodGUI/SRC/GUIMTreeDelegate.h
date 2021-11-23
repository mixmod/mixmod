/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTreeDelegate.h  description
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
#ifndef __GUIM_TREEDELEGATE_H__
#define __GUIM_TREEDELEGATE_H__

#include <QItemDelegate>
#include <QModelIndex>

#include "GUIMAction.h"
#include "GUIMMetaData.h"
#include "GUIUtil.h"

class GUIMAbstractModifier ;

class GUIMTreeDelegate : public QItemDelegate {
	Q_OBJECT

public :

	GUIMTreeDelegate( QObject* = NULL );
	~GUIMTreeDelegate();

	void paint( QPainter*, const QStyleOptionViewItem&, const QModelIndex& ) const ;

	QWidget *createEditor( QWidget*, const QStyleOptionViewItem&, const QModelIndex& ) const ;

	void setEditorData( QWidget*, const QModelIndex& ) const ;
	void setModelData( QWidget*, QAbstractItemModel*, const QModelIndex& ) const ;

	void updateEditorGeometry(QWidget*, const QStyleOptionViewItem&, const QModelIndex& ) const ;

	QSize sizeHint( const QStyleOptionViewItem&, const QModelIndex& ) const ;

private slots :

	void privateCommit( GUIMAbstractModifier* ) ;

signals :

	void throwOutputToCLean();
};

QModelIndex getIndex(QModelIndex refIndex, QList<int> positions);

void getParentAndPosition(QModelIndex refIndex, QList<int> positions, QModelIndex & parent, int & pos);

#endif // __GUIM_TREEDELEGATE_H__
