#!/bin/bash
if [ -z $1 ]; then
    echo "Usage: $0 {2|3}" #NB 2 or 3 : major version of Anaconda Python
    exit
fi
PY_V=$1
PYTHON=$HOME/anaconda$PY_V/bin/python
cd $HOME/anaconda$PY_V/share/pymixmod/examples/
echo "*************************************************"
echo "**************** CLUSTERING *********************"
echo "*************************************************"
for f in `ls clustering/clustering_*.py` ; do
    $PYTHON "$f" >/dev/null && echo "$f passed"
done


echo "*************************************************"
echo "********** DISCRIMINANT ANALYSIS ****************"
echo "*************************************************"
for f in `ls discriminant_analysis/discriminant_analysis_*.py` ; do
    $PYTHON "$f" >/dev/null && echo "$f passed"
done


echo "*************************************************"
echo "**************** PERSISTENCE ********************"
echo "*************************************************"
for f in `ls persistence/*.py` ; do
    $PYTHON "$f" >/dev/null && echo "$f passed"
done

echo "*************************************************"
echo "**************** PLOTTING ***********************"
echo "*************************************************"
cd plotting

for f in `ls ex_*.py` ; do
    echo  "[close the raised windows to continue]"    
    $PYTHON "$f" >/dev/null && echo "$f passed"
done
