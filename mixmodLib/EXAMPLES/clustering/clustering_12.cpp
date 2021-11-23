/***************************************************************************
                             EXAMPLES/clustering/clustering_12.cpp  description
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
void clustering_12_example() {

    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Clustering example : "<<endl;
    cout<<"  - iris data (quantitative data)"<<endl;

    // if mximod_example is installed in the /usr/local/bin folder, data files are in /usr/local/share/mixmod/EXAMPLES folder
    //otherwise, change the following line
    string filename ("/usr/local/share/mixmod/EXAMPLES/data/iris.train");


    // 1. create XEM::ClusteringInput
    //--------------------------

    // nbCluster contains the numbers of clusters to be tested.
    // Here we assume that there are 2, 3 or 4 clusters.
    vector<int64_t> nbCluster;
    nbCluster.push_back (2);

    // XEM::ClusteringInput
    XEM::ClusteringInput* cInput = XEM::getClusteringInput (filename, nbCluster);

    // add a other model type
    cInput->removeModelType ( 0 );

    cInput->addModel ( XEM::Gaussian_p_L_I );
    cInput->addModel ( XEM::Gaussian_p_Lk_I );

    cInput->addModel ( XEM::Gaussian_pk_L_I );
    cInput->addModel ( XEM::Gaussian_pk_Lk_I );

    cInput->addModel ( XEM::Gaussian_p_L_B );
    cInput->addModel ( XEM::Gaussian_p_Lk_B );
    cInput->addModel ( XEM::Gaussian_p_L_Bk );
    cInput->addModel ( XEM::Gaussian_p_Lk_Bk );

    cInput->addModel ( XEM::Gaussian_pk_L_B );
    cInput->addModel ( XEM::Gaussian_pk_Lk_B );
    cInput->addModel ( XEM::Gaussian_pk_L_Bk );
    cInput->addModel ( XEM::Gaussian_pk_Lk_Bk );

    cInput->addModel ( XEM::Gaussian_p_L_C );
    cInput->addModel ( XEM::Gaussian_p_Lk_C );
    cInput->addModel ( XEM::Gaussian_p_L_D_Ak_D );
    cInput->addModel ( XEM::Gaussian_p_Lk_D_Ak_D );
    cInput->addModel ( XEM::Gaussian_p_L_Dk_A_Dk );
    cInput->addModel ( XEM::Gaussian_p_Lk_Dk_A_Dk );
    cInput->addModel ( XEM::Gaussian_p_L_Ck );
    cInput->addModel ( XEM::Gaussian_p_Lk_Ck );

    cInput->addModel ( XEM::Gaussian_pk_L_C );
    cInput->addModel ( XEM::Gaussian_pk_Lk_C );
    cInput->addModel ( XEM::Gaussian_pk_L_D_Ak_D );
    cInput->addModel ( XEM::Gaussian_pk_Lk_D_Ak_D );
    cInput->addModel ( XEM::Gaussian_pk_L_Dk_A_Dk );
    cInput->addModel ( XEM::Gaussian_pk_Lk_Dk_A_Dk );
    cInput->addModel ( XEM::Gaussian_pk_L_Ck );
    cInput->addModel ( XEM::Gaussian_pk_Lk_Ck );

    /*
		 * HD models work only for discriminant analysis
		 * ---------------------------------------------
		 * cInput->addModel ( XEM::Gaussian_HD_p_AkjBkQkDk );
    cInput->addModel ( XEM::Gaussian_HD_p_AkBkQkDk );
    cInput->addModel ( XEM::Gaussian_HD_p_AkjBkQkD );
    cInput->addModel ( XEM::Gaussian_HD_p_AjBkQkD );
    cInput->addModel ( XEM::Gaussian_HD_p_AkjBQkD );
    cInput->addModel ( XEM::Gaussian_HD_p_AjBQkD );
    cInput->addModel ( XEM::Gaussian_HD_p_AkBkQkD );
    cInput->addModel ( XEM::Gaussian_HD_p_AkBQkD );

    cInput->addModel ( XEM::Gaussian_HD_pk_AkjBkQkDk );
    cInput->addModel ( XEM::Gaussian_HD_pk_AkBkQkDk );
    cInput->addModel ( XEM::Gaussian_HD_pk_AkjBkQkD );
    cInput->addModel ( XEM::Gaussian_HD_pk_AjBkQkD );
    cInput->addModel ( XEM::Gaussian_HD_pk_AkjBQkD );
    cInput->addModel ( XEM::Gaussian_HD_pk_AjBQkD );
    cInput->addModel ( XEM::Gaussian_HD_pk_AkBkQkD );
    cInput->addModel ( XEM::Gaussian_HD_pk_AkBQkD );*/
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

        //TODO: Next 2 lines lead to SEGFAULT because the model is apparently destroyed
        //XEM::Model * tempmodel = paramDescription->getParameter()->getModel();
        //cout<<tempmodel->getEntropy();

        //cout<<cMOutput->getLikelihood();

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
        for ( int64_t iCriterion=0; iCriterion < cInput->getCriterionName().size(); iCriterion++ )
            cMOutput->getCriterionOutput ( cInput->getCriterionName ( iCriterion ) ).editTypeAndValue ( std::cout );
    } else {
        cout<<"All models got error\n";
        for ( int i = 0; i < cOutput->getClusteringModelOutput().size(); ++i ) {
            cout<<cOutput->getClusteringModelOutput ( i )->getStrategyRunError().what() <<endl;
        }
    }
    cout<<"-----------------------------------------------------------------------"<<endl;


    // release memory
    delete cInput;
}
