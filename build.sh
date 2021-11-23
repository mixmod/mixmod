#!/bin/bash
#Build the entire dev project (triggered by Jenkins) from mixmod/code folder.
#NOTE: no need to remove everything if nothing change since last commit
set -e 

BTYPE=$1
PREFIX=$2
CLEAN=$3

if [ -z "$BTYPE" ]; then
    BTYPE="Release"
fi
if [ -z "$PREFIX" ]; then
	PREFIX="$PWD/install/$BTYPE"
fi
if [ -z "$CLEAN" ]; then
    CLEAN=0
fi

RED='\033[0;31m'
NC='\033[0m'

current_directory=$PWD

function conditional_build
{
	build_dir="$1/BUILD"
	if [ ! -d "$build_dir" ]; then
		printf "${RED}${build_dir} does not exist. Abort...${NC}\n"
		exit 1
	fi
	if [ -n "$BTYPE" ]; then
		build_dir="$build_dir/$BTYPE"
		mkdir -p "$build_dir"
	else
		printf "${RED}BTYPE unspecified. Abort...${NC}\n"
		exit 1
	fi
	cd "$build_dir"
	if [ $CLEAN -ne 0 ] || [ ! -e Makefile ]; then
		rm -rf *
		cmake -DCMAKE_BUILD_TYPE="$BTYPE" -DCMAKE_INSTALL_PREFIX="$PREFIX" ../..
	fi
	make && make install
  rc=$?
  if [ $rc != 0 ]; then
		printf "${RED}Build of $1 failed. Abort...${NC}\n"
    exit 1
  fi
	cd $current_directory
}

#NEWMAT [current mathematical library]
#conditional_build "dev/UTIL/NEWMAT"

#mixmodLib
conditional_build "./mixmodLib/"

#mixmodIOStream
conditional_build "./mixmodIOStream/"

#mixmodCLI
conditional_build "./mixmodCLI/"


#Next two are frozen (maintained until build 4290. Now unmaintained)

#mixmodMVC
#conditional_build "./mixmodMVC/trunk"

#mixmodGUI
#conditional_build "./mixmodGUI/"
