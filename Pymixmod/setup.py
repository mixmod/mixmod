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

##     All informations available on : http://www.mixmod.org
## ################################################################################

##  @author: Christian Poli, INRIA

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from Cython.Build import cythonize
import os
import os.path
import numpy as np
MIXMOD_SRC = os.environ.get('SRC_DIR', '../../mixmodLib/trunk') + "/SRC/mixmod/"

mixmod_includes = [
    "/DiscriminantAnalysis/Learn/",
    "/DiscriminantAnalysis/Predict/",                            
    "/Clustering/",
    "/Kernel/IO/",
    "/Matrix/",                            
    "/Kernel/Model/",
    "/Kernel/Criterion/",                            
    "/Kernel/Parameter/",
    "/Utilities/",
    "/Utilities/exceptions/"
    ]

ext_modules=[
    Extension("mixmod",
              ["mixmod.pyx"],
              extra_compile_args=['-std=c++11'],
              language="c++",
              include_dirs=[ ".", np.get_include(),] + [MIXMOD_SRC+i for i in  mixmod_includes],
              libraries=["mixmod"]),
    ]

setup(
    name = "PyMixmod",
    cmdclass = {"build_ext": build_ext},
    ext_modules = cythonize(ext_modules, gdb_debug=False,output_dir='.')
)

#gcc -pthread -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -fPIC -I../../mixmodLib/trunk/SRC/mixmod/Clustering/ -I../../mixmodLib/trunk/SRC/mixmod/Kernel/IO/ -I../../mixmodLib/trunk/SRC/mixmod/Utilities/ -I/usr/include/python2.7 -c mixmod.cpp -o build/temp.linux-x86_64-2.7/mixmod.o
