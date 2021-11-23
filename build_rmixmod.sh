#!/bin/bash
set -e -x

# Name the installation folder after the current version number
dir=Rmixmod_`grep -oP "Version: \K([0-9\.]+)" ./Rmixmod/DESCRIPTION`

# Change MIXMOD_ROOT to point to an old source folder, if you prefer (unadvised...)
MIXMOD_ROOT="./mixmodLib/SRC"
MIXMOD_IOSTREAM="./mixmodIOStream/SRC"

mkdir -p ./$dir/Rmixmod/
# remove all potential old content
rm -rf ./$dir/Rmixmod/*
# copy Rmixmod from trunk (DESCRIPTION, configure.ac, NAMESPACE etc.)
cp -r ./Rmixmod ./$dir/

cd ./$dir/Rmixmod

# Copy mixmod + iostream source files
cp -r ../../$MIXMOD_ROOT/mixmod/* src/mixmod/
# cp mixmod_r.mk src/mixmod/
cp -r ../../$MIXMOD_IOSTREAM/mixmod_iostream/* src/mixmod_iostream/
cp -r ../../$MIXMOD_IOSTREAM/XML_specs inst/XML_specs
# cp mixmod_iostream_r.mk src/mixmod_iostream/
#touch src/XmlMakevars # useful for Windows

# Some cleaning (editors temp/backup files + object files + R files)
find . -name '*~' -exec rm {} \;
find . -name '*.swp' -exec rm {} \;
find . -name '*.o' -exec rm {} \;
find . -name '*.so' -exec rm {} \;
find . -name '*.Rhistory' -exec rm {} \;
find . -name '*.RData' -exec rm {} \;

# Generate configure script
autoreconf -fvi .
rm -rf autom4te.cache
rm -f aclocal.m4 tstmacos.ac
rm -f config.*

# clean directory
find . -name '.DS_Store' -exec rm {} \;
find . -name '*.o' -exec rm {} \;
rm -f src/Rmixmod.so
rm -f src/mixmod.a
rm -f src/symbols.rds

# Remove all documentation except Rmixmod-package.Rd (NOT MANDATORY)
# https://unix.stackexchange.com/questions/153862/remove-all-files-directories-except-for-one-file
# shopt -s extglob
# rm -f man/!(Rmixmod-package.Rd)

# Generating documentation
#R -e 'library(roxygen2);roxygenize(".");q()'
R -e 'library(devtools);devtools::document();q()'

cd ..

# create source archive for Linux / MacOS
R CMD build Rmixmod

cd ..

echo "Rmixmod package was generated in $dir/"
echo "You can install it (locally) with the command:"
echo "R CMD INSTALL $dir/$dir.tar.gz"
echo "You can check it for CRAN upload as follows:"
echo "R CMD check [--as-cran] $dir/$dir.tar.gz"

# for Windows go there: http://win-builder.r-project.org/upload.aspx
#tmpdir=IZi5golz4Dlb
#wget http://win-builder.r-project.org/$tmpdir/Rmixmod_$dir.zip
