/***************************************************************************
                             EXAMPLES/clustering/clustering_1.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2016
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

#include <mixmod.h>
#include "mixmod/Utilities/ExampleDataUtil.h"

//--------------------------
//--------------------------
// Clustering example
// Quantitative Data
//--------------------------
//--------------------------
void clustering_1_example() {

	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Clustering example : " << endl;
	cout << "  - iris data (quantitative data)" << endl;
	cout << "  - default options" << endl;
	cout << "-----------------------------------------------------------------------" << endl << endl;

	// if mximod_example is installed in the /usr/local/bin folder, data files are in /usr/local/share/mixmod/EXAMPLES folder
        //otherwise, change the following line
	string filename ("data/iris.train");
        fstream file;
        cout<<filename<<endl;
	file.open (filename.c_str());
	if (!file.is_open()) {
		cout<<"erreur : "<<filename<<endl;
	}


	// 1. create XEM::ClusteringInput
	//--------------------------

	// nbCluster contains the numbers of clusters to be tested.
	// Here we assume that there are 2, 3 or 4 clusters.
	vector<int64_t> nbCluster;
	nbCluster.push_back (2);
	nbCluster.push_back (3);
	nbCluster.push_back (4);

	// XEM::ClusteringInput
	XEM::ClusteringInput* cInput = XEM::getClusteringInput (filename, nbCluster);

    // Finalize input: run a series of sanity checks on it
    cInput->finalize();

	// edit cInput
	cout << "-----------------------------------------------------------------------" << endl;
	cout << " Input : " << endl;
	cout << "-----------------------------------------------------------------------" << endl << endl;
	cInput->edit (cout);
	cout << endl;


	// 2. XEM::ClusteringMain
	//---------------------

	// 2.1. Create XEM::ClusteringMain
	XEM::ClusteringMain cMain (cInput);

	// 2.2. run XEM::ClusteringMain
	// TODO [bauder]: should be a static method :
	//                XEM::ClusteringOutput * cOutput = XEM::ClusteringMain::run(cInput);
	cMain.run();

	//2.3. Create a new XEM::ClusteringOutput object
	// all Outputs are in XEM::ClusteringOutput
	XEM::ClusteringOutput* cOutput = cMain.getOutput();


	// 3. post treatment example
	//------------------------------
	// sort (using BIC - the default criterion)
	cOutput->sort (XEM::BIC);

	if (cOutput->atLeastOneEstimationNoError()) {
		// get the best XEM::ClusteringModelOutput
		XEM::ClusteringModelOutput* cMOutput = cOutput->getClusteringModelOutput().front();
		XEM::ParameterDescription* paramDescription = cMOutput->getParameterDescription();

		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Best model is " << endl;
		cout << " - nbCluster : " << paramDescription->getNbCluster() << endl;
		cout << "-----------------------------------------------------------------------" << endl << endl;

		cout << "-----------------------------------------------------------------------" << endl;
		cout << "Parameters display" << endl;

		XEM::Parameter* param = paramDescription->getParameter();
		// print out parameters
		param->edit();
		// print out criterion values
		for (int64_t iCriterion = 0; iCriterion < cInput->getCriterionName().size(); iCriterion++)
			cMOutput->getCriterionOutput (cInput->getCriterionName (iCriterion)).editTypeAndValue (std::cout);
	}
	cout << "-----------------------------------------------------------------------" << endl;

	// release memory
	delete cInput;
	//delete cOutput; //WRONG: cMain garbage collected ==> _output (==cOutput) is freed already
}


// Simple test: [TODO: move]

//#include <mixmod.h>
//#include "XEM::ExampleDataUtil.h"
//#include <vector>
//
//void clustering_1_example() {
//    // Create clustering input from iris dataset.
//    string file("../EXAMPLES/data/iris.train");
//    int64_t nbClust_arr[] = {2, 3, 4};
//    vector<int64_t> nbClust(nbClust_arr, nbClust_arr+3);
//    XEM::ClusteringInput* cInput=getClusteringInput(file,nbClust);
//
//    // Remove defaults, and specify model + algorithms
//    cInput->removeModelType(0);
//    cInput->getStrategy()->removeAlgo(0);
//    cInput->addModel(Gaussian_pk_Lk_C);
//    cInput->getStrategy()->insertAlgo(EM, 0);
//    cInput->getStrategy()->insertAlgo(CEM, 1);
//
//    // Set strategy and algorithms parameters
//    cInput->getStrategy()->setAlgoIteration(0, 10);
//    cInput->getStrategy()->setAlgoStopRule(NBITERATION, 0);
//    cInput->getStrategy()->setAlgoIteration(1, 100);
//    cInput->getStrategy()->setAlgoStopRule(NBITERATION, 1);
//    cInput->getStrategy()->setNbTry(10);
//    cInput->getStrategy()->setStrategyInitName(RANDOM);
//    cInput->setCriterion(BIC, 0);
//
//    // Check that everything is OK...
//    cInput->finalize();
//
//    // Run models (one for each number of clusters), and get output
//    XEM::ClusteringMain cMain (cInput);
//    cMain.run();
//    XEM::ClusteringOutput* cOutput = cMain.getClusteringOutput();
//
//    if (cOutput->atLeastOneEstimationNoError()) {
//		vector<XEM::ClusteringModelOutput*> cMOutput = cOutput->getClusteringModelOutput();
//		for (int i=0; i<3; i++) {
//			cout << "MODEL " << i << " " << cMOutput[i]->getNbCluster() << " " << cMOutput[i]->getLikelihood() << " " << cMOutput[i]->getCriterionOutput(0).getValue() << endl;
//		}
//    }
//}

//OUTPUT:
//mixmodLib/BIN $ ./example_exe c1
//MODEL 0 2 -278.057 656.327
//MODEL 1 3 -237.855 605.986
//MODEL 2 4 -217.255 594.85
