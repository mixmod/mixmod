/***************************************************************************
							 SRC/GUI/MIXMOD_MVC/Controler.cpp  description
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

#include "mixmod_mvc/Controller.h"
#include "mixmod/Kernel/Model/ModelType.h"
#include "mixmod/Clustering/ClusteringInput.h"
#include "mixmod/Clustering/ClusteringStrategy.h"
#include "mixmod/Clustering/ClusteringStrategyInit.h"
#include "mixmod/Kernel/Algo/Algo.h"
#include <sstream>
#include <stdint.h>

namespace XEM {
namespace MVC {


// constructor
Controller::Controller( View* view,  Model* model )
	: _view(view), _model(model) {
	updateView();
	if (_model->hasOutput()) {
		_view->addOutput(_model->getOutput());
	}
}

// copy constructor
Controller::Controller( const Controller& )
	: _view( NULL ), _model( NULL ) {
}

// operator =
Controller& Controller::operator=( const Controller& ) {
	_view = NULL ;
	_model = NULL ;
	return *this ;
}

// destructor
Controller::~Controller() {
	/* do not delete because no copy was done
	  if( _view )
		delete _view ;
	  if( _model )
		delete _model ;
	 */
	_view = NULL ;
	_model = NULL ;
}

// update view with model
void Controller::updateView() {
	typedef View POS_PROJECT ;
	typedef View POS_INPUT ;
	typedef View POS_DATA ;
	typedef View POS_STRAT ;
	typedef View POS_INIT ;
	typedef View POS_PARAM ;
	typedef View POS_ALGO ;
	typedef View POS_INIT_PARAMETER_STRATEGY;

	if ( !_model || !(_model->hasInput()) || !(dynamic_cast<ClusteringInput *> (_model->getInput())) )
		return;

	ClusteringInput * input = static_cast<ClusteringInput *> (_model->getInput()) ;

	// equivalent to step

	_view->setRoot( TreeItem::createItem( "", TreeProject ) );

	_view->insertChild( _view->getRoot(), POS_PROJECT::INPUT, TreeInput, "" );
	//     // data
	string fileName = "";
	if (input->getData())
		fileName = input->getData()->getFileName();

	_view->insertChild( _view->getInput(), POS_INPUT::DATA , TreeData,  "" );
	//dimension
	_view->insertChild( _view->getInput()->getChild( POS_INPUT::DATA ), POS_DATA::PB_DIMENSION , TreePbDimension, input->getPbDimension() );
	// samples
	_view->insertChild( _view->getInput()->getChild( POS_INPUT::DATA ), POS_DATA::NB_SAMPLE , TreeNbSample, input->getNbSample() );
	_view->insertChild( _view->getInput()->getChild( POS_INPUT::DATA ), POS_DATA::SAMPLES, TreeDataSample, fileName);

	// weight
	//_view->insertChild( _view->getRoot()->getChild( POS_INPUT::DATA ), POS_DATA::WEIGHT, TreeDataWeight, Model::DEFAULTFILENAME );


	// nbModality
	if ( input->getDataType() == QualitativeData) {
		_view->insertChild(
		    _view->getInput()->getChild( POS_INPUT::DATA ),
		    POS_DATA::NB_MODALITY,
		    TreeFactor,
		    Vector<int64_t>( static_cast<const BinaryData* > ( input->getData() )->getTabNbModality(), input->getPbDimension() )
		);
	}

	//_view->insertChild( _view->getRoot(), POS_INPUT::NB_SAMPLE , TreeNbSample, input->getNbSample() );
	_view->insertChild( _view->getInput(), POS_INPUT::NB_NB_CLUSTER , TreeNbNbCluster, "" );
	for ( int64_t i = 0 ; i < input->getNbClusterSize() ; ++i )
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::NB_NB_CLUSTER), i , TreeNbCluster, input->getNbCluster(i));

	// travail sur model
	_view->insertChild( _view->getInput(), POS_INPUT::MODEL , TreeModel, "" );
	for (int64_t i = 0; i < input->getModelType().size(); i++) {
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::MODEL), i , TreeModelChild, ModelNameToString( input->getModelType()[i]->getModelName() ) );
		if (input->getModelType()[i]->getSubDimensionEqual() != 0) {
			//TODO
		}
		else if (input->getModelType()[i]->getTabSubDimensionFree() != NULL) {
			//TODO
		}
	}

	// strategy

	// the strategy
	ClusteringStrategy * strat = dynamic_cast<ClusteringStrategy*> (input->getStrategy());

	_view->insertChild( _view->getInput(), POS_INPUT::STRATEGY , TreeStrategy, " " );
	//nbtry
	_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY),
	                    POS_STRAT::NB_STRATEGY_TRY , TreeNbStrategyTry, strat->getNbTry());
	// init type
	_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY), POS_STRAT::INIT , TreeInitType, " " );

	// init type child (ex:RANDOM)
	StrategyInitName initName = strat->getStrategyInit()->getStrategyInitName();

	_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT), POS_INIT::INIT_NAME, TreeInitTypeName, StrategyInitNameToString( initName ) );
	switch (initName) {
	case RANDOM:
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT), POS_INIT::NB_TRY_INIT_RANDOM, TreeInitNbTry, strat->getNbTryInInit() );
		break;
	case SMALL_EM:
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT), POS_INIT::NB_TRY_INIT_SMALL_EM, TreeInitNbTry, strat->getNbTryInInit() );
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT), POS_INIT::STOP_RULE_SMALL_EM, TreeInitStopRule, "" );
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT)->getChild(POS_STRAT::STOP_RULE_SMALL_EM), POS_INIT::NB_ITERATION, TreeInitNbIteration, strat->getNbIterationInInit() );
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT)->getChild(POS_STRAT::STOP_RULE_SMALL_EM), POS_INIT::EPSILON, TreeInitEpsilon, strat->getEpsilonInInit() );
		break;
	case CEM_INIT:
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT), POS_INIT::NB_TRY_INIT_CEM, TreeInitNbTry, strat->getNbTryInInit() );
		break;
	case SEM_MAX:
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::INIT), POS_INIT::NB_ITERATION_SEM_MAX, TreeInitNbIteration, strat->getNbIterationInInit() );
		break;
	default:
		break;
	}
	const ClusteringStrategyInit * initStrat = strat->getStrategyInit();

	// nb algo
	_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY), POS_STRAT::NB_ALGO , TreeNbAlgo, "NbAlgo" );

	// for each algo
	for ( int64_t i = 0 ; i < strat->getNbAlgo() ; ++i ) {
		// alog root
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::NB_ALGO), i , TreeNbAlgoChild, "  " );

		// add algo name to algo
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::NB_ALGO)->getChild(i), POS_ALGO::ALGO_NAME , TreeAlgoName, AlgoNameToString( strat->getAlgo(i)->getAlgoName() ) );
		// add algo stop rule to algo
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::NB_ALGO)->getChild(i), POS_ALGO::STOP , TreeStopRuleValue, " ");

		// add stop rule data thanks to stop rule value
		if ( strat->getAlgo(i)->getAlgoStopName() == EPSILON ) { // EPSILON
			_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::NB_ALGO)->getChild(i)->getChild(POS_ALGO::STOP), 0 , TreeEpsilon, strat->getAlgo(i)->getEpsilon() );
		}
		else if ( strat->getAlgo(i)->getAlgoStopName() == NBITERATION ) { // NBITERATION
			_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::NB_ALGO)->getChild(i)->getChild(POS_ALGO::STOP), 0 , TreeNbIteration, strat->getAlgo(i)->getNbIteration() );
		}
		else if ( strat->getAlgo(i)->getAlgoStopName() == NBITERATION_EPSILON ) {
			// BOTH
			_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::NB_ALGO)->getChild(i)->getChild(POS_ALGO::STOP), 0 , TreeNbIteration, strat->getAlgo(i)->getNbIteration() );
			_view->insertChild( _view->getInput()->getChild(POS_INPUT::STRATEGY)->getChild(POS_STRAT::NB_ALGO)->getChild(i)->getChild(POS_ALGO::STOP), 1 , TreeEpsilon, strat->getAlgo(i)->getEpsilon() );
		}
	}

	// criterion waiting for better
	_view->insertChild( _view->getInput(), POS_INPUT::CRITERION , TreeCriterion, "" );
	for ( int64_t i = 0 ; i < input->getNbCriterion() ; ++i )
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::CRITERION), i , TreeCriterionChild, CriterionNameToString( input->getCriterionName(i) ) );

	// known partition
	if (input->getNbClusterSize() == 1) {
		_view->insertChild( _view->getInput(), POS_INPUT::KNOWN_PARTITION , TreeKnownPartition, Model::DEFAULTFILENAME );
	}
}

void Controller::updateViewAD() {
	typedef View POS_PROJECT ;
	typedef View POS_INPUT ;
	typedef View POS_DATA ;

	//TODO lancer si input est AD seulement
	if ( ! _model )
		return;

	ClusteringInput* input = _model->getInput() ;

	// equivalent to step
	_view->setRoot( TreeItem::createItem( "", TreeProject ) );

	_view->insertChild( _view->getRoot(), POS_PROJECT::INPUT, TreeInput, "");
	// data
	string fileName = "";
	if (input->getData())
		fileName = input->getData()->getFileName();

	_view->insertChild( _view->getInput(), POS_INPUT::DATA_AD , TreeData,  "" );
	//dimension
	_view->insertChild( _view->getInput()->getChild( POS_INPUT::DATA_AD ), POS_DATA::PB_DIMENSION_AD , TreePbDimension, input->getPbDimension() );
	// samples
	_view->insertChild( _view->getInput()->getChild( POS_INPUT::DATA_AD ), POS_DATA::NB_SAMPLE_AD , TreeNbSample, input->getNbSample() );
	_view->insertChild( _view->getInput()->getChild( POS_INPUT::DATA_AD ), POS_DATA::SAMPLES_AD, TreeDataSample, fileName);

	// weight
	_view->insertChild( _view->getInput()->getChild( POS_INPUT::DATA_AD ), POS_DATA::WEIGHT_AD, TreeDataWeight, Model::DEFAULTFILENAME );

	// nbModality
	if ( isBinary( input->getModelType()[0]->getModelName() ) ) {
		_view->insertChild(
		    _view->getInput()->getChild( POS_INPUT::DATA_AD ),
		    POS_DATA::NB_MODALITY_AD,
		    TreeFactor,
		    Vector<int64_t>( static_cast<const BinaryData* > ( input->getData() )->getTabNbModality(), input->getPbDimension() )
		);
	}

	//NbCluster
	//_view->insertChild( _view->getRoot(), POS_INPUT::NB_SAMPLE , TreeNbSample, input->getNbSample() );
	_view->insertChild( _view->getInput(), POS_INPUT::NB_CLUSTER_AD , TreeNbCluster, input->getNbCluster(0) );
	/*for( int64_t i = 0 ; i < input->getNbNbCluster() ; ++i )
	  _view->insertChild( _view->getRoot()->getChild(POS_INPUT::NB_NB_CLUSTER), i , TreeNbCluster, input->getTabNbCluster()[i] );*/
	// travail sur model
	_view->insertChild( _view->getInput(), POS_INPUT::MODEL_AD , TreeModel, "" );
	for ( int64_t i = 0 ; i < input->getModelType().size() ; ++i ) {
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::MODEL_AD), i , TreeModelChild, ModelNameToString( input->getModelType()[i]->getModelName() ) );
		if (input->getModelType()[i]->getSubDimensionEqual() != 0) {
			//TODO
		}
		else if (input->getModelType()[i]->getTabSubDimensionFree() != NULL) {
			//TODO
		}
	}

	// data to classify
	_view->insertChild( _view->getInput(), POS_INPUT::DATA_CLASSIFY_AD , TreeDataClassify, Model::DEFAULTFILENAME );

	// known partition
	_view->insertChild( _view->getInput(), POS_INPUT::KNOWN_PARTITION_AD , TreeKnownPartition, input->getKnownPartition()->getPartitionFile()._fileName );
	for ( int64_t i = 0 ; i < input->getNbSample() ; ++i ) {
		_view->insertChild( _view->getInput()->getChild(POS_INPUT::KNOWN_PARTITION_AD), i , TreeKnownPartitionSample, Vector<int64_t>(input->getKnownPartition()->getTabValueI(i), input->getNbCluster(0) ));
	}

	// criterion waiting for better
	_view->insertChild( _view->getInput(), POS_INPUT::CRITERION_AD , TreeCriterion, "" );
	_view->insertChild( _view->getInput()->getChild(POS_INPUT::CRITERION_AD), 0 , TreeCriterionChild, "CV" );
}

// process Event
void Controller::processEvent( TreeItem * treeItem, Event* e ) {
	e->setControler( this );
	e->process( treeItem );
}
}
}
