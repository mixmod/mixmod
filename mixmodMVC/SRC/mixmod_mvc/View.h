/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/View.h  description
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
#ifndef ___MVC_VIEW_H__
#define ___MVC_VIEW_H__

#include "mixmod_mvc/TreeItem.h"

#include <iostream>
#include <ostream>
#include <exception>

namespace XEM {
namespace MVC {

/**
	@brief View class
*/

class View {

public :
	// enum

	enum PROJECT {
	    INPUT = 0,
	    OUTPUT = 1
	};

	enum POSITION_IN_INPUT {
	    //PB_DIMENSION,
	    DATA,
	    NB_NB_CLUSTER,
	    MODEL,
	    STRATEGY,
	    CRITERION,
	    KNOWN_PARTITION
	};

	enum POSITION_IN_INPUT_AD {
	    //PB_DIMENSION_AD,
	    DATA_AD,
	    NB_CLUSTER_AD,
	    MODEL_AD,
	    DATA_CLASSIFY_AD,
	    KNOWN_PARTITION_AD,
	    CRITERION_AD
	};

	enum POSITION_IN_DATA {
	    PB_DIMENSION,
	    NB_SAMPLE,
	    SAMPLES,
	    WEIGHT,
	    NB_MODALITY
	};

	enum POSITION_IN_DATA_AD {
	    PB_DIMENSION_AD,
	    NB_SAMPLE_AD,
	    SAMPLES_AD,
	    NB_MODALITY_AD,
	    WEIGHT_AD
	};

	enum POSITION_IN_STRATEGY {
	    NB_STRATEGY_TRY,
	    INIT,
	    NB_ALGO

	};

	enum POSITION_IN_INIT_RANDOM {
	    INIT_NAME,
	    NB_TRY_INIT_RANDOM
	};

	enum POSITION_IN_INIT_PARAMETER {
	    INIT_NAME_PARAMETER,
	    INIT_PARAMETER
	};

	enum POSITION_IN_INIT_SMALL_EM {
	    INIT_NAME_SMALL_EM,
	    NB_TRY_INIT_SMALL_EM,
	    STOP_RULE_SMALL_EM
	};

	enum POSITION_IN_INIT_CEM {
	    INIT_NAME_CEM,
	    NB_TRY_INIT_CEM,
	};

	enum POSITION_IN_INIT_SEM_MAX {
	    INIT_NAME_SEM_MAX,
	    NB_ITERATION_SEM_MAX
	};

	enum POSITION_IN_ALGO {
	    ALGO_NAME,
	    STOP
	};

	enum POSITION_IN_STOP {
	    NB_ITERATION,
	    EPSILON
	};

	enum POSITION_IN_PARAMETER {
	    PROPORTIONS,
	    CENTERS,
	    DISPERSAL,
	    DK = DISPERSAL,
	    AKJ,
	    BK,
	    QK
	};

	enum POSITION_IN_OUTPUT {
	    NUMERIC,
	    GRAPHIC
	};

	enum POSITION_IN_NUMERIC {
	    MODEL_OUTPUT,
	    NBCLUSTER_OUTPUT,
	    CRITERION_OUTPUT,
	    ERROR_OUTPUT = CRITERION_OUTPUT,
	    PARAMETER_OUTPUT,
	    LABEL_OUTPUT,
	    LIKELIHOOD_OUTPUT
	};

	enum PARAMETER_IN_OUTPUT {
	    PROPORTION_OUTPUT,
	    MEAN_OUTPUT,
	    VARIANCE_OUTPUT
	};

	enum POSITION_IN_GRAPHIC {
	    QUANTITATIVE_GRAPHICS_POINT,
	    NO_GRAPHICS = QUANTITATIVE_GRAPHICS_POINT,
	    QUALITATIVE_GRAPHICS_DIAGRAM = QUANTITATIVE_GRAPHICS_POINT,
	    QUANTITATIVE_GRAPHICS_CLASS,
	    QUALITATIVE_GRAPHICS_BOXES = QUANTITATIVE_GRAPHICS_CLASS,
	    QUANTITATIVE_GRAPHICS_HISTOGRAM
	};

	// typedef
	typedef TreeItem::child_size_type size_type ;

	// function
	// constructor
	template< class T >
	View( const T& = T(), const TreeKeyword& key = NoKeyword );
	virtual ~View();

	// display
	virtual void display(std::ostream & f) const = 0 ;

	//setters
	template< class T >
	void setValue( TreeItem* treeItem, const T& value );

	template< class T >
	void insertChild( TreeItem * treeItem, View::size_type pos, const TreeKeyword& key, const T& value );

//     template< class T >
//     void insertChild( const Identifier&, size_type, const TreeKeyword&, const T& );

	void removeChild( TreeItem *, size_type );

	// root

	TreeItem* getInput() const ;
	TreeItem* getOutput() const;
	void setRoot( TreeItem* );

	void addOutput(ClusteringOutput * cOutput);
	void killNoKeyword();

	TreeItem* getRoot();
	void updateOutput(ClusteringOutput* cOutput);
	void updateOutputOrdering(ClusteringOutput* cOutput);

protected :
	// functions
	View( const View& );
	View& operator=( const View& );

	// delete root
	void clearRoot();

	//TreeItem* item( const Identifier& );

	// data
	TreeItem* _root ;
};

// constructor
template< class T >
View::View( const T& value, const TreeKeyword& key )
	: _root( NULL ) {
	_root = TreeItem::createItem( value, key );
}

// set Value
template< class T >
inline void View::setValue( TreeItem * treeItem, const T& value ) {
	treeItem->setValue( value );
}

// insert Child
template< class T >
inline void View::insertChild( TreeItem* treeItem, View::size_type pos, const TreeKeyword& key, const T& value) {
	TreeItem* child = TreeItem::createItem( value, key );
	treeItem->insertChild( child, pos );
}

// template< class T >
// inline void View::insertChild( const Identifier& id, size_type pos, const TreeKeyword& key, const T& value )
// {
//   TreeItem* child = TreeItem::createItem( value, key );
//   item(id)->insertChild( child, pos );
// }

/*** Root ***/

// delete root
inline void View::clearRoot() {
	if( _root ) {
		delete _root ;
	}
	_root = NULL ;

}

inline TreeItem* View::getInput() const {
	if (_root->getChild(INPUT)) {
		return _root->getChild(INPUT) ;
	}
	else {
		throw nullPointerError;
	}
}

inline TreeItem* View::getOutput() const {
	if (_root->getChild(OUTPUT)) {
		return _root->getChild(OUTPUT) ;
	}
	else {
		throw nullPointerError;
	}
}


inline void View::setRoot( TreeItem* newRoot ) {
	clearRoot();
	_root = newRoot ;
}

inline TreeItem* View::getRoot() {
	return _root;
}

inline void View::killNoKeyword() {
	if (_root->getNbChild()==2) {
		_root->getVChild().resize(1);
		int64_t a =1;
	}

}

/************/

}
}

#endif
