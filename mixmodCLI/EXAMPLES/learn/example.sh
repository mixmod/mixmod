#!/bin/bash -e
#. $HOME/env_mixmod.sh
if [ -d ../learnResults ] ; then
    echo "`pwd`../learnResult already exists. Delete content? [y/N]"
    read line
    if [ "$line" = "y" ]; then
        rm -f ../learnResults/*
    else
        echo "Abort..."
        exit
    fi
else    
    mkdir  ../learnResults
fi
mixmod-cli -i iris.mixmod -B -o ../learnResults/res
ls  ../learnResults/res*
echo "NB: The R script 'example.R' converts this result to an R object"
