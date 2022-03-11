message("Generating the build files for the testing the failure encoding library")

set(SOURCES src/failures-test.cpp)

add_executable(failures-test ${SOURCES})
target_include_directories(failures-test PRIVATE ${FAILURES_INCLUDE_DIRS})
target_link_libraries(failures-test jbox-failures gtest_main)
