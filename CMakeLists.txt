cmake_minimum_required(VERSION 3.17)
project(Segments)

set(CMAKE_CXX_STANDARD 17)

#
# geometry library
#
add_library(geomlib
        scr/geomlib/geometry.cpp
        scr/geomlib/geometry.h)

set_target_properties(geomlib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

#
# project itself
#
add_executable(segments scr/main.cpp)

set_target_properties(segments PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

add_dependencies(segments geomlib)
target_link_libraries(segments geomlib)

#
# unit tests
#

# download googletest
configure_file(CMakeLists.txt.gtest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# prevent overriding the parent project's compiler/linker on windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# add googletest to build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_executable(geometry_unittests
        scr/tests/main.cpp
        scr/tests/geometry_unittests.cpp)

set_target_properties(geometry_unittests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

target_include_directories(geometry_unittests PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(geometry_unittests geomlib)
target_link_libraries(geometry_unittests geomlib gtest_main)