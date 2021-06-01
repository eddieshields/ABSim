cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(TEST Test)
project(${TEST})

include_directories(${CMAKE_SOURCE_DIR}/common/include ${CMAKE_SOURCE_DIR}/backend ${CMAKE_SOURCE_DIR}/eventmodel/include ${CMAKE_SOURCE_DIR}/algorithms/include ${CMAKE_SOURCE_DIR}/include)
file(GLOB TEST_SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(${TEST} ${TEST_SRC})
target_link_libraries(${TEST} ABSIM)