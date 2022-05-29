message("Generating the build files for the FakeJammerBox")

set(SIM_SOURCES ${PROJECT_SOURCE_DIR}/tests/sim/src/sim.cpp)
set(SIM_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/tests/sim/include/)

add_executable(jbox-sim ${SIM_SOURCES})
target_include_directories(jbox-sim PRIVATE ${SIM_INCLUDE_DIRS})
target_link_libraries(jbox-sim jbox-com pthread) 
