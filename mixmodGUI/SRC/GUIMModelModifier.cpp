/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMModelModifier.cpp  description
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
#include "GUIMModelModifier.h"
#include "GUIMMetaData.h"
#include <QCursor>

#include <QDesktopWidget>
#include <QtGui/QtGui>

const int GUIMModelModifier::HORIZONTAL_SPAN_AT_END = 40 ;

GUIMModelModifier::GUIMModelModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeModel,const QModelIndex& index,  QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeModel, index, parent ),
	  _scrollArea( NULL ),
	  _widget( NULL ), _widgetBox( NULL ),
	  _grid( NULL ),
	  _sphericalGroup( NULL ), _sphericalBox( NULL ), _sphericalButtons( NULL ),
	  _diagonalGroup( NULL ), _diagonalBox( NULL ), _diagonalButtons( NULL ),
	  _generalGroup( NULL ), _generalBox( NULL ), _generalButtons( NULL ),
	  _binaryGroup( NULL ), _binaryBox( NULL ), _binaryButtons( NULL ),
	  _hdGroup( NULL ), _hdBox( NULL ), _hdButtons( NULL ),
	  _sphericalLabel( NULL ), _sphericalButton( NULL ),
	  _diagonalLabel( NULL ), _diagonalButton( NULL ),
	  _generalLabel( NULL ), _generalButton( NULL ),
	  _binaryLabel( NULL ), _binaryButton( NULL ),
	  _hdLabel( NULL ), _hdButton( NULL ),
	  _vButtons( QVector< QAbstractButton* >() ), _modelInTree( QVector< bool >(XEM::nbModelName,false) ) {
	init();

	initWidget();
	setWindowTitle( QObject::tr("Models : ") );
	move( QCursor::pos().x(), QCursor::pos().y() );

	for( int i = 0 ; i < XEM::nbModelName ; ++i ) {
		XEM::ModelName tmpName = static_cast<XEM::ModelName>(i) ;
		QAbstractButton* tmpButton = addToGroup(tmpName);

		if( tmpButton )
			_vButtons.append( tmpButton );
	}

	_widget->adjustSize();
	_widget->show();

	_scrollArea->adjustSize();
	adjustSize();
}

GUIMModelModifier::~GUIMModelModifier() {
	/*
	  qDeleteAll( _vButtons );
	  _vButtons.clear();
	*/
}

void GUIMModelModifier::init() {
	for( unsigned int i = 0 ; i < _item->getNbChild() ; ++i ) {
		std::string stmp = _item->getChild(i)->toString();
		for( int j = 0 ; j < XEM::nbModelName ; ++j ) {
			if( stmp == XEM::ModelNameToString( static_cast<XEM::ModelName>(j) ) ) {
				_modelInTree[j] = true ;
				break ;
			}
		}
	}
}

void GUIMModelModifier::initWidget() {

	_grid = new QGridLayout( this );

	_scrollArea = new QScrollArea( this );

	_widget = new QWidget( this );
	_widgetBox = new QVBoxLayout( _widget );

	_scrollArea->setWidget( _widget );
	_scrollArea->ensureWidgetVisible( _widget );

	_scrollArea->setStyleSheet("background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff);");

	// Gaussian EDDA
	if( _dataType == XEM::MVC::RootTreeItem::Quantitative ) {

		// Spherical
		_sphericalGroup = new QGroupBox( tr("Spherical Models"), _widget );
		_sphericalBox = new QVBoxLayout ;
		_sphericalButtons = new QButtonGroup( _widget );
		_sphericalButtons->setExclusive( false );

		_sphericalGroup->setLayout( _sphericalBox );
		_sphericalGroup->setStyleSheet( "background-color:white" );

		_sphericalButton = new QCheckBox( tr("select all Spherical Models"), _widget );
		connect( _sphericalButton, SIGNAL( released() ), this, SLOT( selectAllSpherical() ) );
		_sphericalButton->setTristate( true );
		_sphericalBox->addWidget( _sphericalButton, Qt::AlignRight );

		_widgetBox->addWidget( _sphericalGroup );

		// Diagonal
		_diagonalGroup = new QGroupBox( tr("Diagonal Models"), _widget );
		_diagonalBox = new QVBoxLayout ;
		_diagonalButtons = new QButtonGroup( _widget );
		_diagonalButtons->setExclusive( false );

		_diagonalGroup->setLayout( _diagonalBox );
		_diagonalGroup->setStyleSheet( "background-color:white" );

		_diagonalButton = new QCheckBox( tr("select all Diagonal Models"), _widget );
		connect( _diagonalButton, SIGNAL( released() ), this, SLOT( selectAllDiagonal() ) );
		_diagonalButton->setTristate( true );
		_diagonalBox->addWidget( _diagonalButton, Qt::AlignRight );

		_widgetBox->addWidget( _diagonalGroup );

		// General
		_generalGroup = new QGroupBox( tr("General Models"), _widget );
		_generalBox = new QVBoxLayout ;
		_generalButtons = new QButtonGroup( _widget );
		_generalButtons->setExclusive( false );

		_generalGroup->setLayout( _generalBox );
		_generalGroup->setStyleSheet( "background-color:white" );

		_generalButton = new QCheckBox( tr("select all General Models"), _widget );
		connect( _generalButton, SIGNAL( released() ), this, SLOT( selectAllGeneral() ) );
		_generalButton->setTristate( true );
		_generalBox->addWidget( _generalButton, Qt::AlignRight );

		_widgetBox->addWidget( _generalGroup );
	}

	// Binary
	if( _dataType == XEM::MVC::RootTreeItem::Qualitative ) {
		_binaryGroup = new QGroupBox( tr("Binary Models"), _widget );
		_binaryBox = new QVBoxLayout ;
		_binaryButtons = new QButtonGroup( _widget );
		_binaryButtons->setExclusive( false );

		_binaryGroup->setLayout( _binaryBox );
		_binaryGroup->setStyleSheet( "background-color:white" );

		_binaryButton = new QCheckBox( tr("select all Binary Models"), _widget );
		connect( _binaryButton, SIGNAL( released() ), this, SLOT( selectAllBinary() ) );
		_binaryButton->setTristate( true );
		_binaryBox->addWidget( _binaryButton, Qt::AlignRight );

		_widgetBox->addWidget( _binaryGroup );
	}

	// Gaussian HDDA
	if( _dataType == XEM::MVC::RootTreeItem::Quantitative && _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {

		_hdGroup = new QGroupBox( tr("HD Models"), _widget );
		_hdBox = new QVBoxLayout ;
		_hdButtons = new QButtonGroup( _widget );
		_hdButtons->setExclusive( false );

		_hdGroup->setLayout( _hdBox );
		_hdGroup->setStyleSheet( "background-color:white" );

		_hdButton = new QCheckBox( tr("select all HD Models"), _widget );
		connect( _hdButton, SIGNAL( released() ), this, SLOT( selectAllHD() ) );
		_hdButton->setTristate( true );
		_hdBox->addWidget( _hdButton, Qt::AlignRight );

		_widgetBox->addWidget( _hdGroup );
	}

	_grid->addWidget( _scrollArea, 0, 0, 1, 5 );
	_grid->addWidget( _ok, 1, 3 );
	_grid->addWidget( _cancel, 1, 4 );
}

QAbstractButton* GUIMModelModifier::addToGroup( XEM::ModelName name ) {
	QAbstractButton* button = NULL ;

	if( XEM::isDiagonal(name) ) {

		if( _dataType == XEM::MVC::RootTreeItem::Quantitative ) {
			button = new QCheckBox( QString::fromStdString( XEM::ModelNameToString(name) ), _widget );
			connect( button, SIGNAL( released() ), this, SLOT( verifyAllDiagonal() ) );
			_diagonalBox->addWidget( button );
			_diagonalButtons->addButton( button, static_cast<int>(name) );
			button->setChecked( _modelInTree[ static_cast<int>(name) ] );
		}

	}
	else if( XEM::isSpherical(name) ) {

		if( _dataType == XEM::MVC::RootTreeItem::Quantitative ) {
			button = new QCheckBox( QString::fromStdString( XEM::ModelNameToString(name) ), _widget );
			connect( button, SIGNAL( released() ), this, SLOT( verifyAllSpherical() ) );
			_sphericalBox->addWidget( button );
			_sphericalButtons->addButton( button, static_cast<int>(name) );
			button->setChecked( _modelInTree[ static_cast<int>(name) ] );
		}

	}
	else if( XEM::isGeneral(name) ) {

		if( _dataType == XEM::MVC::RootTreeItem::Quantitative ) {
			button = new QCheckBox( QString::fromStdString( XEM::ModelNameToString(name) ), _widget );
			connect( button, SIGNAL( released() ), this, SLOT( verifyAllGeneral() ) );
			_generalBox->addWidget( button );
			_generalButtons->addButton( button, static_cast<int>(name) );
			button->setChecked( _modelInTree[ static_cast<int>(name) ] );
		}

	}
	else if( XEM::isBinary(name) ) {

		if( _dataType == XEM::MVC::RootTreeItem::Qualitative ) {
			button = new QCheckBox( QString::fromStdString( XEM::ModelNameToString(name) ), _widget );
			connect( button, SIGNAL( released() ), this, SLOT( verifyAllBinary() ) );
			_binaryBox->addWidget( button );
			_binaryButtons->addButton( button, static_cast<int>(name) );
			button->setChecked( _modelInTree[ static_cast<int>(name) ] );
		}

	}
	else if( XEM::isHD(name) ) {

		if( _dataType == XEM::MVC::RootTreeItem::Quantitative && _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis ) {
			/*QAbstractButton* plusHD = new QPushButton( "+", _widget );
			plusHD->setFixedSize(plusHD->height()/2, plusHD->height()/2);*/
			/* QAbstractButton* minusHD = new QPushButton( "-", _widget );
			 minusHD->setFixedSize(plusHD->height(), plusHD->height());*/
			//plusHD->setStyleSheet("QPushButton {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff)};");
			//minusHD->setStyleSheet("QPushButton {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff)};");

			button = new QCheckBox( QString::fromStdString( XEM::ModelNameToString(name) ), _widget );
			connect( button, SIGNAL( released() ), this, SLOT( verifyAllHD() ) );
			//connect( plusHD, SIGNAL(  ), this, SLOT( verifyAllHD() ) );
			_hdModelLine = new QHBoxLayout();
			_hdModelLine->addWidget( button);
			_hdModelLine->addWidget( new QLabel(""), Qt::AlignHCenter);
			//_hdModelLine->addWidget( plusHD, Qt::AlignHCenter );
			//_hdModelLine->addWidget( minusHD);
			//_hdModelLine->addWidget(new QSpinBox());
			_hdBox->addLayout(_hdModelLine);
			_hdButtons->addButton( button, static_cast<int>(name) );
			button->setChecked( _modelInTree[ static_cast<int>(name) ] );
		}
	}

	if( button )
		connect( button, SIGNAL( toggled(bool) ), this, SLOT( canConfirm() ) );

	return button ;
}

void GUIMModelModifier::ok() {
	int currentPos = 0 ;
	int cptInsert = 0 ;
	int cptRemove = 0 ;
	QVector<int> removePos ;

	// cross the tree & insert
	for( int i = 0 ; i < XEM::nbModelName ; ++i ) {

		bool isChecked = false ;
		std::string s = XEM::ModelNameToString( static_cast<XEM::ModelName>(i) );
		for( int j = 0 ; j < _vButtons.size() ; ++j ) {
			std::string sj = _vButtons[j]->text().toStdString();

			if( s == sj ) {
				if( _vButtons[j]->isChecked() )
					isChecked = true ;
				break ;
			}
		}

		bool wasChecked = _modelInTree[i] ;

		if( !wasChecked ) {
			if( isChecked ) {
				// insert
				GUIMAction insertAction = createInsertAction(_index, currentPos);
				_processor->addAction(insertAction);

				//set
				QList<int> positions;
				positions.append(currentPos);
				QVariant value;
				value.setValue<XEM::ModelName>( static_cast<XEM::ModelName>(i) );
				GUIMAction setAction = createSetAction(_index, positions, value);
				_processor->addAction(setAction);

				++currentPos ;
				++cptInsert ;
			}
		}
		else {
			if( !isChecked ) {
				int tmpPos = 0 ;
				for( unsigned int j = 0 ; j < _item->getNbChild() ; ++j ) {
					std::string stmp = _item->getChild(j)->toString();
					if( _modelInTree[i] &&
					        stmp == XEM::ModelNameToString(static_cast<XEM::ModelName>(i)) ) {
						tmpPos = j ;
						break ;
					}
				}
				removePos.append( tmpPos + cptInsert + cptRemove-- );
			}
			++currentPos ;
		}
	}

	// remove
	for( int i = 0 ; i < removePos.size() ; ++i ) {
		GUIMAction removeAction = createRemoveAction(_index, removePos[i]);
		_processor->addAction(removeAction);
	}

	confirm();
}

void GUIMModelModifier::discard() {
	cancel();
}

void GUIMModelModifier::canConfirm() {
	bool finish = false ;
	for( int i = 0 ; i < _vButtons.size() ; ++i ) {
		if( _vButtons[i]->isChecked() ) {
			finish = true ;
			break ;
		}
	}
	_ok->setEnabled( finish );
}

void GUIMModelModifier::selectAll( QButtonGroup* group, QCheckBox* button ) {
	QList< QAbstractButton* > list = group->buttons();

	if( button->isChecked() ) {
		button->setCheckState( Qt::Checked );
	}
	else {
		button->setCheckState( Qt::Unchecked );
	}

	for( QList< QAbstractButton* >::iterator it = list.begin() ; it != list.end() ; ++it ) {
		if( button->isChecked() ) {
			(*it)->setChecked( true );
		}
		else {
			(*it)->setChecked( false );
		}
	}
}

void GUIMModelModifier::selectAllSpherical() {
	selectAll( _sphericalButtons, _sphericalButton );
}

void GUIMModelModifier::selectAllDiagonal() {
	selectAll( _diagonalButtons, _diagonalButton );
}

void GUIMModelModifier::selectAllGeneral() {
	selectAll( _generalButtons, _generalButton );
}

void GUIMModelModifier::selectAllBinary() {
	selectAll( _binaryButtons, _binaryButton );
}

void GUIMModelModifier::selectAllHD() {
	selectAll( _hdButtons, _hdButton );
}

void GUIMModelModifier::verifyAll( QButtonGroup* group, QCheckBox* button ) {
	int cpt = 0 ;
	if( button->isChecked() ) {
		QList< QAbstractButton* > list = group->buttons();

		for( QList< QAbstractButton* >::iterator it = list.begin() ; it != list.end() ; ++it ) {
			if( !(*it)->isChecked() ) {
				++cpt ;
				if( cpt == list.size() ) {
					button->setCheckState( Qt::Unchecked );
				}
				else {
					button->setCheckState( Qt::PartiallyChecked );
				}

			}
		}
	}
}

void GUIMModelModifier::verifyAllSpherical() {
	verifyAll( _sphericalButtons, _sphericalButton );
}

void GUIMModelModifier::verifyAllDiagonal() {
	verifyAll( _diagonalButtons, _diagonalButton );
}

void GUIMModelModifier::verifyAllGeneral() {
	verifyAll( _generalButtons, _generalButton );
}

void GUIMModelModifier::verifyAllBinary() {
	verifyAll( _binaryButtons, _binaryButton );
}

void GUIMModelModifier::verifyAllHD() {
	verifyAll( _hdButtons, _hdButton );
}
