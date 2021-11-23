/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTextEntryWidget.cpp  description
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
#include "GUIMTextEntryWidget.h"
#include <QFileDialog>

GUIMTextEntryWidget::GUIMTextEntryWidget( QWidget* parent )
	: QWidget( parent ),
	  _labelFilename( NULL ), _filename( NULL ), _validatorFilename( NULL ), _bFilename( NULL ), _labelValidator( NULL ) {
	TEXT_VALIDATOR = tr("Not a valid File") ;
}

GUIMTextEntryWidget::~GUIMTextEntryWidget() {
}

void GUIMTextEntryWidget::setFilename() {
	if( _filename ) {
		_filename->setText( QFileDialog::getOpenFileName( this, tr("Open Partition File"),GUISettings::workDirectory.absolutePath(), tr("Partitions files (*.mxd);;Text files (*.txt);;All files (*)") ) );
	}
}

void GUIMTextEntryWidget::setFilenameParameter() {
	if ( _parameter == ParamPartition) {
		_filename->setText( QFileDialog::getOpenFileName( this, tr("Open Partition"),GUISettings::workDirectory.absolutePath(), tr("Partition files (*.mxd);;Text files (*.txt);;All files (*)") ) );
	}
	if ( _parameter == ParamInit) {
		_filename->setText( QFileDialog::getOpenFileName( this, tr("Open Data"),GUISettings::workDirectory.absolutePath(), tr("Parameter files (*.init);;Data files (*.dat);;Text files (*.txt);;All files (*)") ) );
	}
}

void GUIMTextEntryWidget::verifyText( const QString & text ) {
	if( _filename && _validatorFilename && _labelValidator ) {
		QString tmpText = text ;
		int cursorPos = _filename->cursorPosition();

		if( _validatorFilename->validate( tmpText, cursorPos ) == QValidator::Acceptable )
			_labelValidator->setText("");
		else
			_labelValidator->setText(TEXT_VALIDATOR);
	}
}
