/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMStopRuleModifier.h  description
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
#ifndef __GUIM_STOPRULE_MODIFIER_H__
#define __GUIM_STOPRULE_MODIFIER_H__

#include <QGridLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QCheckBox>
//#include <QRadioButton>
#include <QPushButton>

#include "GUIMAbstractModifier.h"
#include "mixmod/Utilities/Util.h"
#include "MVCRootTreeItem.h"

class GUIMStopRuleModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :
	GUIMStopRuleModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*,const QModelIndex&, QWidget* );
	virtual ~GUIMStopRuleModifier();
	virtual void init() ;

private slots :
	void ok();
	void discard();

	void canConfirm();

protected :

	QGridLayout* _grid ;

	QScrollArea* _area ;

	QGroupBox* _group ;

	QAbstractButton* _epsilonButton ;
	QAbstractButton* _nbIterationButton ;
	//QRadioButton* _bothButton ;

	bool _isEpsilon ;
	int _posEpsilon ;

	bool _isNbIteration ;
	int _posNbIteration ;

};

#endif // __GUIM_STOPRULE_MODIFIER_H__
