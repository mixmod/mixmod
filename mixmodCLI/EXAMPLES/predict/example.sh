#!/bin/bash
#. $HOME/env_mixmod.sh
if [ -d ../predictResults ] ; then
    echo "`pwd`../predictResults/ already exists. Delete content? [y/N]"
    read line
    if [ "$line" = "y" ]; then
        rm -f ../predictResults/*
    else
        echo "Abort..."
        exit
    fi
else    
    mkdir  ../predictResults/
fi
mixmod-cli -i pred.mixmod  -o ../predictResults/res -B
ls  ../predictResults/res*
echo "NB: The R script 'example.R' converts this result to an R object"
