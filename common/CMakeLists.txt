#--- Build Common library
file(GLOB common_sources "src/*cpp")
add_library(Common STATIC ${common_sources})
target_include_directories(Common PUBLIC include)