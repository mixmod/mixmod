############
PyMixmod API
############
.. py:currentmodule:: mixmod
                      
**************
Main functions
**************

.. #.. autofunction:: mixmod.cluster

.. #.. autofunction:: mixmod.learn                  

.. #automodule:: mixmod

.. autofunction:: mixmod.cluster

                  
.. autofunction:: mixmod.learn

                  
.. autofunction:: mixmod.predict
                  

*********
Utilities
*********

.. autofunction:: mixmod.strategy
                  
.. autofunction:: mixmod.init

.. autofunction:: mixmod.algo

.. comment_out autofunction:: mixmod.sort_by_criterion                  

==========================                  
Models filtering utilities
==========================

The three following functions (:py:func:`gaussian_model`, :py:func:`multinomial_model` and :py:func:`composite_model`) have in common the calling conventions described bellow.



There are three ways to call a models filtering function:

* when called without arguments, the function returns a single element list containing the model name **"by default"**
* when called with **gm.ALL** as an excusive, **positional** argument, the function returns a list containing **ALL** the existing model names belonging to that class (gaussian, multinomial or composite).
* when called with one or more **named arguments** (i.e. **param=value**) the function performs **filtering**. In other words, it takes the existing full list of model names available for the class (gaussian, multinomial or composite) and removes items which don't match one (or more) given criteria. The arguments are interpreted as query predicates connected together with the **logical AND** operator as each **param** corresponds to a given filtering criteria.

.. note:: It isn't relevant to speak about **"default value"** for these function parameters because they play the role of filtering criteria in this context. So, when a parameter is missing, that simply  means there are no filtering at all on that criterion.

                  
.. autofunction:: mixmod.gaussian_model

.. autofunction:: mixmod.multinomial_model

.. autofunction:: mixmod.composite_model





***********************
Visualization utilities
***********************

.. autofunction:: mixmod.plot

.. autofunction:: mixmod.hist

.. autofunction:: mixmod.barplot

****************
PyMixmod classes
****************


.. autoclass:: mixmod.Strategy

.. autoclass:: mixmod.Init

.. autoclass:: mixmod.Algo

.. autoclass:: mixmod.Output               
    :members:
       
.. autoclass:: mixmod.ClusterOutput
    :show-inheritance:
    :members:

.. autoclass:: mixmod.LearnOutput
    :show-inheritance:

.. autoclass:: mixmod.PredictOutput
               
.. autoclass:: mixmod.Result               

.. autoclass:: mixmod.LearnResult               
    :show-inheritance:
       

.. autoclass:: mixmod.Parameter

.. autoclass:: mixmod.GaussianParameter
    :show-inheritance:
       
.. autoclass:: mixmod.MultinomialParameter
    :show-inheritance:
       
.. autoclass:: mixmod.CompositeParameter




****************
Global constants
****************

.. note:: All global constants are implemented as class attributes of the 
          **mixmod.gm** class (i.e. the *mixmod.gm* class plays the role of a namespace).
          
          All enumeration items listed below could be referenced in two ways:
          
          * With their actual names (e.g. **gm.DataType.QUANTITATIVE**)
          * With their shortcuts (e.g. **gm.QUANTITATIVE**)

.. _gmDT:

====================
Enum **gm.DataType**
====================

Items:

.. literalinclude:: ../generated/DataType.txt


.. _gmCN:

=========================
Enum **gm.CriterionName**
=========================

Items:

.. literalinclude:: ../generated/CriterionName.txt

.. _gmSIN:

============================
Enum **gm.StrategyInitName**
============================

Items:

.. literalinclude:: ../generated/StrategyInitName.txt

.. _gmAN:

====================
Enum **gm.AlgoName**
====================

Items:

.. literalinclude:: ../generated/AlgoName.txt


.. _gmFam:

==================
Enum **gm.Family**
==================

Items:

.. literalinclude:: ../generated/Family.txt

.. _gmMN:

=====================
Enum **gm.ModelName**
=====================

Items:

.. literalinclude:: ../generated/ModelName.txt
