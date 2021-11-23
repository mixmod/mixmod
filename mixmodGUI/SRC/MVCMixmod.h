/***************************************************************************
                             SRC/GUI/MIXMOD_QT/MVCMixmod.h  description
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
#ifndef __MVC_MIXMOD_H__
#define __MVC_MIXMOD_H__

#include <QVariant>

#include "mixmod_mvc/Model.h"
#include "mixmod_mvc/View.h"
#include "mixmod_mvc/Controller.h"
#include "MVCRootTreeItem.h"

#include "mixmod_mvc/Event.h"

//#include "GUIMMetaData.h"

namespace XEM {
namespace MVC {

class Mixmod {

public :

	Mixmod();
	~Mixmod();

	Mixmod(ClusteringMain * cMain);

	// construct
	// ------------
	// Clustering Main with gaussian Data
	void constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName);

	// Clustering Main with binary Data
	void constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName, vector<int64_t> iModality);

	//Clustering Main from dataDescription
	void constructClusteringMain(vector<int64_t> nbCluster, DataDescription * dataDescription);

	// DA Main with gaussian Data
	void constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify);

	// DA Main with binary Data
	void constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify, vector<int64_t> iModality);

	bool insertChild( TreeItem*, int );
	bool removeChild( TreeItem*, int );
	bool setValue( TreeItem*, const QVariant& );

	bool find( TreeItem* ) const ;

	View* getView() const ;
	Controller* getEngine() const ;
	Model* getModel() const ;

	void setOutputNULL(  );//after remove in Qt
	void sortOutput(CriterionName criterionName);

private :

	// function
	Mixmod( const Mixmod& );
	Mixmod& operator=( const Mixmod& );

	// data
	Model* _model ;
	View* _view ;
	Controller* _engine ;
};

inline View* Mixmod::getView() const {
	return _view ;
}

inline Controller* Mixmod::getEngine() const {
	return _engine ;
}

inline Model* Mixmod::getModel() const {
	return _model ;
}

inline void Mixmod::sortOutput(CriterionName criterionName) {
	_model->sortOutput(criterionName);
	_engine->getView()->updateOutput(_model->getOutput());
}

inline void Mixmod::setOutputNULL() {
	_view->killNoKeyword();
	_model->setOutputNull();
}

}
}

#endif // __MVC_MIXMOD_H__
