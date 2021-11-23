/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMModelModifier.h  description
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
#ifndef __GUIM_MODEL_MODIFIER_H__
#define __GUIM_MODEL_MODIFIER_H__

#include "GUIMAbstractModifier.h"

#include <QResizeEvent>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QCheckBox>
#include <QVector>
#include <QScrollArea>

#include "mixmod/Utilities/Util.h"
#include "MVCRootTreeItem.h"

class GUIMModelModifier : public GUIMAbstractModifier {
	Q_OBJECT

public :

	GUIMModelModifier( XEM::MVC::RootTreeItem::ProjectType, XEM::MVC::RootTreeItem::DataType, XEM::MVC::TreeItem*, const QModelIndex&, QWidget* );
	virtual ~GUIMModelModifier();

	virtual void init() ;

private slots :

	void ok();
	void discard();

	void canConfirm();

	void selectAllSpherical();
	void selectAllDiagonal();
	void selectAllGeneral();
	void selectAllBinary();
	void selectAllHD();

	void verifyAllSpherical();
	void verifyAllDiagonal();
	void verifyAllGeneral();
	void verifyAllBinary();
	void verifyAllHD();

protected :

	// functions
	void initWidget();
	QAbstractButton* addToGroup( XEM::ModelName );
	void selectAll( QButtonGroup*, QCheckBox* );
	void verifyAll( QButtonGroup*, QCheckBox* );

	// data
	QScrollArea* _scrollArea ;
	QWidget* _widget ;
	QVBoxLayout* _widgetBox ;

	QGridLayout* _grid ;

	QGroupBox* _sphericalGroup ;
	QVBoxLayout* _sphericalBox ;
	QButtonGroup* _sphericalButtons ;

	QGroupBox* _diagonalGroup ;
	QVBoxLayout* _diagonalBox ;
	QButtonGroup* _diagonalButtons ;

	QGroupBox* _generalGroup ;
	QVBoxLayout* _generalBox ;
	QButtonGroup* _generalButtons ;

	QGroupBox* _binaryGroup ;
	QVBoxLayout* _binaryBox ;
	QButtonGroup* _binaryButtons ;

	QGroupBox* _hdGroup ;
	QVBoxLayout* _hdBox ;
	QHBoxLayout* _hdModelLine ;
	QButtonGroup* _hdButtons ;


	QLabel* _sphericalLabel ;
	QCheckBox* _sphericalButton ;

	QLabel* _diagonalLabel ;
	QCheckBox* _diagonalButton ;

	QLabel* _generalLabel ;
	QCheckBox* _generalButton ;

	QLabel* _binaryLabel ;
	QCheckBox* _binaryButton ;

	QLabel* _hdLabel ;
	QCheckBox* _hdButton ;

	QVector< QAbstractButton* > _vButtons ;
	QVector< bool > _modelInTree ;

	// static data
	static const int HORIZONTAL_SPAN_AT_END ;
};

#endif // __GUIM_MODEL_MODIFIER_H__
