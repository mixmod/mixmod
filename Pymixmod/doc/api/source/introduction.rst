################
Package overview
################



**********************
Python version support
**********************

**PyMixmod** supports both **Python 2.7** and **Python 3.4** or greater

**********************
Using PyMixmod package
**********************

Currently, the **PyMixmod** package includes an unique Python module called **mixmod**.

In order to avoid long names for frequently used constants, customarily one imports **mixmod** in two steps, as follows:

::

   In [1]: import mixmod

   In [2]: from mixmod import gm


.. note:: The **gm** object contains all **mixmod** globals (constants, enum types etc.). Importing it directly in the current context is not mandatory, but just a trick to avoid long names

          
   
