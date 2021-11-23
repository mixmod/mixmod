/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTreeView.cpp  description
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
#include "GUIMTreeView.h"
#include <QCursor>

#include "GUIMTreeDelegate.h"
#include "GUIMTreeModel.h"
#include <QItemSelectionRange>
#include <QMessageBox>

GUIMTreeView::GUIMTreeView( QWidget* parent )
	: QTreeView( parent ),
	  _insert( NULL ), _delete( NULL ), _setValue( NULL ), _insertRemoveChild( NULL ) {
}

GUIMTreeView::~GUIMTreeView() {
}

void GUIMTreeView::keyPressEvent ( QKeyEvent * event ) {
	QTreeView::keyPressEvent( event );
	QModelIndex index = currentIndex();
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	if( event->key() == Qt::Key_Delete ) {
		Autorization autorization = TreeItemIsModifiable(index);
		if (autorization.toDelete) {
			menuDelete();
		}
	}
}


void GUIMTreeView::mouseDoubleClickEvent( QMouseEvent* event ) {
	QTreeView::mouseDoubleClickEvent( event );
	QModelIndex index = currentIndex();
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	if( event->button() == Qt::LeftButton && item->getKeyword()==XEM::MVC::TreeInput && TreeItemIsColored(TreeItemIsModifiable(index))) {
// test if we activate or not the actions

		QModelIndex index = currentIndex();

		// menu
		_menu = new QMenu( this );
		_menu->move( QCursor::pos().x(), QCursor::pos().y() );
		_menu->setStyleSheet("QMenu {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);} ");

		// set
		_setValue = _menu->addAction( tr("Set Value") );
		connect( _setValue, SIGNAL( triggered() ), this, SLOT( menuSetValue() ) );

		Autorization autorization = TreeItemIsModifiable(index);
		_setValue->setVisible( autorization.toSet );

		_menu->show();
	}
	else if (event->button() == Qt::LeftButton) {
		switch( item->getKeyword() ) {
		case XEM::MVC::TreeQuantitativeHistogram :
		case XEM::MVC::TreeQualitativeDiagram :
		case XEM::MVC::TreeQualitativeBoxes :
			emit addGraphic(index.row(), item->getGdParentPosition());
			break;
		case XEM::MVC::TreeQuantitativePoint :
		case XEM::MVC::TreeQuantitativeClass : {
			if ((static_cast<GUIMTreeModel *>(this->model()))->getClusteringMain(0)->getInput()->getPbDimension() > 1 ) {
				emit addGraphic(index.row(), item->getGdParentPosition());
			}
			break;
		}
		default:
			break;
		}
	}
}


void GUIMTreeView::mousePressEvent( QMouseEvent* event ) {
	QTreeView::mousePressEvent( event );
	QModelIndex index = currentIndex();
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	if( event->button() == Qt::RightButton && TreeItemIsColored(TreeItemIsModifiable(index))) {
// test if we activate or not the actions

		QModelIndex index = currentIndex();

		// menu
		_menu = new QMenu( this );
		_menu->move( QCursor::pos().x(), QCursor::pos().y() );
		_menu->setStyleSheet("QMenu {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);} ");


		//modify
		_insertRemoveChild = _menu->addAction( tr("Insert/Remove") );
		connect( _insertRemoveChild, SIGNAL( triggered() ), this, SLOT( menuInsertRemoveChild() ) );
		// insert
		_insert = _menu->addAction( tr("Insert") );
		connect( _insert, SIGNAL( triggered() ), this, SLOT( menuInsert() ) );
		// set
		_setValue = _menu->addAction( tr("Set Value") );
		// remove
		_delete = _menu->addAction( tr("Delete") );
		connect( _delete, SIGNAL( triggered() ), this, SLOT( menuDelete() ) );

		connect( _setValue, SIGNAL( triggered() ), this, SLOT( menuSetValue() ) );

		Autorization autorization = TreeItemIsModifiable(index);
		_insertRemoveChild->setVisible( autorization.toInsertRemove );
		_insert->setVisible( autorization.toInsert );
		_setValue->setVisible( autorization.toSet );
		_delete->setVisible( autorization.toDelete );

		_menu->show();
	}
}

void GUIMTreeView::menuInsertRemoveChild() {
	QModelIndex index = currentIndex();
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	switch( item->getKeyword() ) {
	case XEM::MVC::TreeKnownPartition :
	case XEM::MVC::TreeStopRuleValue :
	case XEM::MVC::TreeModel :
	case XEM::MVC::TreeInitStopRule :
	case XEM::MVC::TreeCriterion :
		setCurrentIndex(index);
		edit( currentIndex() );
		break ;
	default :
		break ;
	}
}

void GUIMTreeView::menuInsert() {
	QModelIndex index = currentIndex();
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	switch( item->getKeyword() ) {
	case XEM::MVC::TreeKnownPartition :
	case XEM::MVC::TreeStopRuleValue :
	case XEM::MVC::TreeCriterion :
	case XEM::MVC::TreeNbAlgo :
		setCurrentIndex(index);
		edit( currentIndex() );
		break ;
	case XEM::MVC::TreeQuantitativePoint :
	case XEM::MVC::TreeQuantitativeClass :
	case XEM::MVC::TreeQuantitativeHistogram :
	case XEM::MVC::TreeQualitativeDiagram :
	case XEM::MVC::TreeQualitativeBoxes :
		emit addGraphic(index.row(), item->getGdParentPosition());
		break;
	default :
		break ;
	}
}

void GUIMTreeView::menuDelete() {
	QModelIndex index = currentIndex();
	int64_t indexRow = index.row();

	//it is neccesary to change the current Index to make it visible for Qt
	QModelIndex parent = index.parent();
	setCurrentIndex(parent);
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	switch(  item->getKeyword() ) {
	case XEM::MVC::TreeNbIteration :
	case XEM::MVC::TreeEpsilon :
	case XEM::MVC::TreeInitEpsilon :
	case XEM::MVC::TreeInitNbIteration :
	case XEM::MVC::TreeModelChild :
	case XEM::MVC::TreeCriterionChild :
	case XEM::MVC::TreeNbAlgoChild :
		model()->removeRow(indexRow, parent );
		break ;
	case XEM::MVC::TreeQuantitativePoint :
	case XEM::MVC::TreeQuantitativeClass :
	case XEM::MVC::TreeQuantitativeHistogram :
	case XEM::MVC::TreeQualitativeDiagram :
	case XEM::MVC::TreeQualitativeBoxes :
		emit deleteGraphic(index.row());
		break;
	case XEM::MVC::TreeOutput :
		GUISettings::outputIsPresent = false;
		emit cleanOutput();
	default :
		break ;
	}
}

void GUIMTreeView::menuSetValue() {
	QModelIndex index = currentIndex();

	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );
	if (item->getKeyword()==XEM::MVC::TreeInput) {
		QMessageBox msgBox;
		msgBox.setText(tr("Do you want to modify the inputs?"));
		msgBox.setInformativeText(tr("Careful, ouputs will be deleted!"));
		msgBox.setStandardButtons(QMessageBox:: Yes|QMessageBox::No);
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);}  QPushButton {background-color:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		int ret = msgBox.exec();

		if (ret==QMessageBox::Yes) {
// 		  	QModelIndex parent = index.parent();
// 			int64_t indexRow = index.row();
			GUISettings::outputIsPresent = false;
			emit cleanOutput();
		}
	}
	else {
		setCurrentIndex(index);
		edit( currentIndex() );
	}
}
