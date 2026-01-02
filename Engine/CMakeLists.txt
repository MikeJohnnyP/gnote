project(Engine VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PUBLIC 
                         ON_GNOTE_ENGINE 
                         GNOTE_ENABLE_ASSERTS 
                         DYNAMIC_BUILD=0
                         DYNAMIC_IMPORT=1
                         _DEBUG
                         )

target_include_directories(${PROJECT_NAME} PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_SOURCE_DIR}/Vendors/include
                            ${CMAKE_SOURCE_DIR}/Vendors/glfw/include
                            ${CMAKE_SOURCE_DIR}/Vendors/imgui
                            ${CMAKE_SOURCE_DIR}/Vendors/glad/include
                            ${CMAKE_SOURCE_DIR}/Vendors/stb_image
                            ${CMAKE_SOURCE_DIR}/include
                            )

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/bin)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui spdlog glfw glad stb_image)

target_precompile_headers(${PROJECT_NAME} PUBLIC 
                    ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
                    )
