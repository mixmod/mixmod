/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTreeDelegate.cpp  description
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
#include "GUIMTreeDelegate.h"

#include "mixmod_mvc/TreeItem.h"
#include "GUIMTreeModel.h"
#include "GUIMAlgoNameModifier.h"
#include "GUIMAbstractModifier.h"
#include "GUIMCriteriaModifier.h"
#include "GUIMInitModifier.h"
#include "GUIMCriterionChildModifier.h"
#include "GUIMKnownPartitionModifier.h"
#include "GUIMNbStrategyTryModifier.h"
#include "GUIMModelModifier.h"
#include "GUIMStopRuleModifier.h"
#include "GUIMStopRuleValueModifier.h"
#include "GUIMAlgoModifier.h"
#include "GUIMWeightModifier.h"
#include "GUIMOutputModifier.h"
#include "GUIMInitParameterModifier.h"
#include "GUIMParameterInInitModifier.h"

#include "GUIMTreeModel.h"
#include "mixmod/Utilities/Error.h"
#include <QStyleOption>
#include <QtGui>

GUIMTreeDelegate::GUIMTreeDelegate( QObject* parent )
	: QItemDelegate(parent) {
}

GUIMTreeDelegate::~GUIMTreeDelegate() {
}

void GUIMTreeDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const {
// Called whenever the view needs to repaint an item

	Autorization autorization = TreeItemIsModifiable(index);
	if (index.column()==0 && TreeItemIsColored(autorization)) {
		QStyleOptionViewItem myOption = option;
		myOption.palette.setColor(QPalette::Normal, QPalette::Text,QColor(70,90,200,255));
		//myOption.font.setBold(true);
		QItemDelegate::paint( painter, myOption, index );
	}
	else {
		QItemDelegate::paint( painter, option, index );
	}
}

QWidget* GUIMTreeDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem&
        option, const QModelIndex& index ) const {
// qDebug("createEditor's calling");
// Returns the editor to be used for editing the data item with the given index
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	GUIMAbstractModifier* creator = NULL ;
	XEM::MVC::RootTreeItem* root = static_cast<const GUIMTreeModel*>(index.model())->root();
	if (GUISettings::outputIsPresent && item->getKeyword() != XEM::MVC::TreeOutput)
		return creator;

	switch( item->getKeyword() ) {
	case XEM::MVC::TreeNbAlgo : {
		if (TreeItemIsColored(TreeItemIsModifiable(index))) {
			creator = new GUIMAlgoModifier(root->getProjectType(),
			                               root->getDataType(),
			                               item,
			                               index,
			                               parent
			                              );
			connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
			         this, SLOT( privateCommit(GUIMAbstractModifier*) )  );
		}
	}
	break ;
	case XEM::MVC::TreeNbStrategyTry : {
		if (TreeItemIsColored(TreeItemIsModifiable(index))) {
			creator = new GUIMNbStrategyTryModifier(
			    root->getProjectType(),
			    root->getDataType(),
			    item,
			    index,
			    parent
			);
			connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
			         this, SLOT( privateCommit(GUIMAbstractModifier*) )
			       );
		}
	}
	break ;
	case XEM::MVC::TreeDataWeight: {
		creator = new GUIMWeightModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeInitType : {
		creator = new GUIMInitModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeInitEpsilon :
	case XEM::MVC::TreeInitNbTry :
	case XEM::MVC::TreeInitNbIteration : {
		creator = new GUIMParameterInInitModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeInitStopRule :
	case XEM::MVC::TreeStopRuleValue : {
		creator = new GUIMStopRuleModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeEpsilon :
	case XEM::MVC::TreeNbIteration : {
		creator = new GUIMStopRuleValueModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeOutput : {
		if (TreeItemIsModifiable(index).toSet ) {
			creator = new GUIMOutputModifier(
			    root->getProjectType(),
			    root->getDataType(),
			    item,
			    index,
			    parent
			);
			connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
			         this, SLOT( privateCommit(GUIMAbstractModifier*) ) );
		}
	}
	break ;
	case XEM::MVC::TreeCriterion : {
		creator = new GUIMCriteriaModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeCriterionChild : {
		creator = new GUIMCriterionChildModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeKnownPartition :
	case XEM::MVC::TreeInitPartition : {
		creator = new GUIMKnownPartitionModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeInitParameter : {
		creator = new GUIMInitParameterModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeModel : {
		creator = new GUIMModelModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
	}
	break ;
	case XEM::MVC::TreeAlgoName :
		creator = new GUIMAlgoNameModifier(
		    root->getProjectType(),
		    root->getDataType(),
		    item,
		    index,
		    parent
		);
		connect( creator, SIGNAL( closed(GUIMAbstractModifier*) ),
		         this, SLOT( privateCommit(GUIMAbstractModifier*) )
		       );
		break ;
	case XEM::MVC::TreeSubDimension :
		return QItemDelegate::createEditor( parent, option, index );
		break ;
	default :
		break ;
	}
// 	if (root->getNbChild()>1 && item->getKeyword()!=TreeInput && item->getKeyword()!=TreeOutput)
// 		connect(creator, SIGNAL(verifOutputToClean()), this, SIGNAL(throwOutputToCLean()));

	return creator ;
}

void GUIMTreeDelegate::setEditorData( QWidget* editor, const QModelIndex& index ) const {
// qDebug( "setEditorData's calling" );
// Sets the contents (default values) of the given editor to the data for the item at the given index

	/*XEMMVCTreeItem* item = reinterpret_cast<XEMMVCTreeItem*>( index.internalPointer() );

	switch( item->getKeyword() ){
		case TreeEpsilon :
		case TreeNbIteration :
			QItemDelegate::setEditorData( editor, index );
		break ;
		default :
		break ;
	}*/

// qDebug( "setEditorData End" );
}

void GUIMTreeDelegate::setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
// qDebug( "setModelData's calling" );
// Sets the data for the item at the given index in the model from the contents of the given editor
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );
	GUIMAbstractModifier* creator = qobject_cast<GUIMAbstractModifier*>( editor );

	try {
		if( creator && creator->isValidate() && item->getKeyword() != XEM::MVC::TreeOutput ) {
			for( int i = 0 ; i < creator->getNbAction() ; ++i ) {
				GUIMAction action = creator->getAction(i);
				switch( action._type ) {
				case GUIMInsert : {
					// cout<<"GUIInsert"<<endl;
					if (action._positions.size() != 1) {
						throw;
						// cas non prévu pour l'insant
						//Si on rencontre une telle situation, il faut coder une fonction getPositionAndParent
					}
					bool success = false ;
					QModelIndex index = action._index;
					if (action._level) {
						for (int j=0; j<	action._level; ++j) {
							index=index.parent();
						}
					}
					success = model->insertRow( action._positions[0], index);
				}
				break ;
				case GUIMRemove : {
					//cout<<"GUIRemove"<<endl;
					bool success = false ;
					int pos;
					QModelIndex parent;
					QModelIndex index = action._index;
					if (action._level) {
						for (int j=0; j<	action._level; ++j) {
							index=index.parent();
						}
					}

					getParentAndPosition(index, action._positions, parent, pos);
					//XEMMVCTreeItem* parentItem = reinterpret_cast<XEMMVCTreeItem*>( parent.internalPointer() );
					model->removeRow(pos, parent);
				}
				break ;
				case GUIMSet : {
					// cout<<"GUISet"<<endl;
					QModelIndex index = action._index;
					if (action._level) {
						for (int j=0; j<	action._level; ++j) {
							index=index.parent();
						}
					}
					QModelIndex setIndex = getIndex(index, action._positions);
					model->setData(setIndex, action._value);
				}
				break ;
				default :
					qWarning( "no action" );
					break ;
				}
			}
		}
		else {
			switch( item->getKeyword() ) {
			case XEM::MVC::TreeSubDimension : {
				QItemDelegate::setModelData( editor, model, index );
			}
			break ;
			case XEM::MVC::TreeOutput : {
				if (creator->isValidate()) {
					GUIMAction action = creator->getAction(0);
					XEM::CriterionName criterionName = action._value.value<XEM::CriterionName>();
					((GUIMTreeModel *)model)->sortOutput( index.row()-1, criterionName);
				}
			}
			break;
			default :
				break ;
			}
		}
		GUISettings::authorizedToClosed = true;

	}
	catch( XEM::Exception* e ) {
		QMessageBox msgBox(QMessageBox::Warning, tr("Warning"), tr( e->what() ),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
		if (item->getKeyword() != XEM::MVC::TreeInitPartition && item->getKeyword() != XEM::MVC::TreeInitParameter && item->getKeyword() != XEM::MVC::TreeInitType) {
			emit const_cast<GUIMTreeDelegate*>(this)->closeEditor( editor );
		}
		else {
			GUISettings::authorizedToClosed = false;
		}
	}
	catch(XEM::IOStreamErrorType& e) {
		QMessageBox msgBox(QMessageBox::Warning, tr("Warning"), tr( XEM::IOStreamErrorTypeToString(e).c_str() ),QMessageBox::Ok );
		msgBox.setStyleSheet("QMessageBox {background: qlineargradient(x1:0.5, y1:0, x2:0.5, y2:1, stop:1 white, stop:0 #a0c8fa);} QPushButton{background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);}");
		msgBox.setWindowIcon(QPixmap(":/logo.jpg"));
		msgBox.exec();
		if (item->getKeyword() != XEM::MVC::TreeInitPartition && item->getKeyword() != XEM::MVC::TreeInitParameter && item->getKeyword() != XEM::MVC::TreeInitType) {
			emit const_cast<GUIMTreeDelegate*>(this)->closeEditor( editor );
		}
		else {
			GUISettings::authorizedToClosed = false;
		}
	}
	emit const_cast<GUIMTreeDelegate*>(this)->closeEditor( editor );
// qDebug( "setModelData End" );
}


void GUIMTreeDelegate::updateEditorGeometry( QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
// qDebug( "updateEditorGeometry's calling" );

	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );

	switch( item->getKeyword() ) {
	case XEM::MVC::TreeSubDimension :
		QItemDelegate::updateEditorGeometry( editor, option, index );
		break ;
	default :
		break ;
	}
// qDebug( "updateEditorGeometry End" );
}

QSize GUIMTreeDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const {
// qDebug( "sizeHint's calling" );
	return QItemDelegate::sizeHint( option, index );
}

void GUIMTreeDelegate::privateCommit( GUIMAbstractModifier* creator ) {
	emit commitData(creator);
}


QModelIndex getIndex(QModelIndex refIndex, QList<int> positions) {
	QModelIndex res;
	if (positions.size() == 0) {
		res = refIndex;
	}
	else {
		const QAbstractItemModel * model = refIndex.model();
		QModelIndex curIndex = refIndex;
		for (int i=0; i<positions.size(); i++) {
			res = model->index(positions[i], 0, curIndex);
			curIndex = res;
		}
	}
	return res;
}


/*
returns pos and parent to call removeRow
*/
void getParentAndPosition(QModelIndex refIndex, QList<int> positions, QModelIndex & parent, int & pos) {
	if (positions.size() == 0) {
		throw;
	}
	else if (positions.size() == 1) {
		parent = refIndex;
		pos = positions[0];
	}
	else {
		QModelIndex curIndex = refIndex;
		const QAbstractItemModel * model = refIndex.model();
		for (int i=0; i<positions.size()-1; i++) {
			parent = model->index(positions[i], 0, curIndex);
			curIndex = parent;
		}
		pos = positions[positions.size()-1]; // the last
	}
}
