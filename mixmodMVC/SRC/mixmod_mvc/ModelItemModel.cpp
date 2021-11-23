/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemModel.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2013
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
#include "mixmod_mvc/ModelItemModel.h"
#include "mixmod_mvc/EventMixmodInsertSubDim.h"
#include "mixmod_mvc/EventMixmodSetModelChild.h"
#include "mixmod_mvc/EventMixmodInsertModel.h"
#include "mixmod_mvc/NoEvent.h"
#include "mixmod/Kernel/Model/ModelType.h"

namespace XEM {
namespace MVC {

ModelItem<TreeModelChild, ModelName>::ModelItem( Input* iInput, ModelName iModelName) {
	_modelName = iModelName;
	_input = iInput;
}

ModelItem<TreeModelChild, ModelName> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeModelChild, ModelName> ::setValue( int64_t position) {
	ModelName oldNameModel = _input->getModelType()[position]->getModelName();
	ModelType modelType(_modelName);
	_input->setModelType(&modelType, position);
	Event* eventMixmodSetModel = new EventMixmodSetModelChild(_modelName,oldNameModel,_input->getNbCluster(0),_input->getModelType()[position]->getSubDimensionEqual());

	return eventMixmodSetModel;
}

Event* ModelItem<TreeModelChild, ModelName> ::insertChild( int64_t position) {
	int64_t nbModel = _input->getModelType().size();
	if( position < 0 || position>nbModel) {
		return NULL;
	}
	ModelType modelType(_modelName);
	_input->insertModelType( &modelType, position);
	Event* eventMixmodInsertModel = new EventMixmodInsertModel(_modelName,_input->getNbCluster(0),_input->getModelType()[position]->getSubDimensionEqual(),position);

	return eventMixmodInsertModel;
}

Event* ModelItem<TreeModelChild, ModelName> ::removeChild(int64_t position) {

	Event* event;
	if ((_input->getModelType().size()==1 && (position==0) ) || _input->getModelType().size()<=position || position<0) {
		return NULL;
	}
	else {
		_input->removeModelType(position);
		event = new NoEvent();
	}
	return event;

}

}
}
