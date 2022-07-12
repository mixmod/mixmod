#------------------------
# Recurse in directories
#------------------------
ADD_SUBDIRECTORY(SRC)
#ADD_SUBDIRECTORY(EXAMPLES)

#install some extra files
install(FILES "README" "LICENSE" 
	DESTINATION share/mixmod
	COMPONENT dev)

#-----
#CPack
#-----
include(${CMAKE_CURRENT_SOURCE_DIR}/CPackLists.txt)
include(CPack)

option(MIXMOD_BUILD_EXAMPLES "build examples" OFF)
if (MIXMOD_BUILD_EXAMPLES)
  add_subdirectory(EXAMPLES)
endif ()
