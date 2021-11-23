/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodInsertDispersion.cpp  description
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
#include "mixmod_mvc/EventMixmodInsertDispersion.h"
#include "mixmod_mvc/Controller.h"

namespace XEM {
namespace MVC {



EventMixmodInsertDispersion::EventMixmodInsertDispersion(int64_t iNbCluster, XEM::Matrix** iTabSigma, int64_t iPbDimension, int64_t iPosition) {
	_nbCluster = iNbCluster;
	_tabSigma = iTabSigma;
	_position = iPosition;
	_pbDimension = iPbDimension;

}

EventMixmodInsertDispersion::~EventMixmodInsertDispersion() {
}

std::string EventMixmodInsertDispersion::getDisplay() const {
	return string();
}

bool EventMixmodInsertDispersion::launchNewEvent() const {
	return true;
}

void EventMixmodInsertDispersion::process(TreeItem * treeItem) {
	TreeItem * dispersionItem = treeItem->getChild(_position);
	for (int64_t i=0; i<_nbCluster; ++i) {
		_controller->insertChild(dispersionItem,i,(double **) NULL);
		TreeItem * dispersionChildItem = dispersionItem->getChild(i);
		for (int64_t j=0; j<_controller->getModel()->getInput()->getPbDimension(); ++j) {
			double * tmp = _tabSigma[i]->storeToArray()[j];
			_controller->insertChild(dispersionChildItem,j,tmp);
		}
	}
}

TreeKeyword EventMixmodInsertDispersion::getKeyword() const {
	return TreeInitDispersion;
}

EventMixmodInsertDispersionB::EventMixmodInsertDispersionB(int64_t iNbCluster, double*** iTabScatter, int64_t iPbDimension, int64_t iPosition) {
	_nbCluster = iNbCluster;
	_tabScatter = iTabScatter;
	_position = iPosition;
	_pbDimension = iPbDimension;

}

EventMixmodInsertDispersionB::~EventMixmodInsertDispersionB() {
}

std::string EventMixmodInsertDispersionB::getDisplay() const {
	return string();
}

bool EventMixmodInsertDispersionB::launchNewEvent() const {
	return true;
}

void EventMixmodInsertDispersionB::process(TreeItem * treeItem) {
	//Identifier id2 (id,TreeInitScatter,_position);
	TreeItem * scatterItem = treeItem->getChild(_position);
	for (int64_t i=0; i<_nbCluster; ++i) {
		_controller->insertChild(scatterItem,i,(double **) NULL);
		//Identifier id3 (id2,TreeInitScatterChild,i);
		TreeItem * dispersionChildItem = scatterItem->getChild(i);
		for (int64_t j=0; j<_controller->getModel()->getInput()->getPbDimension(); ++j) {
			_controller->insertChild(dispersionChildItem,j,_tabScatter[i][j]);
		}
	}
}


TreeKeyword EventMixmodInsertDispersionB::getKeyword() const {
	return TreeInitScatter;
}
}
}
