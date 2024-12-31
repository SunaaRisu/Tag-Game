cmake_minimum_required(VERSION 3.10)
project(Tag-Game VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(glfw3 3.4 REQUIRED)

add_executable(Tag-Game src/main.cpp Stitch/Stitch/Core/display.h Stitch/Stitch/Core/display.cpp)
target_link_libraries(Tag-Game GL glfw)

set_property(TARGET Tag-Game PROPERTY CXX_STANDARD 23)
