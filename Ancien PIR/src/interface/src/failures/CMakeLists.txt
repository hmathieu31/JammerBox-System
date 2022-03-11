message("Generating the build files for the failures")

set(FAILURES_SOURCES ${PROJECT_SOURCE_DIR}/src/failures/src/failures.cpp)
set(FAILURES_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/failures/include/)

add_library(jbox-failures STATIC ${FAILURES_SOURCES})
target_include_directories(jbox-failures PUBLIC ${FAILURES_INCLUDE_DIRS})

add_subdirectory(tests)
