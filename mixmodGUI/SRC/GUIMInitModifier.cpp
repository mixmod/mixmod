/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMInitModifier.cpp  description
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

#include "GUIMInitModifier.h"
#include <mixmod_mvc/View.h>

#include "GUIMMetaData.h"
#include "GUIMTreeModel.h"
#include <QCursor>
#include <QtGui/QtGui>

GUIMInitModifier::GUIMInitModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* item, const QModelIndex& index, QWidget* parent)
	: GUIMAbstractModifier( type, dataType, item, index, parent ), _nbFilename(item->getParent()->getParent()->getChild(0)->getNbChild()),  _filenames( QVector< GUIMTextEntryWidget * >() )
{
	init();
	TEXT_VALIDATOR = tr("Not a valid File") ;
	QFont font;
	font.setUnderline( true );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_grid = new QGridLayout( this );

	QLabel* _labelTitle = new QLabel( QObject::tr("STRATEGY INIT"));
	_labelTitle->setFont( font );
	_grid->addWidget( _labelTitle, 0, 2 );

	_widget = new QWidget( this );
	_widgetBox = new QVBoxLayout( _widget );

	/*Name*/
	_gMethod = new QGroupBox(tr("Method"), _widget);
	_gMethod->setStyleSheet( "background-color:white" );

	_methodBox = new QHBoxLayout ;

	QLabel* labelMethod = new QLabel( QObject::tr("Name"), _widget );
	labelMethod->setFont( font );
	_methodBox->addWidget( labelMethod );

	_gName = new QGroupBox(tr(""), _widget);
	_nameBox = new QVBoxLayout;
	_nameGroup = new QButtonGroup( _nameBox );

	_RANDOMButton = new QRadioButton( tr("RANDOM"));
	_SMALL_EMButton = new QRadioButton( tr("SMALL EM"));
	_CEM_INITButton = new QRadioButton( tr("CEM"));
	_SEM_MAXButton = new QRadioButton( tr("SEM MAX"));
	_USERButton = new QRadioButton( tr("PARAMETER"));
	_USER_PARTITIONButton = new QRadioButton( tr("PARTITION"));
	_nameGroup->addButton( _RANDOMButton ) ;
	_nameGroup->addButton( _SMALL_EMButton ) ;
	_nameGroup->addButton( _CEM_INITButton ) ;
	_nameGroup->addButton( _SEM_MAXButton ) ;
	_nameGroup->addButton( _USERButton ) ;
	_nameGroup->addButton( _USER_PARTITIONButton ) ;

	_nameBox->addWidget( _RANDOMButton );
	_nameBox->addWidget( _SMALL_EMButton );
	_nameBox->addWidget( _CEM_INITButton );
	_nameBox->addWidget( _SEM_MAXButton );
	_nameBox->addWidget( _USERButton );
	_nameBox->addWidget( _USER_PARTITIONButton );
	connect( _RANDOMButton, SIGNAL( released() ), this, SLOT( activateParameters() ) );
	connect( _SMALL_EMButton, SIGNAL( released() ), this, SLOT( activateParameters() ) );
	connect( _CEM_INITButton, SIGNAL( released() ), this, SLOT( activateParameters() ) );
	connect( _SEM_MAXButton, SIGNAL( released() ), this, SLOT( activateParameters() ) );
	connect( _USER_PARTITIONButton, SIGNAL( released() ), this, SLOT( activateParameters() ) );
	connect( _USERButton, SIGNAL( released() ), this, SLOT( activateParameters() ) );
	connect( _SMALL_EMButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
	connect( _CEM_INITButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );
	connect( _SEM_MAXButton, SIGNAL( released() ), this, SLOT( canConfirm() ) );

	//RadioButton is desactivate for the moment
	_USERButton->setEnabled(false);
	_USER_PARTITIONButton->setEnabled(false);

	_SMALL_EMButton->setChecked (true );

	_gName->setLayout( _nameBox );
	_methodBox->addWidget( _gName );
	_gMethod->setLayout( _methodBox );
	_widgetBox->addWidget(_gMethod);
	/*Name*/

	/*Options in Init*/
	_gInInit = new QGroupBox(tr("Initialization Options"), _widget);
	_gInInit->setStyleSheet( "background-color:white" );

	_gridInInitBox = new QGridLayout;

	QLabel * _labelNbTryInInit = new QLabel( QObject::tr("Number of try in Init"), _widget );
	QLabel * _labelNbIterationInInit = new QLabel( QObject::tr("Number of Iteration in Init"), _widget );
	QLabel * _labelEpsilonInInit = new QLabel( QObject::tr("Epsilon in Init"), _widget );

	_gridInInitBox->addWidget( _labelNbTryInInit, 0, 1);//label
	_gridInInitBox->addWidget( _labelNbIterationInInit, 1, 1);//label
	_gridInInitBox->addWidget( _labelEpsilonInInit, 2, 1);//label

	_editNbTryInInit = new QLineEdit( _widget );
	_editNbIterationInInit = new QLineEdit( _widget );
	_editEpsilonInInit = new QLineEdit( _widget );

	std::ostringstream sNbTryI, sNbItI, sEpsI;
	sNbTryI << XEM::defaultNbTryInInit;
	sNbItI << XEM::defaultNbIterationInInit;
	sEpsI << XEM::defaultEpsilonInInit;

	_editNbTryInInit->setText(QString::fromStdString(sNbTryI.str()));
	_editNbIterationInInit->setText(QString::fromStdString(sNbItI.str()));
	_editEpsilonInInit->setText(QString::fromStdString(sEpsI.str()));

	_validNbTryI = new QIntValidator(XEM::minNbTryInInit,XEM::maxNbTryInInit, _widget);//validity of nbiteration
	_editNbTryInInit->setMaxLength( 4 );
	_validNbIterationI = new QIntValidator(XEM::minNbIterationInInit,XEM::maxNbIterationInInit, _widget);//validity of nbiteration
	_editNbIterationInInit->setMaxLength( 6 );
	_validEpsilonI = new QDoubleValidator(XEM::minEpsilonInInit, XEM::maxEpsilonInInit, 6, _widget);//validity of epsilon
	_editEpsilonInInit->setMaxLength( 8 );

	connect( _editNbTryInInit, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );
	connect( _editNbIterationInInit, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );
	connect( _editEpsilonInInit, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );

	_editNbTryInInit->setValidator( _validNbTryI );
	_editNbIterationInInit->setValidator( _validNbIterationI );
	_editEpsilonInInit->setValidator( _validEpsilonI );

	_gridInInitBox->addWidget(_editNbTryInInit, 0, 2);
	_gridInInitBox->addWidget(_editNbIterationInInit, 1, 2);
	_gridInInitBox->addWidget(_editEpsilonInInit, 2, 2);

	_gInInit->setLayout(_gridInInitBox);
	_gInInit->setEnabled(true);
	/*_editNbIterationInInit->setEnabled(false);
	_editEpsilonInInit->setEnabled(false);
	_editNbTryInInit->setEnabled(true);*/

	_widgetBox->addWidget(_gInInit);
	/*Parameters*/
	_gParameters = new QGroupBox(tr("Parameters"), _widget);
	_gParameters->setStyleSheet( "background-color:white" );

	_gridParam = new QGridLayout;

	int hPos=0;
	int hPosMax = 2 ;

	for( int i = 0 ; i < _nbFilename ; ++i ) {
		GUIMTextEntryWidget* entry = new GUIMTextEntryWidget( this ) ;

		QLabel* labelParam = new QLabel( QObject::tr("Filename ")+QString::number(i+1), _widget );
		labelParam->setFont( font );
		_gridParam->addWidget( labelParam, hPos+i*hPosMax, 0 );

		entry->_filename = new QLineEdit( _widget );
		entry->_validatorFilename = new GUIMFilenameValidator( _widget );
		entry->_bFilename = new QPushButton( "...", _widget );
		entry->_bFilename->setStyleSheet("QPushButton {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff)};");
		connect( entry->_bFilename, SIGNAL( released() ), entry, SLOT( setFilenameParameter() ) );
		connect( entry->_filename, SIGNAL( textChanged(const QString &) ), entry, SLOT( verifyText(const QString &) ) );
		connect( entry->_filename, SIGNAL( textChanged(const QString &) ), this, SLOT( verifyAllText(const QString &) ) );
		entry->_labelValidator = new QLabel( TEXT_VALIDATOR );

		_gridParam->addWidget( entry->_filename, hPos+i*hPosMax, 2, 1, 3 );
		_gridParam->addWidget( entry->_bFilename, hPos+i*hPosMax, 5 );
		_gridParam->addWidget( entry->_labelValidator, ++hPos+i*hPosMax, 2 );

		_filenames.append(entry);
	}
	_scrollArea = new QScrollArea;
	_scrollArea->setStyleSheet("background : white");
	_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_scrollArea->setMinimumWidth(350);

	_gParameters->setLayout( _gridParam );
	_scrollArea->setWidget(_gParameters);
	_scrollArea->setMaximumHeight(200);
	_scrollArea->setEnabled(false);
	_widgetBox->addWidget(_scrollArea);
	/*end Parameters*/

	_grid->addWidget( _widget, 1, 0, 1, 5 );
	_grid->addWidget( _ok, 2, 3 );
	_grid->addWidget( _cancel, 2, 4 );
}

GUIMInitModifier::~GUIMInitModifier() {
	qDeleteAll( _filenames );
}

void GUIMInitModifier::init() {
	std::istringstream iss( _item->getParent()->getParent()->getChild( XEM::MVC::View::NB_NB_CLUSTER)->toString() );
	iss >> _nbFilename ;

	_filenames.reserve( _nbFilename );

	if ( _item->getChild(0)->toString() == XEM::StrategyInitNameToString( XEM::RANDOM ) )
		_oldName = XEM::RANDOM;
	if ( _item->getChild(0)->toString() == XEM::StrategyInitNameToString( XEM::CEM_INIT ) )
		_oldName = XEM::CEM_INIT;
	if ( _item->getChild(0)->toString() == XEM::StrategyInitNameToString( XEM::SMALL_EM ) )
		_oldName = XEM::SMALL_EM;
	if ( _item->getChild(0)->toString() == XEM::StrategyInitNameToString( XEM::SEM_MAX ) )
		_oldName = XEM::SEM_MAX;
	if ( _item->getChild(0)->toString() == XEM::StrategyInitNameToString( XEM::USER ) )
		_oldName = XEM::USER;
	if ( _item->getChild(0)->toString() == XEM::StrategyInitNameToString( XEM::USER_PARTITION ) )
		_oldName = XEM::USER_PARTITION;
}


void GUIMInitModifier::verifyAllText( const QString& ) {
	bool finish = true ;

	for( int i = 0 ; i < _nbFilename ; ++i ) {
		QString tmpText = _filenames[i]->_filename->text() ;
		int cursorPos = _filenames[i]->_filename->cursorPosition();
		if( !(_filenames[i]->_validatorFilename->validate( tmpText, cursorPos ) == QValidator::Acceptable) ) {
			finish = false ;
			break ;
		}
	}
	_ok->setEnabled( finish );
}


void GUIMInitModifier::activateParameters() {
	if (_USERButton->isChecked() || _USER_PARTITIONButton->isChecked()) {
		_gInInit->setEnabled(false);
		_scrollArea->setEnabled(true);
		_ok->setEnabled(false);
		if (_USERButton->isChecked()) {
			for (int i = 0; i< _filenames.size(); ++i) {
				_filenames[i]->_parameter = ParamInit;
			}
		}
		else if (_USER_PARTITIONButton->isChecked()) {
			for (int i = 0; i< _filenames.size(); ++i) {
				_filenames[i]->_parameter = ParamPartition;
			}
		}
	}
	else {
		std::ostringstream sNbItI;
		_gInInit->setEnabled(true);
		_scrollArea->setEnabled(false);
		_ok->setEnabled(true);
		if (_CEM_INITButton->isChecked() || _RANDOMButton->isChecked()) {
			_editNbIterationInInit->setEnabled(false);
			_editEpsilonInInit->setEnabled(false);
			_editNbTryInInit->setEnabled(true);
		}
		if (_SEM_MAXButton->isChecked()) {
			_editNbIterationInInit->setEnabled(true);
			_editNbTryInInit->setEnabled(false);
			_editEpsilonInInit->setEnabled(false);
			sNbItI << XEM::defaultNbIterationInInitForSemMax;
			_editNbIterationInInit->setText(QString::fromStdString(sNbItI.str()));
		}
		if (_SMALL_EMButton->isChecked()) {
			sNbItI << XEM::defaultNbIterationInInit;
			_editNbIterationInInit->setText(QString::fromStdString(sNbItI.str()));
			_editNbIterationInInit->setEnabled(true);
			_editNbTryInInit->setEnabled(true);
			_editEpsilonInInit->setEnabled(true);
		}
	}
}

void GUIMInitModifier::canConfirm() {
	bool finish = true ;
	if (_CEM_INITButton->isChecked() || _RANDOMButton->isChecked())
		finish = _editNbTryInInit->hasAcceptableInput();

	if (_SEM_MAXButton->isChecked())
		finish = _editNbIterationInInit->hasAcceptableInput();

	if (_SMALL_EMButton->isChecked())
		finish = _editNbTryInInit->hasAcceptableInput() & _editNbIterationInInit->hasAcceptableInput() & _editEpsilonInInit->hasAcceptableInput();

	_ok->setEnabled( finish );
}

void GUIMInitModifier::ok() {
	init();

	if ( _processor->getNbAction() )
		_processor->removeAll();

	QVariant InitName ;

	if ( _RANDOMButton->isChecked() )
		InitName.setValue<XEM::StrategyInitName>( XEM::RANDOM );
	if ( _CEM_INITButton->isChecked())
		InitName.setValue<XEM::StrategyInitName>( XEM::CEM_INIT );
	if ( _SMALL_EMButton->isChecked())
		InitName.setValue<XEM::StrategyInitName>( XEM::SMALL_EM );
	if ( _SEM_MAXButton->isChecked())
		InitName.setValue<XEM::StrategyInitName>( XEM::SEM_MAX );
	if ( _USERButton->isChecked())
		InitName.setValue<XEM::StrategyInitName>( XEM::USER );
	if ( _USER_PARTITIONButton->isChecked())
		InitName.setValue<XEM::StrategyInitName>( XEM::USER_PARTITION );

	//parameters to remove
	if ( _oldName == XEM::SEM_MAX || _oldName == XEM::RANDOM || _oldName == XEM::CEM_INIT || _oldName == XEM::SMALL_EM) { //parameter in init
		GUIMAction removeAction = createRemoveAction(_index, 1);
		_processor->addAction(removeAction);
	}

	//nbTry change
	if (_oldName != XEM::USER && _oldName != XEM::USER_PARTITION) {// nbtry by default
		QList<int> positions;
		positions.append(XEM::MVC::View::NB_STRATEGY_TRY);
		QVariant value;
		value.setValue<int>( XEM::defaultNbTryInStrategy );
		GUIMAction setAction = createSetAction(_index, positions, value, 1);
		_processor->addAction(setAction);
	}
	//name to change
	if (_USERButton->isChecked() || _USER_PARTITIONButton->isChecked()) {
		if (_oldName != XEM::USER && _oldName != XEM::USER_PARTITION) {	//nbtry must be 1
			QList<int> positionsToSet;
			positionsToSet.append(XEM::MVC::View::NB_STRATEGY_TRY);
			QVariant value;
			value.setValue<int>( 1 );
			GUIMAction setAction = createSetAction(_index, positionsToSet, value,1);
			_processor->addAction(setAction);
		}
		QList<int> positions;
		positions.append(XEM::MVC::View::INIT_NAME_PARAMETER); //InitName is the position of Name in INIT
		GUIMAction setAction = createSetAction(_index, positions, InitName);
		_processor->addAction(setAction);

		QVariant v ;
		for (int i=0; i<_nbFilename; ++i) {
			v.setValue(_filenames[i]->_filename->text());
			QList<int> positionsToSet;
			positionsToSet.append(XEM::MVC::View::INIT_NAME_PARAMETER); //InitName is the position of Name in INIT
			positionsToSet.append(i);//position of filename
			GUIMAction setActionFile = createSetAction(_index, positionsToSet, v);
			_processor->addAction(setActionFile);
		}
	}
	else {//case RANDOM, CEM, SEM_MAX,SMALL_EM
		QList<int> positions;
		positions.append(XEM::MVC::View::INIT_NAME); //InitName is the position of Name in INIT
		GUIMAction setAction = createSetAction(_index, positions, InitName);
		_processor->addAction(setAction);
	}

	//parameters to insert
	if ( _CEM_INITButton->isChecked() || _SEM_MAXButton->isChecked() || _SMALL_EMButton->isChecked() || _RANDOMButton->isChecked()) { //parameter in init
		GUIMAction insertAction = createInsertAction(_index, 1);
		_processor->addAction(insertAction);
	}
	//parameters to set
	if ( _CEM_INITButton->isChecked() || _RANDOMButton->isChecked()) {
		QList<int> positions;
		positions.append(XEM::MVC::View::NB_TRY_INIT_RANDOM); //position of nbtry in INIT
		QVariant value;
		value.setValue<int>( _editNbTryInInit->text().toInt() );
		GUIMAction setAction = createSetAction(_index, positions, value);
		_processor->addAction(setAction);
	}
	else if (_SEM_MAXButton->isChecked()) {
		QList<int> positionsNbIt;
		//positionsNbIt.append(XEMMVCView::STOP_RULE_SEM_MAX);
		positionsNbIt.append(XEM::MVC::View::NB_ITERATION_SEM_MAX); //position of nbIteration in INIT
		QVariant valueNbIt;
		valueNbIt.setValue<int>( _editNbIterationInInit->text().toInt() );
		_processor->addAction(createSetAction(_index, positionsNbIt, valueNbIt));

	}
	else if (_SMALL_EMButton->isChecked()) {
		QList<int> positionsNbTry;
		positionsNbTry.append(XEM::MVC::View::NB_TRY_INIT_SMALL_EM);  //position of nbtry in INIT
		QVariant valueNbTry;
		valueNbTry.setValue<int>( _editNbTryInInit->text().toInt() );
		_processor->addAction(createSetAction(_index, positionsNbTry, valueNbTry));

		QList<int> positionsNbIt;
		positionsNbIt.append(XEM::MVC::View::STOP_RULE_SMALL_EM);
		positionsNbIt.append(XEM::MVC::View::NB_ITERATION); //position of nbIteration in INIT
		QVariant valueNbIt;
		valueNbIt.setValue<int>( _editNbIterationInInit->text().toInt() );
		_processor->addAction(createSetAction(_index, positionsNbIt, valueNbIt));

		QList<int> positionsEps;
		positionsEps.append(XEM::MVC::View::STOP_RULE_SMALL_EM);
		positionsEps.append(XEM::MVC::View::EPSILON);//position of epsilon in INIT
		QVariant valueEps;
		valueEps.setValue<double>( _editEpsilonInInit->text().toDouble() );
		_processor->addAction(createSetAction(_index, positionsEps, valueEps));
	}

	confirm();
}


void GUIMInitModifier::discard() {
	cancel();
}
