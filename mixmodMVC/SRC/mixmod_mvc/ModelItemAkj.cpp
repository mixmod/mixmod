/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/ModelItemAkj.cpp  description
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
#include "mixmod_mvc/ModelItemAkj.h"
#include "mixmod_mvc/EventMixmodSetInitName.h"
#include "mixmod_mvc/EventMixmodDisplayCenter.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"

namespace XEM {
namespace MVC {


ModelItem<TreeInitParameterAkj, double>::ModelItem( Input* iInput, double* iTabAI, int64_t iPosition) {
	_tabAI = iTabAI;
	_input = iInput;
	_position = iPosition;
}

ModelItem<TreeInitParameterAkj, double> ::~ModelItem() {
	_input = NULL ;
}

Event* ModelItem<TreeInitParameterAkj, double> ::setValue( int64_t /*position*/) {
	return NULL ;
}

Event* ModelItem<TreeInitParameterAkj, double> ::insertChild( int64_t position) {
	ClusteringStrategy * strategy = dynamic_cast<ClusteringInput*>(_input)->getStrategy();
	GaussianHDDAParameter * initParam = ((GaussianHDDAParameter *)strategy->getStrategyInit()->getInitParameter(_position));
	Event* eventDisplay = new EventMixmodDisplayCenter(_tabAI,initParam->getTabD()[position]);

	return eventDisplay ;
}

Event* ModelItem<TreeInitParameterAkj, double> ::removeChild(int64_t /*position*/) {
	return NULL ;
}
}
}
