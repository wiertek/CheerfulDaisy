cmake_minimum_required(VERSION 3.17.0)

project(Renderer)

set(SOURCES CheerfulDaisy.cpp Interface/Window.cpp Engine/DaisyEngine.cpp Engine/OpenGLRenderer.cpp Scene/Scene.cpp Scene/Box.cpp Scene/Plain.cpp
  Engine/Shaders/Shader.cpp Engine/Camera.cpp Interface/Overlay.cpp)

set(HEADERS Common/Definitions.h Common/OpenGL.h Engine/Camera.h Engine/DaisyEngine.h Engine/OpenGLRenderer.h Engine/OpenGLRendererSettings.h
  Engine/Shaders/Shader.h Engine/Shaders/SimpleShader.h Engine/Shaders/PhongShader.h Engine/Shaders/GouraudShader.h Interface/FpsLimiter.h Interface/Overlay.h Interface/Window.h
  Scene/Box.h Scene/Plain.h Scene/Primitive.h Scene/Scene.h)

set(SHADERS Shaders/SimpleVertexShader.glsl Shaders/SimpleFragmentShader.glsl Shaders/LightVertexShader.glsl Shaders/LightFragmentShader.glsl
  Shaders/PhongVertexShader.glsl Shaders/PhongFragmentShader.glsl Shaders/GouraudVertexShader.glsl Shaders/GouraudFragmentShader.glsl)

add_executable(Renderer ${HEADERS} ${SOURCES} ${SHADERS})
target_link_libraries(Renderer
  PRIVATE
  glad glfw glm DearImGui)
target_compile_features(Renderer PUBLIC cxx_std_20)

if(MSVC)
  set(WARNINGS_FLAGS "/W4")
else()
  set(WARNINGS_FLAGS "-Wall -Wextra -Wpedantic -Werror")
endif()

set_source_files_properties(
  ${SOURCES}
  PROPERTIES
  COMPILE_FLAGS ${WARNINGS_FLAGS}
)

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

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/LightVertexShader.glsl
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/LightVertexShader.glsl)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/LightFragmentShader.glsl
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/LightFragmentShader.glsl)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/PhongVertexShader.glsl
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/PhongVertexShader.glsl)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/PhongFragmentShader.glsl
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/PhongFragmentShader.glsl)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/GouraudVertexShader.glsl
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/GouraudVertexShader.glsl)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/GouraudFragmentShader.glsl
  $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders/GouraudFragmentShader.glsl)