/***************************************************************************
                             SRC/GUI/MIXMOD_QT/MVCMixmod.cpp  description
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
#include "MVCMixmod.h"
#include "MVCDefaultView.h"
#include "MVCEventUser.h"

#include "mixmod/Kernel/IO/GaussianData.h"
#include "mixmod/Kernel/IO/BinaryData.h"
#include "mixmod/Kernel/Algo/Algo.h"
#include "mixmod/Utilities/Util.h"
#include "GUIMMetaData.h"

namespace XEM {
namespace MVC {

Mixmod::Mixmod()
	: _model( new Model() ), _view( new DefaultView() ), _engine( new Controller( _view, _model ) ) {
}

Mixmod::Mixmod(ClusteringMain * cMain): _model( new Model(cMain) ), _view( new DefaultView() ), _engine( new Controller( _view, _model ) ) {

}

Mixmod::~Mixmod() {
	if( _engine )
		delete _engine ;
	if( _view )
		delete _view ;
	if( _model )
		delete _model ;
}

Mixmod::Mixmod( const Mixmod& )
	: _model( NULL ), _view( NULL ), _engine( NULL ) {
}

Mixmod& Mixmod::operator=( const Mixmod& ) {
	_model = NULL ;
	_view = NULL ;
	_engine = NULL ;
	return *this ;
}

// Clustering Main with gaussian Data
void Mixmod::constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName) {

	_model->constructClusteringMain(iNbSample, iPbDimension, iNbCluster, iDataFileName);

	_engine->updateView();
}

// Clustering Main with binary Data
void Mixmod::constructClusteringMain(int64_t iNbSample, int64_t iPbDimension, vector<int64_t> iNbCluster, const std::string & iDataFileName, vector<int64_t> iModality) {

	_model->constructClusteringMain(iNbSample, iPbDimension, iNbCluster, iDataFileName, iModality);

	_engine->updateView();
}

//CLustering Main from dataDescription
void Mixmod::constructClusteringMain(vector<int64_t> nbCluster, DataDescription * dataDescription) {

	_model->constructClusteringMain(nbCluster, *dataDescription);

	_engine->updateView();
}

// DA Main with gaussian Data
void Mixmod::constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify) {

	_model->constructDAMain(iNbSample, iPbDimension, iNbCluster, iDataFileName, iDataPartitionFileName, iDataFileNameToClassify);

	_engine->updateViewAD();
}

// DA Main with binary Data
void Mixmod::constructDAMain(int64_t iNbSample, int64_t iPbDimension, int64_t iNbCluster, const std::string & iDataFileName, const string & iDataPartitionFileName, const string iDataFileNameToClassify, vector<int64_t> iModality) {

	_model->constructDAMain(iNbSample, iPbDimension, iNbCluster, iDataFileName, iDataPartitionFileName, iDataFileNameToClassify, iModality);

	_engine->updateViewAD();
}


//////////////////// Modify data /////////////////////

// insert
bool Mixmod::insertChild( TreeItem* item, int pos ) {
	unsigned int oldNbChild = item->getNbChild() ;
	Event* event = NULL ;

	switch( item->getKeyword() ) {
	case TreeProject :
		_model->getInput()->finalize();
		_model->getClusteringMain()->run();
		_view->addOutput(_model->getClusteringMain()->getOutput());;
		break;
	case TreeModel :
		// _engine->insertChild( item, pos, UNKNOWN_MODEL_TYPE );
		event = new EventUserInsertModel( UNKNOWN_MODEL_NAME, pos );
		break ;
	case TreeNbAlgo :
		// _engine->insertChild( item, pos, UNKNOWN_ALGO_TYPE );
		event = new EventUserInsertAlgo( UNKNOWN_ALGO_NAME, pos );
		break ;
	case TreeKnownPartition : // DO
		// _engine->insertChild( item, pos, "NONE" );
		event = new EventUserInsertKnownPartition( Model::DEFAULTFILENAME );
		break ;
	case TreeDataWeight : // DO
		// _engine->insertChild( item, pos, "NONE" );
		event = new EventUserInsertWeight( Model::DEFAULTFILENAME );
		break ;
	case TreeCriterion : // DO
		// _engine->insertChild( item, pos, UNKNOWN_CRITERION_TYPE );
		event = new EventUserInsertCriterion( UNKNOWN_CRITERION_NAME, pos );
		break ;
	case TreeStopRuleValue : // DO
		if (oldNbChild == 1) {
			event = new EventUserInsertStopRule(NBITERATION_EPSILON, pos );
		}
		break ;
	case TreeInitType :
		event = new EventUserInsertParamInInit( pos );
		break;
	default :
		return true ;
	}

	if( event ) {
		_engine->processEvent( item, event );
		delete event ;
	}

	if( item->getNbChild() == oldNbChild )
		return false ;

	return true ;
}

// remove
bool Mixmod::removeChild( TreeItem* item, int pos ) {
	unsigned int oldNbChild = item->getNbChild() ;
	Event* event = NULL ;

	switch( item->getKeyword() ) {
//   case TreeProject :
//     _view->removeOutput();
//     break;
	case TreeModel :
		// _engine->removeChild<XEMModelName>( item, pos );
		event = new EventUserRemoveModel(pos);
		break ;
	case TreeNbAlgo :
		// _engine->removeChild<XEMAlgoName>( item, pos );
		event = new EventUserRemoveAlgo(pos);
		break ;
	case TreeKnownPartition : // DO
		// _engine->removeChild<std::string>( item, pos );
		event = new EventUserRemoveKnownPartition();
		break ;
	case TreeCriterion : // DO
		// _engine->removeChild<XEMCriterionType>( item, pos );
		event = new EventUserRemoveCriterion(pos);
		break ;
	case TreeDataWeight :
		event = new EventUserRemoveWeight( );
		break;
	case TreeStopRuleValue :
		if (oldNbChild == 2) { //stopRule becomes epsilon or nbiteration
			if (pos == 0) { //nbiteration to delete
				event = new EventUserRemoveNbIteration(pos);
			}
			else {
				event = new EventUserRemoveEpsilon(pos);
			}
		}
		break ;
	case TreeInitType :
		event = new EventUserRemoveParamInInit( pos );
		break;
	case TreeInitStopRule :
		if (pos == 1) {
			event = new EventUserRemoveEpsilon(pos);
		}
		else {
			event = new EventUserRemoveNbIteration(pos);
		}
		break;
	default :
		return true ;
	}

	if( event ) {
		_engine->processEvent( item, event );
		delete event ;
	}

	if( item->getNbChild() == oldNbChild )
		return false ;

	return true ;
}

// set
bool Mixmod::setValue( TreeItem* item, const QVariant& v ) {
	Event* event = NULL ;

	switch( item->getKeyword() ) {
// TODO InitType
	case TreeModelChild :
		// _engine->setValue( item, v.value<XEMModelName>() );
		event = new EventUserSetModelChild( v.value<ModelName>() );
		break ;
	case TreeAlgoName : // DO
		// _engine->setValue( item, v.value<XEMAlgoName>() );
		event = new EventUserSetAlgoName( v.value<AlgoName>() );
		break ;
	case TreeStopRuleValue : // DO
		if ( v.value<AlgoStopName>() == EPSILON ) {
			event = new EventUserSetEpsilon( getModel()->getInput()->getStrategy()->getAlgo(0)->getEpsilon() );
		}
		else if ( v.value<AlgoStopName>() == NBITERATION ) {
			event = new EventUserSetNbIteration( getModel()->getInput()->getStrategy()->getAlgo(0)->getNbIteration() );
		}
		break ;
	case TreeInitStopRule :
		event = new EventUserSetStopRuleInit( v.value<AlgoStopName>() );
		break;
	case TreeNbStrategyTry :
		event = new EventUserSetNbStrategyTry( v.toInt() );
		break;
	case TreeDataWeight :
		event = new EventUserSetWeight( v.toString().toStdString() );
		break;
	case TreeEpsilon : // DO
		// _engine->setValue( item, v.toDouble() );
		event = new EventUserSetEpsilon( v.toDouble() );
		break ;
	case TreeNbIteration : // DO
		// _engine->setValue( item, v.toInt() );
		event = new EventUserSetNbIteration( v.toInt() );
		break ;
	case TreeKnownPartition : // DO
		// _engine->setValue( item, v.toString().toStdString() );
		event = new EventUserSetKnownPartition( v.toString().toStdString() );
		break ;
	case TreeCriterionChild : // DO
		// _engine->setValue( item, v.value<XEMCriterionType>() );
		event = new EventUserSetCriterionChild( v.value<CriterionName>() );
		break ;
	case TreeSubDimension : // DO
		//_engine->setValue( item, v.toInt() );
		event = new EventUserSetSubDim( v.toInt() );
		break ;
	case TreeInitTypeName :
		event = new EventUserSetInitName( v.value<StrategyInitName>() );
		break;
	case TreeInitPartition :
		event = new EventUserSetInitPart( v.toString().toStdString()  );
		break;
	case TreeInitParameterBinary :
	case TreeInitParameter :
		event = new EventUserSetInitParam( v.toString().toStdString()  );
		break;
	case TreeInitNbTry :
		event = new EventUserSetNbTryInit( v.toInt() );
		break;
	case TreeInitNbIteration :
		event = new EventUserSetNbIteration( v.toInt() );
		break;
	case TreeInitEpsilon :
		event = new EventUserSetEpsilon( v.toDouble() );
		break;
	default :
		return false ;
	}

	if( event ) {
		_engine->processEvent( item, event );
		delete event ;
	}

	return true ;
}

//////////////////////////////////////////////////////

bool Mixmod::find( TreeItem* item ) const {
	TreeItem* tmp = _view->getInput() ;

	while( tmp ) {
		if( tmp == item )
			break ;

		if( tmp->getNbChild() ) {
			tmp = tmp->getChild(0);
		}
		else {
			while( tmp->getParent() && tmp->getPosition() == ( tmp->getParent()->getNbChild() - 1 ) ) {
				tmp = tmp->getParent();
			}
			if( tmp->getParent() && tmp->getPosition() != ( tmp->getParent()->getNbChild() - 1 ) ) {
				tmp = tmp->getParent()->getChild( tmp->getPosition() + 1 );
			}
			else {
				tmp = NULL ;
			}
		}
	}

	if( tmp == NULL )
		return false ;

	return true ;
}

}
}
