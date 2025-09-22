#only one headers include directory (at root)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#Generation de la liste des fichiers sources
FILE(GLOB_RECURSE mixmod_src ${CMAKE_CURRENT_SOURCE_DIR}/mixmod/*.cpp)
ADD_LIBRARY(mixmod ${mixmod_src})
target_link_libraries(mixmod PRIVATE Eigen3::Eigen)

SET_TARGET_PROPERTIES(mixmod PROPERTIES VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" )
target_include_directories (mixmod PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mixmod/Utilities>)

INSTALL(TARGETS mixmod 
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	COMPONENT runtime)

#to allow #include <mixmod.h>
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/mixmod/Utilities/mixmod.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	COMPONENT dev)

#installed headers have same structure as in source folder
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mixmod
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	COMPONENT dev
	FILES_MATCHING
		PATTERN "*.h"
		#Cleanly exclude Utilities/mixmod.h
		PATTERN "mixmod.h" EXCLUDE)

