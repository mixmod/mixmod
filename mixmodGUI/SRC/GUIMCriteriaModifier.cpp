/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMCriteriaModifier.cpp  description
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
#include "GUIMCriteriaModifier.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

GUIMCriteriaModifier::GUIMCriteriaModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* item,const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, item, index, parent ),
	  _bicButton( NULL ),
	  _cvButton ( NULL ),
	  _iclButton( NULL ),
	  _necButton( NULL ),
	  _dcvButton( NULL ),
	  _hasBIC( false ), _posBIC(0),
	  _hasNEC( false ), _posNEC(0),
	  _hasICL( false ), _posICL(0),
	  _hasDCV( false ), _posDCV(0),
	  _hasCV ( false ), _posCV (0) {
	init();

	setWindowTitle( QObject::tr("Criteria") );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_grid = new QGridLayout( this );
	int hPos = 0 ;

	_group = new QGroupBox( this );
	_group->setStyleSheet( "background-color:white" );

	QVBoxLayout *vbox = new QVBoxLayout;

	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		_bicButton = new QCheckBox( QString::fromStdString(XEM::CriterionNameToString( XEM::BIC )), this );
		connect( _bicButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		_bicButton->setChecked(_hasBIC);
		vbox->addWidget( _bicButton, hPos++, Qt::AlignLeft );

		_iclButton = new QCheckBox( QString::fromStdString(XEM::CriterionNameToString( XEM::ICL )), this );
		connect( _iclButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		_iclButton->setChecked(_hasICL);
		vbox->addWidget( _iclButton, hPos++, Qt::AlignLeft );

		_necButton = new QCheckBox( QString::fromStdString(XEM::CriterionNameToString( XEM::NEC )), this );
		connect( _necButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		_necButton->setChecked(_hasNEC);
		vbox->addWidget( _necButton, hPos++, Qt::AlignLeft );

	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {

		_cvButton = new QCheckBox( QString::fromStdString(XEM::CriterionNameToString( XEM::CV )), this );
		connect( _cvButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		_cvButton->setChecked(_hasCV);
		vbox->addWidget( _cvButton, hPos++, Qt::AlignLeft );

		_dcvButton = new QCheckBox( QString::fromStdString(XEM::CriterionNameToString( XEM::DCV )), this );
		connect( _dcvButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		_dcvButton->setChecked(_hasDCV);
		vbox->addWidget( _dcvButton, hPos++, Qt::AlignLeft );

		_bicButton = new QCheckBox( QString::fromStdString(XEM::CriterionNameToString( XEM::BIC )), this );
		connect( _bicButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
		_bicButton->setChecked(_hasBIC);
		vbox->addWidget( _bicButton, hPos++, Qt::AlignLeft );
	}

	_group->setLayout( vbox );
	_grid->addWidget( _group, 0, 0, 1, 5 );

	_grid->addWidget( _ok, 1, 3 );

	_grid->addWidget( _cancel, 1, 4 );
}

GUIMCriteriaModifier::~GUIMCriteriaModifier() {
}

void GUIMCriteriaModifier::init() {
	for( int i = 0 ; i < static_cast<int>( _item->getNbChild() ) ; ++i ) {
		if( _item->getChild(i)->toString() == XEM::CriterionNameToString( XEM::BIC ) ) {
			_hasBIC = true ;
			_posBIC = i ;
		}
		else if( _item->getChild(i)->toString() == XEM::CriterionNameToString( XEM::ICL ) ) {
			_hasICL = true ;
			_posICL = i ;
		}
		else if( _item->getChild(i)->toString() == XEM::CriterionNameToString( XEM::NEC ) ) {
			_hasNEC = true ;
			_posNEC = i ;
		}
		else if( _item->getChild(i)->toString() == XEM::CriterionNameToString( XEM::CV  ) ) {
			_hasCV  = true ;
			_posCV  = i ;
		}
		else if( _item->getChild(i)->toString() == XEM::CriterionNameToString( XEM::DCV ) ) {
			_hasDCV = true ;
			_posDCV = i ;
		}
	}
}

void GUIMCriteriaModifier::canConfirm() {
	bool finish = false ;
	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		finish = ( _bicButton->isChecked() ||
		           _iclButton->isChecked() ||
		           _necButton->isChecked() );
	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		finish = ( _cvButton->isChecked() ||
		           _dcvButton->isChecked() || _bicButton->isChecked());
	}
	_ok->setEnabled( finish );
}


void GUIMCriteriaModifier::ok() {
	int cptInsert = 0 ;
	int cptRemove = 0 ;
	int pos = 0 ;
	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {

		bool removeBIC = false ;
		bool removeICL = false ;
		bool removeNEC = false ;

		// BIC
		if( !_hasBIC ) {
			if( _bicButton->isChecked() ) {
				// insert
				GUIMAction insertAction = createInsertAction(_index, pos);
				_processor->addAction(insertAction);

				//set
				QList<int> positions;
				positions.append(pos);
				QVariant value;
				value.setValue<XEM::CriterionName>(XEM::BIC);
				GUIMAction setAction = createSetAction(_index, positions, value);
				_processor->addAction(setAction);

				++pos ;
				++cptInsert ;
			}
		}
		else {
			if( !_bicButton->isChecked() ) {
				removeBIC = true ;
				_posBIC += cptInsert + cptRemove-- ;
			}
			++pos ;
		}
		// ICL
		if( !_hasICL ) {
			if( _iclButton->isChecked() ) {
				// insert
				GUIMAction insertAction = createInsertAction(_index, pos);
				_processor->addAction(insertAction);

				//set
				QList<int> positions;
				positions.append(pos);
				QVariant value;
				value.setValue<XEM::CriterionName>( XEM::ICL );
				GUIMAction setAction = createSetAction(_index, positions, value);
				_processor->addAction(setAction);

				++pos ;
				++cptInsert ;
			}
		}
		else {
			if( !_iclButton->isChecked() ) {
				removeICL = true ;
				_posICL += cptInsert + cptRemove-- ;
			}
			++pos ;
		}
		// NEC
		if( !_hasNEC ) {
			if( _necButton->isChecked() ) {
				// insert
				GUIMAction insertAction = createInsertAction(_index, pos);
				_processor->addAction(insertAction);

				//set
				QList<int> positions;
				positions.append(pos);
				QVariant value;
				value.setValue<XEM::CriterionName>( XEM::NEC );
				GUIMAction setAction = createSetAction(_index, positions, value);
				_processor->addAction(setAction);
				++pos ;
				++cptInsert ;
			}
		}
		else {
			if( !_necButton->isChecked() ) {
				removeNEC = true ;
				_posNEC += cptInsert + cptRemove-- ;
			}
			++pos ;
		}

		// remove at the end
		if( removeBIC ) {
			GUIMAction removeAction = createRemoveAction(_index, _posBIC);
			_processor->addAction(removeAction);
		}
		if( removeICL ) {
			GUIMAction removeAction = createRemoveAction(_index, _posICL);
			_processor->addAction(removeAction);
		}
		if( removeNEC ) {
			GUIMAction removeAction = createRemoveAction(_index, _posNEC);
			_processor->addAction(removeAction);
		}

	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {

		bool removeDCV = false ;
		bool removeCV = false ;
		bool removeBIC = false ;
		// CV
		if( !_hasCV  ) {
			if( _cvButton->isChecked()  ) {
				// insert
				GUIMAction insertAction = createInsertAction(_index, pos);
				_processor->addAction(insertAction);

				//set
				QList<int> positions;
				positions.append(pos);
				QVariant value;
				value.setValue<XEM::CriterionName>(XEM::CV);
				GUIMAction setAction = createSetAction(_index, positions, value);
				_processor->addAction(setAction);

				++pos ;
				++cptInsert ;
			}
		}
		else {
			if( !_cvButton->isChecked()  ) {
				removeCV  = true ;
				_posCV  += cptInsert + cptRemove-- ;
			}
			++pos ;
		}
		// DCV
		if( !_hasDCV ) {
			if( _dcvButton->isChecked()  ) {
				// insert
				GUIMAction insertAction = createInsertAction(_index, pos);
				_processor->addAction(insertAction);

				//set
				QList<int> positions;
				positions.append(pos);
				QVariant value;
				value.setValue<XEM::CriterionName>(XEM::DCV);
				GUIMAction setAction = createSetAction(_index, positions, value);
				_processor->addAction(setAction);

				++pos ;
				++cptInsert ;
			}
		}
		else {
			if( !_dcvButton->isChecked()  ) {
				removeDCV = true ;
				_posDCV += cptInsert + cptRemove-- ;
			}
			++pos ;
		}
		//BIC
		if( !_hasBIC ) {
			if( _bicButton->isChecked() ) {
				// insert
				GUIMAction insertAction = createInsertAction(_index, pos);
				_processor->addAction(insertAction);

				//set
				QList<int> positions;
				positions.append(pos);
				QVariant value;
				value.setValue<XEM::CriterionName>(XEM::BIC);
				GUIMAction setAction = createSetAction(_index, positions, value);
				_processor->addAction(setAction);

				++pos ;
				++cptInsert ;
			}
		}
		else {
			if( !_bicButton->isChecked() ) {
				removeBIC = true ;
				_posBIC += cptInsert + cptRemove-- ;
			}
			++pos ;
		}
		// remove at the end
		if( removeCV  ) {
			GUIMAction removeAction = createRemoveAction(_index, _posCV);
			_processor->addAction(removeAction);
		}
		if( removeDCV ) {
			GUIMAction removeAction = createRemoveAction(_index, _posDCV);
			_processor->addAction(removeAction);
		}
		if( removeBIC ) {
			GUIMAction removeAction = createRemoveAction(_index, _posBIC);
			_processor->addAction(removeAction);
		}
	}

	confirm();
}

void GUIMCriteriaModifier::discard() {
	cancel();
}
