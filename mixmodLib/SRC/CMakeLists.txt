#only one headers include directory (at root)
include_directories(${CMAKE_SOURCE_DIR}/SRC)

#Generation de la liste des fichiers sources
FILE(GLOB_RECURSE mixmod_src ${CMAKE_SOURCE_DIR}/SRC/mixmod/*.cpp)
ADD_LIBRARY(mixmod SHARED ${mixmod_src})

SET_TARGET_PROPERTIES(mixmod PROPERTIES VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" )

INSTALL(TARGETS mixmod 
	LIBRARY DESTINATION lib
	COMPONENT runtime)

#to allow #include <mixmod.h>
INSTALL(FILES ${CMAKE_SOURCE_DIR}/SRC/mixmod/Utilities/mixmod.h 
	DESTINATION include
	COMPONENT dev)

#installed headers have same structure as in source folder
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/SRC/mixmod
	DESTINATION include
	COMPONENT dev
	FILES_MATCHING
		PATTERN "*.h"
		#Cleanly exclude Utilities/mixmod.h
		PATTERN "mixmod.h" EXCLUDE)

