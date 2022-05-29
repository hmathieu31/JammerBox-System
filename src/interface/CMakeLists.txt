cmake_minimum_required(VERSION 3.16.0)
project(JammerBox)

# Les configurations globales du projet se font ici

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_BUILD_TYPE Debug)

# Add Qt to the prefix
if(WIN32)
  list(APPEND CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.9/5.12.9/mingw73_64")
elseif(APPLE)
  list(APPEND CMAKE_PREFIX_PATH "~/Qt5.12.9/5.12.9/clang_64") 
elseif(UNIX)
  list(APPEND CMAKE_PREFIX_PATH "/opt/Qt5.12.9/5.12.9/gcc_64")
endif()

# GoogleTest
# Download and unpack googletest at configure time
configure_file(cmake/CMakeLists.txt.gtest googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
  ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
  EXCLUDE_FROM_ALL)

# Find Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS SerialPort REQUIRED)

# Add QtWaitingSpinner
configure_file(cmake/CMakeLists.txt.qtwaitingspinner.download qtwaitingspinner-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qtwaitingspinner-download)
if(result)
  message(FATAL_ERROR "CMake step for qtwaitingspinner failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qtwaitingspinner-download)
if(result)
  message(FATAL_ERROR "Build step for qtwaitingspinner failed: ${result}")
endif()
configure_file(cmake/CMakeLists.txt.qtwaitingspinner qtwaitingspinner-src/CMakeLists.txt)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/qtwaitingspinner-src)

# La configuration des executables/librairies se font
# avec des subdirectories.
# 
# Ils peuvent être ajoutés avec la ligne :
# 
#   add_subdirectory(source_dir)

add_subdirectory(src/failures)
add_subdirectory(src/graphics)
add_subdirectory(src/virtualcomport)
add_subdirectory(src/results)
add_subdirectory(src/middleware)

add_subdirectory(tests/sim)

