/***************************************************************************
							 SRC/GUI/MIXMOD_MVC/Controler.h  description
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

#ifndef ___MVC_CONTROLLER_H__
#define ___MVC_CONTROLLER_H__

#include "mixmod_mvc/View.h"
#include "mixmod_mvc/Model.h"
#include "mixmod_mvc/Event.h"
#include <exception>

namespace XEM {
namespace MVC {


struct no_model_or_view_exception : public std::exception {
	virtual const char* what() const throw () {
		return "No Model or View in Controler";
	}
};

class Controller {
public:
	// functions
	Controller(View* = NULL, Model* = NULL);
	~Controller();

	// view
	void setView(View*);
	View* getView() const;

	void updateView();
	void updateViewAD();

	// model
	void setModel(Model*);
	Model* getModel() const;

	// process Event
	void processEvent(TreeItem* treeItem, Event* e);

	// setters
	template< class T >
	void setValue(TreeItem* treeItem, const T& value);

	template< class T >
	void insertChild(TreeItem* treeItem, int64_t pos, const T& value);

	template< class T >
	void removeChild(TreeItem * treeItem, int64_t pos);

private:
	// functions
	Controller(const Controller&);
	Controller& operator=(const Controller&);

	bool canProcess() const;

	// data
	View* _view;
	Model* _model;
};

/*** View ***/

inline void Controller::setView(View* newView) {
	_view = newView;
}

inline View* Controller::getView() const {
	return _view;
}

/************/

/*** Model ***/

inline void Controller::setModel(Model* newModel) {
	_model = newModel;
}

inline Model* Controller::getModel() const {
	return _model;
}

/*************/

inline bool Controller::canProcess() const {
	return (_model && _view);
}

// set Value
template< class T >
void Controller::setValue(TreeItem * treeItem, const T& value) {
	if (!canProcess()) throw no_model_or_view_exception();

	Event* e = _model->setValue<T>(treeItem, value);

	if (e) {
		e->setControler(this);
		_view->setValue(treeItem, e->getDisplay());
		if (e->launchNewEvent()) {
			processEvent(treeItem, e);
		}
		else if (e->launchError()) {
			throw e->getError();
		}
		delete e;
	}
}

// insert Child
template< class T >
void Controller::insertChild(TreeItem* treeItem, int64_t pos, const T& value) {
	if (!canProcess()) throw no_model_or_view_exception();

	Event* e = _model->insertChild(treeItem, pos, value);

	if (e) {
		e->setControler(this);
		_view->insertChild(treeItem, pos, e->getKeyword(), e->getDisplay());
		if (e->launchNewEvent()) {
			processEvent(treeItem, e);
		}
		delete e;
	}
}

// remove child
template< class T >
void Controller::removeChild(TreeItem* treeItem, int64_t pos) {
	if (!canProcess()) throw no_model_or_view_exception();

	Event* e = _model->removeChild<T>(treeItem, pos);

	if (e) {
		e->setControler(this);
		_view->removeChild(treeItem, pos);
		if (e->launchNewEvent()) {
			processEvent(treeItem, e);
		}
		delete e;
	}
}


}
}

#endif
