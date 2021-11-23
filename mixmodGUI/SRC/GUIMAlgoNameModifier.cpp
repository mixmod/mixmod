/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAlgoNameModifier.cpp  description
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
#include "GUIMAlgoNameModifier.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

GUIMAlgoNameModifier::GUIMAlgoNameModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* item, const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, item, index, parent ),
	  _mapButton( NULL ),
	  _emButton( NULL ),
	  _cemButton( NULL ),
	  _semButton( NULL ),
	  _mButton( NULL ),
	  _isMAP( false ),
	  _isEM( false ),
	  _isCEM( false ),
	  _isSEM( false ),
	  _isM( false ) {
	init();

	setWindowTitle( QObject::tr("Algo Name : ") );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_grid = new QGridLayout( this );
	int hPos = 0 ;

	_group = new QGroupBox( this );
	_group->setStyleSheet( "background-color:white" );

	QVBoxLayout *vbox = new QVBoxLayout;

	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		// EM
		_emButton = new QRadioButton( QString::fromStdString(XEM::AlgoNameToString(XEM::EM)), this );
		vbox->addWidget( _emButton, hPos++, Qt::AlignLeft );
		_emButton->setChecked( _isEM );

		// CEM
		_cemButton = new QRadioButton( QString::fromStdString(XEM::AlgoNameToString(XEM::CEM)), this );
		vbox->addWidget( _cemButton, hPos++, Qt::AlignLeft );
		_cemButton->setChecked( _isCEM );

		// SEM
		_semButton = new QRadioButton( QString::fromStdString(XEM::AlgoNameToString(XEM::SEM)), this );
		vbox->addWidget( _semButton, hPos++, Qt::AlignLeft );
		_semButton->setChecked( _isSEM );
	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		// MAP
		_mapButton = new QRadioButton( QString::fromStdString(XEM::AlgoNameToString(XEM::MAP)), this );
		vbox->addWidget( _mapButton, hPos++, Qt::AlignLeft );
		_mapButton->setChecked( _isMAP );

		// M
		_mButton = new QRadioButton( QString::fromStdString(XEM::AlgoNameToString(XEM::M)), this );
		vbox->addWidget( _mButton, hPos++, Qt::AlignLeft );
		_mButton->setChecked( _isM );
	}

	_group->setLayout( vbox );
	_grid->addWidget( _group, 0, 0, 1, 5 );

	_grid->addWidget( _ok, 1, 3 );

	_grid->addWidget( _cancel, 1, 4 );
}

GUIMAlgoNameModifier::~GUIMAlgoNameModifier() {
}

void GUIMAlgoNameModifier::init() {
	if( _item->toString() == XEM::AlgoNameToString(XEM::MAP) ) {
		_isMAP = true ;
	}
	else if( _item->toString() == XEM::AlgoNameToString(XEM::EM) ) {
		_isEM = true ;
	}
	else if( _item->toString() == XEM::AlgoNameToString(XEM::CEM) ) {
		_isCEM = true ;
	}
	else if( _item->toString() == XEM::AlgoNameToString(XEM::SEM) ) {
		_isSEM = true ;
	}
	else if( _item->toString() == XEM::AlgoNameToString(XEM::M) ) {
		_isM = true ;
	}
}

void GUIMAlgoNameModifier::ok() {
	// MAP
	if( _mapButton && _mapButton->isChecked() ) {
		QVariant value;
		value.setValue<XEM::AlgoName>(XEM::MAP);
		GUIMAction setAction = createSetAction(_index, value);
		_processor->addAction(setAction);
	}
	if( _projectType == XEM::MVC::RootTreeItem::Classification ) {
		// EM
		if( _emButton && _emButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::AlgoName>(XEM::EM);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
		// CEM
		if( _cemButton && _cemButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::AlgoName>(XEM::CEM);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
		// SEM
		if( _semButton && _semButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::AlgoName>(XEM::SEM);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
	}
	else if( _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
		// M
		if( _mButton && _mButton->isChecked() ) {
			QVariant value;
			value.setValue<XEM::AlgoName>(XEM::M);
			GUIMAction setAction = createSetAction(_index, value);
			_processor->addAction(setAction);
		}
	}
	confirm();
}

void GUIMAlgoNameModifier::discard() {
	cancel();
}
