/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMWeightModifier.h  description
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
#ifndef __GUIM_WEIGHT_MODIFIER_H__
#define __GUIM_WEIGHT_MODIFIER_H__

#include <QGridLayout>

#include "GUIMAbstractModifier.h"
#include "GUIMTextEntryWidget.h"
#include "GUIMFilenameValidator.h"
#include "MVCRootTreeItem.h"


class GUIMWeightModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :

	GUIMWeightModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*,const QModelIndex&, QWidget* );
	virtual ~GUIMWeightModifier();

	virtual void init() {};

private slots :

	virtual void ok();
	virtual void discard();
	virtual void noWeight();
	void setFilename();
	void verifyText( const QString& );

private :

	//data
	int _fixedWidth ;
	QPushButton* _bDefault ;
	QGridLayout* _grid ;
	GUIMFilenameValidator* _validatorFilename ;
	int _nbFilename ;
	QLabel* _labelFilename ;
	QLineEdit* _filename ;
	QAbstractButton* _bFilename ;
	QLabel* _labelValidator ;
	QString TEXT_VALIDATOR ;
};

#endif // __GUIM_WEIGHT_MODIFIER_H__
