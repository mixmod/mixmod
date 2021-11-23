/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMInitModifier.h  description
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
#ifndef __GUIM_INTI_MODIFIER_H__
#define __GUIM_INIT_MODIFIER_H__

#include "GUIMAbstractModifier.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QScrollArea>

#include "mixmod/Utilities/Util.h"
#include "MVCRootTreeItem.h"
#include "GUIMFilenameValidator.h"
#include "GUIMTextEntryWidget.h"

class GUIMInitModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :

	GUIMInitModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*, const QModelIndex&, QWidget* );
	virtual ~GUIMInitModifier();

	virtual void init();

private slots :

	void ok();
	void discard();

	void verifyAllText( const QString& );
	void activateParameters();
	void canConfirm();

protected :

	// data
	QGridLayout* _grid, *_gridParam, * _gridInInitBox;

	QValidator* _validFilename, * _validNbTryI, *_validNbIterationI, *_validEpsilonI;

	QWidget* _widget ;

	QLineEdit* _filename, *_editNbTryInInit, *_editNbIterationInInit, *_editEpsilonInInit;
	GUIMFilenameValidator* _validatorFilename ;
	QAbstractButton* _bFilename ;
	QLabel* _labelValidator ;
	QString TEXT_VALIDATOR ;

	QGroupBox* _gMethod, *_gName, * _gParameters, * _gInInit;
	QHBoxLayout *_methodBox, * _parameterBox;
	QVBoxLayout* _widgetBox,* _nameBox, * _vInInitBox;

	QButtonGroup* _nameGroup ;
	QRadioButton* _RANDOMButton, * _USERButton, * _USER_PARTITIONButton, * _SMALL_EMButton, * _CEM_INITButton, * _SEM_MAXButton ;

	bool _validate;
	XEM::StrategyInitName _oldName;
	QVector< GUIMTextEntryWidget* > _filenames ;
	int _nbFilename;
	QScrollArea * _scrollArea;
};

#endif // __GUIM_INIT_MODIFIER_H__
