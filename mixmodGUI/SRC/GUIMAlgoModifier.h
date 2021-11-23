/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMAlgoModifier.h  description
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
#ifndef __GUIM_ALGO_MODIFIER_H__
#define __GUIM_ALGO_MODIFIER_H__

#include "GUIMAbstractModifier.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QVector>
#include <QSpinBox>
#include <QDialogButtonBox>
#include "MVCRootTreeItem.h"

class GUIMAlgoModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :

	GUIMAlgoModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*, const QModelIndex&, QWidget* );
	virtual ~GUIMAlgoModifier();

	virtual void init() {};

private slots :

	void ok();
	void discard();

	void canConfirm();
	void verifyAlgo();

protected :

	// data
	QGridLayout* _grid, * _gridStopRuleValue ;

	QLineEdit* _editValueEpsilon, * _editValueNbIteration ;

	QValidator* _validEpsilon, * _validNbIteration;

	QWidget* _widget ;

	QGroupBox* _gPosition, * _gStopRule, * _gRule, * _gRuleValue, * _gAlgoName, * _gName;
	QHBoxLayout* _positionBox, * _algoNameBox, * _stopRuleBox;
	QVBoxLayout* _widgetBox, * _ruleBox, * _nameBox;

	QSpinBox* _valuePosition ;

	QButtonGroup* _algoNameGroup ;
	QRadioButton* _EMButton, * _CEMButton, * _SEMButton, * _MButton, * _MAPButton ;
	QAbstractButton* _epsilonButton, * _nbIterationButton ;
};

#endif // __GUIM_ALGO_MODIFIER_H__
