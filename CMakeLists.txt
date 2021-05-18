# CMakeLists.txt for ABSIM.
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(PACKAGE ABSIM)
project(${PACKAGE})

#--- Options
option(DEBUG "Debug" ON)
option(RELEASE "Release" OFF)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic")
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
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/backend/src/*.cpp)

##--- Generate library 
add_library(${PACKAGE} SHARED ${SOURCES})
target_include_directories(${PACKAGE} PUBLIC include)

##--- Link libraries
target_link_libraries(${PACKAGE} ${CMAKE_THREAD_LIBS_INIT})

###--- Create an executable
add_executable(ABSimRun ${CMAKE_SOURCE_DIR}/main/src/ABSim.cpp)
target_link_libraries(ABSimRun ${PACKAGE})

if ( BUILD_TESTS )
    add_subdirectory(tests)
endif()
