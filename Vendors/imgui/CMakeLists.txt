# Require minimum standard version of CMake
cmake_minimum_required (VERSION 3.10)

# Set C++ 20 compiler flags
set(CMAKE_CXX_STANDARD 20)

# Set project name
project (imgui LANGUAGES CXX)

# Set the source files to a list
set(
    source_list
    "imgui/imconfig.h"
    "imgui/imgui.cpp"
    "imgui/imgui.h"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/misc/cpp/imgui_stdlib.h"
    "imgui/misc/cpp/imgui_stdlib.cpp"
    "imgui/imgui_internal.h"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/imstb_rectpack.h"
    "imgui/imstb_textedit.h"
    "imgui/imstb_truetype.h"
    "imgui/backends/imgui_impl_glfw.cpp"
    "imgui/backends/imgui_impl_glfw.h"
    "imgui/backends/imgui_impl_opengl3.cpp"
    "imgui/backends/imgui_impl_opengl3.h"

)

add_library(${PROJECT_NAME} ${source_list})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

target_link_libraries(imgui PUBLIC
  glfw
  OpenGL::GL
)
