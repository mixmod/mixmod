/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/TreeItem.h  description
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
#ifndef ___MVC_TREEITEM_H__
#define ___MVC_TREEITEM_H__

#include <cstddef>
#include <string>
#include <deque>

#include "mixmod_mvc/Store.h"
#include "mixmod_mvc/Util.h"

namespace XEM {
namespace MVC {

enum TreeKeyword {
    NoKeyword,
    DefaultKeyword,
    TreeProject,
    TreeInput,
    TreeOutput,
    TreeNbSample,
    TreePbDimension,
    TreeNbNbCluster,
    TreeNbCluster,
    TreeData,
    TreeDataSample,
    TreeDataSampleChild,
    TreeDataWeight,
    TreeDataWeightChild,
    TreeFactor,
    TreeDataClassify,
    TreeModel,
    TreeModelChild,
    TreeKnownPartition,
    TreeKnownPartitionSample,
    TreeStrategy,
    TreeNbStrategyTry,
    TreeInitType,
    TreeInitTypeName,
    TreeInitTypeNameUser,
    TreeInitTypeNameUserPartition,
    TreeInitParameter,
    TreeInitParameterBinary,
    TreeInitParameterHD,
    TreeInitParameterChild,
    TreeInitParameterChildBinary,
    TreeInitParameterChildHD,
    TreeInitProportion,
    TreeInitProportionChild,
    TreeInitCenter,
    TreeInitCenterChild,
    TreeInitDispersion,
    TreeInitDispersionChild,
    TreeInitDispersionData,
    TreeInitScatter,
    TreeInitScatterChild,
    TreeInitParameterDimension,
    TreeInitParameterOrientation,
    TreeInitParameterBk,
    TreeInitParameterAkj,
    TreeInitParameterSample,
    TreeInitPartition,
    TreeInitPartitionSample,
    TreeInitParameterStrategy,
    TreeInitNbTry,
    TreeInitStopRule,
    TreeInitNbIteration,
    TreeInitEpsilon,
    TreeNbAlgo,
    TreeNbAlgoChild,
    TreeAlgoName,
    TreeEpsilon,
    TreeNbIteration,
    TreeStopRuleValue,
    TreeCriterion,
    TreeCriterionChild,
    TreeSubDimension,
    //mots-cle output
    TreeResult,
    TreeNumeric,
    TreeGraphic,
    TreeOutputNbCluster,
    TreeOutputModel,
    TreeOutputCriterion,
    TreeOutputCriterionName,
    TreeOutputParameter,
    TreeOutputParameterChild,
    TreeOutputLabel,
    TreeLabelSample,
    TreeOutputPostProba,
    TreePostProbaSample,
    TreeOutputError,
    TreeLikelihood,
    TreeCompletedLikelihood,
    TreeCriterionValue,
    TreeOutputProportion,
    TreeOutputProportionChild,
    TreeOutputCenter,
    TreeOutputCenterChild,
    TreeOutputDispersion,
    TreeOutputDispersionChild,
    TreeOutputScatter,
    TreeOutputScatterChild,
    TreeOutputDispersionData,
    TreeOutputTabA,
    TreeOutputTabB,
    TreeOutputTabD,
    TreeQuantitativePoint,
    TreeQuantitativeClass,
    TreeQuantitativeHistogram,
    TreeQualitativeDiagram,
    TreeQualitativeBoxes,
    TreeNoGraphics,
    TreeSize
};

class TreeItem {
private :
	// typedef
	typedef std::deque< TreeItem* >::const_iterator const_iterator ;
	typedef std::deque< TreeItem* >::iterator iterator ;

public :
	//typedef
	typedef std::deque< TreeItem* >::size_type child_size_type ;
	typedef std::deque< TreeItem* >::reference child_reference ;

	// functions
	virtual ~TreeItem();

	// getters
	TreeItem* getParent() const ;
	TreeKeyword getKeyword() const ;
	int64_t getPosition() const ;
	int64_t getParentPosition() const ;
	int64_t getGdParentPosition() const ;

	child_reference getChild( TreeItem::child_size_type pos ) ;
	child_size_type getNbChild() const ;

	std::string getName() const ;
	virtual std::string toString() const ;

	// setters
	void insertChild( TreeItem*, child_size_type );
	void setChild( TreeItem* child, child_size_type pos );
	void removeChild( child_size_type );

	template< class T >
	void setValue( const T& );

	template< class T >
	static TreeItem* createItem( T = T(), const TreeKeyword& = NoKeyword );
	std::deque< TreeItem* > & getVChild() {
		return _children;
	};

	std::deque<int64_t> getListPosition()const {
		return _listPosition;
	} ;
	void setListPosition(deque< int64_t >& listPosition);
	string getStringListPosition();

	//update the _listPosition of current TreeItem after an insertion or a deletion
	void updateListPosition(int64_t pos);
	void updateChildListPosition(int64_t pos);

protected :
	// constructors
	TreeItem();

	template< class T >
	TreeItem( T, TreeKeyword = NoKeyword, TreeItem* = NULL );
	// copy
	TreeItem( const TreeItem& );
	TreeItem& operator=( const TreeItem& );

	void clearData();

	// data
	// parent
	TreeItem* _parent ;

	// id
	TreeKeyword _keyword ; // not unique, also use getPosition

	// children
	std::deque< TreeItem* > _children ;

	///position matchs to the node index in tree
	std::deque<int64_t> _listPosition;

	AbstractStore* _data ;
};

// only this way to create a TreeItem, the returned TreeItem has not parent node
template< class T >
inline TreeItem* TreeItem::createItem( T value, const TreeKeyword& key ) {
	return new TreeItem( value, key ,NULL );
}

// protected constructor
template< class T >
inline TreeItem::TreeItem( T value, TreeKeyword key, TreeItem* parent )
	:  _parent(parent), _keyword(key), _children(), _data(NULL) {
	_listPosition.push_back(0);
	_data = new Store<T>( value );
}

/*** getters ***/

inline TreeItem* TreeItem::getParent() const {
	return _parent ;
}

inline TreeKeyword TreeItem::getKeyword() const {
	return _keyword ;
}

inline TreeItem::child_reference TreeItem::getChild( child_size_type pos) {
	if (_children.size()>pos) {
		return _children[pos] ;
	}
	else {
		throw internalMixmodError;
	}
}

inline TreeItem::child_size_type TreeItem::getNbChild() const {
	return _children.size() ;
}

/***************/

// set value
template< class T >
inline void TreeItem::setValue( const T& value ) {
	clearData();

	_data = new Store<T>( value );
}

}
}

#endif
