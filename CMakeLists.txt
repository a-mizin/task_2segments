cmake_minimum_required(VERSION 3.17)
project(Segments)

set(CMAKE_CXX_STANDARD 17)

#
# Vector3D library
#
add_library(vectorlib
        scr/vectorLib/Vector3D.cpp
        scr/vectorLib/Vector3D.h)

set_target_properties(vectorlib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

#
# Segment3D library
#
add_library(segmentlib
        scr/segmentLib/Segment3D.cpp
        scr/segmentLib/Segment3D.h)

set_target_properties(segmentlib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

#
# geometry library
#
add_library(geometrylib
        scr/geometryLib/geometry.cpp)

set_target_properties(geometrylib PROPERTIES
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

add_dependencies(segments geometrylib segmentlib vectorlib)
target_link_libraries(segments geometrylib segmentlib vectorlib)

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

add_dependencies(geometry_unittests geometrylib segmentlib vectorlib)
target_link_libraries(geometry_unittests geometrylib segmentlib vectorlib gtest_main)