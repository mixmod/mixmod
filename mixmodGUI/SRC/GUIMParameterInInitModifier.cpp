/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMParameterInInitModifier.cpp  description
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
#include "GUIMParameterInInitModifier.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

GUIMParameterInInitModifier::GUIMParameterInInitModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeParameterInit,const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeParameterInit, index, parent ) {

	init();

	setWindowTitle( QObject::tr("Parameter Init ") );
	move( QCursor::pos().x(), QCursor::pos().y() );
	switch (treeParameterInit->getKeyword() ) {
	case XEM::MVC::TreeInitNbIteration :
		_labelValue = new QLabel( QObject::tr("Choose the number of iterations : "), this );
		break;
	case XEM::MVC::TreeInitEpsilon :
		_labelValue = new QLabel( QObject::tr("Choose the value of epsilon : "), this );
		break;
	case XEM::MVC::TreeInitNbTry :
		_labelValue = new QLabel( QObject::tr("Choose the number of repeats : "), this );
		break;
	default:
		break;
	}
	_grid = new QGridLayout( this );
	int hPos = 0 ;

	_grid->addWidget( _labelValue, hPos, 1 );//label

	_editValue = new QLineEdit( this );
	QTimer::singleShot(0,_editValue,SLOT(setFocus()));//set focus ALL the time in the edit
	connect( _editValue, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );

	_editValue->setText(QString::fromStdString(_item->toString()));

	if (_isNbIteration ) {
		_valid = new QIntValidator(XEM::minNbTryInInit,XEM::maxNbTryInInit, this);//validity of nbiteration
		_editValue->setMaxLength( 6 );
	}
	else if ( _isNbTry) {
		_valid = new QIntValidator(XEM::minNbIterationInInit,XEM::maxNbIterationInInit, this);//validity of nbiteration
		_editValue->setMaxLength( 6 );
	}
	else if ( _isEpsilon) {
		_valid = new QDoubleValidator(XEM::minEpsilonInInit, XEM::maxEpsilonInInit, 7, this);//validity of epsilon
		_editValue->setMaxLength( 8 );
	}
	_editValue->setValidator( _valid );

	_grid->addWidget(_editValue, hPos, 2, 1,2);

	_grid->addWidget( _ok, ++hPos, 2, 1,1 );

	_grid->addWidget( _cancel, hPos, 3 );

}

GUIMParameterInInitModifier::~GUIMParameterInInitModifier() {
}

void GUIMParameterInInitModifier::canConfirm() {
	bool finish = false ;

	finish = _editValue->hasAcceptableInput();

	_ok->setEnabled( finish );
}

void GUIMParameterInInitModifier::init() {
	if ( _item->getKeyword() == XEM::MVC::TreeInitEpsilon ) {
		_isEpsilon = true ;
		_isNbIteration = false ;
		_isNbTry = false ;
	}
	else if (_item->getKeyword() == XEM::MVC::TreeInitNbIteration) {
		_isNbIteration = true ;
		_isEpsilon = false ;
		_isNbTry = false ;
	}
	else {
		_isNbTry = true ;
		_isEpsilon = false ;
		_isNbIteration = false ;
	}
}

void GUIMParameterInInitModifier::ok() {
	QString valueString = _editValue->text();
	if (_isNbIteration || _isNbTry) {
		QVariant value;
		value.setValue<int>( valueString.toInt() );
		GUIMAction setAction = createSetAction(_index, value);
		_processor->addAction(setAction);
	}
	else {
		QVariant value;
		value.setValue<double>( valueString.toDouble() );
		GUIMAction setAction = createSetAction(_index, value);
		_processor->addAction(setAction);
	}

	confirm();
}

void GUIMParameterInInitModifier::discard() {
	cancel();
}
