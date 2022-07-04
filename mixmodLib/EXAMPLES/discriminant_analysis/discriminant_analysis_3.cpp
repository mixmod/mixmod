/***************************************************************************
                             EXAMPLES/discriminant_analysis/discriminant_analysis_3.cpp  description
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
void discriminant_analysis_3_example() {

    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"Discrimiant analysis example : "<<endl;
    cout<<"  - iris data (quantitative data)"<<endl;
    cout<<"  - default options"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl<<endl;

     // if mximod_example is installed in the /usr/local/bin folder, data files are in /usr/local/share/mixmod/EXAMPLES folder
    //otherwise, change the following line
    string basePath ("data/");
    string learnFile("iris.train");
    string predictFile("iris.test");
    int64_t nbCluster=3;

    //--------------------------
    //--------------------------
    // A. Mixmod learn step
    //--------------------------
    //--------------------------

    // 1. create XEM::LearnInput
    //--------------------------
    // XEM::LearnInput
    XEM::LearnInput * lInput = XEM::getLearnInput(basePath + learnFile);

    // custom model types
    lInput->removeModelType ( 0 );
    /*----------------*/
    /* 16 HD models*/
    /*----------------*/
 		XEM::ModelType mType1(XEM::Gaussian_HD_p_AkjBQkD);
		mType1.setSubDimensionEqual(2);
    lInput->addModelType(&mType1);

		XEM::ModelType mType2(XEM::Gaussian_HD_pk_AkjBQkD);
		mType2.setSubDimensionEqual(1);
    lInput->addModelType(&mType2);

		XEM::ModelType mType3(XEM::Gaussian_HD_p_AjBQkD);
		mType3.setSubDimensionEqual(2);
    lInput->addModelType(&mType3);

		XEM::ModelType mType4(XEM::Gaussian_HD_p_AkBQkD);
		mType4.setSubDimensionEqual(3);
    lInput->addModelType(&mType4);

		XEM::ModelType mType5(XEM::Gaussian_HD_pk_AjBQkD);
		mType5.setSubDimensionEqual(1);
    lInput->addModelType(&mType5);

		XEM::ModelType mType6(XEM::Gaussian_HD_pk_AkBQkD);
		mType6.setSubDimensionEqual(1);
    lInput->addModelType(&mType6);


		XEM::ModelType mType7(XEM::Gaussian_HD_p_AkjBkQkDk, nbCluster);
		mType7.setTabSubDimensionFree(1,0);
		mType7.setTabSubDimensionFree(1,1);
		mType7.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType7);

		XEM::ModelType mType8(XEM::Gaussian_HD_p_AkBkQkDk, nbCluster);
		mType8.setTabSubDimensionFree(1,0);
		mType8.setTabSubDimensionFree(1,1);
		mType8.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType8);

		XEM::ModelType mType9(XEM::Gaussian_HD_p_AkjBkQkD, nbCluster);
		mType9.setTabSubDimensionFree(1,0);
		mType9.setTabSubDimensionFree(1,1);
		mType9.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType9);

		XEM::ModelType mType10(XEM::Gaussian_HD_p_AjBkQkD, nbCluster);
		mType10.setTabSubDimensionFree(1,0);
		mType10.setTabSubDimensionFree(1,1);
		mType10.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType10);

		XEM::ModelType mType11(XEM::Gaussian_HD_p_AkBkQkD, nbCluster);
		mType11.setTabSubDimensionFree(1,0);
		mType11.setTabSubDimensionFree(1,1);
		mType11.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType11);

		XEM::ModelType mType12(XEM::Gaussian_HD_pk_AkjBkQkDk, nbCluster);
		mType12.setTabSubDimensionFree(1,0);
		mType12.setTabSubDimensionFree(1,1);
		mType12.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType12);

		XEM::ModelType mType13(XEM::Gaussian_HD_pk_AkBkQkDk, nbCluster);
		mType13.setTabSubDimensionFree(1,0);
		mType13.setTabSubDimensionFree(1,1);
		mType13.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType13);

		XEM::ModelType mType14(XEM::Gaussian_HD_pk_AkjBkQkD, nbCluster);
		mType14.setTabSubDimensionFree(1,0);
		mType14.setTabSubDimensionFree(1,1);
		mType14.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType14);

		XEM::ModelType mType15(XEM::Gaussian_HD_pk_AjBkQkD, nbCluster);
		mType15.setTabSubDimensionFree(1,0);
		mType15.setTabSubDimensionFree(1,1);
		mType15.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType15);

		XEM::ModelType mType16(XEM::Gaussian_HD_pk_AkBkQkD, nbCluster);
		mType16.setTabSubDimensionFree(1,0);
		mType16.setTabSubDimensionFree(1,1);
		mType16.setTabSubDimensionFree(2,2);
    lInput->addModelType(&mType16);

    // Finalize
    lInput->finalize();

    // edit lInput
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<" Input : "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl<<endl;
    lInput->edit ( cout );
    cout<<endl;


    // 2. XEM::LearnMain
    //---------------------

    // 2.1. Create XEM::ClusteringMain
    XEM::LearnMain lMain ( lInput );

    // 2.2 run XEM::LearnMain
    lMain.run();

    //2.3. Create a new XEM::LeranrOutput object
    XEM::LearnOutput * lOutput = lMain.getLearnOutput();


    // 3. post treatment example
    //------------------------------
    // sort (using CV - the default criterion)
    lOutput->sort ( XEM::CV );

    XEM::LearnModelOutput * lMOutput = NULL;

    // TODO: next 3 lines should not be needed (always use vector ?)
    int64_t* vLabel_p = lInput->getKnownLabelDescription()->getLabel()->getTabLabel();
    vector<int64_t> vLabel;
    for (int j=0; j<lInput->getNbSample(); j++) vLabel.push_back(vLabel_p[j]);

/*
    //Display Input label :
    cout<<"Known labels"<<endl;
    cout<<"-------------"<<endl;
    for (int j=0; j<lInput->getNbSample(); j++)
      cout<<vLabel_p[j]<<endl;
*/
    if ( lOutput->atLeastOneEstimationNoError() ) {
        // get the best XEM::ClusteringModelOutput
        lMOutput = lOutput->getLearnModelOutput().front();
        XEM::ParameterDescription * paramDescription = lMOutput->getParameterDescription();


        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"    LEARN STEP  "<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<endl;

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<" Output : "<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Best model is (for CV criterion) "<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Best model is "<<endl;
        cout<<" - model : "<<* ( paramDescription->getModelType() ) <<endl;
        cout<<"-----------------------------------------------------------------------"<<endl<<endl;

        cout<<"-----------------------------------------------------------------------"<<endl;
        cout<<"Parameters display"<<endl;

        XEM::Parameter * param = paramDescription->getParameter();
        // print out parameters
        param->edit();

        // print out CV Label
        //std::cout << "CV Labels:" << std::endl;
        //lMOutput->getCVLabel()->getLabel()->edit(std::cout);

        // print out proba
        //std::cout << "Probas:" << std::endl;
        //lMOutput->getProbaDescription()->getProba()->edit ( std::cout );

        std::cout << "CV Error Rate:" << ( 1-lMOutput->getCVLabel()->getLabel()->getErrorRate ( vLabel ) ) *100 << "%" << std::endl;

        int64_t ** classif = lMOutput->getCVLabel()->getLabel()->getClassificationTab ( vLabel, lMOutput->getNbCluster());
        /*cout<<"CV labels "<<endl;
        cout<<"----------"<<endl;
        lMOutput->getCVLabel()->getLabel()->edit(cout);*/
        std::cout << "CV Classification Tab:" << std::endl;
        for ( int i=0; i<lMOutput->getNbCluster(); i++ ) {
            std::cout << " | " ;
            for ( int j=0; j<lMOutput->getNbCluster()-1; j++ ) std::cout << classif[i][j] << " ";
            std::cout << classif[i][lMOutput->getNbCluster()-1] << "|" << std::endl;
        }

        // release memory
        for ( int i=0; i<lMOutput->getNbCluster(); i++ ) delete [] classif[i];
        delete [] classif;
    }
    cout<<"-----------------------------------------------------------------------"<<endl;


    //--------------------------
    //--------------------------
    // B. Mixmod predict step
    //--------------------------
    //--------------------------

    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"    PREDICT STEP  "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<endl;

    // XEM::PredictInput
    XEM::PredictInput * pInput = XEM::getPredictInput(basePath + predictFile, lMOutput);
    pInput->finalize();

    // XEM::PredictMain
    XEM::PredictMain pMain ( pInput );
    pMain.run();

    // XEM::PredictOutput
    XEM::PredictOutput * pOutput = pMain.getPredictOutput();
    // get prediction model
    XEM::PredictModelOutput * pMOutput = pOutput->getPredictModelOutput().front();

    // print out labels
    std::cout << "Predict Labels:" << std::endl;
    pMOutput->getLabelDescription()->getLabel()->edit ( std::cout );
    // print out proba
    std::cout << "Predict Probas:" << std::endl;
    pMOutput->getProbaDescription()->getProba()->edit ( std::cout );


    // release memory
    delete lInput;
    delete pInput;
}
