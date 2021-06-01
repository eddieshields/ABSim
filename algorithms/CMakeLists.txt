#--- Add models
add_subdirectory(${CMAKE_SOURCE_DIR}/models ${CMAKE_BINARY_DIR}/models)

#--- Build EventModel library
file(GLOB algorithm_sources "src/*cpp")
add_library(Algorithms STATIC ${algorithm_sources})
target_include_directories(Algorithms PUBLIC include ${CMAKE_SOURCE_DIR}/common/include)
target_link_libraries(Algorithms DalitzModel Common)