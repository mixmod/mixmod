#!/bin/bash
source ./anaconda_settings.sh

if [ -z $1 ]; then
    echo "Usage: $0 {2|3}" #NB 2 or 3 : major version of Anaconda Python
    exit
fi
PY_V=$1
./build_pymixmod.sh "$PY_V"
CONDA_BIN=$ANACONDA_HOME/anaconda$PY_V/bin/conda
$CONDA_BIN remove -y  pymixmod
CONDA_BLD="$ANACONDA_HOME/anaconda$PY_V/conda-bld/linux-64/"
$CONDA_BIN install -y  $CONDA_BLD/pymixmod*tar.bz2
