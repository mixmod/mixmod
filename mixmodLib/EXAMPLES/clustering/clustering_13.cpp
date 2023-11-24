/***************************************************************************
                             EXAMPLES/clustering/clustering_13.cpp  description
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
#include "mixmod/Kernel/IO/GaussianSample.h"
#include "mixmod/Utilities/ExampleDataUtil.h"

/**
 * @file heterogeneousclustering.cpp
 * @brief Example for heterogeneous clustering.
 * @author Parmeet Bhatia
 */

void clustering_13_example () {

    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Heterogeneous clustering: "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl<<endl;

    // if mximod_example is installed in the /usr/local/bin folder, data files are in /usr/local/share/mixmod/EXAMPLES folder
    //otherwise, change the following line
    string filename ("data/heterodata.csv");

    
    // 1. create XEM::ClusteringInput
    //--------------------------

    // nbCluster contains the numbers of clusters to be tested.
    // Here we assume that there are 2, 3 or 4 clusters.
    vector<int64_t> nbCluster;
    nbCluster.push_back (2);
    
    // XEM::ClusteringInput
    XEM::ClusteringInput* cInput = XEM::getClusteringInput (filename, nbCluster);

    //remove default and add another model
    cInput->removeModelType ( 0 );
    cInput->addModel ( XEM::Heterogeneous_pk_E_L_B );
    cInput->addModel ( XEM::Heterogeneous_pk_E_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_pk_E_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_E_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ek_L_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ek_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ek_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ek_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ej_L_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ej_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ej_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ej_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekj_L_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekj_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekj_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekj_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekjh_L_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekjh_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekjh_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_pk_Ekjh_Lk_Bk );
    /* : cInput->addModel(Heterogeneous model name:proportions fix */
    cInput->addModel ( XEM::Heterogeneous_p_E_L_B );
    cInput->addModel ( XEM::Heterogeneous_p_E_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_p_E_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_E_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ek_L_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ek_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ek_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ek_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ej_L_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ej_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ej_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ej_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ekj_L_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ekj_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ekj_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ekj_Lk_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ekjh_L_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ekjh_Lk_B );
    cInput->addModel ( XEM::Heterogeneous_p_Ekjh_L_Bk );
    cInput->addModel ( XEM::Heterogeneous_p_Ekjh_Lk_Bk );
    // Finalize
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
        cout<<"- Model : "<<XEM::ModelNameToString ( paramDescription->getModelType()->_nameModel ) <<endl;
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
