# CMakeLists.txt for ABSIM.
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE ABSIM)
project(${PACKAGE})

#--- Options
option(DEBUG "Debug" ON)
option(RELEASE "Release" OFF)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -g")
endif()

if (RELEASE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
endif()

set (CMAKE_CXX_STANDARD 17)

include_directories(include/)
include_directories(backend/include/)

#--- Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#--- Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist EG)

#--- Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Find threads.
find_package(Threads REQUIRED)

##--- Define the header and src directories
file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/backend/src/*.cpp)

##--- Generate library 
add_library(${PACKAGE} SHARED ${SOURCES})
target_include_directories(${PACKAGE} PUBLIC include backend/include)

##--- Link libraries
target_link_libraries(${PACKAGE} ${ROOT_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

###--- Create an executable
add_executable(ABSimRun ${CMAKE_SOURCE_DIR}/main/src/ABSim.cpp)
target_link_libraries(ABSimRun ${PACKAGE})

if ( BUILD_TESTS )
    add_subdirectory(tests)
endif()
