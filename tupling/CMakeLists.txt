#--- ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS Core Tree)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

#--- Build Tupling library
file(GLOB tupling_sources "src/*cpp")
add_library(Tupling STATIC ${tupling_sources})
target_include_directories(Tupling PUBLIC include ${CMAKE_SOURCE_DIR}/common/include ${CMAKE_SOURCE_DIR}/eventmodel/include)
target_link_libraries(Tupling ${ROOT_LIBRARIES})