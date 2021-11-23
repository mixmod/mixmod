/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIUtil.h  description
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
#ifndef __GUI_UTIL
#define __GUI_UTIL

#include "mixmod_mvc/TreeItem.h"
#include <QModelIndex>
#include <QString>
#include <QDir>


class GUISettings {
public:
	static bool authorizedToClosed;/*if window is authorized to be closed*/
	static bool outputIsPresent;   /*if ouput is present*/

	//the current directory
	static QDir workDirectory;
};

struct Autorization {
	bool toSet;
	bool toInsertRemove;
	bool toInsert;
	bool toDelete;
};

Autorization TreeItemIsModifiable(QModelIndex ind);

bool TreeItemIsColored(Autorization a);

QString getName(XEM::MVC::TreeItem* item);

#endif
