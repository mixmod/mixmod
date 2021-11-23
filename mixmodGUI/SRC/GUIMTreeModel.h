/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMTreeModel.h  description
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
#ifndef __GUIM_TREE_MODEL_H__
#define __GUIM_TREE_MODEL_H__

#include <vector>

#include <QObject>
#include <QAbstractItemModel>
#include "GUIMProjectCreator.h"

#include "MVCMixmod.h"
#include "MVCRootTreeItem.h"
#include "mixmod/Kernel/IO/Input.h"
#include "GUIUtil.h"
#include "GUIMMetaData.h"

class GUIMTreeModel : public QAbstractItemModel {
	Q_OBJECT

public:

	GUIMTreeModel( GUIMProjectCreator*, QObject* = 0 );
	~GUIMTreeModel();

	GUIMTreeModel( GUIMProjectCreator*, XEM::ClusteringMain *, QObject* = 0 );

	QVariant data( const QModelIndex&, int ) const ;
	QVariant headerData( int, Qt::Orientation, int = Qt::DisplayRole ) const ;

	QModelIndex index( int, int, const QModelIndex& = QModelIndex() ) const ;
	QModelIndex parent( const QModelIndex& ) const ;

	int rowCount( const QModelIndex& = QModelIndex() ) const ;
	int columnCount( const QModelIndex& = QModelIndex() ) const ;

	Qt::ItemFlags flags( const QModelIndex& ) const ;
	bool setData( const QModelIndex&, const QVariant&, int = Qt::EditRole );

	bool setHeaderData( int, Qt::Orientation, const QVariant&, int = Qt::EditRole );

	bool insertColumns( int, int, const QModelIndex& = QModelIndex() );

	bool removeColumns( int, int, const QModelIndex& = QModelIndex() );

	bool insertRows( int, int, const QModelIndex& = QModelIndex() );

	bool removeRows( int, int, const QModelIndex& = QModelIndex() );

	// new functions
	void generateTree(XEM::ClusteringMain * cMain = NULL);

	XEM::MVC::RootTreeItem* root() const {
		return _rootItem ;
	}

	XEM::ClusteringMain * getClusteringMain(int pos) const {
		return _data[pos]->getModel()->getClusteringMain();
	};
	/*

		XEMInput* input( int pos ) const { return _data[pos]->getModel()->getInput(); }

	XEMClusteringOutput * getClusteringOutput(int pos) const{ return _data[pos]->getModel()->getOutput();};*/

	void setOutput( int pos );
	void sortOutput(int pos, XEM::CriterionName criterionName );
	void removeOutput( int );
	XEM::MVC::TreeItem* getItem( const QModelIndex& ) const ;
	//bool saveInputXML(const QString& s);

protected : // functions

	void generateMixmod( int pos );
	void generateMixmod( int pos, XEM::ClusteringMain * cMain);


protected : // data ??

	XEM::MVC::RootTreeItem* _rootItem ;

	// _data contains MIXMOD data (input, output, ...)
	QVector< XEM::MVC::Mixmod* > _data ;

	GUIMProjectCreator* _creator ;
};


#endif // __GUIM_TREE_MODEL_H__
