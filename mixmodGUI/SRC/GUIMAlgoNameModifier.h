/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAlgoNameModifier.h  description
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
#ifndef __GUIM_ALGONAME_MODIFIER_H__
#define __GUIM_ALGONAME_MODIFIER_H__

#include <QGridLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>

#include "GUIMAbstractModifier.h"
#include "MVCRootTreeItem.h"

class GUIMAlgoNameModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :

	GUIMAlgoNameModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*, const QModelIndex& , QWidget* );
	virtual ~GUIMAlgoNameModifier();

	virtual void init() ;

private slots :

	void ok();
	void discard();

protected :

	QGridLayout* _grid ;

	QGroupBox* _group ;

	QRadioButton* _mapButton ;
	QRadioButton* _emButton ;
	QRadioButton* _cemButton ;
	QRadioButton* _semButton ;
	QRadioButton* _mButton ;

	bool _isMAP ;
	bool _isEM ;
	bool _isCEM ;
	bool _isSEM ;
	bool _isM ;
};

#endif // __GUIM_ALGONAME_MODIFIER_H__
