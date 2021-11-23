/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIMGraphicManager.cpp  description
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

#include "GUIMGraphicManager.h"
#include "GUIUtil.h"

GUIMGraphicManager::GUIMGraphicManager(QMainWindow* parent) {
	_parent = parent;
	_cMain = NULL;
}

GUIMGraphicManager::~GUIMGraphicManager() {
	for (int64_t i = 0; i<_vGraphics.size(); ++i) {
		delete _vGraphics[i];
	}
	_vGraphics.clear();
}

void GUIMGraphicManager::close() {
	for (int64_t i = 0; i<_vGraphics.size(); ++i) {
		if (_vGraphics[i]) {
			_vGraphics[i]->close();
			delete _vGraphics[i];
		}
	}
	_vGraphics.clear();
	_cMain = NULL;
}

void GUIMGraphicManager::setClusteringMain(XEM::ClusteringMain* main) {
	_cMain = main;
}

void GUIMGraphicManager::init() {
	for (int64_t i=0; i<_vGraphics.size(); ++i) {
		if (_vGraphics[i])
			delete _vGraphics[i];

		_vGraphics[i] = NULL ;
	}
}

void GUIMGraphicManager::createAll(XEM::MVC::RootTreeItem::DataType dataType) {

	if (dataType == XEM::MVC::RootTreeItem::Quantitative) {
		_vGraphics.resize(XEM::nbQuantitativeGraphics);
	}
	else if(dataType == XEM::MVC::RootTreeItem::Qualitative) {
		_vGraphics.resize(XEM::nbQualitativeGraphics);
	}
	init();
	_indexResult = 0;
	for (int64_t i =0; i<_vGraphics.size(); ++i) {
		if(dataType == XEM::MVC::RootTreeItem::Quantitative) {
			switch(i) {
			case static_cast<int64_t>(QuantitativePoint): {
				if (_cMain->getInput()->getPbDimension()>1) {
					_vGraphics[i] = new GUIMGraphicQuantitativePoint(_parent, _cMain);
					connect(_vGraphics[i], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
					_vGraphics[i]->create(_indexResult);
				}
				break;
			}
			case static_cast<int64_t>(QuantitativeClass): {
				if (_cMain->getInput()->getPbDimension()>1) {
					_vGraphics[i] = new GUIMGraphicQuantitativeClass(_parent, _cMain);
					connect(_vGraphics[i], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
					_vGraphics[i]->create(_indexResult);
				}
				break;
			}
			case static_cast<int>(QuantitativeHistogram) :
				_vGraphics[i] = new GUIMGraphicQuantitativeHist(_parent, _cMain);
				_vGraphics[i]->create(_indexResult);
				connect(_vGraphics[i], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
				break;
			default:
				break;
			}
		}
		else if (dataType == XEM::MVC::RootTreeItem::Qualitative) {
			switch(i) {
			case static_cast<int64_t>(QualitativeDiagram):
				_vGraphics[i] = new GUIMGraphicQualitativeDiagram(_parent, _cMain);
				connect(_vGraphics[i], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
				_vGraphics[i]->create(_indexResult);
				break;
			case static_cast<int64_t>(QualitativePointBoxes):
				break;
			default :
				break;
			}
		}

	}
	if (_vGraphics.size()>=2 && _vGraphics[0] && _vGraphics[1])
		_parent->tabifyDockWidget(_vGraphics[0]->getDock(), _vGraphics[1]->getDock());
}

void GUIMGraphicManager::create(XEM::MVC::RootTreeItem::DataType dataType, int index, int64_t indexResult) {
	if (_vGraphics.isEmpty() || indexResult!=_indexResult) { //new graphic or change of result
		if (dataType == XEM::MVC::RootTreeItem::Quantitative) {
			_vGraphics.resize(XEM::nbQuantitativeGraphics);
		}
		else if(dataType == XEM::MVC::RootTreeItem::Qualitative) {
			_vGraphics.resize(XEM::nbQualitativeGraphics);
		}
		init();
	}
	_indexResult = indexResult;


	if (!_vGraphics[index]) {
		if(dataType == XEM::MVC::RootTreeItem::Quantitative) {
			switch(index) {
			case static_cast<int>(QuantitativePoint):
				_vGraphics[index] = new GUIMGraphicQuantitativePoint(_parent, _cMain);
				_vGraphics[index]->create(_indexResult);
				connect(_vGraphics[index], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
				break;
			case static_cast<int>(QuantitativeClass):
				_vGraphics[index] = new GUIMGraphicQuantitativeClass(_parent, _cMain);
				connect(_vGraphics[index], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
				_vGraphics[index]->create(_indexResult);
				break;
			case static_cast<int>(QuantitativeHistogram) :
				_vGraphics[index] = new GUIMGraphicQuantitativeHist(_parent, _cMain);
				_vGraphics[index]->create(_indexResult);
				connect(_vGraphics[index], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
				break;
			default :
				break;
			}
		}
		else if (dataType == XEM::MVC::RootTreeItem::Qualitative) {
			switch(index) {
			case static_cast<int64_t>(QualitativeDiagram):
				_vGraphics[index] = new GUIMGraphicQualitativeDiagram(_parent, _cMain);
				connect(_vGraphics[index], SIGNAL( graphicToDelete(GUIMGraphic *) ), this, SLOT(deleteGraphic(GUIMGraphic *)));
				_vGraphics[index]->create(_indexResult);
				break;
			case static_cast<int64_t>(QualitativePointBoxes):
				break;
			default :
				break;
			}
		}
	}
	if (_vGraphics.size()>=2 && _vGraphics[0] && _vGraphics[1])
		_parent->tabifyDockWidget(_vGraphics[0]->getDock(), _vGraphics[1]->getDock());
}

const bool GUIMGraphicManager::hasMain() const {
	if (_cMain) {
		return true;
	}
	else {
		return false;
	}
}

const bool GUIMGraphicManager::hasGraphics() const {
	if (_vGraphics.isEmpty()) {
		return false;
	}
	else {
		return true;
	}
}

void GUIMGraphicManager::deleteGraphic(GUIMGraphic* graphic) {
	int64_t index = _vGraphics.indexOf(graphic);
	if (index>=0 && index<_vGraphics.size()) {
		delete _vGraphics[index];
		_vGraphics[index] = NULL;
	}
}

void GUIMGraphicManager::deleteGraphic(int indexGraphic) {
	if (indexGraphic>=0 && indexGraphic<_vGraphics.size()) {
		delete _vGraphics[indexGraphic];
		_vGraphics[indexGraphic] = NULL;
	}
}
