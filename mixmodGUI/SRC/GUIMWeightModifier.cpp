/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMWeightModifier.cpp  description
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
#include "GUIMWeightModifier.h"

#include <sstream>
#include <QCursor>
#include <QString>
#include <QPushButton>
#include <QFileDialog>

#include "GUIMMetaData.h"
#include "mixmod_mvc/View.h"
#include "mixmod_mvc/Model.h"

GUIMWeightModifier::GUIMWeightModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeWeight,const QModelIndex& index,QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeWeight, index, parent ),
	  _fixedWidth( 600 ),
	  _nbFilename( 0 ),  _validatorFilename(NULL) ,/*_filenames( QVector< GUIMTextEntryWidget* >() ),*/ _bDefault( new QPushButton( tr("Default"), this ) ) {
	TEXT_VALIDATOR = tr("Not a valid File") ;
	setWindowTitle( QObject::tr("Weight : ") );
	move( QCursor::pos().x(), QCursor::pos().y() );
	setFixedWidth( _fixedWidth );

	_grid = new QGridLayout( this );

	int hPos = 0 ;

	_filename = new QLineEdit( this );
	_validatorFilename = new GUIMFilenameValidator( this );
	_bFilename = new QPushButton( "...", this );
	_labelValidator = new QLabel(TEXT_VALIDATOR );
	_labelFilename = new QLabel( QObject::tr("data filename : "), this );

	_grid->addWidget( const_cast<QLabel*>(_labelFilename), hPos, 1 );
	_grid->addWidget( _filename, hPos, 2, 1, 3 );
	_grid->addWidget( _bFilename, hPos++, 5 );
	_grid->addWidget( _labelValidator, hPos++, 2 );

	connect( _bFilename, SIGNAL( released() ), this, SLOT( setFilename() ) );
	connect( _filename, SIGNAL( textChanged(const QString &) ), this, SLOT( verifyText(const QString &) ) );

	_grid->addWidget( _bDefault, hPos, 1 );

	_grid->addWidget( _ok, hPos, 4 );

	_grid->addWidget( _cancel, hPos, 5 );

	_ok->setEnabled( false );
	connect( _bDefault, SIGNAL( released() ), this, SLOT( noWeight()) ) ;

}

GUIMWeightModifier::~GUIMWeightModifier() {
}

void GUIMWeightModifier::setFilename() {
	if( _filename ) {
		_filename->setText( QFileDialog::getOpenFileName( this, tr("Open Weight File"),"./", tr("Weight files (*.wgt);;Text files (*.txt);;All files (*)") ) );
	}
}

void GUIMWeightModifier::verifyText( const QString & text ) {
	bool finish = true ;
	if( _filename && _validatorFilename && _labelValidator ) {
		QString tmpText = text ;
		int cursorPos = _filename->cursorPosition();

		if( _validatorFilename->validate( tmpText, cursorPos ) == QValidator::Acceptable ) {
			_labelValidator->setText("");
		}
		else {
			_labelValidator->setText(TEXT_VALIDATOR);
			finish = false;
		}
	}
	_ok->setEnabled( finish );
}

void GUIMWeightModifier::noWeight() {
	/*QVariant v ;
	v.setValue(QString::fromStdString(XEMMVCModel::DEFAULTFILENAME));*/


	GUIMAction removeAction = createRemoveAction(_index, XEM::MVC::View::WEIGHT);
	_processor->addAction(removeAction);
	confirm() ;
}


void GUIMWeightModifier::ok() {
	QVariant v ;
	v.setValue( _filename->text() );
	GUIMAction setAction = createSetAction(_index, v);
	_processor->addAction(setAction);

	confirm();
}

void GUIMWeightModifier::discard() {
	cancel();
}
