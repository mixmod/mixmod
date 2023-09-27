from enum import Enum
def pickle_enums(c, x):return gm.__dict__[c][x]

class gm(object):

    class Family(Enum):
        ALL = 1
        GENERAL = 2
        DIAGONAL = 3
        SPHERICAL = 4
        def __reduce_ex__(self, proto):
            return pickle_enums, (self.__class__.__name__, self.name, )

    ALL = Family.ALL
    GENERAL = Family.GENERAL
    DIAGONAL = Family.DIAGONAL
    SPHERICAL = Family.SPHERICAL
    class Proportions(Enum):
        FREE = 1
        EQUAL = 2
        def __reduce_ex__(self, proto):
            return pickle_enums, (self.__class__.__name__, self.name, )

    FREE = Proportions.FREE
    EQUAL = Proportions.EQUAL
    class CriterionName(Enum):
        UNKNOWN_CRITERION_NAME = mxm.UNKNOWN_CRITERION_NAME # Unknown criterion
        BIC = mxm.BIC               # Bayesian information criterion
        CV  = mxm.CV                # Cross validation criterion
        ICL = mxm.ICL                     # Integrated completed likelihood
        NEC = mxm.NEC                     # Entropy criterion
        DCV = mxm.DCV                     # Double Cross validation criterion
        def __repr__(self):
            return '<{}>'.format(self.__str__())
        def rebuild(self, name):
            for e in self.__class__:
                if e.name == name:
                    return e
            raise ValueError("Enum item {} not found".format(name))
        def __reduce_ex__(self, proto):
            #import pymixmod
            return pickle_enums, (self.__class__.__name__, self.name, )

    UNKNOWN_CRITERION_NAME = CriterionName.UNKNOWN_CRITERION_NAME
    BIC = CriterionName.BIC
    CV  = CriterionName.CV
    ICL = CriterionName.ICL
    NEC = CriterionName.NEC
    DCV = CriterionName.DCV

    default_criterion_name = CriterionName.BIC
    default_learn_criterion_name = CriterionName.CV

    valid_cluster_criterion = [BIC, ICL, NEC]
    valid_learn_criterion = [CV, DCV, BIC]

    class DataType(Enum):
        QUALITATIVE = mxm.QualitativeData
        QUANTITATIVE = mxm.QuantitativeData
        HETEROGENEOUS = mxm.HeterogeneousData
        def __reduce_ex__(self, proto):
            return pickle_enums, (self.__class__.__name__, self.name, )

    QUALITATIVE = DataType.QUALITATIVE
    QUANTITATIVE = DataType.QUANTITATIVE
    HETEROGENEOUS = DataType.HETEROGENEOUS
    COMPOSITE = DataType.HETEROGENEOUS # alias

    class AlgoName(Enum):
        UNKNOWN_ALGO_NAME = mxm.UNKNOWN_ALGO_NAME # Unknown algorithm
        MAP = mxm.MAP                # Maximum a posteriori
        EM = mxm.EM                 # Expectation maximization
        CEM = mxm.CEM                # Classification EM
        SEM = mxm.SEM                # Stochastic EM
        M = mxm.M                  # Maximization
        def __reduce_ex__(self, proto):
            return pickle_enums, (self.__class__.__name__, self.name, )

    UNKNOWN_ALGO_NAME = AlgoName.UNKNOWN_ALGO_NAME
    MAP = AlgoName.MAP
    EM = AlgoName.EM
    CEM = AlgoName.CEM
    SEM = AlgoName.SEM
    M = AlgoName.M

    valid_algos = [EM, SEM, CEM]


    class StrategyInitName(Enum):
        RANDOM = mxm.RANDOM         # Random centers
        PARAMETER = mxm.USER           # Initial parameters specified by user
        LABEL = mxm.USER_PARTITION # Partition specified by user
        SMALL_EM = mxm.SMALL_EM       # EM strategy for initial parameters
        CEM_INIT = mxm.CEM_INIT       # initialization with CEM
        SEM_MAX = mxm.SEM_MAX         # initialization with SEM max
        def __reduce_ex__(self, proto):
            return pickle_enums, (self.__class__.__name__, self.name, )

    RANDOM = StrategyInitName.RANDOM
    PARAMETER = StrategyInitName.PARAMETER
    LABEL = StrategyInitName.LABEL
    SMALL_EM = StrategyInitName.SMALL_EM
    CEM_INIT = StrategyInitName.CEM_INIT
    SEM_MAX = StrategyInitName.SEM_MAX


    class ModelName(Enum):
        #####################
        #                   #
        #  Gaussian Models  #
        #                   #
        #####################

        # Unknown model type
        UNKNOWN_MODEL_NAME = mxm.UNKNOWN_MODEL_NAME
        
        # 28 Gaussian 'Classical' models
        
        # Spherical Gaussian model: proportion fixed
        Gaussian_p_L_I = mxm.Gaussian_p_L_I
        Gaussian_p_Lk_I = mxm.Gaussian_p_Lk_I
    
        # Spherical Gaussian model: proportion free
        Gaussian_pk_L_I = mxm.Gaussian_pk_L_I
        Gaussian_pk_Lk_I = mxm.Gaussian_pk_Lk_I

        # Diagonal Gaussian model: proportion fixed
        Gaussian_p_L_B = mxm.Gaussian_p_L_B
        Gaussian_p_Lk_B = mxm.Gaussian_p_Lk_B
        Gaussian_p_L_Bk = mxm.Gaussian_p_L_Bk
        Gaussian_p_Lk_Bk = mxm.Gaussian_p_Lk_Bk

        # Diagonal Gaussian model: proportion free
        Gaussian_pk_L_B = mxm.Gaussian_pk_L_B
        Gaussian_pk_Lk_B = mxm.Gaussian_pk_Lk_B
        Gaussian_pk_L_Bk = mxm.Gaussian_pk_L_Bk
        Gaussian_pk_Lk_Bk = mxm.Gaussian_pk_Lk_Bk

        # Ellipsoidal Gaussian model: proportion fixed
        Gaussian_p_L_C = mxm.Gaussian_p_L_C
        Gaussian_p_Lk_C = mxm.Gaussian_p_Lk_C
        Gaussian_p_L_D_Ak_D = mxm.Gaussian_p_L_D_Ak_D
        Gaussian_p_Lk_D_Ak_D = mxm.Gaussian_p_Lk_D_Ak_D
        Gaussian_p_L_Dk_A_Dk = mxm.Gaussian_p_L_Dk_A_Dk
        Gaussian_p_Lk_Dk_A_Dk = mxm.Gaussian_p_Lk_Dk_A_Dk
        Gaussian_p_L_Ck = mxm.Gaussian_p_L_Ck
        Gaussian_p_Lk_Ck = mxm.Gaussian_p_Lk_Ck

        # Ellipsoidal Gaussian model: proportion free
        Gaussian_pk_L_C = mxm.Gaussian_pk_L_C
        Gaussian_pk_Lk_C = mxm.Gaussian_pk_Lk_C
        Gaussian_pk_L_D_Ak_D = mxm.Gaussian_pk_L_D_Ak_D
        Gaussian_pk_Lk_D_Ak_D = mxm.Gaussian_pk_Lk_D_Ak_D
        Gaussian_pk_L_Dk_A_Dk = mxm.Gaussian_pk_L_Dk_A_Dk
        Gaussian_pk_Lk_Dk_A_Dk = mxm.Gaussian_pk_Lk_Dk_A_Dk
        Gaussian_pk_L_Ck = mxm.Gaussian_pk_L_Ck
        Gaussian_pk_Lk_Ck = mxm.Gaussian_pk_Lk_Ck
    
        #----------------#
        # 16 HD models   #
        #----------------#
        Gaussian_HD_p_AkjBkQkDk = mxm.Gaussian_HD_p_AkjBkQkDk
        Gaussian_HD_p_AkBkQkDk = mxm.Gaussian_HD_p_AkBkQkDk
        Gaussian_HD_p_AkjBkQkD = mxm.Gaussian_HD_p_AkjBkQkD
        Gaussian_HD_p_AjBkQkD = mxm.Gaussian_HD_p_AjBkQkD
        Gaussian_HD_p_AkjBQkD = mxm.Gaussian_HD_p_AkjBQkD
        Gaussian_HD_p_AjBQkD =   mxm.Gaussian_HD_p_AjBQkD
        Gaussian_HD_p_AkBkQkD =  mxm.Gaussian_HD_p_AkBkQkD
        Gaussian_HD_p_AkBQkD =  mxm.Gaussian_HD_p_AkBQkD
    
        Gaussian_HD_pk_AkjBkQkDk = mxm.Gaussian_HD_pk_AkjBkQkDk
        Gaussian_HD_pk_AkBkQkDk =  mxm.Gaussian_HD_pk_AkBkQkDk
        Gaussian_HD_pk_AkjBkQkD = mxm.Gaussian_HD_pk_AkjBkQkD
        Gaussian_HD_pk_AjBkQkD = mxm.Gaussian_HD_pk_AjBkQkD
        Gaussian_HD_pk_AkjBQkD = mxm.Gaussian_HD_pk_AkjBQkD
        Gaussian_HD_pk_AjBQkD = mxm.Gaussian_HD_pk_AjBQkD
        Gaussian_HD_pk_AkBkQkD = mxm.Gaussian_HD_pk_AkBkQkD
        Gaussian_HD_pk_AkBQkD = mxm.Gaussian_HD_pk_AkBQkD

        ######################
        #                    #
        #  10 Binary Models  #
        #                    #
        ######################

        # proportion fixed
        Binary_p_E = mxm.Binary_p_E
        Binary_p_Ek = mxm.Binary_p_Ek
        Binary_p_Ej = mxm.Binary_p_Ej
        Binary_p_Ekj = mxm.Binary_p_Ekj
        Binary_p_Ekjh = mxm.Binary_p_Ekjh
        # proportion free
        Binary_pk_E = mxm.Binary_pk_E
        Binary_pk_Ek = mxm.Binary_pk_Ek
        Binary_pk_Ej = mxm.Binary_pk_Ej
        Binary_pk_Ekj = mxm.Binary_pk_Ekj
        Binary_pk_Ekjh = mxm.Binary_pk_Ekjh

        # Heterogeneous model name:proportions free
        Heterogeneous_pk_E_L_B = mxm.Heterogeneous_pk_E_L_B
        Heterogeneous_pk_E_Lk_B = mxm.Heterogeneous_pk_E_Lk_B
        Heterogeneous_pk_E_L_Bk = mxm.Heterogeneous_pk_E_L_Bk
        Heterogeneous_pk_E_Lk_Bk = mxm.Heterogeneous_pk_E_Lk_Bk
        Heterogeneous_pk_Ek_L_B = mxm.Heterogeneous_pk_Ek_L_B
        Heterogeneous_pk_Ek_Lk_B = mxm.Heterogeneous_pk_Ek_Lk_B
        Heterogeneous_pk_Ek_L_Bk = mxm.Heterogeneous_pk_Ek_L_Bk
        Heterogeneous_pk_Ek_Lk_Bk = mxm.Heterogeneous_pk_Ek_Lk_Bk
        Heterogeneous_pk_Ej_L_B = mxm.Heterogeneous_pk_Ej_L_B
        Heterogeneous_pk_Ej_Lk_B = mxm.Heterogeneous_pk_Ej_Lk_B
        Heterogeneous_pk_Ej_L_Bk = mxm.Heterogeneous_pk_Ej_L_Bk
        Heterogeneous_pk_Ej_Lk_Bk = mxm.Heterogeneous_pk_Ej_Lk_Bk
        Heterogeneous_pk_Ekj_L_B = mxm.Heterogeneous_pk_Ekj_L_B
        Heterogeneous_pk_Ekj_Lk_B = mxm.Heterogeneous_pk_Ekj_Lk_B
        Heterogeneous_pk_Ekj_L_Bk = mxm.Heterogeneous_pk_Ekj_L_Bk
        Heterogeneous_pk_Ekj_Lk_Bk = mxm.Heterogeneous_pk_Ekj_Lk_Bk
        Heterogeneous_pk_Ekjh_L_B = mxm.Heterogeneous_pk_Ekjh_L_B
        Heterogeneous_pk_Ekjh_Lk_B = mxm.Heterogeneous_pk_Ekjh_Lk_B
        Heterogeneous_pk_Ekjh_L_Bk = mxm.Heterogeneous_pk_Ekjh_L_Bk
        Heterogeneous_pk_Ekjh_Lk_Bk = mxm.Heterogeneous_pk_Ekjh_Lk_Bk
        # Heterogeneous model name:proportions fix
        Heterogeneous_p_E_L_B = mxm.Heterogeneous_p_E_L_B
        Heterogeneous_p_E_Lk_B = mxm.Heterogeneous_p_E_Lk_B
        Heterogeneous_p_E_L_Bk = mxm.Heterogeneous_p_E_L_Bk
        Heterogeneous_p_E_Lk_Bk = mxm.Heterogeneous_p_E_Lk_Bk
        Heterogeneous_p_Ek_L_B = mxm.Heterogeneous_p_Ek_L_B
        Heterogeneous_p_Ek_Lk_B = mxm.Heterogeneous_p_Ek_Lk_B
        Heterogeneous_p_Ek_L_Bk = mxm.Heterogeneous_p_Ek_L_Bk
        Heterogeneous_p_Ek_Lk_Bk = mxm.Heterogeneous_p_Ek_Lk_Bk
        Heterogeneous_p_Ej_L_B = mxm.Heterogeneous_p_Ej_L_B
        Heterogeneous_p_Ej_Lk_B = mxm.Heterogeneous_p_Ej_Lk_B
        Heterogeneous_p_Ej_L_Bk = mxm.Heterogeneous_p_Ej_L_Bk
        Heterogeneous_p_Ej_Lk_Bk = mxm.Heterogeneous_p_Ej_Lk_Bk
        Heterogeneous_p_Ekj_L_B = mxm.Heterogeneous_p_Ekj_L_B
        Heterogeneous_p_Ekj_Lk_B = mxm.Heterogeneous_p_Ekj_Lk_B
        Heterogeneous_p_Ekj_L_Bk = mxm.Heterogeneous_p_Ekj_L_Bk
        Heterogeneous_p_Ekj_Lk_Bk = mxm.Heterogeneous_p_Ekj_Lk_Bk
        Heterogeneous_p_Ekjh_L_B = mxm.Heterogeneous_p_Ekjh_L_B
        Heterogeneous_p_Ekjh_Lk_B = mxm.Heterogeneous_p_Ekjh_Lk_B
        Heterogeneous_p_Ekjh_L_Bk = mxm.Heterogeneous_p_Ekjh_L_Bk
        Heterogeneous_p_Ekjh_Lk_Bk = mxm.Heterogeneous_p_Ekjh_Lk_Bk
        def __reduce_ex__(self, proto):
            return pickle_enums, (self.__class__.__name__, self.name, )


    #
    # Model shortcuts
    #

    UNKNOWN_MODEL_NAME = ModelName.UNKNOWN_MODEL_NAME

    # 28 Gaussian 'Classical' models

    # Spherical Gaussian model: proportion fixed
    Gaussian_p_L_I = ModelName.Gaussian_p_L_I
    Gaussian_p_Lk_I = ModelName.Gaussian_p_Lk_I
    
    # Spherical Gaussian model: proportion free
    Gaussian_pk_L_I = ModelName.Gaussian_pk_L_I
    Gaussian_pk_Lk_I = ModelName.Gaussian_pk_Lk_I

    # Diagonal Gaussian model: proportion fixed
    Gaussian_p_L_B = ModelName.Gaussian_p_L_B
    Gaussian_p_Lk_B = ModelName.Gaussian_p_Lk_B
    Gaussian_p_L_Bk = ModelName.Gaussian_p_L_Bk
    Gaussian_p_Lk_Bk = ModelName.Gaussian_p_Lk_Bk

    # Diagonal Gaussian model: proportion free
    Gaussian_pk_L_B = ModelName.Gaussian_pk_L_B
    Gaussian_pk_Lk_B = ModelName.Gaussian_pk_Lk_B
    Gaussian_pk_L_Bk = ModelName.Gaussian_pk_L_Bk
    Gaussian_pk_Lk_Bk = ModelName.Gaussian_pk_Lk_Bk

    # Ellipsoidal Gaussian model: proportion fixed
    Gaussian_p_L_C = ModelName.Gaussian_p_L_C
    Gaussian_p_Lk_C = ModelName.Gaussian_p_Lk_C
    Gaussian_p_L_D_Ak_D = ModelName.Gaussian_p_L_D_Ak_D
    Gaussian_p_Lk_D_Ak_D = ModelName.Gaussian_p_Lk_D_Ak_D
    Gaussian_p_L_Dk_A_Dk = ModelName.Gaussian_p_L_Dk_A_Dk
    Gaussian_p_Lk_Dk_A_Dk = ModelName.Gaussian_p_Lk_Dk_A_Dk
    Gaussian_p_L_Ck = ModelName.Gaussian_p_L_Ck
    Gaussian_p_Lk_Ck = ModelName.Gaussian_p_Lk_Ck

    # Ellipsoidal Gaussian model: proportion free
    Gaussian_pk_L_C = ModelName.Gaussian_pk_L_C
    Gaussian_pk_Lk_C = ModelName.Gaussian_pk_Lk_C
    Gaussian_pk_L_D_Ak_D = ModelName.Gaussian_pk_L_D_Ak_D
    Gaussian_pk_Lk_D_Ak_D = ModelName.Gaussian_pk_Lk_D_Ak_D
    Gaussian_pk_L_Dk_A_Dk = ModelName.Gaussian_pk_L_Dk_A_Dk
    Gaussian_pk_Lk_Dk_A_Dk = ModelName.Gaussian_pk_Lk_Dk_A_Dk
    Gaussian_pk_L_Ck = ModelName.Gaussian_pk_L_Ck
    Gaussian_pk_Lk_Ck = ModelName.Gaussian_pk_Lk_Ck

    #----------------#
    # 16 HD models   #
    #----------------#
    Gaussian_HD_p_AkjBkQkDk = ModelName.Gaussian_HD_p_AkjBkQkDk
    Gaussian_HD_p_AkBkQkDk = ModelName.Gaussian_HD_p_AkBkQkDk
    Gaussian_HD_p_AkjBkQkD = ModelName.Gaussian_HD_p_AkjBkQkD
    Gaussian_HD_p_AjBkQkD = ModelName.Gaussian_HD_p_AjBkQkD
    Gaussian_HD_p_AkjBQkD = ModelName.Gaussian_HD_p_AkjBQkD
    Gaussian_HD_p_AjBQkD =   ModelName.Gaussian_HD_p_AjBQkD
    Gaussian_HD_p_AkBkQkD =  ModelName.Gaussian_HD_p_AkBkQkD
    Gaussian_HD_p_AkBQkD =  ModelName.Gaussian_HD_p_AkBQkD
    
    Gaussian_HD_pk_AkjBkQkDk = ModelName.Gaussian_HD_pk_AkjBkQkDk
    Gaussian_HD_pk_AkBkQkDk =  ModelName.Gaussian_HD_pk_AkBkQkDk
    Gaussian_HD_pk_AkjBkQkD = ModelName.Gaussian_HD_pk_AkjBkQkD
    Gaussian_HD_pk_AjBkQkD = ModelName.Gaussian_HD_pk_AjBkQkD
    Gaussian_HD_pk_AkjBQkD = ModelName.Gaussian_HD_pk_AkjBQkD
    Gaussian_HD_pk_AjBQkD = ModelName.Gaussian_HD_pk_AjBQkD
    Gaussian_HD_pk_AkBkQkD = ModelName.Gaussian_HD_pk_AkBkQkD
    Gaussian_HD_pk_AkBQkD = ModelName.Gaussian_HD_pk_AkBQkD

    ######################
    #    #
    #  10 Binary Models  #
    #    #
    ######################

    # proportion fixed
    Binary_p_E = ModelName.Binary_p_E
    Binary_p_Ek = ModelName.Binary_p_Ek
    Binary_p_Ej = ModelName.Binary_p_Ej
    Binary_p_Ekj = ModelName.Binary_p_Ekj
    Binary_p_Ekjh = ModelName.Binary_p_Ekjh
    # proportion free
    Binary_pk_E = ModelName.Binary_pk_E
    Binary_pk_Ek = ModelName.Binary_pk_Ek
    Binary_pk_Ej = ModelName.Binary_pk_Ej
    Binary_pk_Ekj = ModelName.Binary_pk_Ekj
    Binary_pk_Ekjh = ModelName.Binary_pk_Ekjh

    # Heterogeneous model name:proportions free
    Heterogeneous_pk_E_L_B = ModelName.Heterogeneous_pk_E_L_B
    Heterogeneous_pk_E_Lk_B = ModelName.Heterogeneous_pk_E_Lk_B
    Heterogeneous_pk_E_L_Bk = ModelName.Heterogeneous_pk_E_L_Bk
    Heterogeneous_pk_E_Lk_Bk = ModelName.Heterogeneous_pk_E_Lk_Bk
    Heterogeneous_pk_Ek_L_B = ModelName.Heterogeneous_pk_Ek_L_B
    Heterogeneous_pk_Ek_Lk_B = ModelName.Heterogeneous_pk_Ek_Lk_B
    Heterogeneous_pk_Ek_L_Bk = ModelName.Heterogeneous_pk_Ek_L_Bk
    Heterogeneous_pk_Ek_Lk_Bk = ModelName.Heterogeneous_pk_Ek_Lk_Bk
    Heterogeneous_pk_Ej_L_B = ModelName.Heterogeneous_pk_Ej_L_B
    Heterogeneous_pk_Ej_Lk_B = ModelName.Heterogeneous_pk_Ej_Lk_B
    Heterogeneous_pk_Ej_L_Bk = ModelName.Heterogeneous_pk_Ej_L_Bk
    Heterogeneous_pk_Ej_Lk_Bk = ModelName.Heterogeneous_pk_Ej_Lk_Bk
    Heterogeneous_pk_Ekj_L_B = ModelName.Heterogeneous_pk_Ekj_L_B
    Heterogeneous_pk_Ekj_Lk_B = ModelName.Heterogeneous_pk_Ekj_Lk_B
    Heterogeneous_pk_Ekj_L_Bk = ModelName.Heterogeneous_pk_Ekj_L_Bk
    Heterogeneous_pk_Ekj_Lk_Bk = ModelName.Heterogeneous_pk_Ekj_Lk_Bk
    Heterogeneous_pk_Ekjh_L_B = ModelName.Heterogeneous_pk_Ekjh_L_B
    Heterogeneous_pk_Ekjh_Lk_B = ModelName.Heterogeneous_pk_Ekjh_Lk_B
    Heterogeneous_pk_Ekjh_L_Bk = ModelName.Heterogeneous_pk_Ekjh_L_Bk
    Heterogeneous_pk_Ekjh_Lk_Bk = ModelName.Heterogeneous_pk_Ekjh_Lk_Bk
    # Heterogeneous model name:proportions fix
    Heterogeneous_p_E_L_B = ModelName.Heterogeneous_p_E_L_B
    Heterogeneous_p_E_Lk_B = ModelName.Heterogeneous_p_E_Lk_B
    Heterogeneous_p_E_L_Bk = ModelName.Heterogeneous_p_E_L_Bk
    Heterogeneous_p_E_Lk_Bk = ModelName.Heterogeneous_p_E_Lk_Bk
    Heterogeneous_p_Ek_L_B = ModelName.Heterogeneous_p_Ek_L_B
    Heterogeneous_p_Ek_Lk_B = ModelName.Heterogeneous_p_Ek_Lk_B
    Heterogeneous_p_Ek_L_Bk = ModelName.Heterogeneous_p_Ek_L_Bk
    Heterogeneous_p_Ek_Lk_Bk = ModelName.Heterogeneous_p_Ek_Lk_Bk
    Heterogeneous_p_Ej_L_B = ModelName.Heterogeneous_p_Ej_L_B
    Heterogeneous_p_Ej_Lk_B = ModelName.Heterogeneous_p_Ej_Lk_B
    Heterogeneous_p_Ej_L_Bk = ModelName.Heterogeneous_p_Ej_L_Bk
    Heterogeneous_p_Ej_Lk_Bk = ModelName.Heterogeneous_p_Ej_Lk_Bk
    Heterogeneous_p_Ekj_L_B = ModelName.Heterogeneous_p_Ekj_L_B
    Heterogeneous_p_Ekj_Lk_B = ModelName.Heterogeneous_p_Ekj_Lk_B
    Heterogeneous_p_Ekj_L_Bk = ModelName.Heterogeneous_p_Ekj_L_Bk
    Heterogeneous_p_Ekj_Lk_Bk = ModelName.Heterogeneous_p_Ekj_Lk_Bk
    Heterogeneous_p_Ekjh_L_B = ModelName.Heterogeneous_p_Ekjh_L_B
    Heterogeneous_p_Ekjh_Lk_B = ModelName.Heterogeneous_p_Ekjh_Lk_B
    Heterogeneous_p_Ekjh_L_Bk = ModelName.Heterogeneous_p_Ekjh_L_Bk
    Heterogeneous_p_Ekjh_Lk_Bk = ModelName.Heterogeneous_p_Ekjh_Lk_Bk
        
