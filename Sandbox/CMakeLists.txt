project(Sandbox VERSION 0.1)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp CMAKE_CONFIGURE_DEPENDS)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_SOURCE_DIR}/Vendors/glm
                            ${CMAKE_SOURCE_DIR}/Engine
                            )

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/bin)
target_link_libraries(${PROJECT_NAME} PRIVATE Engine)

file(COPY ${CMAKE_SOURCE_DIR}/Sandbox/Assets
     DESTINATION ${CMAKE_BINARY_DIR}/bin)
