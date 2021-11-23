#############
Prerequisites
#############

Copy anaconda_settings.sh.tpl to anaconda_settings.sh in this (i.e. conda-recipes) directory.

In order to run the scripts described below you have to install
Anaconda https://www.continuum.io/downloads

If Anaconda is NOT installed in the default location (i.e. your homedir), consider setting ANACONDA_HOME in anaconda_settings.sh

NB: ANACONDA_HOME is the parent directory of your Anaconda installation, so it has to contain anaconda3 or/and anaconda2 directory


In order to keep compatibility with the libstdc++ on Anaconda3-2.5.0
we are currently (i.e. Feb 2016) still using gcc and g++ v4.8.x
You will probably need to set CXX an CC variable in  anaconda_settings.sh according to your particular environment

##################################
Build a new pymixmod conda package
##################################

In this directory execute:

./build_pymixmod.sh 3 #for Python 3.x

or 

./build_pymixmod.sh 2 #for Python 2.7

then get the result (i.e. the pymixmod*.tar.bz2 tarball) in

$ANACONDA_HOME/anaconda{2|3}/conda-bld/linux-64/


#####################
Build and (re)install
#####################

This is a shortcut for build a new pymixmod package (with ./build_pymixmod.sh) and (re)install it in
your current anaconda environment:

./reinstall 3  #for Python 3.x
or
./reinstall 2 #for Python 2.7

################
Run all examples
################

./run_all_examples.sh 3 #for Python 3.x
or
./run_all_examples.sh 2 #for Python 2.7

