# Require minimum standard version of CMake
cmake_minimum_required (VERSION 3.10)

# Set C++ 20 compiler flags
set(CMAKE_CXX_STANDARD 20)

# Set project name
project (imgui LANGUAGES CXX)

# Set the source files to a list
set(
    source_list
	"imconfig.h"
    "imgui.cpp"
	"imgui.h"
	"imgui_demo.cpp"
	"imgui_draw.cpp"
	"misc/cpp/imgui_stdlib.h"
	"misc/cpp/imgui_stdlib.cpp"
	"imgui_internal.h"
    "imgui_tables.cpp"
	"imgui_widgets.cpp"
	"imstb_rectpack.h"
	"imstb_textedit.h"
	"imstb_truetype.h"
    "backends/imgui_impl_glfw.cpp"
    "backends/imgui_impl_glfw.h"
    "backends/imgui_impl_opengl3.cpp"
    "backends/imgui_impl_opengl3.h"

)

add_library(${PROJECT_NAME} ${source_list})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(imgui PUBLIC
  glfw
  OpenGL::GL
)
