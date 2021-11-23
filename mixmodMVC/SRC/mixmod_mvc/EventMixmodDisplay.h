/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodDisplay.h  description
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
#ifndef __EVENTMIXMODDISPLAY_H__
#define __EVENTMIXMODDISPLAY_H__

#include <sstream>

#include "mixmod_mvc/Vector.h"
#include "mixmod_mvc/Matrix.h"
#include "mixmod_mvc/Scatter.h"

#include "mixmod_mvc/Util.h"
#include "mixmod_mvc/Event.h"

namespace XEM {
namespace MVC {



template< class T >
class EventMixmodDisplay :public Event {

public :
	EventMixmodDisplay(T iValue);
	~EventMixmodDisplay();
	virtual std::string getDisplay()const ;
	bool launchNewEvent() const ;
	void process(TreeItem * treeItem);
	virtual TreeKeyword getKeyword() const;
private :
	T _value;
};

template< class T >
EventMixmodDisplay<T>::EventMixmodDisplay(T iValue) {
	_value = iValue;
}


template< class T >
EventMixmodDisplay<T>::~EventMixmodDisplay() {
}


template< class T >
std::string EventMixmodDisplay<T>::getDisplay() const {
	std::stringstream ss ;
	ss << _value ;

	return ss.str() ;
}



template< class T >
void EventMixmodDisplay<T>::process(TreeItem* treeItem /*id*/) {
}

template< class T >
bool EventMixmodDisplay<T>::launchNewEvent() const {
	return false;
}

template<class T>
TreeKeyword EventMixmodDisplay<T>::getKeyword() const {
	return Event::getKeyword();
}


// specialisation pour T*


template< class T >
class EventMixmodDisplay<T*>:public Event {

public :
	EventMixmodDisplay(T* iValue,int64_t iSizeVector);
	~EventMixmodDisplay();
	std::string getDisplay() const;
	bool launchNewEvent() const;
	void process(TreeItem * treeItem);

private :
	T* _value;
	int64_t _sizeVector;
};

template< class T >
EventMixmodDisplay<T*>::EventMixmodDisplay(T* iValue,int64_t iSizeVector) {
	_value = iValue;
	_sizeVector = iSizeVector;
}


template< class T >
EventMixmodDisplay<T*>::~EventMixmodDisplay() {
}


template< class T >
std::string EventMixmodDisplay<T*>::getDisplay() const {
	Vector<T> vector = Vector<T>(_value,_sizeVector);
	std::stringstream ss ;
	ss << vector ;

	return ss.str() ;
}



template< class T >
void EventMixmodDisplay<T*>::process( TreeItem * /*id*/) {
}

template< class T >
bool EventMixmodDisplay<T*>::launchNewEvent() const {
	return false;
}








// specialisation pour T** avec T= double **


template< class T >
class EventMixmodDisplay<T**>:public Event {

public :
	EventMixmodDisplay(T** iValue, int64_t iPbDimension);
	~EventMixmodDisplay();
	virtual std::string  getDisplay() const;
	bool launchNewEvent() const;
	void process(TreeItem * treeItem);

protected :
	T** _value;
	int64_t _pbDimension;
};






template< class T >
EventMixmodDisplay<T**>::EventMixmodDisplay(T** iValue, int64_t iPbDimension) {
	_value = iValue;
	_pbDimension = iPbDimension;
}



template< class T >
EventMixmodDisplay<T**>::~EventMixmodDisplay() {
}


template< class T >
std::string  EventMixmodDisplay<T**>::getDisplay() const {
	Matrix<T>matrix = Matrix<T>(_value,_pbDimension);
	std::stringstream ss ;
	ss << matrix ;
	return ss.str();
}


template< class T >
void EventMixmodDisplay<T**>::process( TreeItem * /*treeItem*/) {
}

template< class T >
bool EventMixmodDisplay<T**>::launchNewEvent() const {
	return false;
}





// faire pour un enum
template <>
class EventMixmodDisplay<CriterionName>:public Event {

public :
	EventMixmodDisplay(CriterionName iCriterion);
	~EventMixmodDisplay();
	std::string getDisplay() const ;
	bool launchNewEvent() const ;
	void process(TreeItem * treeItem);
	TreeKeyword getKeyword() const ;
private :
	CriterionName  _criterionName;
};








template<>
class EventMixmodDisplay<StrategyInitName> :public Event {

public :
	EventMixmodDisplay(StrategyInitName iStrategyInitName);
	~EventMixmodDisplay();
	string getDisplay()const ;
	bool launchNewEvent()const ;
	void process(TreeItem* treeItem);
	virtual TreeKeyword getKeyword() const;
private :
	StrategyInitName  _strategyInitName;
};




template <>
class EventMixmodDisplay<AlgoStopName> :public Event {

public :
	EventMixmodDisplay(AlgoStopName iAlgoStopName, TreeKeyword iTreeKeyword);
	~EventMixmodDisplay();
	string getDisplay()const ;
	bool launchNewEvent()const ;
	void process(TreeItem * treeItem);
	virtual TreeKeyword getKeyword() const;
private :
	AlgoStopName  _algoStopName;
	TreeKeyword _treeKeyword;
};






template <>
class EventMixmodDisplay<AlgoName> :public Event {

public :
	EventMixmodDisplay(AlgoName iAlgoName);
	~EventMixmodDisplay();
	string getDisplay()const ;
	bool launchNewEvent()const ;
	void process(TreeItem * treeItem);
	virtual TreeKeyword getKeyword() const;
private :
	AlgoName  _algoName;
};




template <>
class EventMixmodDisplay<ModelName>:public Event {

public :
	EventMixmodDisplay(ModelName iModelName);
	~EventMixmodDisplay();
	string getDisplay()const ;
	bool launchNewEvent()const ;
	void process(const TreeItem& treeItem);
	virtual TreeKeyword getKeyword() const;
private :
	ModelName  _modelName;
};



























}
}

#endif
