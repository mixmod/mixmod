/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMKnownPartitionModifier.cpp  description
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
#include "GUIMKnownPartitionModifier.h"

#include <sstream>
#include <QMessageBox>
#include <QCursor>
#include <QString>
#include <QPushButton>

#include "GUIMMetaData.h"
#include "mixmod_mvc/View.h"
#include "mixmod_mvc/Model.h"

GUIMKnownPartitionModifier::GUIMKnownPartitionModifier( XEM::MVC::RootTreeItem::ProjectType type, XEM::MVC::RootTreeItem::DataType dataType, XEM::MVC::TreeItem* treeKP,const QModelIndex& index,QWidget* parent )
	: GUIMAbstractModifier( type, dataType, treeKP, index, parent ),
	  _fixedWidth( 600 ), _bNoPartition( new QPushButton( tr("No Partition"), this ) ) {
	//init();
	QString TEXT_VALIDATOR = tr("Not a valid File") ;
	setWindowTitle( QObject::tr("Known Partition : ") );
	move( QCursor::pos().x(), QCursor::pos().y() );
	setFixedWidth( _fixedWidth );

	_grid = new QGridLayout( this );

	int hPosMax = 2 ;
	int hPos = 0 ;
	_entry = new GUIMTextEntryWidget( this ) ;

	_entry->_filename = new QLineEdit( this );
	QTimer::singleShot(0,_entry->_filename,SLOT(setFocus()));
	_entry->_validatorFilename = new GUIMFilenameValidator( this );
	_entry->_bFilename = new QPushButton( "...", this );
	_entry->_labelValidator = new QLabel(TEXT_VALIDATOR );
	_entry->_labelFilename = new QLabel( QObject::tr("data filename : "), this );

	_grid->addWidget( const_cast<QLabel*>(_entry->_labelFilename),  hPos, 1 );
	_grid->addWidget( _entry->_filename,  hPos, 2, 1, 3 );
	_grid->addWidget( _entry->_bFilename,  hPos++, 5 );
	_grid->addWidget( _entry->_labelValidator,  hPos++, 2 );

	connect( _entry->_bFilename, SIGNAL( released() ), _entry, SLOT( setFilename() ) );
	connect( _entry->_filename, SIGNAL( textChanged(const QString &) ), _entry, SLOT( verifyText(const QString &) ) );
	connect( _entry->_filename, SIGNAL( textChanged(const QString &) ), this, SLOT( verifyAllText(const QString &) ) );

	if (treeKP->getKeyword() == XEM::MVC::TreeInitPartition || _projectType == XEM::MVC::RootTreeItem::DiscriminantAnalysis)
		_bNoPartition->setVisible(false);

	//validator XML
	QRegExp rxXML("*.mxd");
	rxXML.setPatternSyntax(QRegExp::Wildcard);
	_validatorXML = new QRegExpValidator(rxXML, 0);

	_grid->addWidget( _bNoPartition, hPosMax, 1 );

	_grid->addWidget( _ok, hPosMax, 4 );

	_grid->addWidget( _cancel, hPosMax, 5 );

	verifyAllText("");

	connect( _bNoPartition, SIGNAL( released() ), this, SLOT( noPartition()) ) ;
}

GUIMKnownPartitionModifier::~GUIMKnownPartitionModifier() {
}

void GUIMKnownPartitionModifier::noPartition() {
	/*QVariant v ;
	v.setValue(QString::fromStdString(XEMMVCModel::DEFAULTFILENAME));*/

	GUIMAction removeAction = createRemoveAction(_index, XEM::MVC::View::KNOWN_PARTITION);
	_processor->addAction(removeAction);
	confirm() ;
}


void GUIMKnownPartitionModifier::ok() {
	if ( _processor->getNbAction() )
		_processor->removeAll();

	QVariant v ;
	v.setValue(_entry->_filename->text() );
	GUIMAction setAction = createSetAction(_index, v);
	_processor->addAction(setAction);

	confirm();
}

void GUIMKnownPartitionModifier::discard() {
	cancel();
}

void GUIMKnownPartitionModifier::verifyAllText( const QString& ) {
	bool finish = true ;

	QString tmpText = _entry->_filename->text() ;
	int cursorPos = _entry->_filename->cursorPosition();
	if( !( _entry->_validatorFilename->validate( tmpText, cursorPos ) == QValidator::Acceptable) /*|| !(_validatorXML->validate(tmpText, cursorPos) == QValidator::Acceptable)*/) {
		finish = false ;
	}

	_ok->setEnabled( finish );
}
