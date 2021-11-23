/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMKnownPartitionModifier.h  description
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
#ifndef __GUIM_KNOWNPARTITION_MODIFIER_H__
#define __GUIM_KNOWNPARTITION_MODIFIER_H__

#include <QGridLayout>
#include "GUIMAbstractModifier.h"
#include "GUIMTextEntryWidget.h"
#include "GUIMFilenameValidator.h"

class GUIMKnownPartitionModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :

	GUIMKnownPartitionModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*,const QModelIndex&, QWidget* );
	virtual ~GUIMKnownPartitionModifier();

	virtual void init() {};

private slots :

	virtual void ok();
	virtual void discard();
	virtual void noPartition();

	void verifyAllText( const QString& );

private :

	//data
	int _fixedWidth ;
	QPushButton* _bNoPartition ;
	QGridLayout* _grid ;
	GUIMTextEntryWidget* _entry;
	QValidator * _validatorXML;
	int _nbFilename ;
};

#endif // __GUIM_KNOWNPARTITION_MODIFIER_H__
