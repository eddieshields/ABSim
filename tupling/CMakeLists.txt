#--- ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS Core Tree)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB tupling_sources "src/*cpp")
file(GLOB tupling_headers "include/*h")

include_directories(include ${ABSIM_BASE}/common/include ${ABSIM_BASE}/eventmodel/include)

#--- Generate library
ROOT_GENERATE_DICTIONARY(G__Tupling ${tupling_headers} LINKDEF TuplingLinkDef.h)

#--- Build Tupling library
add_library(Tupling STATIC ${SOURCES} ${} G__Tupling.cxx)
#add_library(Tupling STATIC ${tupling_sources})
target_include_directories(Tupling PUBLIC include ${ABSIM_BASE}/common/include ${ABSIM_BASE}/eventmodel/include)
target_link_libraries(Tupling ${ROOT_LIBRARIES})