/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMNbStrategyTryModifier.cpp  description
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
#include "GUIMNbStrategyTryModifier.h"
#include <QCursor>

#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

GUIMNbStrategyTryModifier::GUIMNbStrategyTryModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeNbStrategyTry,const QModelIndex& index, QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeNbStrategyTry, index, parent ) {

	setWindowTitle( QObject::tr("Strategy Try Value: ") );
	move( QCursor::pos().x(), QCursor::pos().y() );

	_labelValue = new QLabel( QObject::tr("Choose Value : "), this );

	_grid = new QGridLayout( this );
	int hPos = 0 ;

	_grid->addWidget( _labelValue, hPos, 1 );//label

	_editValue = new QLineEdit( this );

	connect( _editValue, SIGNAL( textChanged(const QString &) ), this, SLOT( canConfirm() ) );

	_editValue->setText(QString::fromStdString(_item->toString()));

	_valid = new QIntValidator(XEM::minNbTryInStrategy,XEM::maxNbTryInStrategy, this);//validity of nbiteration
	_editValue->setMaxLength( 6 );

	_editValue->setValidator( _valid );

	_grid->addWidget(_editValue, hPos, 2, 1,2);

	_grid->addWidget( _ok, ++hPos, 2, 1,1 );

	_grid->addWidget( _cancel, hPos, 3 );
	QTimer::singleShot(0,_editValue,SLOT(setFocus()));//put focus on the QlineEdit
}

GUIMNbStrategyTryModifier::~GUIMNbStrategyTryModifier() {
}

void GUIMNbStrategyTryModifier::canConfirm() {
	bool finish = false ;

	finish = _editValue->hasAcceptableInput();

	_ok->setEnabled( finish );
}

void GUIMNbStrategyTryModifier::ok() {
	QString valueString = _editValue->text();
	QVariant value;
	value.setValue<int>( valueString.toInt() );
	GUIMAction setAction = createSetAction(_index, value);
	_processor->addAction(setAction);

	confirm();
}

void GUIMNbStrategyTryModifier::discard() {
	cancel();
}
