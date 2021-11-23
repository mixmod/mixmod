/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMCriterionChildModifier.cpp  description
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
#include "GUIMCriterionChildModifier.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

GUIMCriterionChildModifier::GUIMCriterionChildModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeCriterion,const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeCriterion, index, parent ),
	  _bicButton( NULL ),
	  _cvButton ( NULL ),
	  _iclButton( NULL ),
	  _necButton( NULL ),
	  _dcvButton( NULL ),
	  _hasBIC( false ),_isBIC( false ), _posBIC(0),
	  _hasNEC( false ),_isNEC( false ), _posNEC(0),
	  _hasICL( false ),_isICL( false ), _posICL(0),
	  _hasDCV( false ),_isDCV( false ), _posDCV(0),
	  _hasCV ( false ),_isCV ( false ), _posCV (0) {
	init();

	setWindowTitle( QObject::tr("Criteria : ") );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_grid = new QGridLayout( this );
	int hPos = 0 ;

	_group = new QGroupBox( this );
	_group->setStyleSheet( "background-color:white" );

	QVBoxLayout *vbox = new QVBoxLayout;

	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		if( !_hasBIC || _isBIC ) {
			_bicButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::BIC )), this );
			vbox->addWidget( _bicButton, hPos++, Qt::AlignLeft );
			_bicButton->setChecked( _isBIC );
		}
		if( !_hasICL || _isICL ) {
			_iclButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::ICL )), this );
			vbox->addWidget( _iclButton, hPos++, Qt::AlignLeft );
			_iclButton->setChecked( _isICL );
		}
		if( !_hasNEC || _isNEC ) {
			_necButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::NEC )), this );
			vbox->addWidget( _necButton, hPos++, Qt::AlignLeft );
			_necButton->setChecked( _isNEC );
		}
	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		if( !_hasDCV || _isDCV ) {
			_dcvButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::DCV )), this );
			vbox->addWidget( _dcvButton, hPos++, Qt::AlignLeft );
			_dcvButton->setChecked( _isDCV );
		}
		if( !_hasCV || _isCV ) {
			_cvButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::CV )), this );
			vbox->addWidget( _cvButton, hPos++, Qt::AlignLeft );
			_cvButton->setChecked( _isCV );
		}
		if( !_hasBIC || _isBIC ) {
			_bicButton = new QRadioButton( QString::fromStdString(XEM::CriterionNameToString( XEM::BIC )), this );
			vbox->addWidget( _bicButton, hPos++, Qt::AlignLeft );
			_bicButton->setChecked( _isBIC );
		}
	}

	_group->setLayout( vbox );
	_grid->addWidget( _group, 0, 0, 1, 5 );

	_grid->addWidget( _ok, 1, 3 );

	_grid->addWidget( _cancel, 1, 4 );
}

GUIMCriterionChildModifier::~GUIMCriterionChildModifier() {
}

void GUIMCriterionChildModifier::init() {
	XEM::MVC::TreeItem * itemParent = _item->getParent();
	for( int i = 0 ; i < static_cast<int>( itemParent->getNbChild() ) ; ++i ) {
		if( itemParent->getChild(i)->toString() == XEM::CriterionNameToString( XEM::BIC ) ) {
			_hasBIC = true ;
			_posBIC = i ;
		}
		else if( itemParent->getChild(i)->toString() == XEM::CriterionNameToString( XEM::NEC ) ) {
			_hasNEC = true ;
			_posNEC = i ;
		}
		else if( itemParent->getChild(i)->toString() == XEM::CriterionNameToString( XEM::ICL ) ) {
			_hasICL = true ;
			_posICL = i ;
		}
		else if( itemParent->getChild(i)->toString() == XEM::CriterionNameToString( XEM::DCV ) ) {
			_hasDCV = true ;
			_posDCV = i ;
		}
		else if( itemParent->getChild(i)->toString() == XEM::CriterionNameToString( XEM::CV ) ) {
			_hasCV = true ;
			_posCV = i ;
		}
	}

	if( _item->toString() == XEM::CriterionNameToString( XEM::BIC ) ) {
		_isBIC = true ;
	}
	else if( _item->toString() == XEM::CriterionNameToString( XEM::NEC ) ) {
		_isNEC = true ;
	}
	else if( _item->toString() == XEM::CriterionNameToString( XEM::ICL ) ) {
		_isICL = true ;
	}
	else if( _item->toString() == XEM::CriterionNameToString( XEM::DCV ) ) {
		_isDCV = true ;
	}
	else if( _item->toString() == XEM::CriterionNameToString( XEM::CV ) ) {
		_isCV = true ;
	}
}

void GUIMCriterionChildModifier::ok() {
	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		// BIC
		if( _bicButton && _bicButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::BIC);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
		// NEC
		if( _necButton && _necButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::NEC);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
		// ICL
		if( _iclButton && _iclButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::ICL);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		// DCV
		if( _dcvButton && _dcvButton->isChecked()) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::DCV);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
		// CV
		if( _cvButton && _cvButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::CV);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
		//BIC
		if( _bicButton && _bicButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::CriterionName>(XEM::BIC);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
	}

	confirm();
}

void GUIMCriterionChildModifier::discard() {
	cancel();
}
