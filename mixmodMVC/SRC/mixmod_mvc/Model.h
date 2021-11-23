/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/Model.h  description
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
#ifndef ___MVC_MODEL_H__
#define ___MVC_MODEL_H__

#include <cstddef>

//#include "mixmod_mvc/Identifier.h"
#include "mixmod_mvc/ModelItemCriterion.h"
#include "mixmod_mvc/ModelItemModel.h"
#include "mixmod_mvc/ModelItemSubDim.h"
#include "mixmod_mvc/ModelItemKnownPartition.h"
#include "mixmod_mvc/ModelItemInitPartition.h"
#include "mixmod_mvc/ModelItemKnownPartitionSample.h"
#include "mixmod_mvc/ModelItemWeight.h"
#include "mixmod_mvc/ModelItemAlgo.h"
#include "mixmod_mvc/ModelItemAlgoName.h"
#include "mixmod_mvc/ModelItemAlgoStopValue.h"
#include "mixmod_mvc/ModelItemAlgoStopRule.h"
#include "mixmod_mvc/ModelItemNbStrategyTry.h"
#include "mixmod_mvc/ModelItemParamInInit.h"
#include "mixmod_mvc/ModelItemInitName.h"
#include "mixmod_mvc/ModelItemInitParam.h"
#include "mixmod_mvc/ModelItemInitParamChild.h"
#include "mixmod_mvc/ModelItemInitParamChildBinary.h"
#include "mixmod_mvc/ModelItemInitParamChildHD.h"
#include "mixmod_mvc/ModelItemInitProportion.h"
#include "mixmod_mvc/ModelItemInitCenter.h"
#include "mixmod_mvc/ModelItemInitDispersion.h"
#include "mixmod_mvc/ModelItemScatter.h"
#include "mixmod_mvc/ModelItemInitDimension.h"
#include "mixmod_mvc/ModelItemAkj.h"
#include "mixmod_mvc/ModelItemOrientation.h"
#include "mixmod_mvc/ModelItemStopRuleInit.h"
#include "mixmod_mvc/NoTemplate.h"

#include "mixmod_mvc/Util.h"
#include "mixmod_iostream/IOStreamUtil.h"

namespace XEM {
namespace MVC {


class Event ;

class Model {
public :
	Model();
	virtual ~Model();

	/// create a MVCMixmod from an existing clustering main
	Model(ClusteringMain * cMain);

	ClusteringInput* getInput() const ;

	ClusteringOutput* getOutput() const ;

	bool hasInput();
	bool hasOutput();

	template< class T >
	Event* setValue( TreeItem * treeItem, const T& );

	template< class T >
	Event* insertChild( TreeItem* treeItem, int64_t pos, const T& value );

	template< class T >
	Event* removeChild( TreeItem* treeItem, int64_t pos );

	//TODO a enlever
	static const std::string DEFAULTFILENAME;


	// construct
	// ------------
	// Clustering Main with gaussian Data
	void constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName);

	// Clustering Main with binary Data
	void constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName, vector<int64_t> iModality);

	//Clustering Main from datadescription
	void constructClusteringMain(vector< int64_t > iNbCluster, DataDescription& dataDescription);

	// DA Main with gaussian Data
	void constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify);

	// DA Main with binary Data
	void constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify, vector<int64_t> iModality);

	void constructMain(istream & flux, IOStreamFormat format=IOStreamFormat::XML);

	void sortOutput(CriterionName criterionName);
	ClusteringMain * getClusteringMain();
	void setOutputNull();

private :
	// functions
	Model( const Model& );
	Model& operator=( const Model& );

	// delete item
	void clearItem();
	// delete input
	void clearMain();
	/*
	    template< class T >
	    AbstractModelItem* createItem( const Identifier&, const T& = T() ) const ;
	*/
	AbstractModelItem* createItem( TreeItem * treeItem, ModelName ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, AlgoName value ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, AlgoStopName value ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, double ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, double* ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, double**) const ;
	//AbstractModelItem* createItem( const Identifier&, double***) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, CriterionName ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, int64_t ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, int64_t* ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, int64_t** ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, string ) const ;
	AbstractModelItem* createItem( TreeItem * treeItem, StrategyInitName ) const ;

	template< class T >
	AbstractModelItem* createItem( TreeItem* treeItem) const ;

	// data
	AbstractModelItem* _mItem ;

	// ClusteringMain
	ClusteringMain * _cMain ;
};

/*** constructors ***/

inline Model::Model()
	: _mItem( NULL ), _cMain( NULL ) {
}

inline void Model::sortOutput(CriterionName criterionName) {
	_cMain->getOutput()->sort(criterionName);
}

inline void Model::setOutputNull() {
	_cMain->setOutputNull();
}



inline Model::Model( const Model& ) {
	throw nonImplementedMethod;
}

inline Model& Model::operator=( const Model& ) {
	throw nonImplementedMethod;

	return *this ;
}

/********************/

inline ClusteringInput* Model::getInput() const {
	if (_cMain) {
		return _cMain->getInput() ;
	}
	else {
		throw nullPointerError;
	}
}

//check if input exists
inline bool Model::hasInput() {
	if (_cMain && _cMain->getInput()) {
		return true;
	}
	else {
		return false;
	}
}

//check if input exists
inline bool Model::hasOutput() {
	if (_cMain && _cMain->getOutput()) {
		return true;
	}
	else {
		return false;
	}
}

// delete Item
inline void Model::clearItem() {
	if( _mItem )
		delete _mItem ;
	_mItem = NULL ;

}

// delete input
inline void Model::clearMain() {
	if( _cMain ) {
		delete _cMain ;
		_cMain = NULL ;
	}
}

// set Value
template< class T >
inline Event* Model::setValue( TreeItem* treeItem, const T& value) {
	clearItem();

	_mItem = createItem(treeItem, value) ;
	if( _mItem )
		return _mItem->setValue(treeItem->getPosition()) ;
	else
		return NULL ;
}

// insert Child
template< class T >
inline Event* Model::insertChild( TreeItem * treeItem, int64_t pos, const T& value) {
	clearItem();

	_mItem = createItem(treeItem, value) ;
	if( _mItem ) {
		return _mItem->insertChild(pos) ;
	}
	else {
		return NULL ;
	}
}

// remove Child
template< class T >
inline Event* Model::removeChild( TreeItem* treeItem, int64_t pos) {
	clearItem();

	_mItem = createItem<T>(treeItem) ;
	if( _mItem )
		return _mItem->removeChild(pos) ;
	else
		return NULL ;
}

inline AbstractModelItem* Model::createItem( TreeItem * treeItem, ModelName value) const {
// TODO verify
	switch( treeItem->getKeyword() ) {
	case TreeModel :
	case TreeModelChild :
		return new ModelItem< TreeModelChild, ModelName >(getInput(), value);
	default :
		break ;
	}
	return NULL ;
}


inline AbstractModelItem* Model::createItem( TreeItem * treeItem, AlgoName value) const {
// TODO verify
	switch( treeItem->getKeyword() ) {
	case TreeNbAlgo :
		//case TreeNbAlgoChild :
		return new ModelItem< TreeNbAlgo, AlgoName >(getInput(), value);
	case TreeNbAlgoChild :
	case TreeAlgoName :
		return new ModelItem< TreeNbAlgoChild, AlgoName >(getInput(), value,treeItem->getParentPosition());
	default :
		break ;
	}
	return NULL ;
}


inline AbstractModelItem* Model::createItem( TreeItem * treeItem, AlgoStopName value) const {
// TODO verify
	switch( treeItem->getKeyword() ) {
	case TreeNbAlgoChild :
		return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), value, treeItem->getPosition());
	case TreeInitStopRule :
		return new ModelItem< TreeInitStopRule, AlgoStopName >(getInput(), value);
	case TreeStopRuleValue:
		return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), value, treeItem->getParentPosition());
	default :
		break ;
	}
	return NULL ;
}

inline AbstractModelItem* Model::createItem( TreeItem * treeItem, double value) const {
// TODO verify
	switch( treeItem->getKeyword() ) {
	case TreeStopRuleValue ://insert epsilon
		if (treeItem->getNbChild() == 1) { //stopRule starts at nbiteration and becomes nbiteration_epsilon
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), NBITERATION_EPSILON, treeItem->getParentPosition());
		}
		else if (treeItem->getNbChild() == 0) {//stopRule hasn't value
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), EPSILON, treeItem->getParentPosition());
		}
	case TreeInitStopRule ://insert nbiteration
		return new ModelItem< TreeInitEpsilon, double >(getInput(), value);
	case TreeInitEpsilon:
		return new ModelItem< TreeInitEpsilon, double >(getInput(), value);
	case TreeEpsilon: {
		std::deque<int64_t > listPosition = treeItem->getListPosition();
		return new ModelItem< TreeEpsilon, double >(getInput(), value, treeItem->getParentPosition(), listPosition[listPosition.size()-3]);//listPosition[listPosition.size()-2] is the Gparent position
	}
	case TreeInitProportion :
		return new ModelItem< TreeInitProportionChild, double >(value);
	case TreeDataWeight :
		return new ModelItem< TreeDataWeightChild, double >(getInput(), value);
	default :
		break ;
	}
	return NULL ;
}

inline AbstractModelItem* Model::createItem( TreeItem * treeItem, double* value) const {
// TODO verify
	switch( treeItem->getKeyword() ) {
	case TreeInitCenter :
		return new ModelItem< TreeInitCenterChild, double >(getInput(),value, treeItem->getParentPosition());
	case TreeInitParameterChildHD :
		return new ModelItem< TreeInitParameterAkj, double >(getInput(),value, treeItem->getParentPosition());
	case TreeInitDispersionChild :
	case TreeInitScatterChild :
		return new ModelItem< TreeInitDispersionData, double >(getInput(),value);
	default :
		break ;
	}
	return NULL ;
}


inline AbstractModelItem* Model::createItem( TreeItem * treeItem, double** value) const {
// TODO verify
	switch( treeItem->getKeyword() ) {
	case TreeInitDispersion :
		return new ModelItem< TreeInitDispersionChild, double >(getInput(),value, treeItem->getParentPosition());
	case TreeInitScatter :
		return new ModelItem< TreeInitScatterChild, double >(getInput(),value, treeItem->getParentPosition());
		//case TreeInitParameterChild :
	case TreeInitParameterChildHD :
		return new ModelItem< TreeInitParameterOrientation, double >(getInput(),value, treeItem->getParentPosition());
	default :
		break ;
	}
	return NULL ;
}


inline AbstractModelItem* Model::createItem( TreeItem * treeItem, CriterionName value) const {
	switch( treeItem->getKeyword() ) {
	case TreeCriterion :
	case TreeCriterionChild :
		return new ModelItem< TreeCriterionChild, CriterionName >(getInput(), value);
	default :
		break ;
	}
	return NULL ;
}


inline AbstractModelItem* Model::createItem( TreeItem * treeItem, int64_t value) const {
	switch( treeItem->getKeyword() ) {
	case TreeModelChild :
	case TreeSubDimension :
		return new ModelItem< TreeSubDimension, int64_t >(getInput(), value, treeItem->getParentPosition());
	case TreeStopRuleValue ://insert nbiteration
		if (treeItem->getNbChild() == 1) { //stopRule starts at epsilon and becomes nbiteration_epsilon
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), NBITERATION_EPSILON, treeItem->getParentPosition());
		}
		else if (treeItem->getNbChild() == 0) {//stopRule hasn't value
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), NBITERATION, treeItem->getParentPosition());
		}
	case TreeInitStopRule ://insert nbiteration
		return new ModelItem< TreeInitNbIteration, int64_t >(getInput(), value);
	case TreeInitNbIteration :
		return new ModelItem< TreeInitNbIteration, int64_t >(getInput(), value);
	case TreeNbIteration : {
		deque<int64_t> listPosition = treeItem->getListPosition();
		return new ModelItem<TreeNbIteration , int64_t >(getInput(), value, treeItem->getParentPosition(), listPosition[listPosition.size()-3]);
	}
	case TreeInitParameter :
		return new ModelItem< TreeInitParameterChild, int64_t >(getInput(), treeItem->getPosition());
	case TreeInitParameterBinary :
		return new ModelItem< TreeInitParameterChildBinary, int64_t >(getInput(), treeItem->getPosition());
	case TreeInitParameterHD :
		return new ModelItem< TreeInitParameterChildHD, int64_t >(getInput(), treeItem->getPosition());
	case TreeInitParameterChildHD :
		//case TreeInitParameterChild :
		return new ModelItem< TreeInitParameterDimension, int64_t >(getInput(), value);
	case TreeStrategy :
	case TreeNbStrategyTry :
		return new ModelItem< TreeNbStrategyTry, int64_t >(getInput(), value);
	case TreeInitNbTry :
		return new ModelItem< TreeInitNbTry, int64_t >(getInput(), value);
	case TreeInitType :
		return new ModelItem< TreeInitType, int64_t >(getInput(), value);
	case TreeKnownPartition :
		return new ModelItem< TreeKnownPartitionSample, int64_t >(getInput());
	default :
		break ;
	}
	return NULL ;
}


inline AbstractModelItem* Model::createItem( TreeItem * treeItem, int64_t** /*value*/ ) const {
	switch( treeItem->getKeyword() ) {
//     case TreeKnownPartition :
//       return new ModelItem< TreeKnownPartitionSample, int64_t >(getInput());
	case TreeInitPartition :
		return new ModelItem< TreeInitPartitionSample, int64_t >(getInput(), treeItem->getPosition());
	default :
		break ;
	}
	return NULL ;
}


inline AbstractModelItem* Model::createItem( TreeItem * treeItem, int64_t* value) const {
	switch( treeItem->getKeyword() ) {
	case TreeInitCenter :
		return new ModelItem< TreeInitCenterChild, int64_t >(getInput(),value, treeItem->getParentPosition());
	default :
		break ;
	}
	return NULL ;
}

inline AbstractModelItem* Model::createItem( TreeItem* treeItem, string value) const {
	switch( treeItem->getKeyword() ) {
	case TreeKnownPartition :
		return new ModelItem< TreeKnownPartition, string >(getInput(), value);
	case TreeDataWeight :
		return new ModelItem< TreeDataWeight, string >(getInput(), value);
	case TreeInitPartition :
	case TreeInitTypeNameUserPartition :
		return new ModelItem< TreeInitPartition, string >(getInput(), value);
	case TreeInitParameter :
	case TreeInitTypeNameUser :
		return new ModelItem< TreeInitParameter, string >(getInput(), value);
	default :
		break ;
	}
	return NULL ;
}

inline AbstractModelItem* Model::createItem( TreeItem* treeItem, StrategyInitName value) const {
	switch( treeItem->getKeyword() ) {
	case TreeInitType :
	case TreeInitTypeName :
		return new ModelItem< TreeInitTypeName, StrategyInitName >(getInput(), value);
	default :
		break ;
	}
	return NULL ;
}


//create item for removeChild


// do not use, prefer specialization
template< class T >
inline AbstractModelItem* Model::createItem( TreeItem* treeItem ) const {
	throw ;
}

template< >
inline AbstractModelItem* Model::createItem<CriterionName>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeCriterion :
	case TreeCriterionChild :
		return new ModelItem< TreeCriterionChild, CriterionName >(getInput());
	default :
		break ;
	}
	return NULL ;
}


template< >
inline AbstractModelItem* Model::createItem<ModelName>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeModel :
	case TreeModelChild :
		return new ModelItem< TreeModelChild, ModelName >(getInput());
	default :
		break ;
	}
	return NULL ;
}

template< >
inline AbstractModelItem* Model::createItem<StrategyInitName>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeInitTypeName :
	case TreeInitParameter :
		return new ModelItem< TreeInitTypeName, StrategyInitName >(getInput());
	default :
		break ;
	}
	return NULL ;
}



template< >
inline AbstractModelItem* Model::createItem<int64_t>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeModelChild :
		return new ModelItem< TreeSubDimension, int64_t >(getInput());
	case TreeStopRuleValue ://remove nbiteration
		if (treeItem->getNbChild() == 2) { //stopRule becomes epsilon
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), EPSILON, treeItem->getParentPosition());
		}
		else if (treeItem->getNbChild() == 1) {//stopRule switchs
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), NO_STOP_NAME, treeItem->getParentPosition());
		}
	case TreeInitStopRule :
		return new ModelItem< TreeInitNbIteration, int64_t >(getInput());
	case TreeInitType :
		return new ModelItem< TreeInitType, int64_t >(getInput());
	case TreeKnownPartition :
		return new ModelItem< TreeKnownPartitionSample, int64_t >(getInput());
	default :
		break ;
	}
	return NULL ;
}

template< >
inline AbstractModelItem* Model::createItem<int64_t**>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeInitPartition :
		return new ModelItem< TreeInitPartitionSample, int64_t >(getInput(), treeItem->getPosition());
		/*case TreeKnownPartition :
		  return new ModelItem< TreeKnownPartitionSample, int64_t >(getInput(),treeItem->getPosition());*/
	default :
		break ;
	}
	return NULL ;
}


template< >
inline AbstractModelItem* Model::createItem<double>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeStopRuleValue ://remove epsilon
		if (treeItem->getNbChild() == 2) { //stopRule becomes nbiteration
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), NBITERATION, treeItem->getParentPosition());
		}
		else if (treeItem->getNbChild() == 1) {//stopRule switch
			return new ModelItem< TreeNbAlgoChild, AlgoStopName >(getInput(), NO_STOP_NAME, treeItem->getParentPosition());
		}
	case TreeInitType :
		return new ModelItem< TreeInitType, double >(getInput());
	case TreeInitStopRule :
		return new ModelItem< TreeInitEpsilon, double >(getInput());
	case TreeDataWeight :
		if (treeItem->getNbChild() != 0) {
			return new ModelItem< TreeDataWeightChild, double >(getInput());
		}
	default :
		break ;
	}
	return NULL ;
}



template< >
inline AbstractModelItem* Model::createItem<string>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeKnownPartition :
		return new ModelItem< TreeKnownPartition, std::string >(getInput());
	default :
		break ;
	}
	return NULL ;
}

template< >
inline AbstractModelItem* Model::createItem<AlgoName>( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeNbAlgo :
		return new ModelItem< TreeNbAlgo, AlgoName >(getInput());
	default :
		break ;
	}
	return NULL ;
}

template< >
inline AbstractModelItem* Model::createItem< AlgoStopName >( TreeItem * treeItem ) const {
	switch( treeItem->getKeyword() ) {
	case TreeInitType :
		return new ModelItem< TreeInitType, int64_t >(getInput());
	default :
		break ;
	}
	return NULL ;
}


inline ClusteringOutput* Model::getOutput() const {
	if (_cMain && _cMain->getOutput()) {
		return _cMain->getOutput();
	}
	else {
		throw nullPointerError;
	}
}

inline ClusteringMain* Model::getClusteringMain() {
	return _cMain;
}

}
}

#endif
