cmake_minimum_required(VERSION 3.17.0)

project(CheerfulDaisy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#LIBRARIES
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_subdirectory(lib/DearImGui)

#MAIN PROJECT
add_subdirectory(src)