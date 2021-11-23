/***************************************************************************
                             SRC/GUI/MIXMOD_MVC/View.cpp  description
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
#include "mixmod_mvc/View.h"
#include "mixmod_mvc/EventMixmodDisplayScatter.h"
#include "mixmod_mvc/EventMixmodDisplayCenter.h"
#include "mixmod_mvc/EventMixmodDisplayDispersion.h"
#include "mixmod_mvc/EventMixmodDisplayDispersionData.h"
#include "mixmod/Clustering/ClusteringModelOutput.h"
#include "mixmod/Kernel/IO/ParameterDescription.h"
#include "mixmod/Kernel/IO/Label.h"
#include "mixmod/Kernel/IO/ProbaDescription.h"
#include "mixmod/Kernel/IO/LabelDescription.h"
#include "mixmod/Kernel/IO/Proba.h"
#include "mixmod/Matrix/GeneralMatrix.h"
#include <algorithm>

namespace XEM {
namespace MVC {

// copy constructor (protected, do not use it )
View::View( const View& )
	: _root( NULL ) {
}

// basic assignment (protected, do not use it )
View& View::operator=( const View& ) {
	_root = NULL ;

	return *this ;
}

// destructor
View::~View() {
	clearRoot();
}

// remove child
void View::removeChild( TreeItem* treeItem, View::size_type pos) {
	treeItem->removeChild( pos );
}


/*TreeItem* View::item( const Identifier& id )
{
  if( id.getKeyword() == NoKeyword )
    return NULL ;

  bool otherTest ( id.getKeyword() == TreeInitTypeName ||
      id.getKeyword() == TreeInitTypeNameUser ||
      id.getKeyword() == TreeInitTypeNameUserPartition
    );

  bool testParam (id.getKeyword() == TreeInitParameter ||
      id.getKeyword() == TreeInitParameterBinary ||
      id.getKeyword() == TreeInitParameterHD);

  bool testParamChild (id.getKeyword() == TreeInitParameterChild ||
      id.getKeyword() == TreeInitParameterChildBinary ||
      id.getKeyword() == TreeInitParameterChildHD);

  TreeItem* tmp = _root ;

  if (id.getKeyword() == TreeOutput && _root->getChild(1)){
    tmp = _root->getChild(1);
    return tmp;
  }


  while( tmp ){
    if( tmp->getKeyword() == id.getKeyword() )
      break ;
    if( otherTest &&
        tmp->getKeyword() == TreeInitTypeName ||
        tmp->getKeyword() == TreeInitTypeNameUser ||
        tmp->getKeyword() == TreeInitTypeNameUserPartition
      )
      break ;

    if( testParam &&
        tmp->getKeyword() == TreeInitParameter ||
        tmp->getKeyword() == TreeInitParameterBinary ||
        tmp->getKeyword() == TreeInitParameterHD
      )
      break ;

      if( testParamChild &&
        tmp->getKeyword() == TreeInitParameterChild ||
        tmp->getKeyword() == TreeInitParameterChildBinary ||
        tmp->getKeyword() == TreeInitParameterChildHD
      )
      break ;

    if( tmp->getNbChild() ){
      tmp = tmp->getChild(0);
    }else{
      while( tmp->getParent() && tmp->getPosition() == ( tmp->getParent()->getNbChild() - 1 ) ){
          tmp = tmp->getParent();
      }
      if( tmp->getParent() && tmp->getPosition() != ( tmp->getParent()->getNbChild() - 1 ) ){
        tmp = tmp->getParent()->getChild( tmp->getPosition() + 1 );
      }else{
        tmp = NULL ;
      }
    }
  }


  TreeItem* tmpParent2 = tmp->getParent();
  if( tmpParent2 ){
    TreeItem* tmpGParent2 = tmpParent2->getParent();
    if( tmpGParent2 ){
      TreeItem* tmpGGParent2 = tmpGParent2->getParent();
      if (tmpGGParent2){
        return tmpGGParent2->getChild( id.getGParentPosition() )->getChild( id.getParentPosition() )->getChild( id.getPosition() ) ;
      }else{
        return tmpGParent2->getChild( id.getParentPosition() )->getChild( id.getPosition() ) ;
      }
    }else{
      return tmpParent2->getChild( id.getPosition() );
    }
  }

  return tmp ;
}*/

void View::addOutput(ClusteringOutput* cOutput) {


	_root->insertChild( TreeItem::createItem( "", TreeOutput ), OUTPUT) ;

	updateOutputOrdering(cOutput);

}

void View::updateOutput(ClusteringOutput* cOutput) {
	if (_root->getNbChild() == 2) {
		for (int64_t i = 0; i<cOutput->getNbClusteringModelOutput(); ++i) {
			getOutput()->removeChild(0);
		}
		updateOutputOrdering(cOutput);
	}
}

void View::updateOutputOrdering(ClusteringOutput* cOutput ) {
	typedef View POS_IN_OUTPUT;
	typedef View PARAM_IN_OUTPUT;
	typedef View POS_IN_NUMERIC;
	typedef View POS_IN_GRAPHIC;

	int64_t i;
	int64_t iPos;

	for (iPos = 0; iPos< cOutput->getNbClusteringModelOutput(); ++iPos) {

		ClusteringModelOutput* cMOutput = cOutput->getClusteringModelOutput(iPos);
		getOutput()->insertChild( TreeItem::createItem( "", TreeResult ), iPos );

		//Numeric node
		getOutput()->getChild(iPos)->insertChild( TreeItem::createItem( "", TreeNumeric ), POS_IN_OUTPUT::NUMERIC );
		//Model
		//-----
		getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->insertChild(TreeItem::createItem( ModelNameToString(cMOutput->getModelType().getModelName()), TreeOutputModel ),POS_IN_NUMERIC::MODEL_OUTPUT);
		if(isHD(cMOutput->getModelType().getModelName()) ) {
			GaussianHDDAParameter * param = static_cast<GaussianHDDAParameter *> (cMOutput->getParameterDescription()->getParameter());
			for (i=0; i<cMOutput->getNbCluster(); ++i) {
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::MODEL_OUTPUT)->insertChild(TreeItem::createItem( param->getTabD()[i] ,TreeSubDimension),i );
			}
		}

		// nbCluster
		//----------
		getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->insertChild(TreeItem::createItem( cMOutput->getNbCluster(),TreeOutputNbCluster) ,POS_IN_NUMERIC::NBCLUSTER_OUTPUT);

		if(cMOutput->getStrategyRunError()==NOERROR) { //si l'estimation a abouti
			// criterion
			//-----------
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->insertChild(TreeItem::createItem("", TreeOutputCriterion),POS_IN_NUMERIC::CRITERION_OUTPUT);

			//Critertion name & value
			// loop over all criterion
			for (i = 0; i<cOutput->getCriterionSize() ; ++i) {
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::CRITERION_OUTPUT)->insertChild(TreeItem::createItem(CriterionNameToString(cOutput->getCriterionName(i)),TreeOutputCriterionName),i);
				if(cMOutput->getCriterionOutput(cOutput->getCriterionName(i)).getError()==NOERROR) {
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::CRITERION_OUTPUT)->getChild(i)->insertChild(TreeItem::createItem(cMOutput->getCriterionOutput(cOutput->getCriterionName(i)).getValue(),TreeCriterionValue), 0 );
				}
				else {//error while computing
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::CRITERION_OUTPUT)->getChild(i)->insertChild(TreeItem::createItem(string(cMOutput->getCriterionOutput(cOutput->getCriterionName(i)).getError().what()),TreeOutputError), 0 );
				}
			}

			//parameter
			//---------

			Parameter * parameter = cMOutput->getParameterDescription()->getParameter();
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->insertChild(TreeItem::createItem("", TreeOutputParameter),POS_IN_NUMERIC::PARAMETER_OUTPUT);

			//proportion
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("",TreeOutputProportion),PARAM_IN_OUTPUT::PROPORTION_OUTPUT);
			for (i = 0; i<cMOutput->getNbCluster(); ++i) {
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::PROPORTION_OUTPUT)->insertChild(TreeItem::createItem(parameter->getTabProportion()[i], TreeOutputProportionChild) ,i);
			}

			//EDDA
			if (isEDDA(cMOutput->getModelType().getModelName())) {
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("",TreeOutputCenter) ,PARAM_IN_OUTPUT::MEAN_OUTPUT);
				GaussianEDDAParameter * param = static_cast<GaussianEDDAParameter *> (parameter);
				//Mean
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					Event* event = new EventMixmodDisplayCenter(param->getTabMean()[i],param->getPbDimension());
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::MEAN_OUTPUT)->insertChild(TreeItem::createItem(event->getDisplay() ,TreeOutputCenterChild),i);
					delete event;
				}

				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("",TreeOutputDispersion) ,PARAM_IN_OUTPUT::VARIANCE_OUTPUT);

				//Dispersion
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					Event* event = new EventMixmodDisplayDispersion((double **) NULL, param->getPbDimension());
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::VARIANCE_OUTPUT)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputDispersionChild),i );
					delete event;
					for (int64_t j=0; j<param->getPbDimension(); ++j) {
						Event* event = new EventMixmodDisplayDispersionData(param->getTabSigma()[i]->storeToArray()[j], param->getPbDimension());
						getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::VARIANCE_OUTPUT)->getChild(i)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputDispersionData),j);
						delete event;
					}
				}
			}

			// Binary
			else if (isBinary(cMOutput->getModelType().getModelName())) {
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("",TreeOutputCenter) ,PARAM_IN_OUTPUT::MEAN_OUTPUT);
				BinaryParameter * param = static_cast<BinaryParameter*> (parameter);
				//center
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					Event* event = new EventMixmodDisplayCenterB(param->getTabCenter()[i],param->getPbDimension());
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::MEAN_OUTPUT)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputCenterChild), i );
					delete event;
				}

				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("", TreeOutputScatter),PARAM_IN_OUTPUT::VARIANCE_OUTPUT);

				//Scatter
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					Event* event = new EventMixmodDisplayScatter((double **) NULL, param->getPbDimension(), param->getTabNbModality());
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::VARIANCE_OUTPUT)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputScatterChild),i );
					delete event;
					for (int64_t j=0; j<param->getPbDimension(); ++j) {
						Event* event = new EventMixmodDisplayDispersionData(param->scatterToArray()[i][j], param->getTabNbModality()[j]);
						getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::VARIANCE_OUTPUT)->getChild(i)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputDispersionData),j );
						delete event;
					}
				}
			}

			//HD
			else if (isHD(cMOutput->getModelType().getModelName())) {
				// a faire et faire des tests dans setAlgoName et insertAlgo pour M et MAP
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("",TreeOutputCenter) ,PARAM_IN_OUTPUT::MEAN_OUTPUT);
				GaussianHDDAParameter * param = static_cast<GaussianHDDAParameter*> (parameter);
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					Event* event = new EventMixmodDisplayCenter(param->getTabMean()[i],param->getPbDimension());
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(PARAM_IN_OUTPUT::MEAN_OUTPUT)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputCenterChild),i );
					delete event;
				}

				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("Parameter Akj",TreeOutputParameterChild),2 );
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					Event* event = new EventMixmodDisplayCenter(param->getTabA()[i],param->getTabD()[i]);
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(2)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputTabA),i );
					delete event;
				}
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("Parameter Bk",TreeOutputParameterChild),3 );
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(3)->insertChild(TreeItem::createItem(param->getTabB()[i],TreeOutputTabB),i );
				}

				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->insertChild(TreeItem::createItem("Parameter Qk",TreeOutputParameterChild),4 );
				GeneralMatrix ** tabQk = param->getTabQ();
				for (i = 0; i<cMOutput->getNbCluster(); ++i) {
					Event* event = new EventMixmodDisplayScatter(tabQk[i]->storeToArray(),param->getPbDimension(),param->getTabD());
					getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::PARAMETER_OUTPUT)->getChild(4)->insertChild(TreeItem::createItem(event->getDisplay(),TreeOutputDispersion),i );
					delete event;
				}
			}

			//label+Proba
			//-----
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->insertChild(TreeItem::createItem("",TreeOutputLabel),POS_IN_NUMERIC::LABEL_OUTPUT );
			Label * label = const_cast<Label *>(cMOutput->getLabelDescription()->getLabel());
			double * labelAndProba = new double[2];
			for (i=0 ; i<label->getNbSample(); ++i) {
				labelAndProba[0] = label->getLabel()[i];
				vector<double> v(cMOutput->getProbaDescription()->getProba()->getProba()[i]);
				vector<double>::iterator iterator= max_element( v.begin(),v.end() );
				labelAndProba[1] = *iterator;
				Event* event = new EventMixmodDisplay<double *>(labelAndProba, 2);
				getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->getChild(POS_IN_NUMERIC::LABEL_OUTPUT)->insertChild( TreeItem::createItem(event->getDisplay(),TreeLabelSample),i);
				delete event;
			}
			delete labelAndProba;

			// posterior probabilities
			/*insertChild(getRoot()->getChild(iPos),5, TreeOutputLabel, "Posterior Probabilities");

			for (i=0 ; i<_tabEstimation[iPos]->getProbaOutput()->getNbSample(); ++i){
			double ** probabilities = _tabEstimation[iPos]->getProbaOutput()->getTabPostProba();
			Event * event = new EventMixmodDisplayCenter(probabilities[i],_tabEstimation[iPos]->getNbCluster());
			insertChild(getRoot()->getChild(iPos)->getChild(5),i, TreePostProbaSample, event->getDisplay());
			   }*/

			// likelihood
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->insertChild(TreeItem::createItem(cMOutput->getLikelihood(),TreeLikelihood),POS_IN_NUMERIC::LIKELIHOOD_OUTPUT );
			//insertChild( getRoot()->getChild(iPos), 1 , TreeGraphic,"" );
		} // end if paremeter!=NULL
		else {
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::NUMERIC)->insertChild(TreeItem::createItem( string(cMOutput->getStrategyRunError().what()),TreeOutputError), POS_IN_NUMERIC::ERROR_OUTPUT);
		}

		getOutput()->getChild(iPos)->insertChild( TreeItem::createItem( "", TreeGraphic ), POS_IN_OUTPUT::GRAPHIC );
		//if (cMOutput->getParameterDescription()->getParameter()->getPbDimension()>1){
		if (isBinary(StringToModelName(getInput()->getChild(MODEL)->getChild(0)->toString()))) {
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::GRAPHIC)->insertChild( TreeItem::createItem( "", TreeQualitativeDiagram ), POS_IN_GRAPHIC::QUALITATIVE_GRAPHICS_DIAGRAM );
			//getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::GRAPHIC)->insertChild( TreeItem::createItem( "", TreeQualitativeBoxes ), POS_IN_GRAPHIC::QUALITATIVE_GRAPHICS_BOXES );

		}
		else {
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::GRAPHIC)->insertChild( TreeItem::createItem( "", TreeQuantitativePoint ), POS_IN_GRAPHIC::QUANTITATIVE_GRAPHICS_POINT );
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::GRAPHIC)->insertChild( TreeItem::createItem( "", TreeQuantitativeClass ), POS_IN_GRAPHIC::QUANTITATIVE_GRAPHICS_CLASS );
			getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::GRAPHIC)->insertChild( TreeItem::createItem( "", TreeQuantitativeHistogram ), POS_IN_GRAPHIC::QUANTITATIVE_GRAPHICS_HISTOGRAM );
		}
//     }else{
//       getOutput()->getChild(iPos)->getChild(POS_IN_OUTPUT::GRAPHIC)->insertChild( TreeItem::createItem( "", TreeNoGraphics ), POS_IN_GRAPHIC::NO_GRAPHICS );
//     }

	}
}

}
}
