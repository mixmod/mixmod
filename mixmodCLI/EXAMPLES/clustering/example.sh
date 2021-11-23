#!/bin/bash -e
#. $HOME/env_mixmod.sh
if [ -d ../clusteringResults ] ; then
    echo "`pwd`../clusteringResult already exists. Delete content? [y/N]"
    read line
    if [ "$line" = "y" ]; then
        rm -f ../clusteringResults/*
    else
        echo "Abort..."
        exit
    fi
else    
    mkdir  ../clusteringResults
fi
mixmod-cli -i iris.mixmod -B -o ../clusteringResults/res
ls  ../clusteringResults/res*
echo "NB: The R script 'example.R' converts this result to an R object"
