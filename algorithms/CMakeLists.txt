#--- Add models
add_subdirectory(${ABSIM_BASE}/models ${CMAKE_BINARY_DIR}/models)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS Core Tree)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Build EventModel library
file(GLOB algorithm_sources "src/*cpp")
add_library(Algorithms STATIC ${algorithm_sources})
target_include_directories(Algorithms PUBLIC include ${ABSIM_BASE}/common/include ${ABSIM_BASE}/eventmodel/include)
target_link_libraries(Algorithms DalitzModel)