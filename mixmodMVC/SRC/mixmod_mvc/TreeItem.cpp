/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/TreeItem.cpp  description
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
#include "TreeItem.h"

#include <algorithm>
#include <sstream>
#include <cassert>
#include "mixmod_mvc/NoTemplate.h"

namespace XEM {
namespace MVC {

// default constructor (protected, do not use it )
TreeItem::TreeItem()
	:  _parent(NULL), _keyword(NoKeyword), _children(), _data(NULL) {
	_data = new Store<NoTemplate>( NoTemplate() );
}

// destructor
TreeItem::~TreeItem() {
	_parent = NULL ;
	_keyword = NoKeyword ;

//std::cerr << "-> " << toString() ;

	clearData();
//std::cerr << " <-" << std::endl ;

	while( !_children.empty() ) {
		delete *(_children.begin());
		_children.erase( _children.begin() );
	}
}

// copy constructor (protected, do not use it )
TreeItem::TreeItem( const TreeItem& /*item*/ )
	: _parent(NULL), _keyword(NoKeyword), _children(), _data(NULL) {
}

// basic assignment (protected, do not use it )
TreeItem& TreeItem::operator=( const TreeItem& /*item*/ ) {
	_parent = NULL ;
	_keyword = NoKeyword ;
	_children = std::deque< TreeItem* >() ;

	_data = NULL ;

	return *this ;
}

// clear data
void TreeItem::clearData() {
	if( _data )
		delete _data ;
	_data = NULL ;
}

// get the position of this in parent
//TreeItem::child_size_type TreeItem::getPosition() const
int64_t TreeItem::getPosition() const {
	return _listPosition[_listPosition.size()-1];

//   if( !_parent )
//     return 0 ;
//
//   iterator it = find( _parent->_children.begin(), _parent->_children.end(), this );
//   return ( it - _parent->_children.begin() ) ;
}

int64_t TreeItem::getParentPosition() const {
	if (_parent) {
		return _parent->getPosition();
	}
	else {
		return 0;
	}
}

int64_t TreeItem::getGdParentPosition() const {
	if (_listPosition.size()>=3) {
		return _listPosition[_listPosition.size()-3];
	}
	else {
		throw;
	}
}


// get displayable keyword
std::string TreeItem::getName() const {
	switch( _keyword ) {
	case NoKeyword :
		return "NoKeyword" ;
	case DefaultKeyword :
		return "DefaultKeyword" ;
	case TreeProject :
		return "Project" ;
	case TreeInput :
		return "Input";
	case TreeOutput :
		return "Results";
	case TreeNbSample :
		return "Number of samples";
	case TreePbDimension :
		return "Variables";
	case TreeNbNbCluster :
		return "NbNbCluster" ;
	case TreeNbCluster :
		return "NbCluster" ;
	case TreeData :
		return "Data" ;
	case TreeDataSample :
		return "DataSample";
	case TreeDataSampleChild :
		return "DataSampleChild";
	case TreeDataWeight :
		return "Weight";
	case TreeDataWeightChild :
		return "WeightChild";
	case TreeFactor :
		return "Factor";
	case TreeDataClassify :
		return "Data to classify ";
	case TreeModel :
		return "Model" ;
	case TreeModelChild :
		return "Model " ;
	case TreeKnownPartition :
		return "KnownPartition" ;
	case TreeKnownPartitionSample :
		return "KnownPartitionSample" ;
	case TreeStrategy :
		return "Strategy";
	case TreeNbStrategyTry :
		return "Number of strategy repeats";
	case TreeInitType :
		return "Initialization Type" ;
	case TreeInitTypeName :
		return "Name of initialization type" ;
	case TreeInitTypeNameUser :
		return "InitTypeNameUser" ;
	case TreeInitTypeNameUserPartition :
		return "InitTypeNameUserPartition" ;
	case TreeInitParameter :
		return "Initialization parameters" ;
	case TreeInitParameterChild :
		return "Initialization parameters childs" ;
	case TreeInitParameterSample :
		return "Sample" ;
	case TreeInitProportion :
		return "Proportion";
	case TreeInitProportionChild :
		return "Proportion";
	case TreeInitCenter:
		return "Center";
	case TreeInitCenterChild :
		return "Center ";
	case TreeInitDispersion :
		return "Dispersion";
	case TreeInitDispersionChild :
		return "Class ";
	case TreeInitDispersionData :
		return "Dispersion";
	case TreeInitScatter:
		return "Scatter";
	case TreeInitScatterChild :
		return "Class ";
	case TreeInitPartition :
		return "Initialization partition " ;
	case TreeInitParameterStrategy :
		return "Initialization Parameter " ;
	case TreeInitNbTry :
		return "Initialization Repeats" ;
	case TreeInitNbIteration :
		return "Number of iteration in strategy" ;
	case TreeInitEpsilon :
		return "Epsilon in strategy" ;
	case TreeNbAlgo :
		return "Number of Algorithm" ;
	case TreeNbAlgoChild :
		return "Algorithm " ;
	case TreeAlgoName :
		return "Name" ;
	case TreeStopRuleValue :
		return "Stop Rule Value" ;
	case TreeCriterion :
		return "Criterion" ;
	case TreeCriterionChild :
		return "Criterion " ;
	case TreeSubDimension :
		return "SubDimension" ;
	case TreeInitStopRule :
		return "Init Stop Rule";
	case TreeNbIteration :
		return "Number of iteration in algorithm";
	case TreeEpsilon :
		return "Epsilon in algorithm";
	case TreeResult :
		return "Result ";
	case TreeOutputModel :
		return "Model";
	case TreeOutputCriterion :
		return "Criterion";
	case TreeOutputCriterionName :
		return "Name ";
	case TreeOutputParameter :
		return "Parameter";
	case TreeOutputParameterChild :
		return "ParameterChild";
	case TreeOutputLabel :
		return "Label - Proba";
	case TreeOutputNbCluster :
		return "NbCLuster";
	case TreeLabelSample :
		return "Sample ";
	case TreeOutputPostProba :
		return "PostProba";
	case TreePostProbaSample :
		return "PostProbaSample";
	case TreeLikelihood :
		return "Likelihood";
	case TreeCompletedLikelihood :
		return "Completed likelihood";
	case TreeCriterionValue :
		return "Value";
	case TreeOutputProportion :
		return "Proportion";
	case TreeOutputCenter :
		return "Center";
	case TreeOutputCenterChild :
		return "Center ";
	case TreeOutputDispersion :
		return "Dispersion";
	case TreeOutputDispersionChild :
		return "Class ";
	case TreeOutputScatter :
		return "Scatter";
	case TreeOutputScatterChild :
		return "Class ";
	case TreeOutputDispersionData :
		return "Dispersion ";
	case TreeOutputTabA :
		return "Output TabA";
	case TreeOutputTabB :
		return "Output TabB";
	case TreeOutputTabD :
		return "Output TabD";
	case TreeSize :
		return "Size" ;
	case TreeNumeric :
		return "Numeric";
	case TreeGraphic :
		return "Graphics";
	case TreeQuantitativePoint :
		return "Point";
	case TreeQuantitativeClass :
		return "Class";
	case TreeQuantitativeHistogram :
		return "Histogram";
	case TreeQualitativeDiagram :
		return "Diagram";
	case TreeQualitativeBoxes :
		return "Parameter";
	case TreeNoGraphics :
		return "No Graphics";
	case TreeOutputError:
		return "Error";
	default :
		return "Error" ;
	}
}

// to string
std::string TreeItem::toString() const {
	if( _data && _keyword )
		return _data->str() ;
	else
		return std::string() ;
}

// insert the child at pos in this
void TreeItem::insertChild( TreeItem* child, child_size_type pos ) {
	child->_listPosition = _listPosition;
	if( pos >= _children.size() ) {
		pos = _children.size();
		child->_listPosition.push_back(pos);
		_children.push_back( child );
	}
	else {

		child->_listPosition.push_back(pos);
		_children.insert( _children.begin() + pos, child );
	}
	child->_parent = this ;
	updateListPosition(static_cast<int64_t>(pos+1));
}

void TreeItem::setChild( TreeItem* child, child_size_type pos ) {
	if( pos >= _children.size() ) {
		_children.push_back( child );
	}
	else {
		delete _children.at( pos );
		_children.at( pos ) = child;
	}
	child->_parent = this ;
}


// remove the child at pos in this
void TreeItem::removeChild( child_size_type pos ) {
	if( pos >= _children.size() )
		//assert(pos<_children.size());
		pos = _children.size() - 1 ;

	delete _children.at(pos);
	_children.erase( _children.begin() + pos );
	updateListPosition(static_cast<int64_t>(pos));
}

string TreeItem::getStringListPosition() {
	string str;
	for (std::deque<int64_t>::iterator it = _listPosition.begin(); it != _listPosition.end(); ++it) {
		std::ostringstream os;
		os << *it;
		str.append(os.str() + " ");
	}
	return str;
}

void TreeItem::setListPosition(deque<int64_t> & listPosition) {
	if (!_listPosition.empty())
		_listPosition.clear();

	_listPosition = listPosition;
}


void TreeItem::updateListPosition(int64_t pos) {
	if (pos < _children.size()) {
		int64_t index = pos;
		for (deque<TreeItem *>::iterator it = _children.begin() + pos; it!= _children.end(); ++it) {
			(*it)->updateChildListPosition(index);
			index++;
		}
	}
}

void TreeItem::updateChildListPosition(int64_t pos) {
	deque<int64_t> mydeque = _parent->getListPosition();
	mydeque.push_back(pos);
	setListPosition(mydeque);
	if (!_children.empty()) {
		for (int64_t index = 0; index< _children.size(); ++index) {
			_children[index]->updateChildListPosition(index);
		}
	}
}

}
}
