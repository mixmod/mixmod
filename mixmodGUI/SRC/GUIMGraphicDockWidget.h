/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicDockWidget.h  description
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

#ifndef GUIMGRAPHICDOCKWIDGET_H
#define GUIMGRAPHICDOCKWIDGET_H

#include <QDockWidget>
#include <QCloseEvent>
#include <QObject>

class GUIMGraphicDockWidget : public QDockWidget {

	Q_OBJECT

public :

	GUIMGraphicDockWidget(const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~GUIMGraphicDockWidget();

signals:

	void dockToClose();

protected :

	virtual void closeEvent(QCloseEvent* event);
};

#endif // GUIMGRAPHICDOCKWIDGET_H
