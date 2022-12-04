cmake_minimum_required(VERSION 3.17.0)

project(DearImGui)
add_library(DearImGui
    src/imgui_demo.cpp src/imgui_draw.cpp src/imgui_impl_glfw.cpp src/imgui_impl_opengl3.cpp
    src/imgui_tables.cpp src/imgui_widgets.cpp src/imgui.cpp)
target_include_directories(DearImGui PUBLIC include)
target_link_libraries(DearImGui
    PRIVATE
    glad glfw)
