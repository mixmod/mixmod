/***************************************************************************
                             EXAMPLES/clustering/clustering_11.cpp  description
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
#include <stdint.h>
#include "mixmod/Utilities/ExampleDataUtil.h"

//--------------------------
//--------------------------
// Clustering example
// Qualitative Data
//--------------------------
//--------------------------
void clustering_11_example() {

    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Clustering example (number 2) : "<<endl;
    cout<<"  - birds data (qualitative data)"<<endl;
    cout<<"  - default options"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl<<endl;

    // if mximod_example is installed in the /usr/local/bin folder, data files are in /usr/local/share/mixmod/EXAMPLES folder
    //otherwise, change the following line
    string filename ("data/birds.dat");

    
    // 1. create XEM::ClusteringInput
    //--------------------------

    // nbCluster contains the numbers of clusters to be tested.
    // Here we assume that there are 2, 3 or 4 clusters.
    vector<int64_t> nbCluster;
    nbCluster.push_back (3);

    // XEM::ClusteringInput
    XEM::ClusteringInput* cInput = XEM::getClusteringInput (filename, nbCluster);

    // Finalize
    cInput->removeModelType ( 0 );
    /* : proportion fixed  */
    cInput->addModel ( XEM::Binary_p_E ) ;
    cInput->addModel ( XEM::Binary_p_Ek );
    cInput->addModel ( XEM::Binary_p_Ej );
    cInput->addModel ( XEM::Binary_p_Ekj );
    cInput->addModel ( XEM::Binary_p_Ekjh );
    /* : proportion free  */
    cInput->addModel ( XEM::Binary_pk_E );
    cInput->addModel ( XEM::Binary_pk_Ek );
    cInput->addModel ( XEM::Binary_pk_Ej );
    cInput->addModel ( XEM::Binary_pk_Ekj );
    cInput->addModel ( XEM::Binary_pk_Ekjh );
    cInput->finalize();

    // edit cInput
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<" Input : "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl<<endl;
    cInput->edit ( cout );
    cout<<endl;


    // 2. XEM::ClusteringMain
    //---------------------

    // 2.1. Create XEM::ClusteringMain
    XEM::ClusteringMain cMain ( cInput );

    // 2.2. run XEM::ClusteringMain
    cMain.run();

    //2.3. Create a new XEM::ClusteringOutput object
    // all Outputs are in XEM::ClusteringOutput
    XEM::ClusteringOutput * cOutput = cMain.getOutput();


    // 3. post treatment example
    //------------------------------
    // sort (using BIC - the default criterion)
    cOutput->sort ( XEM::BIC );

    if ( cOutput->atLeastOneEstimationNoError() ) {
        // get the best XEM::ClusteringModelOutput
        XEM::ClusteringModelOutput * cMOutput = cOutput->getClusteringModelOutput().front();
        XEM::ParameterDescription * paramDescription = cMOutput->getParameterDescription();

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Best model is "<<endl;
        cout<<" - nbCluster : "<<paramDescription->getNbCluster() <<endl;
        cout<<"Model name: "<<XEM::ModelNameToString ( paramDescription->getModelType()->getModelName() ) <<endl;
        cout<<"-----------------------------------------------------------------------"<<endl<<endl;

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Parameters display"<<endl;

        XEM::Parameter * param = paramDescription->getParameter();
        // print out parameters
        param->edit();
        // print out criterion values
        for ( std::size_t iCriterion=0; iCriterion < cInput->getCriterionName().size(); iCriterion++ )
            cMOutput->getCriterionOutput ( cInput->getCriterionName ( iCriterion ) ).editTypeAndValue ( std::cout );
    }
    cout<<"-----------------------------------------------------------------------"<<endl;


    // release memory
    delete cInput;
}
