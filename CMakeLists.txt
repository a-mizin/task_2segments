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
