# ANACONDA_HOME is the parent directory of your Anaconda installation,
# so it has to contain anaconda3 or/and anaconda2 directory

export ANACONDA_HOME=$HOME

# currently (i.e. Feb 2016) we are still using gcc and g++ v4.8.x
# in order to keep compatibility with the libstdc++ on Anaconda3-2.5.0
# you may need to set CXX an CC variable below according to your environment

export CXX=/usr/bin/g++
export CC=/usr/bin/gcc