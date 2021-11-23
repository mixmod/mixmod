/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMStopRuleValueModifier.cpp  description
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
#include "GUIMStopRuleValueModifier.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

GUIMStopRuleValueModifier::GUIMStopRuleValueModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeStopRuleValue,const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeStopRuleValue, index, parent ) {

	init();

	setWindowTitle( QObject::tr("Stop Rule Value: ") );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_labelValue = new QLabel( QObject::tr("Choose Value : "), this );

	_grid = new QGridLayout( this );
	int hPos = 0 ;

	_grid->addWidget( _labelValue, hPos, 1 );//label

	_editValue = new QLineEdit( this );
	QTimer::singleShot(0,_editValue,SLOT(setFocus()));
	connect( _editValue, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );

	_editValue->setText(QString::fromStdString(_item->toString()));

	if (_isNbIteration ) {
		_valid = new QIntValidator(XEM::minNbIteration,XEM::maxNbIteration, this);//validity of nbiteration
		XEM::MVC::TreeItem * child = treeStopRuleValue->getParent()->getParent()->getChild(0);
		if( treeStopRuleValue->getParent()->getParent()->getChild(0)->toString() == XEM::AlgoNameToString( XEM::SEM ) ) {
			reinterpret_cast< QIntValidator *>(_valid)->setBottom(XEM::minNbIterationForSEM);
		}
		_editValue->setMaxLength( 6 );
	}
	else {
		_valid = new QDoubleValidator(XEM::minEpsilon, XEM::maxEpsilon, 6, this);//validity of epsilon
		_editValue->setMaxLength( 8 );
	}
	_editValue->setValidator( _valid );

	_grid->addWidget(_editValue, hPos, 2, 1,2);

	_grid->addWidget( _ok, ++hPos, 2, 1,1 );

	_grid->addWidget( _cancel, hPos, 3 );
}

GUIMStopRuleValueModifier::~GUIMStopRuleValueModifier() {
}

void GUIMStopRuleValueModifier::canConfirm() {
	bool finish = false ;

	finish = _editValue->hasAcceptableInput();

	_ok->setEnabled( finish );
}

void GUIMStopRuleValueModifier::init() {
	if ( _item->getKeyword() == XEM::MVC::TreeEpsilon ) {
		_isEpsilon = true ;
		_isNbIteration = !_isEpsilon ;
	}
	else {
		_isNbIteration = true ;
		_isEpsilon = !_isNbIteration ;
	}
}

void GUIMStopRuleValueModifier::ok() {
	QString valueString = _editValue->text();
	if (_isNbIteration ) {
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

void GUIMStopRuleValueModifier::discard() {
	cancel();
}
