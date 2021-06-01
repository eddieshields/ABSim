#--- Build DalitzModel library
include_directories(include)
file(GLOB dalitz_sources "src/*cpp")
add_library(DalitzModel STATIC ${dalitz_sources})
target_include_directories(DalitzModel PUBLIC include ${CMAKE_SOURCE_DIR}/common/include)
target_link_libraries(DalitzModel Common)