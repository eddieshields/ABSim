# CMakeLists.txt for ABSIM.
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE ABSIM)
project(${PACKAGE})
set(ABSIM_BASE ${CMAKE_CURRENT_SOURCE_DIR})

#--- Options
option(BUILD_TESTS "Build test programs" OFF)

#--- Device target architecture
set(TARGET_BACKEND CPU CACHE STRING "Target architecture of the device")
set_property(CACHE TARGET_BACKEND PROPERTY STRINGS CPU THREADS OPENMP GPU)
# Add compile definition for target
add_compile_definitions(TARGET_BACKEND_${TARGET_BACKEND})

#--- CMake build type.
set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS RelWithDebInfo Release Debug)


#--- Compiler flag options.
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -g")
    add_compile_definitions(Debug)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -g -O3 -march=native")
    add_compile_definitions(RelWithDebInfo)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
endif()

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

#--- Find ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist EG)

#--- Add backend
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)