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

#--- Add backend
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)

#--- Add common
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)

#--- Add eventmodel
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/eventmodel)

#--- Add algorithms
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/algorithms)

#--- Add tupling
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tupling)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

#--- Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist EG)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Define the header and src directories
file(GLOB_RECURSE HEADERS include/*.h common/include/*h eventmodel/include/*h tupling/include/*h)
file(GLOB_RECURSE SOURCES src/*.cpp)

#--- Generate library 
include_directories(include backend/ common/include eventmodel/include tupling/include algorithms/include)
ROOT_GENERATE_DICTIONARY(G__${PACKAGE} ${HEADERS} LINKDEF dict/${PACKAGE}LinkDef.h)

#--- Generate library with ROOT dictionary
add_library(${PACKAGE} STATIC ${SOURCES} ${} G__${PACKAGE}.cxx)
#add_library(${PACKAGE} SHARED ${SOURCES})
target_include_directories(${PACKAGE} PUBLIC include backend/ common/include eventmodel/include tupling/include)

#--- Link libraries
target_link_libraries(${PACKAGE} Backend Common EventModel Algorithms Tupling ${ROOT_LIBRARIES})

#--- Create an executable
add_executable(ABSimRun ${CMAKE_CURRENT_SOURCE_DIR}/main/src/ABSim.cpp)
target_link_libraries(ABSimRun ${PACKAGE})

if ( BUILD_TESTS )
    add_subdirectory(tests)
endif()