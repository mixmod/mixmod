/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMInitParameterModifier.h  description
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
#ifndef __GUIM_INITPARAMETER_MODIFIER_H__
#define __GUIM_INITPARAMETER_MODIFIER_H__

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

#include "GUIMAbstractModifier.h"
#include "GUIMFilenameValidator.h"

class GUIMInitParameterModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :

	GUIMInitParameterModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*,const QModelIndex&, QWidget* );
	virtual ~GUIMInitParameterModifier();

	virtual void init() {};

private slots :

	virtual void ok();
	virtual void discard();

	void setFilename();
	void verifyText( const QString& );

private :

	//data
	QWidget* _widget ;
	int _fixedWidth ;
	QGridLayout* _grid ;
	QLineEdit* _filename;
	QAbstractButton* _bFilename ;
	GUIMFilenameValidator* _validatorFilename ;
	QLabel* _labelValidator ;
	QString TEXT_VALIDATOR ;
};

#endif // __GUIM_INITPARAMETER_MODIFIER_H__
