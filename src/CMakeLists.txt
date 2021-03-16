cmake_minimum_required(VERSION 3.17.0)

project(Renderer)
set(CMAKE_TOOLCHAIN_FILE C:\\Prog\\repos\\CheerfulDaisy\\lib\\vcpkg.windows\\scripts\\buildsystems\\vcpkg.cmake)

set(SOURCES CheerfulDaisy.cpp Interface/Window.cpp Engine/DaisyEngine.cpp Engine/OpenGLRenderer.cpp Scene/Scene.cpp Scene/Box.cpp
  Engine/Shader.cpp Engine/Camera.cpp Interface/Overlay.cpp
  Interface/DearImGui/imgui_demo.cpp Interface/DearImGui/imgui_draw.cpp Interface/DearImGui/imgui_impl_glfw.cpp Interface/DearImGui/imgui_impl_opengl3.cpp
  Interface/DearImGui/imgui_tables.cpp Interface/DearImGui/imgui_widgets.cpp Interface/DearImGui/imgui.cpp)
  
set(HEADERS Common/Definitions.h Common/OpenGL.h Engine/Camera.h Engine/DaisyEngine.h Engine/OpenGLRenderer.h Engine/OpenGLRendererSettings.h Engine/Shader.h
  Interface/FpsLimiter.h Interface/Overlay.h Interface/Window.h Scene/Box.h Scene/Primitive.h Scene/Scene.h)

set(SHADERS Shaders/SimpleVertexShader.glsl Shaders/SimpleFragmentShader.glsl)

add_executable(Renderer ${HEADERS} ${SOURCES} ${SHADERS}) 
target_link_libraries(Renderer 
    PRIVATE
        glad glfw glm)
target_compile_features(Renderer PUBLIC cxx_std_20)

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