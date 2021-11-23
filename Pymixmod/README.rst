############
Installation
############

There are two ways to install PyMixmod :

 * Test/Evaluation installation with Anaconda distribution
 * Standard installation (root privileges are required)

Installation with Anaconda
==========================

This method is faster than the standard method and it can be performed without root privileges. On the other hand, Anaconda contains a lot of additional packages, not required by PyMixmod.

The installation of PyMixmod requires tree steps:

 * Download and install the Anaconda distribution by following the online documentation http://continuum.io/downloads  (both Python 2.7.x and 3.4.x releases are convenent for PyMixmod)
 * Build PyMixmod
   
   ::
      python setup.py  build_ext

   NB: be sure to use the Python interpreter provided by Anaconda distribution
   instead of the standard Python interpreter

 * Install PyMixmod

   ::
      python setup.py install
   

   

Standard installation
=====================
   
PyMixmod requires Python 2.7.x or Python 3.4.x and the following  Python modules:

  * numpy (v >= 1.9.0)
  * scipy (v >= 0.15.1)
  * pandas (v >= 0.15.2)
  * matplotlib (v >= 1.4.3)
  * enum34 (only for Python 2.7.x)
    
**NB:** One way (among others) to install a Python module is the **pip** command. In order to install a module into the standard location, you need *root* privileges. Example:

::

   sudo pip install numpy

**Warning:** Currently (april 2015) there are a known bug (cf. http://stackoverflow.com/questions/25674612/ubuntu-14-04-pip-cannot-upgrade-matplotllib) which prevents installing matplotlib1.4.3 on Python3.4 unless you previously installed the freetype6-dev package (i.e. the package name on Ubuntu 14.04). This bug has already been fixed on master https://github.com/matplotlib/matplotlib/pull/3414




*****************
Building PyMixmod
*****************

In addition, the Cython module is required for building PyMixmod:

* Install Cython (v>=0.20)

::

   sudo pip install cython

Building PyMixmod for test and developpement
============================================

* Go into *..../Py* directory and execute:

::

   python setup.py build_ext --inplace


**NB:** The module *mixmod.so* is generated and it is available for execution (i.e. import) **only in the current directory**.


Building PyMixmod + installation in the standard location
=========================================================

* Go to Py directory and execute:

::

   python setup.py build_ext 


**NB** The module *mixmod.so* is generated in ./build/lib.linux-xxxx/

* Then execute:

::

   sudo python setup.py install

**NB:** This way,  *mixmod.so* is available from every directory on the computer
