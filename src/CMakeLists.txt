cmake_minimum_required(VERSION 3.17.0)

project(Renderer)
set(CMAKE_TOOLCHAIN_FILE C:\\Prog\\repos\\CheerfulDaisy\\lib\\vcpkg.windows\\scripts\\buildsystems\\vcpkg.cmake)

set(SOURCES CheerfulDaisy.cpp Interface/Window.cpp Engine/DaisyEngine.cpp Engine/OpenGLRenderer.cpp Scene/Scene.cpp Scene/Box.cpp
  Engine/Shader.cpp Engine/Camera.cpp)

add_executable(Renderer  ${SOURCES}) 
target_link_libraries(Renderer 
    PRIVATE
        glad glfw glm)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/SimpleVertexShader.glsl 
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/SimpleVertexShader.glsl)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/SimpleFragmentShader.glsl 
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/SimpleFragmentShader.glsl)