/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMDataCreator.h  description
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
#ifndef __GUIM_DATA_CREATOR_H__
#define __GUIM_DATA_CREATOR_H__

#include <QVector>
#include <QWidget>
#include <QScrollArea>
#include <QWizardPage>
#include <QGridLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QResizeEvent>

#include <QWizardPage>
#include <QWizard>
#include "GUIMFilenameValidator.h"
#include "GUIMSpinBoxesWidget.h"
#include "MVCRootTreeItem.h"
#include "mixmod_iostream/DomData.h"
#include "mixmod/Utilities/Util.h"

class GUIMDataCreator : public QWizardPage {
	Q_OBJECT

	friend class GUIMProjectCreator ;

public :

	GUIMDataCreator( XEM::MVC::RootTreeItem::ProjectType type = XEM::MVC::RootTreeItem::Classification, QWizard* = 0);
	virtual ~GUIMDataCreator();

public slots :

	void setFilename();
	void setFilenameReclassify();
	void setFilenamePartition();
	void updateNbNbCluster( int );
	void verifyText( const QString& );
	void verifyTextPartition( const QString& );
	void verifyTextReclassify( const QString& );
	void addToNbNbCluster();
	void removeToNbNbCluster();

protected : // function

	virtual void resizeEvent( QResizeEvent* );

private : // data

	QGridLayout* _grid ;
	const QLabel * _labelNbNbCluster;

	QSpinBox * _sbNbNbCluster, * _sbNbClusterAD ;

	QScrollArea* _nbClusterArea ;
	SpinBoxesWidget* _nbCluster ;

	QButtonGroup* _bgroup ;

	QPushButton* _plus ;
	QPushButton* _minus ;

	QLabel* _labelFilename, * _labelFilenamePartition, * _labelFilenameReclassify ;
	QLineEdit* _filename, * _filenamePartition, * _filenameReclassify ;
	GUIMFilenameValidator* _validatorFilename, * _validatorFilenamePartition, * _validatorFilenameReclassify ;
	QAbstractButton* _bFilename, * _bFilenamePartition, * _bFilenameReclassify;
	QLabel* _labelValidator, * _labelValidatorPartition, * _labelValidatorReclassify ;
	QString TEXT_VALIDATOR ;

	int _height;
	QRegExpValidator* _validatorXML;
};

#endif //  __GUIM_DATA_CREATOR_H__
