# CMakeLists.txt for ABSIM.
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE ABSIM)
project(${PACKAGE})

#--- Options
option(DEBUG "Debug" ON)
option(RELEASE "Release" OFF)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

if (RELEASE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -flto")
endif()

set (CMAKE_CXX_STANDARD 11)

include_directories(include/)
include_directories(backend/include/)

##--- UMESIMD
include_directories(external/umesimd)

#--- Find threads.
find_package(Threads REQUIRED)

##--- Define the header and src directories
file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp backend/src/*.cpp)

##--- Generate library with ROOT dictionary
add_library(${PACKAGE} SHARED ${SOURCES})

##--- Link libraries
target_link_libraries(${PACKAGE} ${CMAKE_THREAD_LIBS_INIT})

###--- Create an executable
add_executable(ABSimRun ${CMAKE_SOURCE_DIR}/main/src/ABSim.cpp)
target_link_libraries(ABSimRun ${PACKAGE})

if ( BUILD_TESTS )
    add_subdirectory(tests)
endif()
