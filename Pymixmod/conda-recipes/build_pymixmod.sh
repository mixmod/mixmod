#!/bin/bash
source ./anaconda_settings.sh

if [ -z $1 ]; then
    echo "Usage: $0 {2|3}" #NB 2 or 3 : major version of Anaconda Python
    echo "WARNING: you'll probably need to set CXX an CC variables in this" 
    echo "script according to your environment"    
    exit
fi
PY_V=$1
# currently (Feb 2016) I'm still using gcc and g++ v4.8.x
# in order to keep compatibility with the libstdc++ on Anaconda3-2.5.0
# you may need to set CXX an CC variable below according to your environment
#export CXX=/usr/local/gcc-4.8.5/bin/g++
#export CC=/usr/local/gcc-4.8.5/bin/gcc
if ! [ -x "$CXX" ];then
    echo "CXX path is incorrect ($CXX)"
    exit
fi
CXX_V=`$CXX -v 2>&1|tail -1|grep '4\.8'`

if [ -z "$CXX_V" ] && [ `uname` = "Linux" ] ;then
    echo "CXX version is not 4.8.x, abort!"
    exit
fi
if ! [ -x "$CC" ];then
    echo "CC path is incorrect ($CXX)"
    exit
fi
CC_V=`$CC -v 2>&1|tail -1|grep '4\.8'`
if [ -z "$CC_V" ] && [ `uname` = "Linux" ] ;then
    echo "CC version is not 4.8.x, abort!"
    exit
fi


# PYMIXMOD_SRC="/some/path/ending/in/Pymixmod/"
export PYMIXMOD_SRC="`pwd`/../../../Pymixmod/"
$ANACONDA_HOME/anaconda$PY_V/bin/conda build pymixmod
