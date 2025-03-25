cmake_minimum_required(VERSION 3.10)
project(Tag-Game VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_subdirectory(Stitch)

include_directories(Stitch/include)
include_directories(Stitch/Stitch/vendor/glew-2.2.0/include)

add_executable(Tag-Game src/main.cpp src/IndexBuffer.cpp src/IndexBuffer.h src/Renderer.cpp src/Renderer.h src/VertexBuffer.cpp src/VertexBuffer.h src/VertexArray.cpp src/VertexArray.h src/VertexBufferLayout.h src/vendor/stb_image/stb_image.cpp src/vendor/stb_image/stb_image.h src/Texture.h src/Texture.cpp src/vendor/imGui/imconfig.h src/vendor/imGui/imgui.cpp src/vendor/imGui/imgui.h src/vendor/imGui/imgui_demo.cpp src/vendor/imGui/imgui_draw.cpp src/vendor/imGui/imgui_internal.h src/vendor/imGui/imstb_rectpack.h src/vendor/imGui/imstb_textedit.h src/vendor/imGui/imstb_truetype.h src/vendor/imGui/imgui_impl_glfw.cpp src/vendor/imGui/imgui_impl_glfw.h src/vendor/imGui/imgui_tables.cpp src/vendor/imGui/imgui_widgets.cpp src/vendor/imGui/imgui_impl_opengl3.cpp src/vendor/imGui/imgui_impl_opengl3.h src/vendor/imGui/imgui_impl_opengl3_loader.h)
target_link_libraries(Tag-Game stitch)

set_property(TARGET Tag-Game PROPERTY CXX_STANDARD 23)
