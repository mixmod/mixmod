## ################################################################################
##     copyright            : (C) MIXMOD Team - 2001-2014
##     email                : contact@mixmod.org
## ################################################################################

## ################################################################################
##     This file is part of MIXMOD

##     MIXMOD is free software: you can redistribute it and/or modify
##     it under the terms of the GNU General Public License as published by
##     the Free Software Foundation, either version 3 of the License, or
##     (at your option) any later version.

##     MIXMOD is distributed in the hope that it will be useful,
##     but WITHOUT ANY WARRANTY; without even the implied warranty of
##     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##     GNU General Public License for more details.

##     You should have received a copy of the GNU General Public License
##     along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

##     All information available on : http://www.mixmod.org
## ################################################################################

from libc.stdint cimport int64_t
from libcpp.vector cimport vector
from libcpp cimport bool
from libcpp.string cimport string

## cdef extern from *:
##     void delete_array 'delete[]'


cdef extern from "":
    void array_delete_int64_p 'delete[] '(int64_t* iii)
    void array_delete_int64_pp 'delete[] '(int64_t** iii)
    Parameter** new_array_parameter_1 'new XEM::Parameter*[1]'

cdef extern from "cppmixmod.h":
    double *new_double_array(int ii)
    double **new_double_p_array(int ii)
    double ***new_double_pp_array(int ii)
    int64_t *new_int64_t_array(int ii)



cdef extern from "Util.h" namespace "XEM":
    cdef Exception & NOERROR
    cdef enum DataType:
        QualitativeData = 0
        QuantitativeData
        HeterogeneousData
    cdef enum AlgoName:
        UNKNOWN_ALGO_NAME = -1 # Unknown algorithm
        MAP = 0                # Maximum a posteriori
        EM = 1                 # Expectation maximization
        CEM = 2                # Classification EM
        SEM = 3                # Stochastic EM
        M = 4                  # Maximization
    cdef enum StrategyInitName:
        RANDOM = 0         # Random centers
        USER = 1           # Initial parameters specified by user
        USER_PARTITION = 2 # Partition specified by user
        SMALL_EM = 3       # EM strategy for initial parameters
        CEM_INIT = 4       # initialization with CEM
        SEM_MAX = 5        # initialization with SEM max
    cdef enum CriterionName:
        UNKNOWN_CRITERION_NAME = -1 # Unknown criterion
        BIC = 0                     # Bayesian information criterion
        CV  = 1                     # Cross validation criterion
        ICL = 2                     # Integrated completed likelihood
        NEC = 3                     # Entropy criterion
        DCV = 4                      # Double Cross validation criterion
    cdef enum ModelName:
        #####################
        #                   #
        #  Gaussian Models  #
        #                   #
        #####################

        # Unknown model type
        UNKNOWN_MODEL_NAME = -1

        # 28 Gaussian 'Classical' models

        # Spherical Gaussian model: proportion fixed
        Gaussian_p_L_I = 0
        Gaussian_p_Lk_I

        # Spherical Gaussian model: proportion free
        Gaussian_pk_L_I
        Gaussian_pk_Lk_I

        # Diagonal Gaussian model: proportion fixed
        Gaussian_p_L_B
        Gaussian_p_Lk_B
        Gaussian_p_L_Bk
        Gaussian_p_Lk_Bk

        # Diagonal Gaussian model: proportion free
        Gaussian_pk_L_B
        Gaussian_pk_Lk_B
        Gaussian_pk_L_Bk
        Gaussian_pk_Lk_Bk

        # Ellipsoidal Gaussian model: proportion fixed
        Gaussian_p_L_C
        Gaussian_p_Lk_C
        Gaussian_p_L_D_Ak_D
        Gaussian_p_Lk_D_Ak_D
        Gaussian_p_L_Dk_A_Dk
        Gaussian_p_Lk_Dk_A_Dk
        Gaussian_p_L_Ck
        Gaussian_p_Lk_Ck

        # Ellipsoidal Gaussian model: proportion free
        Gaussian_pk_L_C
        Gaussian_pk_Lk_C
        Gaussian_pk_L_D_Ak_D
        Gaussian_pk_Lk_D_Ak_D
        Gaussian_pk_L_Dk_A_Dk
        Gaussian_pk_Lk_Dk_A_Dk
        Gaussian_pk_L_Ck
        Gaussian_pk_Lk_Ck

        #----------------#
        # 16 HD models   #
        #----------------#
        Gaussian_HD_p_AkjBkQkDk
        Gaussian_HD_p_AkBkQkDk
        Gaussian_HD_p_AkjBkQkD
        Gaussian_HD_p_AjBkQkD
        Gaussian_HD_p_AkjBQkD
        Gaussian_HD_p_AjBQkD
        Gaussian_HD_p_AkBkQkD
        Gaussian_HD_p_AkBQkD

        Gaussian_HD_pk_AkjBkQkDk
        Gaussian_HD_pk_AkBkQkDk
        Gaussian_HD_pk_AkjBkQkD
        Gaussian_HD_pk_AjBkQkD
        Gaussian_HD_pk_AkjBQkD
        Gaussian_HD_pk_AjBQkD
        Gaussian_HD_pk_AkBkQkD
        Gaussian_HD_pk_AkBQkD

        ######################
        #                    #
        #  10 Binary Models  #
        #                    #
        ######################

        # proportion fixed
        Binary_p_E
        Binary_p_Ek
        Binary_p_Ej
        Binary_p_Ekj
        Binary_p_Ekjh
        # proportion free
        Binary_pk_E
        Binary_pk_Ek
        Binary_pk_Ej
        Binary_pk_Ekj
        Binary_pk_Ekjh

        # Heterogeneous model name:proportions free
        Heterogeneous_pk_E_L_B
        Heterogeneous_pk_E_Lk_B
        Heterogeneous_pk_E_L_Bk
        Heterogeneous_pk_E_Lk_Bk
        Heterogeneous_pk_Ek_L_B
        Heterogeneous_pk_Ek_Lk_B
        Heterogeneous_pk_Ek_L_Bk
        Heterogeneous_pk_Ek_Lk_Bk
        Heterogeneous_pk_Ej_L_B
        Heterogeneous_pk_Ej_Lk_B
        Heterogeneous_pk_Ej_L_Bk
        Heterogeneous_pk_Ej_Lk_Bk
        Heterogeneous_pk_Ekj_L_B
        Heterogeneous_pk_Ekj_Lk_B
        Heterogeneous_pk_Ekj_L_Bk
        Heterogeneous_pk_Ekj_Lk_Bk
        Heterogeneous_pk_Ekjh_L_B
        Heterogeneous_pk_Ekjh_Lk_B
        Heterogeneous_pk_Ekjh_L_Bk
        Heterogeneous_pk_Ekjh_Lk_Bk
        # Heterogeneous model name:proportions fix
        Heterogeneous_p_E_L_B
        Heterogeneous_p_E_Lk_B
        Heterogeneous_p_E_L_Bk
        Heterogeneous_p_E_Lk_Bk
        Heterogeneous_p_Ek_L_B
        Heterogeneous_p_Ek_Lk_B
        Heterogeneous_p_Ek_L_Bk
        Heterogeneous_p_Ek_Lk_Bk
        Heterogeneous_p_Ej_L_B
        Heterogeneous_p_Ej_Lk_B
        Heterogeneous_p_Ej_L_Bk
        Heterogeneous_p_Ej_Lk_Bk
        Heterogeneous_p_Ekj_L_B
        Heterogeneous_p_Ekj_Lk_B
        Heterogeneous_p_Ekj_L_Bk
        Heterogeneous_p_Ekj_Lk_Bk
        Heterogeneous_p_Ekjh_L_B
        Heterogeneous_p_Ekjh_Lk_B
        Heterogeneous_p_Ekjh_L_Bk
        Heterogeneous_p_Ekjh_Lk_Bk

        nbModelName = 54
    string ModelNameToString(const ModelName & modelName)
    ModelName StringToModelName(const string & strModelName)



cdef extern from "ModelType.h" namespace "XEM":
    cdef cppclass ModelType:
        const ModelName & getModelName() const

cdef extern from "ClusteringStrategy.h" namespace "XEM":
    cdef cppclass ClusteringStrategy:
        ClusteringStrategy()
        void removeAlgo(unsigned int  position)
        void addAlgo(AlgoName algoName)
        void setAlgoIteration(  int64_t position, int64_t nbIterationValue)
        void setAlgoEpsilon( int64_t position, double epsilonValue)
        void setNbTry(int64_t nbTry)
        void setNbTryInInit(int64_t nbTry)
        void setStrategyInitName(StrategyInitName initName)
        void setTabInitParameter(Parameter** tabInitParameter,
                                 int64_t nbInitParameter)
        void setEpsilonInInit(double epsilon)
        void setInitPartition(Partition * part, int64_t position)

cdef extern from "Input.h" namespace "XEM":
    cdef cppclass Input:
        Input()
        void removeCriterion(unsigned int index)
        void finalize()
        void setWeight(double* weight)
        CriterionName getCriterionName(unsigned int index) const
        void setKnownLabelDescription(LabelDescription & labeldescription)
        void setModel(vector[ModelName] & modelName)
        vector[ModelType*] getModelType() const

cdef extern from "ClusteringInput.h" namespace "XEM":
    #ctypedef ClusteringInput ClusteringInput_c
    cdef cppclass ClusteringInput:
        ClusteringInput()
        ClusteringInput(const vector[int64_t] & iNbCluster, const DataDescription & iDataDescription)
        ClusteringStrategy *getStrategy() const
        void addCriterion(const CriterionName criterionName)
        # inherited:
        void finalize()

cdef extern from "Exception.h" namespace "XEM":
    cdef cppclass Exception:
        #virtual const char* what() const throw ();
        const char* what() except +
        #virtual bool operator==(const Exception&) const throw ();
        bool operator==(const Exception&) except +


cdef extern from "Matrix.h" namespace "XEM":
    cdef cppclass Matrix:
        double** storeToArray() const

cdef extern from "Parameter.h" namespace "XEM":
    cdef cppclass Parameter:
        double * getTabProportion() const
        int64_t getPbDimension() const
        int64_t getFreeParameter() const

cdef extern from "GaussianParameter.h" namespace "XEM":
    cdef cppclass GaussianParameter:
        double ** getTabMean() const
        int64_t getFreeParameter() const

cdef extern from "GaussianEDDAParameter.h" namespace "XEM":
    cdef cppclass GaussianEDDAParameter:
        Matrix ** getTabSigma() const
        int64_t getFreeParameter() const

cdef extern from "GaussianGeneralParameter.h" namespace "XEM":
    cdef cppclass GaussianGeneralParameter:
        GaussianGeneralParameter(
			int64_t iNbCluster,
			int64_t iPbDimension,
			ModelType * iModelType,
			double * proportions,
			double ** means,
			double *** variances)
        int64_t getFreeParameter() const

cdef extern from "BinaryParameter.h" namespace "XEM":
    cdef cppclass BinaryParameter:
        int64_t ** getTabCenter() const
        int64_t * getTabNbModality() const
        int64_t getTotalNbModality() const
        double *** scatterToArray() const
        int64_t getFreeParameter() const

cdef extern from "BinaryEkjhParameter.h" namespace "XEM":
    cdef cppclass BinaryEkjhParameter:
        BinaryEkjhParameter(
			int64_t iNbCluster,
			int64_t iPbDimension,
			ModelType * iModelType,
			int64_t * tabNbModality,
			double * proportions,
			double ** centers,
			double *** scatters)
        int64_t getFreeParameter() const

cdef extern from "CompositeParameter.h" namespace "XEM":
    cdef cppclass CompositeParameter:
        BinaryParameter* getBinaryParameter()
        GaussianParameter* getGaussianParameter()
        int64_t getFreeParameter() const

cdef extern from "ParameterDescription.h" namespace "XEM":
    cdef cppclass ParameterDescription:
    # constructor for binary data
        ParameterDescription(
            int64_t nbCluster,
            int64_t nbVariable,
            ModelName& modelName,
            double * proportions,
            double ** centers,
            double *** scatters,
            vector[int64_t] nbFactor)
        # constructor for Gaussian data
        ParameterDescription(
            int64_t nbCluster,
            int64_t nbVariable,
            ModelName& modelName,
            double * proportions,
            double ** means,
            double *** variances)
        # constructor for Heterogeneous
        ParameterDescription(
            int64_t nbCluster,
            int64_t nbBinaryVariable,
            int64_t nbGaussianVariable,
            ModelName& modelName,
            double * proportions,
            double ** centers,
            double *** scatters,
            double ** means,
            double *** variances,
            vector[int64_t] nbFactor)
        Parameter * getParameter()

cdef extern from "Label.h" namespace "XEM":
    cdef cppclass Label:
        Label(int64_t nbSample)
        vector[int64_t] & getLabel() const
        void setLabel(vector[int64_t] label, int64_t nbSample);
        int64_t** getClassificationTab(vector[int64_t] & label, int64_t nbCluster) const
        const double getErrorRate(vector[int64_t] & label) const

cdef extern from "LabelDescription.h" namespace "XEM":
    cdef cppclass LabelDescription:
        const Label * getLabel() const
        LabelDescription(int64_t nbSample, vector[int64_t] vLabel)

cdef extern from "Partition.h" namespace "XEM":
    cdef cppclass Partition:
        Partition(const Label * label, int64_t nbCluster)

cdef extern from "Proba.h" namespace "XEM":
    cdef cppclass Proba:
        vector[vector[double]] getProba() const

cdef extern from "ProbaDescription.h" namespace "XEM":
    cdef cppclass ProbaDescription:
        const Proba * getProba()

cdef extern from "CriterionOutput.h" namespace "XEM":
    cdef cppclass CriterionOutput:
        double getValue() const
        Exception & getError() const

cdef extern from "ModelOutput.h" namespace "XEM":
    cdef cppclass ModelOutput:
        ModelType getModelType() const
        int64_t getNbCluster() const
        Exception & getStrategyRunError() const
        LabelDescription * getLabelDescription() const
        ProbaDescription * getProbaDescription() const
        double getLikelihood() const
        ParameterDescription * getParameterDescription() const
        CriterionOutput & getCriterionOutput(CriterionName criterionName) const

cdef extern from "ClusteringModelOutput.h" namespace "XEM":
    cdef cppclass ClusteringModelOutput


cdef extern from "ClusteringOutput.h" namespace "XEM":
    cdef cppclass ClusteringOutput:
        void sort(CriterionName criterionName)
        bool atLeastOneEstimationNoError() const
        int64_t getNbClusteringModelOutput() const
        ClusteringModelOutput * getClusteringModelOutput(const int64_t index) const
        vector[ClusteringModelOutput*]&  getClusteringModelOutput() const

cdef extern from "Data.h" namespace "XEM":
    cdef cppclass Data

cdef extern from "GaussianData.h" namespace "XEM":
    cdef cppclass GaussianData:
        GaussianData(int64_t nbSample, int64_t pbDimension, double ** matrix)

cdef extern from "BinaryData.h" namespace "XEM":
    cdef cppclass BinaryData:
        BinaryData(int64_t nbSample, int64_t pbDimension, vector[int64_t] nbModality, int64_t ** matrix)

cdef extern from "CompositeData.h" namespace "XEM":
    cdef cppclass CompositeData:
        CompositeData(Data*, Data*)

cdef extern from "DataDescription.h" namespace "XEM":
    cdef cppclass DataDescription:
        DataDescription(GaussianData * gData)
        DataDescription(BinaryData * bData)
        DataDescription(CompositeData * cData)

cdef extern from "ClusteringMain.h" namespace "XEM":
    cdef cppclass ClusteringMain:
        ClusteringMain()
        ClusteringMain(ClusteringInput *cInput, ClusteringOutput *output=NULL)
        void run(int seed) except +
        ClusteringOutput * getOutput() const

cdef extern from "ClusteringOutput.h" namespace "XEM":
    cdef cppclass ClusteringOutput:
        void sort(CriterionName criterionName)

cdef extern from "LearnInput.h" namespace "XEM":
    cdef cppclass LearnInput:
        LearnInput(DataDescription * learnData, LabelDescription * knownLabelDescription)
        void addCriterion(const CriterionName criterionName)
        void setNbCVBlock(int64_t nbCVBlock)
        # inherited:
        void finalize()

cdef extern from "LearnOutput.h" namespace "XEM":
    cdef cppclass LearnOutput:
        void sort(CriterionName criterionName)
        bool atLeastOneEstimationNoError() const
        LearnModelOutput * getLearnModelOutput(unsigned int index) const
        int64_t getNbLearnModelOutput() const

cdef extern from "LearnMain.h" namespace "XEM":
    cdef cppclass LearnMain:
        LearnMain()
        LearnMain(LearnInput * input,  LearnOutput * output = NULL)
        void run(int seed) except +
        LearnOutput * getLearnOutput()

cdef extern from "LearnModelOutput.h" namespace "XEM":
    cdef cppclass LearnModelOutput:
        LearnModelOutput()
        const LabelDescription * getCVLabel() const
        # inherited methods
        int64_t getNbCluster() const
        CriterionOutput & getCriterionOutput(CriterionName criterionName) const
        Exception & getStrategyRunError() const
        LabelDescription * getLabelDescription() const

cdef extern from "PredictInput.h" namespace "XEM":
    cdef cppclass PredictInput:
        PredictInput(DataDescription * predictData, ParameterDescription * classificationRule)
        # inherited:
        #void finalize()

cdef extern from "PredictModelOutput.h" namespace "XEM":
    cdef cppclass PredictModelOutput:
        PredictModelOutput()
        # inherited methods
        Exception & getStrategyRunError() const
        LabelDescription * getLabelDescription() const
        ProbaDescription * getProbaDescription() const

cdef extern from "PredictOutput.h" namespace "XEM":
    cdef cppclass PredictOutput:
        PredictOutput()
        vector[PredictModelOutput*] & getPredictModelOutput() const
cdef extern from "PredictMain.h" namespace "XEM":
    cdef cppclass PredictMain:
        PredictMain()
        PredictMain(PredictInput * input,  PredictOutput * output = NULL)
        PredictOutput * getPredictOutput() const
        void run() except +
