/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAbstractModifier.h  description
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
#ifndef __GUIM_ABSTRACT_MODIFIER_H__
#define __GUIM_ABSTRACT_MODIFIER_H__

#include <QWidget>
#include <QVariant>
#include <QPushButton>
#include <QFrame>

#include "GUIMAction.h"
#include "MVCRootTreeItem.h"
#include "GUIMProcessModifier.h"

#include "mixmod_mvc/Util.h"
#include "GUIMixmod.h"
#include <QKeyEvent>

class GUIMAbstractModifier : public QFrame {
	Q_OBJECT

public :

	GUIMAbstractModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*, const QModelIndex& ,QWidget* );
	virtual ~GUIMAbstractModifier();

	bool isValidate() const {
		return _validate ;
	}

	GUIMAction getAction( int pos = 0 ) const {
		return _processor->getAction(pos) ;
	}
	//const QVariant& getVariant( int pos = 0 ) const { return _processor->getValue(pos) ; }
	//int getPosition( int pos = 0 ) const { return _processor->getPosition(pos) ; }
	//const QModelIndex&  getIndex( int pos = 0 ) const { return _processor->getIndex(pos) ; }
	int getNbAction() const {
		return _processor->getNbAction() ;
	}

public slots :

	void confirm();
	void cancel();

protected slots :

	virtual void ok() = 0 ;
	virtual void discard() = 0 ;

signals :

	void closed( GUIMAbstractModifier* );
	//void verifOutputToClean();

protected :

	// function
	virtual void init() = 0 ;

	// data

	XEM::MVC::RootTreeItem::ProjectType _projectType ;
	XEM::MVC::RootTreeItem::DataType _dataType ;
	XEM::MVC::TreeItem * _item ;
	QModelIndex _index;

	GUIMProcessModifier* _processor ;

	bool _validate ;

	QPushButton* _ok ;
	QPushButton* _cancel ;
};

#endif // __GUIM_ABSTRACT_MODIFIER_H__
