
ADD_EXECUTABLE(mixmod-cli SRC/mixmodCli.cpp)

TARGET_LINK_LIBRARIES("mixmod-cli" mixmod_iostream)

INSTALL(TARGETS "mixmod-cli" DESTINATION bin)

add_test (NAME cli_clustering COMMAND mixmod-cli -i iris.mixmod -B -o ${CMAKE_CURRENT_BINARY_DIR}/res_c WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/EXAMPLES/clustering)
add_test (NAME cli_learn COMMAND mixmod-cli -i iris.mixmod -B -o ${CMAKE_CURRENT_BINARY_DIR}/res_l WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/EXAMPLES/learn)

add_test (NAME cli_predict COMMAND mixmod-cli -i pred.mixmod -B -o ${CMAKE_CURRENT_BINARY_DIR}/res_p WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/EXAMPLES/predict)
