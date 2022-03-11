message("Generating the build files for the results")

set(RESULTS_SOURCES ${PROJECT_SOURCE_DIR}/src/results/src/results.cpp)
set(RESULTS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/results/include/)

add_library(jbox-results STATIC ${RESULTS_SOURCES})
target_include_directories(jbox-results PUBLIC ${RESULTS_INCLUDE_DIRS})
