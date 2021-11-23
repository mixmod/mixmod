/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTextEntryWidget.h  description
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
#ifndef __GUIM_TEXTENTRY_WIDGET_H__
#define __GUIM_TEXTENTRY_WIDGET_H__

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QAbstractButton>
#include <QString>

#include "GUIMAbstractModifier.h"
#include "GUIMFilenameValidator.h"

enum Parameter {
    ParamPartition,
    ParamInit
};

class GUIMTextEntryWidget : public QWidget {

	Q_OBJECT

public :

	// function
	GUIMTextEntryWidget( QWidget* );
	~GUIMTextEntryWidget();

public slots :

	void setFilename();
	void setFilenameParameter();
	void verifyText(const QString &);

public :

	// data
	QLabel* _labelFilename ;
	QLineEdit* _filename ;
	GUIMFilenameValidator* _validatorFilename ;
	QAbstractButton* _bFilename ;
	QLabel* _labelValidator ;
	QString TEXT_VALIDATOR ;
	Parameter _parameter;
};

#endif // __GUIM_TEXTENTRY_WIDGET_H__
