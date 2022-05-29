message("Generating the build files for the middleware")

set(MIDDLEWARE_SOURCES 
  ${PROJECT_SOURCE_DIR}/src/middleware/src/main.cpp 
  ${PROJECT_SOURCE_DIR}/src/middleware/src/middleware.cpp
)
set(MIDDLEWARE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/middleware/include/)

add_executable(jbox-ui ${MIDDLEWARE_SOURCES})
target_include_directories(jbox-ui PUBLIC ${MIDDLEWARE_INCLUDE_DIRS})
target_link_libraries(jbox-ui PUBLIC jbox-results jbox-graphics jbox-failures jbox-com)
