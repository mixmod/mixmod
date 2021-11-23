/***************************************************************************
                             SRC/GUI/MIXMOD_QT/MVCRootTreeItem.h  description
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
#ifndef __MVC_ROOT_TREEITEM
#define __MVC_ROOT_TREEITEM

#include "mixmod_mvc/TreeItem.h"

namespace XEM {
namespace MVC {

struct RootTreeItem : public TreeItem {

public :

	enum ProjectType {
	    NoProjectType = 0, 		// by default, when no type of project is set
	    Classification, 		// for classification project
	    DiscriminantAnalysis, 	// for discriminant analysis
	    InputProject, 		// for a project load from a input
	    UserProject = 8 		// for User project
	};

	enum DataType {
	    NoDataType = 0, 		// by default, when no type of data is set
	    Qualitative,
	    Quantitative
	};

	RootTreeItem( const std::string&, TreeKeyword );

	virtual ~RootTreeItem();

	void setProjectType( ProjectType newType ) {
		_projectType = newType ;
	}
	ProjectType getProjectType() const {
		return _projectType ;
	}

	void setDataType( DataType newType ) {
		_dataType = newType ;
	}
	DataType getDataType() const {
		return _dataType ;
	}

protected :

	// data
	ProjectType _projectType ;
	DataType _dataType ;
};

}
}

#endif // __MVC_ROOT_TREEITEM
