/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/EventMixmodDisplayScatter.h  description
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
#ifndef __EVENTMIXMODDISPLAYSCATTER_H__
#define __EVENTMIXMODDISPLAYSCATTER_H__


#include "mixmod_mvc/EventMixmodDisplay.h"


namespace XEM {
namespace MVC {


class EventMixmodDisplayScatter :public EventMixmodDisplay<double**> {

public :
	EventMixmodDisplayScatter(double** iTabValue, int64_t iSizeVector, int64_t * iTabModality);
	~EventMixmodDisplayScatter();
	std::string  getDisplay() const;
	TreeKeyword getKeyword() const;

private :
	int64_t * _tabModality;
};







/*template <class T>
class EventMixmodDisplayScatter : public EventMixmodDisplay<T>{

  public :
    EventMixmodDisplayScatter(T** iValue, int64_t iPbDimension, int64_t * iTabModality);
    ~EventMixmodDisplayScatter();
     std::string getDisplay() const;
    bool launchNewEvent();
    void processEvent();
  private :
    int64_t * _tabModality;
};


template <class T>
 EventMixmodDisplayScatter<T> ::~EventMixmodDisplayScatter(){
  _tabModality = NULL;
}


template <class T>
  EventMixmodDisplayScatter<T**> ::EventMixmodDisplayScatter (T** iValue, int64_t iPbDimension, int64_t * iTabModality):EventMixmodDisplay<T**>(iValue,iPbDimension){
  _tabModality = iTabModality;
}



template <class T>
  std::string EventMixmodDisplayScatter<T**> ::getDisplay() const{
  Scatter<T> scatter = Scatter<T>(EventMixmodDisplay<T**>::_value,_tabModality,EventMixmodDisplay<T**>::_pbDimension);
    std::stringstream ss ;
    ss << scatter ;
    return ss.str();
}



template <class T>
  bool EventMixmodDisplayScatter<T**>::launchNewEvent(){
  return false;
}

template <class T>
  void EventMixmodDisplayScatter<T**>::processEvent(){
}
*/


}
}

#endif
