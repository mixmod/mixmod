############
Installation
############

There are two ways to install PyMixmod :

 * Test/Evaluation installation with Anaconda distribution
 * Standard installation (root privileges are required)

Install mixmod C++ library
==========================

First, you need to install the c++ library. Go to the root of the mixmod repository and run

::

  mkdir build
  cd build
  cmake -DCMAKE_INSTALL_PREFIX=/usr/local/ -DCMAKE_CXX_FLAGS="-Wall -Wextra -D_GLIBCXX_ASSERTIONS" ..
  make install

Do not forget to add the folder containing the compiled library to your `LD_LIBRARY_PATH` environment variable

::

  export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"


Standard installation
=====================

In the Pymixmod folder.

Python requirements
-------------------

PyMixmod requires Python 2.7.x or Python 3.4.x and the following Python modules:

  * numpy (v >= 1.9.0)
  * scipy (v >= 0.15.1)
  * pandas (v >= 0.15.2)
  * matplotlib (v >= 1.4.3)
  * cython (v >= 0.20)
  * enum34 (only for Python 2.7.x)

You can install them with pip

::

  pip install -r requirements.txt


Build PyMixmod
--------------

::

  pip install -e .


Building PyMixmod for test and development
==========================================

* Go into *..../Pymixmod* directory and execute:

::

   python setup.py build_ext --inplace


**NB:** The module *mixmod.so* is generated and it is available for execution (i.e. import) **only in the current directory**.


Building PyMixmod + installation in the standard location
=========================================================

* Go to Pymixmod directory and execute:

::

   python setup.py build_ext


**NB** The module *mixmod.so* is generated in ./build/lib.linux-xxxx/

* Then execute:

::

   sudo python setup.py install

**NB:** This way,  *mixmod.so* is available from every directory on the computer


Installation with Anaconda
==========================

This method is faster than the standard method and it can be performed without root privileges.
On the other hand, Anaconda contains a lot of additional packages, not required by PyMixmod.

The installation of PyMixmod requires three steps:

 * Download and install the Anaconda distribution by following the online documentation http://continuum.io/downloads
 (both Python 2.7.x and 3.4.x releases are convenient for PyMixmod)
 * Build PyMixmod

   ::

      python setup.py build_ext

   NB: be sure to use the Python interpreter provided by Anaconda distribution
   instead of the standard Python interpreter

 * Install PyMixmod

   ::

      python setup.py install
