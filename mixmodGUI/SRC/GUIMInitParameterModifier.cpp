/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMInitParameterModifier.cpp  description
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
#include "GUIMInitParameterModifier.h"
#include <sstream>

#include <QCursor>
#include <QString>
#include <QFileDialog>

#include "GUIMMetaData.h"
#include "mixmod_mvc/View.h"
#include "mixmod_mvc/Model.h"

GUIMInitParameterModifier::GUIMInitParameterModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeKP,const QModelIndex& index,QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeKP, index, parent ),
	  _fixedWidth( 600 ) {
	QString TEXT_VALIDATOR = tr("Not a valid File") ;
	setWindowTitle( QObject::tr("Parameter : ") );
	QFont font;
	font.setUnderline( true );
	move( QCursor::pos().x(), QCursor::pos().y() );
	setFixedWidth( _fixedWidth );

	_widget = new QWidget( this );
	_grid = new QGridLayout(this);

	QLabel* labelParam = new QLabel( QObject::tr("Filename "), this);
	labelParam->setFont( font );

	int hPos=0;
	_grid->addWidget( labelParam, hPos, 0 );

	_filename = new QLineEdit( _widget );
	QTimer::singleShot(0,_filename,SLOT(setFocus()));
	_validatorFilename = new GUIMFilenameValidator( _widget );
	_bFilename = new QPushButton( "...", _widget );
	_bFilename->setStyleSheet("QPushButton {background:qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #82aae6, stop: 1.0 #ffffff)};");
	connect( _bFilename, SIGNAL( released() ), this, SLOT( setFilename() ) );
	connect( _filename, SIGNAL( textChanged(const QString &) ), this, SLOT( verifyText(const QString &) ) );
	_labelValidator = new QLabel( TEXT_VALIDATOR );

	_grid->addWidget( _filename, hPos, 2, 1, 3 );
	_grid->addWidget( _bFilename, hPos, 5 );
	_grid->addWidget( _labelValidator, ++hPos, 2 );

	_grid->addWidget( _ok, ++hPos, 4 );
	_grid->addWidget( _cancel, hPos, 5 );
	_ok->setEnabled(false);
}

GUIMInitParameterModifier::~GUIMInitParameterModifier() {
}

void GUIMInitParameterModifier::setFilename() {
	_filename->setText( QFileDialog::getOpenFileName( this, tr("Open Data"),"./", tr("Parameter files (*.init);;Data files (*.dat);;Text files (*.txt);;All files (*)") ) );
}

void GUIMInitParameterModifier::verifyText( const QString & text ) {
	QString tmpText = text ;
	int cursorPos = _filename->cursorPosition() ;

	if( _validatorFilename->validate( tmpText, cursorPos ) == QValidator::Acceptable ) {
		_labelValidator->setText("");
		_ok->setEnabled(true);
	}
	else {
		_labelValidator->setText(TEXT_VALIDATOR);
		_ok->setEnabled(false);
	}
}

void GUIMInitParameterModifier::ok() {
	if ( _processor->getNbAction() )
		_processor->removeAll();

	QVariant v ;
	v.setValue(_filename->text() );
	GUIMAction setAction = createSetAction(_index, v);
	_processor->addAction(setAction);

	confirm();
}

void GUIMInitParameterModifier::discard() {
	cancel();
}
