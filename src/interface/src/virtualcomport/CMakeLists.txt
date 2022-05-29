message("Generating the build files for the virtualcomport")

set(VIRTUALCOMPORT_SOURCES ${PROJECT_SOURCE_DIR}/src/virtualcomport/src/virtualcomport.cpp)
set(VIRTUALCOMPORT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/virtualcomport/include/)

add_library(jbox-com STATIC ${VIRTUALCOMPORT_SOURCES})
target_include_directories(jbox-com PUBLIC ${VIRTUALCOMPORT_INCLUDE_DIRS})
target_link_libraries(jbox-com PUBLIC pthread)
