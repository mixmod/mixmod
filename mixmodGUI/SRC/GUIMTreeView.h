/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTreeView.h  description
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
#ifndef __GUIM_TREE_VIEW_H__
#define __GUIM_TREE_VIEW_H__

#include <QTreeView>
#include <QMouseEvent>
#include <QMenu>

class GUIMTreeView : public QTreeView {
	Q_OBJECT

public :

	GUIMTreeView( QWidget* = NULL );
	~GUIMTreeView();

protected :

	virtual void mousePressEvent( QMouseEvent* );
	virtual void mouseDoubleClickEvent( QMouseEvent* );
	virtual void keyPressEvent ( QKeyEvent * );

public slots :

	void menuInsert();
	void menuDelete();
	void menuSetValue();
	void menuInsertRemoveChild();

private :

	QMenu* _menu ;
	QAction* _insert ;
	QAction* _delete ;
	QAction* _setValue ;
	QAction* _insertRemoveChild ;

signals :

	void cleanOutput();
	void addGraphic(int indexGraphic, int indexVariable);
	void deleteGraphic(int);
};

#endif // __GUIM_TREE_VIEW_H__
