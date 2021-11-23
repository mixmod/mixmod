#from mixmod import *

_MVI = 'variable_independency'
_MCI = 'component_independency'     
_EQP = 'equal_proportions'
_FAM = 'family'

## def data_type_from_model(m):    
##     if m is None:
##         return None
##     if not isinstance(m, Model):
##         raise ValueError("Wrong model {}".format(m))
##     return m.required_data_type()


def _match_any_re(whole_str, pattern):
    for p in pattern:
        if hasattr(p, 'match'): # i.e. is a regex object
            if p.match(whole_str):
                return True
        else:
            if p in whole_str:
                return True
    return False    



def gaussian_model_(*args, **kwargs):
    if not args and not kwargs:
        return [gm.ModelName.Gaussian_pk_Lk_C]            
    
    if args and (len(args) != 1 or args[0] != gm.ALL or kwargs):
        raise ValueError("Invalid arguments in: {} or in {}".format(args, kwargs))
    # query mode bellow
    valid_props = [_EQP, 'family']
    invalid_args = [arg for arg in kwargs if arg not in valid_props]
    if invalid_args:
        raise ValueError("Invalid predicate(s): {}. Only {} attributes are allowed".format(invalid_args, valid_props))
    #family=None, free_proportions=True, equal_proportions=True):
    family = [gm.ALL] if 'family' not in kwargs else kwargs['family']
    if family in gm.Family:
        family = [family]
    elif not is_included(family, gm.Family):
        raise ValueError("unknown family {}".format(family))
    elif gm.ALL in family:
        family = [gm.ALL]
    equal_proportions = True if _EQP not in kwargs else kwargs[_EQP]
    free_proportions = True if _EQP not in kwargs else not kwargs[_EQP]    
    gaussian_f = 'Gaussian_p'
    family_dict = {
        gm.ALL:['_'],
        gm.GENERAL:['_C', '_D'],
        gm.DIAGONAL:['_B'],
        gm.SPHERICAL:['_I']
        }
    prop_free = '_pk_'
    prop_equal = '_p_'
    family_filter = [s for k, L in family_dict.items() if k in family for s in L]
    gaussian_all = [e for e in gm.ModelName if gaussian_f in e.name and _match_any_re(e.name, family_filter)]
    if not free_proportions:
        return [e for e in gaussian_all if prop_free not in e.name]
    if not equal_proportions:
        return [e for e in gaussian_all if prop_equal not in e.name]
    return gaussian_all 

from re import compile as rec

class IndepMulti(object):
    var_true = [rec(r'.*E$'), rec(r'.*Ek$')] # ['E$', 'Ek$']
    var_false = ['kj', 'Ej'] # ['Ekj$', 'Ekjh', 'Ej']
    comp_true = [rec(r'.*E$'), 'Ej'] # ['E$', 'Ej']
    comp_false = ['kj', rec(r'.*Ek$')] # ['Ekj$', 'Ekjh', 'Ek$']

class IndepComposite(object):
    var_true = ['E_', 'Ek_']
    var_false = ['kj', 'Ej']
    comp_true = ['E_', 'Ej']
    comp_false = ['kj', 'Ek_']


def multi_like_model_impl(indep, model_, **kwargs):
    equal_proportions = True if _EQP not in kwargs else kwargs[_EQP]
    free_proportions = True if _EQP not in kwargs else not kwargs[_EQP]    
    prop_free = '_pk_'
    prop_equal = '_p_'
    result = [e for e in gm.ModelName if model_ in e.name]
    if _MVI in kwargs:
        if kwargs[_MVI]: # variable_independency==True
            result = [e for e in result if _match_any_re(e.name, indep.var_true)]
        else:
            result = [e for e in result if _match_any_re(e.name, indep.var_false)]
    if _MCI in kwargs:
        if kwargs[_MCI]: 
            result = [e for e in result if _match_any_re(e.name, indep.comp_true)]
        else:
            result = [e for e in result if _match_any_re(e.name, indep.comp_false)]
    if not free_proportions:
        return [e for e in result if prop_free not in e.name]
    if not equal_proportions:
        return [e for e in result if prop_equal not in e.name]                     
    return result

def multinomial_model_(*args, **kwargs):
    if not args and not kwargs:
        return [gm.ModelName.Binary_pk_Ekjh]    
    if args and (len(args) != 1 or args[0] != gm.ALL or kwargs):
        raise ValueError("Invalid arguments in: {} or in {}".format(args, kwargs))
    # query mode bellow
    valid_props = [_EQP, _MVI, _MCI]
    invalid_args = [arg for arg in kwargs if arg not in valid_props]
    if invalid_args:
        raise ValueError("Invalid predicate(s): {}. Only {} attributes are allowed".format(invalid_args, valid_props))


    return multi_like_model_impl(IndepMulti, 'Binary',  **kwargs)

#mymod.composite_model(equal_proportions=False,variable_independency=True)


def composite_model_(*args, **kwargs):
    if not args and not kwargs:
        return [gm.ModelName.Heterogeneous_pk_Ekjh_Lk_Bk]    
    if args and (len(args) != 1 or args[0] != gm.ALL or kwargs):
        raise ValueError("Invalid arguments in: {} or in {}".format(args, kwargs))
    # query mode bellow
    valid_props = [_EQP, _MVI, _MCI]
    invalid_args = [arg for arg in kwargs if arg not in valid_props]
    if invalid_args:
        raise ValueError("Invalid predicate(s): {}. Only {} attributes are allowed".format(invalid_args, valid_props))
    return multi_like_model_impl(IndepComposite, 'Heterogeneous', **kwargs)

def check_models(model_list, pattern=None):
    data_type_dict = dict(Gaussian=gm.QUANTITATIVE, Binary=gm.QUALITATIVE,
                          Heterogeneous=gm.HETEROGENEOUS)
    if not isinstance(model_list, list):
        raise ValueError("Invalid model_list arg. (it have to be a list)")
    if not model_list:
        raise ValueError("model_list cannot be empty")
    if pattern is None:
        pattern = model_list[0].name.split('_')[0]
    for m in model_list:
        if m not in gm.ModelName:
            raise ValueError("Invalid model {} (not a gm.ModelName)".format(m))
        if not m.name.startswith(pattern):
            raise ValueError("Invalid model: {} have to be a {} model".format(m, pattern))
    return data_type_dict[pattern]

## class Model(object):
##     """
##     :Description: Represents the abstract base class of PyMixmod model classes

##     .. admonition:: Constructor
##         :class: warning

##         This is an abstract class, so instanciate it directly is not a good \
##         idea ...
        
##     :ivar model_list: list of selected model names
##     :vartype model_list: list[:ref:`gm.ModelName<gmMN>`]
##     :ivar default: is **True** if *model_list* holds the default value
##     :vartype default: bool
##     :ivar full: *(bool)* :  is **True** if *model_list* holds all the gaussian \
##     model names (i.e. the object is the result of \
##     *mixmod.gaussian_model(gm.ALL)* call)
##     :vartype full: bool
##     :ivar query: holds (as a dictionary) the set of named \
##     arguments (in other words, the query) which selects the content of \
##     **model_list**. It has no meaning if **default** or **all** is **True**
##     :vartype query: dict    
##     """    
##     def __init__(self, model_list, default_=False, all_=False, query_=None):
##         self.default = default_
##         self.full = all_
##         self.model_list = model_list
##         self.query = query_
##     def __call__(self):
##         return self.model_list
    
## class GaussianModel(Model):
##     """
##     :Description: This class is useful for build collections of gaussian \
##     models. Its instances hold collections of gaussian items of \
##     (:ref:`gm.ModelName<gmMN>`) and they are accepted as **models** parameter \
##     for :py:func:`cluster` and :py:func:`learn` calls.

##     .. admonition:: Constructor
##         :class: note
        
##         models = GaussianModel(model_list)

##         **NB:** If possible, consider calling :py:func:`gaussian_model` \
##         function rather than the constructor.

##     """
##     #actually: models = GaussianModel(model_list, default, all, query)
    
##     def __init__(self, model_list, default_=False, all_=False, query_=None):
##         check_models(model_list, "Gaussian")
##         super(GaussianModel, self).__init__(model_list, default_, all_, query_)
##     def required_data_type(self):
##         return gm.QUANTITATIVE

## class MultinomialModel(Model):
##     """
##     :Description: This class is useful for build collections of multinomial \
##     models. Its instances hold collections of multinomial items of \
##     (:ref:`gm.ModelName<gmMN>`) and they are accepted as **models** parameter \
##     for :py:func:`cluster`  and :py:func:`learn` calls.

##     .. admonition:: Constructor
##         :class: note
        
##         models = MultinomialModel(model_list)

##         **NB:** If possible, consider calling :py:func:`multinomial_model` \
##         function rather than the constructor.

##     """
##     # actually: models = MultinomialModel(model_list, default, all, query)
##     def __init__(self, model_list, default_=False, all_=False, query_=None):
##         check_models(model_list, "Binary")
##         super(MultinomialModel, self).__init__(model_list, default_, all_, query_)
##     def required_data_type(self):
##         return gm.QUALITATIVE


## class CompositeModel(Model):
##     """
##     :Description: This class is useful for build collections of composite \
##     models. Its instances hold collections of composite (i.e. heterogeneous) \
##     items of (:ref:`gm.ModelName<gmMN>`) and they are accepted as **models** \
##     parameter for :py:func:`cluster`\
##     and :py:func:`learn` calls.

##     .. admonition:: Constructor
##         :class: note
        
##         models = CompositeModel(model_list)

##         **NB:** If possible, consider calling :py:func:`composite_model` \
##         function rather than the constructor.

##     """
##     # actually: models = CompositeModel(model_list, default, all, query)
##     def __init__(self, model_list, default_=False, all_=False, query_=None):
##         check_models(model_list, "Heterogeneous")
##         super(CompositeModel, self).__init__(model_list, default_, all_, query_)    
##     def required_data_type(self):
##         return gm.HETEROGENEOUS
    


def gaussian_model(*args, **kwargs):
    """
    :Description: This function returns a list of **gaussian** :ref:`gm.ModelName<gmMN>` enumeration items satisfying a given criterion
    
    .. admonition:: Signature
        :class: note
        
            model_list = mixmod.gaussian_model(gm.ALL)

            model_list = mixmod.gaussian_model([equal_proportions, family])

    :param equal_proportions: when **True**, only models having **equal proportions** are selected. When **False**, only models having **free proportions** are selected.
    :type equal_proportions: bool
    :param family: selects one or more families of gaussian models (gm.GENERAL, gm.DIAGONAL, gm.SPHERICAL)
    :type family: :ref:`gm.Family<gmFam>`, list[:ref:`gm.Family<gmFam>`]
    :return:  list of selected models
    :rtype: list[:ref:`gm.ModelName<gmMN>`]
    """    
    model_list = gaussian_model_(*args, **kwargs)
    return model_list
    #return GaussianModel(model_list, not kwargs, bool(args), kwargs)

def multinomial_model(*args, **kwargs):
    """
    :Description: This function returns a list of **multinomial** :ref:`gm.ModelName<gmMN>` enumeration itemqsatisfying a given criterion
    
    .. admonition:: Signature
        :class: note
        
            model_list = mixmod.multinomial_model(gm.ALL)

            model_list = mixmod.multinomial_model([equal_proportions, variable_independency, component_independency])

    :param equal_proportions: when **True**, only models having **equal proportions** are selected. When **False**, only models having **free proportions** are selected.
    :type equal_proportions: bool
    :param variable_independecy: when **True**, only models not depending on the **j** variables are selected. When **False**, only models which depend on the **j** variables are selected.
    :type variable_independency: bool
    :param component_independecy: when **True**, only models not depending on the **k** components are selected. When **False**, only models which depend on the **k** components are selected.
    :type component_independency: bool
    :return:  list of selected models
    :rtype: list[:ref:`gm.ModelName<gmMN>`]
    """    
    model_list = multinomial_model_(*args, **kwargs)
    return model_list    
    #return MultinomialModel(model_list, not kwargs, bool(args), kwargs)

def composite_model(*args, **kwargs):
    """
    :Description: This function returns a list of **composite** :ref:`gm.ModelName<gmMN>` enumeration items satisfying a given criterion
    
    .. admonition:: Signature
        :class: note
        
            model_list = mixmod.composite_model(gm.ALL)

            model_list = mixmod.composite_model([equal_proportions, variable_independency, component_independency])

    :param equal_proportions: when **True**, only models having **equal proportions** are selected. When **False**, only models having **free proportions** are selected.
    :type equal_proportions: bool
    :param variable_independecy: when **True**, only models not depending on the **j** variables are selected. When **False**, only models which depend on the **j** variables are selected.
    :type variable_independency: bool
    :param component_independecy: when **True**, only models not depending on the **k** components are selected. When **False**, only models which depend on the **k** components are selected.
    :type component_independency: bool
    :return:  list of selected models
    :rtype: list[:ref:`gm.ModelName<gmMN>`]    
    """    
    model_list = composite_model_(*args, **kwargs)
    return model_list    
    #return CompositeModel(model_list, not kwargs, bool(args),  kwargs)
