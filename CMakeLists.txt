cmake_minimum_required(VERSION 3.10)
project(Tag-Game VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(Stitch)

include_directories(Stitch/include)
include_directories(Stitch/Stitch/vendor/glew-2.2.0/include)

add_executable(Tag-Game 
src/main.cpp 
src/Texture.h 
src/Texture.cpp

src/vendor/stb_image/stb_image.cpp 
src/vendor/stb_image/stb_image.h 
)

target_link_libraries(Tag-Game stitch)

set_property(TARGET Tag-Game PROPERTY CXX_STANDARD 23)
