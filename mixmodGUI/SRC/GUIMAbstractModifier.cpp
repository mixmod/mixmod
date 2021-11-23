/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAbstractModifier.cpp  description
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
#include "GUIMAbstractModifier.h"
#include <QKeySequence>

GUIMAbstractModifier::GUIMAbstractModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* item, const QModelIndex& index , QWidget* /*parent*/ )
	: QFrame( NULL/*parent*/ ), _projectType(type), _dataType(dataType), _item(item ), _index(index),
	  _processor( new GUIMProcessModifier(this) ),
	  _validate(false),
	  _ok( new QPushButton( tr("OK"), this ) ), _cancel( new QPushButton( tr("Cancel"), this ) ) {
	QLinearGradient gradient(QPointF(0,200), QPointF(400,300));
	gradient.setColorAt(1, QColor(140,180,250,240));
	gradient.setColorAt(0, Qt::white);
	QBrush back = QBrush(gradient);

	QPalette pal = palette();
	pal.setBrush(QPalette::Background, back);
	pal.setBrush(QPalette::Base, back);
	//setAutoFillBackground(true);

	setPalette(pal);
	setStyleSheet("QPushButton {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff)};");
	setWindowIcon(QPixmap(":/logo.png"));
	//_ok->setShortcut(Qt::Key_Enter);
	_ok->setShortcut(Qt::Key_Return);
	setAttribute( Qt::WA_DeleteOnClose );
	connect( _ok, SIGNAL( released() ), this , SLOT( ok() ) );
	connect( _cancel, SIGNAL( released() ), this , SLOT( discard() ) );
	setWindowModality (Qt::ApplicationModal);
}

GUIMAbstractModifier::~GUIMAbstractModifier() {
	_item = NULL ;
	if (_ok)
		delete _ok;
	if (_cancel)
		delete _cancel;
}

void GUIMAbstractModifier::confirm() {
	_validate = true ;
	//emit verifOutputToClean();
	emit closed(this);
}

void GUIMAbstractModifier::cancel() {
	_validate = false ;
	emit closed(this);
}
