#--- Build Common library
include_directories(include)
file(GLOB common_sources "src/*cpp")
add_library(Common STATIC ${common_sources})