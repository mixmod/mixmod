#!/bin/bash

BTYPE=Release
CLEAN=1


RED='\033[0;31m'
NC='\033[0m'
current_directory=$RECIPE_DIR

function build_component
{
	new_dir="$1/BUILD"
	if [ ! -d "$new_dir" ]; then
	    printf "${RED}${new_dir} does not exist.abort...${NC}\n"
	    exit 1
	fi
	if [ ! -z "$BTYPE" ]; then
	    new_dir="$new_dir/$BTYPE"
	    mkdir -p "$new_dir"
	fi
	if [ ! -d "$new_dir" ]; then
	    printf "${RED}${new_dir} does not exist.abort...${NC}\n"
	    exit 1
	fi
	cd "$new_dir"
	if [ $CLEAN -ne 0 ] || [ ! -e "$new_dir/Makefile" ]; then
	    /bin/rm -rf "$new_dir"/*
	    cmake -DCMAKE_BUILD_TYPE="$BTYPE" \
		-DCMAKE_INSTALL_PREFIX=$PREFIX ../..
	fi
	make -j`nproc` && make install
	#cd $current_directory
}
cp -r "$PYMIXMOD_SRC"  "$SRC_DIR"
#exit
#NEWMAT [current mathematical library]
#build_component "$SRC_DIR/dev/UTIL/NEWMAT"
#exit
#mixmodLib
#build_component "$SRC_DIR/mixmodLib/"
build_component "$SRC_DIR"
PYMIXMOD_SRC_DIR="$SRC_DIR/Pymixmod/"
cd "$PYMIXMOD_SRC_DIR"
$PYTHON  setup.py build_ext --inplace
$PYTHON  setup.py install
export PYTHONPATH="$PYMIXMOD_SRC_DIR:$PYTHONPATH"
cd "$PYMIXMOD_SRC_DIR/doc/api"
MIXMOD_SHARE="$PREFIX/share/mixmod/"
PYMIXMOD_SHARE="$PREFIX/share/pymixmod/"
export DYLD_FALLBACK_LIBRARY_PATH="$SRC_DIR/../../conda-bld/work/mixmodLib/BUILD/Release/SRC"
make clean
make html BUILDDIR="$PYMIXMOD_SHARE/doc"
mkdir -p "$PYMIXMOD_SHARE/examples/clustering/"
mkdir -p "$PYMIXMOD_SHARE/examples/persistence/"
mkdir -p "$PYMIXMOD_SHARE/examples/discriminant_analysis/"
mkdir -p "$PYMIXMOD_SHARE/examples/plotting/data/"

# quickstart
cp "$PYMIXMOD_SRC_DIR/doc/IPynb/PyMixmod_quickstart_EN.ipynb"  "$PYMIXMOD_SHARE//doc/quickstart.ipynb"
cd "$PYMIXMOD_SHARE/doc/"

#"$SRC_DIR/../../bin/ipython" nbconvert --to html --template full quickstart.ipynb
jupyter-nbconvert --to html --template full quickstart.ipynb
rm   "$PYMIXMOD_SHARE//doc/quickstart.ipynb"
cp $PYMIXMOD_SRC_DIR/examples/README "$PYMIXMOD_SHARE/examples/"
cp $PYMIXMOD_SRC_DIR/examples/clustering/clustering*py "$PYMIXMOD_SHARE/examples/clustering/"
cp $PYMIXMOD_SRC_DIR/examples/persistence/persist*py "$PYMIXMOD_SHARE/examples/persistence/"
cp $PYMIXMOD_SRC_DIR/examples/discriminant_analysis/discriminant_analysis*py "$PYMIXMOD_SHARE/examples/discriminant_analysis/"
cp $PYMIXMOD_SRC_DIR/examples/plotting/*py "$PYMIXMOD_SHARE/examples/plotting/"
cp $PYMIXMOD_SRC_DIR/examples/plotting/data/*csv "$PYMIXMOD_SHARE/examples/plotting/data/"
cp $PYMIXMOD_SRC_DIR/examples/plotting/data/*info "$PYMIXMOD_SHARE/examples/plotting/data/"
ln -s "$MIXMOD_SHARE/EXAMPLES/data/" "$PYMIXMOD_SHARE/examples/data"
ln -s "$MIXMOD_SHARE/EXAMPLES/data/" "$PYMIXMOD_SHARE/examples/clustering/data"
ln -s "$MIXMOD_SHARE/EXAMPLES/data/" "$PYMIXMOD_SHARE/examples/persistence/data"
ln -s "$MIXMOD_SHARE/EXAMPLES/data/" "$PYMIXMOD_SHARE/examples/discriminant_analysis/data"
