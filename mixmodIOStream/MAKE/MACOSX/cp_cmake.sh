#./cp_cmake.sh 32 or ./cp_cmake.sh 64

#test le nombre d'argument passé
if  test $# -ne 1
then
	echo 'il manque un argument (32 ou 64) decrivant l architecture'
else

  # CMakeLists.txt
  cp -f ../DIST_cmake/CMakeLists.txt ../../CMakeLists.txt
  cp -f Install.txt ../../Install.txt
  cp -f ../DIST_cmake/SRC/CMakeLists.txt ../../SRC/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/MIXMOD/CMakeLists.txt ../../SRC/MIXMOD/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/MIXMOD/Kernel/CMakeLists.txt ../../SRC/MIXMOD/Kernel/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/MIXMOD/Matrix/CMakeLists.txt ../../SRC/MIXMOD/Matrix/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/MIXMOD/Utilities/CMakeLists.txt ../../SRC/MIXMOD/Utilities/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/MIXMOD_IOSTREAM/CMakeLists.txt ../../SRC/MIXMOD_IOSTREAM/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/NEWMAT/CMakeLists.txt ../../SRC/NEWMAT/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/GUI/CMakeLists.txt ../../SRC/GUI/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/GUI/MIXMOD_MVC/CMakeLists.txt ../../SRC/GUI/MIXMOD_MVC/CMakeLists.txt
  cp -f ../DIST_cmake/SRC/GUI/MIXMOD_QT/CMakeLists.txt ../../SRC/GUI/MIXMOD_QT/CMakeLists.txt
  cp -f ../DIST_cmake/LIB/CMakeLists.txt ../../LIB/thirdparty/CMakeLists.txt

  # LIB (64 or 32 bits)
  cp -R ../DIST_cmake/LIB/LIB$1/*.dylib ../../LIB/thirdparty/
  cp -R ../DIST_cmake/LIB/LIB$1/qt_menu.nib ../../LIB/thirdparty/

fi
