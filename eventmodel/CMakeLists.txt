#--- Tell CMake where to find ROOT.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS Core RooFit RooFitCore Tree MathCore Physics Hist EG)

#--- Build EventModel library
file(GLOB eventmodel_sources "src/*cpp")
add_library(EventModel STATIC ${eventmodel_sources})
target_include_directories(EventModel PUBLIC include ${ABSIM_BASE}/common/include ${ROOT_INCLUDE_DIRS})