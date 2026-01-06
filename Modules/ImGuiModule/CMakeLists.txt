project(ImGuiModule VERSION 0.1)

add_library(${PROJECT_NAME} SHARED ImGuiModule.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Vendors/glfw/include
    ${CMAKE_SOURCE_DIR}/Vendors/imgui
    ${CMAKE_SOURCE_DIR}/Vendors/glad/include
    ${CMAKE_SOURCE_DIR}/Vendors/stb_image
)

target_precompile_headers(${PROJECT_NAME} PUBLIC 
                    ${CMAKE_CURRENT_SOURCE_DIR}/ex_pch.h

                    )

target_link_libraries(${PROJECT_NAME} PRIVATE imgui glfw stb_image glad)

target_compile_definitions(ImGuiModule PUBLIC 
                        ON_EXMODULE
                         DYNAMIC_BUILD=1
                         GNOTE_EXMODULE_ENABLE_ASSERTS
                         DYNAMIC_IMPORT=0
                         _DEBUG
                         )

