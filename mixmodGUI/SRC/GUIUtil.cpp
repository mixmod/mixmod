/***************************************************************************
                             SRC/GUI/MIXMOD_QT/GUIUtil.cpp  description
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
#include "GUIUtil.h"
#include "GUIMixmod.h"

bool GUISettings::authorizedToClosed = true;	/*if window is authorized to be closed*/
bool GUISettings::outputIsPresent = false;
QDir GUISettings::workDirectory = QDir();

Autorization TreeItemIsModifiable(QModelIndex index) {
	XEM::MVC::TreeItem* item = reinterpret_cast<XEM::MVC::TreeItem*>( index.internalPointer() );
	Autorization autorization;
	autorization.toDelete=false;
	autorization.toSet=false;
	autorization.toInsertRemove=false;
	autorization.toInsert=false;
	if (GUISettings::outputIsPresent) { //if output is present
		switch( item->getKeyword() ) {
		case XEM::MVC::TreeInput :
			autorization.toSet = true;
			break;
		case XEM::MVC::TreeOutput : {
			if (index.row()-1>=0) {
				int64_t nbCriterion = ((GUIMTreeModel *)index.model())->getClusteringMain(index.row()-1)->getInput()->getCriterionName().size();
				int64_t nbModel = ((GUIMTreeModel *)index.model())->getClusteringMain(index.row()-1)->getInput()->getModelType().size();
				int64_t nbCluster = ((GUIMTreeModel *)index.model())->getClusteringMain(index.row()-1)->getInput()->getNbClusterSize();
				autorization.toSet = nbCriterion>1 && (nbModel>1 || nbCluster>1);
				autorization.toDelete = true;
			}
			break ;
		}
		case XEM::MVC::TreeQuantitativeHistogram :
		case XEM::MVC::TreeQualitativeDiagram :
		case XEM::MVC::TreeQualitativeBoxes : {
			bool graphicPresent = (static_cast<GUIMixmod *>((index.model())->QObject::parent())->getGraphic(index.row())!=NULL) ;
			autorization.toInsert = !graphicPresent;
			autorization.toDelete = graphicPresent;
			break;
		}
		case XEM::MVC::TreeQuantitativePoint :
		case XEM::MVC::TreeQuantitativeClass : {
			if (((GUIMTreeModel *)index.model())->getClusteringMain(0)->getInput()->getPbDimension()>1) {
				bool graphicPresent = (static_cast<GUIMixmod *>((index.model())->QObject::parent())->getGraphic(index.row())!=NULL) ;
				autorization.toInsert = !graphicPresent;
				autorization.toDelete = graphicPresent;
			}
			break;
		}
		default :
			break;
		}
		return autorization;
	}

	switch( item->getKeyword() ) {
	case XEM::MVC::TreeStopRuleValue :
	case XEM::MVC::TreeModel :
	case XEM::MVC::TreeCriterion :
	case XEM::MVC::TreeInitStopRule :
		autorization.toInsertRemove=true;
		break;
	case XEM::MVC::TreeInitNbIteration :
	case XEM::MVC::TreeInitEpsilon :
	case XEM::MVC::TreeEpsilon :
	case XEM::MVC::TreeNbIteration :
	case XEM::MVC::TreeCriterionChild :
		autorization.toDelete = ( item->getParent()->getNbChild() != 1 && item->getParent()->getKeyword() != XEM::MVC::TreeInitType) ;
		autorization.toSet = true ;
		break ;
	case XEM::MVC::TreeModelChild :
	case XEM::MVC::TreeNbAlgoChild :
		autorization.toDelete = ( item->getParent()->getNbChild() != 1 ) ;
		break;
		//case TreeKnownPartition :
	case XEM::MVC::TreeDataWeight :
	case XEM::MVC::TreeInitPartition :
	case XEM::MVC::TreeInitParameter :
	case XEM::MVC::TreeInitType :
	case XEM::MVC::TreeInitNbTry :
		autorization.toSet = true ;
		break ;
	case XEM::MVC::TreeNbStrategyTry :
		autorization.toSet = (item->getParent()->getChild(1)->getChild(0)->toString() != XEM::StrategyInitNameToString(XEM::USER) && item->getParent()->getChild(1)->getChild(0)->toString() != XEM::StrategyInitNameToString(XEM::USER_PARTITION));
		break;
	case XEM::MVC::TreeNbAlgo :
		autorization.toInsert = ( item->getNbChild() < 10 ) ;
		break;
	case XEM::MVC::TreeSubDimension :
		autorization.toSet = true;
		break ;
	case XEM::MVC::TreeAlgoName :
		autorization.toSet = true ;
		break;
//     case TreeOutput :{
//       int64_t nbCriterion = ((GUIMTreeModel *)index.model())->getClusteringMain(index.row()-1)->getInput()->getNbCriterionName();
//       autorization.toSet = NbCriterion>1 ;
//       break ;
//     }
	default :
		break;
	}
	return autorization;
}

//define if nodes in tree Qt can be colored (so the event will throw a possibility to modify an option)
bool TreeItemIsColored(Autorization a) {
	return (a.toDelete == true || a.toSet == true || a.toInsertRemove == true || a.toInsert == true);
}

QString getName(XEM::MVC::TreeItem* item) {
	switch( item->getKeyword() ) {
	case XEM::MVC::NoKeyword :
		return QObject::tr("NoKeyword") ;
	case XEM::MVC::DefaultKeyword :
		return QObject::tr("DefaultKeyword") ;
	case XEM::MVC::TreeProject :
		return QObject::tr("Project") ;
	case XEM::MVC::TreeInput :
		return QObject::tr("Input");
	case XEM::MVC::TreeOutput :
		return QObject::tr("Results");
	case XEM::MVC::TreeNbSample :
		return QObject::tr("Number of samples");
	case XEM::MVC::TreePbDimension :
		return QObject::tr("Variables");
	case XEM::MVC::TreeNbNbCluster :
		return QObject::tr("NbCluster" );
	case XEM::MVC::TreeNbCluster :
		return QObject::tr("NbCluster " );
	case XEM::MVC::TreeData :
		return QObject::tr("Data") ;
	case XEM::MVC::TreeDataSample :
		return QObject::tr("DataFile");
	case XEM::MVC::TreeDataSampleChild :
		return QObject::tr("DataSampleChild");
	case XEM::MVC::TreeDataWeight :
		return QObject::tr("Weight");
	case XEM::MVC::TreeDataWeightChild :
		return QObject::tr("WeightChild ");
	case XEM::MVC::TreeFactor :
		return QObject::tr("Factor");
	case XEM::MVC::TreeDataClassify :
		return QObject::tr("Data to classify ");
	case XEM::MVC::TreeModel :
		return QObject::tr("Model") ;
	case XEM::MVC::TreeModelChild :
		return QObject::tr("Model ") ;
	case XEM::MVC::TreeKnownPartition :
		return QObject::tr("KnownPartition") ;
	case XEM::MVC::TreeKnownPartitionSample :
		return QObject::tr("Sample ") ;
	case XEM::MVC::TreeStrategy :
		return QObject::tr("Strategy");
	case XEM::MVC::TreeNbStrategyTry :
		return QObject::tr("Number of strategy repeats");
	case XEM::MVC::TreeInitType :
		return QObject::tr("Initialization Type" );
	case XEM::MVC::TreeInitTypeName :
		return QObject::tr("Name of initialization type") ;
	case XEM::MVC::TreeInitTypeNameUser :
		return QObject::tr("InitTypeNameUser" );
	case XEM::MVC::TreeInitTypeNameUserPartition :
		return QObject::tr("InitTypeNameUserPartition") ;
	case XEM::MVC::TreeInitParameter :
		return QObject::tr("Initialization parameters") ;
	case XEM::MVC::TreeInitParameterChild :
		return QObject::tr("Initialization parameters childs") ;
	case XEM::MVC::TreeInitParameterSample :
		return QObject::tr("Sample") ;
	case XEM::MVC::TreeInitProportion :
		return  QObject::tr("Proportion");
	case XEM::MVC::TreeInitProportionChild :
		return QObject::tr("Proportion ");
	case XEM::MVC::TreeInitCenter:
		return QObject::tr("Center");
	case XEM::MVC::TreeInitCenterChild :
		return QObject::tr("Center ");
	case XEM::MVC::TreeInitDispersion :
		return QObject::tr("Dispersion");
	case XEM::MVC::TreeInitDispersionChild :
		return QObject::tr("Class ");
	case XEM::MVC::TreeInitDispersionData :
		return QObject::tr("Dispersion ");
	case XEM::MVC::TreeInitScatter:
		return QObject::tr("Scatter");
	case XEM::MVC::TreeInitScatterChild :
		return QObject::tr("Scatter ");
	case XEM::MVC::TreeInitPartition :
		return QObject::tr("Initialization partition ") ;
	case XEM::MVC::TreeInitParameterStrategy :
		return QObject::tr("Initialization Parameter ") ;
	case XEM::MVC::TreeInitNbTry :
		return QObject::tr("Initialization Repeats") ;
	case XEM::MVC::TreeInitStopRule :
		return QObject::tr("Init Stop Rule");
	case XEM::MVC::TreeInitNbIteration :
		return QObject::tr("Number of iteration in strategy") ;
	case XEM::MVC::TreeInitEpsilon :
		return QObject::tr("Epsilon in strategy") ;
	case XEM::MVC::TreeNbAlgo :
		return QObject::tr("Number of Algorithm") ;
	case XEM::MVC::TreeNbAlgoChild :
		return QObject::tr("Algorithm ") ;
	case XEM::MVC::TreeAlgoName :
		return QObject::tr("Name") ;
	case XEM::MVC::TreeStopRuleValue :
		return QObject::tr("Stop Rule Value") ;
	case XEM::MVC::TreeCriterion :
		return QObject::tr("Criterion") ;
	case XEM::MVC::TreeCriterionChild :
		return QObject::tr("Criterion ") ;
	case XEM::MVC::TreeSubDimension :
		return QObject::tr("SubDimension") ;
	case XEM::MVC::TreeNbIteration :
		return QObject::tr("Number of iteration in algorithm");
	case XEM::MVC::TreeEpsilon :
		return QObject::tr("Epsilon in algorithm");
	case XEM::MVC::TreeResult :
		return QObject::tr("Result ");
	case XEM::MVC::TreeOutputModel :
		return QObject::tr("Model");
	case XEM::MVC::TreeOutputCriterion :
		return QObject::tr("Criterion");
	case XEM::MVC::TreeOutputCriterionName :
		return QObject::tr("Name ");
	case XEM::MVC::TreeOutputParameter :
		return QObject::tr("Parameter");
	case XEM::MVC::TreeOutputParameterChild :
		return QObject::tr("ParameterChild");
	case XEM::MVC::TreeOutputLabel :
		return QObject::tr("Label - Proba");
	case XEM::MVC::TreeOutputNbCluster :
		return QObject::tr("NbCLuster");
	case XEM::MVC::TreeLabelSample :
		return QObject::tr("Sample ");
	case XEM::MVC::TreeOutputPostProba :
		return QObject::tr("PostProba");
	case XEM::MVC::TreePostProbaSample :
		return QObject::tr("PostProbaSample");
	case XEM::MVC::TreeLikelihood :
		return QObject::tr("Likelihood");
	case XEM::MVC::TreeCompletedLikelihood :
		return QObject::tr("Completed likelihood");
	case XEM::MVC::TreeCriterionValue :
		return QObject::tr("Value");
	case XEM::MVC::TreeOutputProportion :
		return QObject::tr("Proportion");
	case XEM::MVC::TreeOutputProportionChild :
		return QObject::tr("Proportion ");
	case XEM::MVC::TreeOutputCenter :
		return QObject::tr("Center");
	case XEM::MVC::TreeOutputCenterChild :
		return QObject::tr("Center ");
	case XEM::MVC::TreeOutputDispersion :
		return QObject::tr("Dispersion");
	case XEM::MVC::TreeOutputDispersionChild :
		return QObject::tr("Class ");
	case XEM::MVC::TreeOutputScatter :
		return QObject::tr("Scatter");
	case XEM::MVC::TreeOutputScatterChild :
		return QObject::tr("Class ");
	case XEM::MVC::TreeOutputDispersionData :
		return QObject::tr("Dispersion ") ;
	case XEM::MVC::TreeOutputTabA :
		return QObject::tr("Output TabA");
	case XEM::MVC::TreeOutputTabB :
		return QObject::tr("Output TabB");
	case XEM::MVC::TreeOutputTabD :
		return QObject::tr("Output TabD");
	case XEM::MVC::TreeSize :
		return QObject::tr("Size") ;
	case XEM::MVC::TreeNumeric :
		return QObject::tr("Numeric");
	case XEM::MVC::TreeGraphic :
		return QObject::tr("Graphics");
	case XEM::MVC::TreeQuantitativePoint :
		return QObject::tr("2D - Point");
	case XEM::MVC::TreeQuantitativeClass :
		return QObject::tr("2D - Class");
	case XEM::MVC::TreeQuantitativeHistogram :
		return QObject::tr("1D - Histogram");
	case XEM::MVC::TreeQualitativeDiagram :
		return QObject::tr("1D - Diagram");
	case XEM::MVC::TreeQualitativeBoxes :
		return QObject::tr("Parameter");
	case XEM::MVC::TreeNoGraphics :
		return QObject::tr("No Graphics");
	case XEM::MVC::TreeOutputError :
		return QObject::tr("Error");
	default :
		return QObject::tr("Error") ;
	}
}
