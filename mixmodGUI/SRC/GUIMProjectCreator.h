/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMProjectCreator.h  description
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
#ifndef __GUIM_PROJECT_CREATOR_H__
#define __GUIM_PROJECT_CREATOR_H__

#include <QWizard>
#include "GUIMDataCreator.h"
#include "GUIMMetaData.h"

class GUIMProjectCreator : public QWizard {
	Q_OBJECT

public :

	GUIMProjectCreator( XEM::MVC::RootTreeItem::ProjectType, QWidget* = 0, Qt::WindowFlags = 0 );
	virtual ~GUIMProjectCreator();

	XEM::MVC::RootTreeItem::ProjectType getProjectType() const {
		return _projectType ;
	}
	XEM::MVC::RootTreeItem::DataType getDataType() const {
		return _dataType ;
	}

	//long getNbSample() const { return _nbSample ; }
	//int64_t getPbDimension() const { return _pbDimension ; }
	//const QString& getDataFilename() const { return _dataFilename ; }
	const QString& getDataFilenamePartition() const {
		return _dataPartition ;
	}
	const QString& getDataFilenameReclassify() const {
		return _dataFilenameReclassify ;
	}
	//const QString& getWeightFilename() const { return _weightFilename ; }

	const QVector< int64_t >& getNbClusters() const {
		return _vClusters ;
	}
	//const QVector< QPair< XEMModelName, QVector<int64_t> > >& getModels() const { return _vModels ; }
	const QVector< XEM::CriterionName >& getCriteria() const {
		return _vCriteria ;
	}
	XEM::DataDescription * getDataDescription() const {
		return _dataDescription;
	};
	//const QVector< int64_t >& getModality() const { return _vModality ; }

private slots :

	void finished();

signals :

	void itemCreated();

private :// data

	XEM::MVC::RootTreeItem::ProjectType _projectType ;
	XEM::MVC::RootTreeItem::DataType _dataType ;
	XEM::DataDescription * _dataDescription;
	//long _nbSample ;
	//int64_t _pbDimension ;
	//QString _dataFilename ;
	QString _dataPartition ;
	QString _dataFilenameReclassify ;
	//QString _weightFilename ;

	QVector< int64_t > _vClusters ;
	//QVector< QPair< XEMModelName, QVector<int64_t> > > _vModels ;
	QVector< XEM::CriterionName > _vCriteria ;
	//QVector< int64_t > _vModality ;
};

#endif // __GUIM_PROJECT_CREATOR_H__
