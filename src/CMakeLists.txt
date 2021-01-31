cmake_minimum_required(VERSION 3.17.0)

project(Renderer)
set(CMAKE_TOOLCHAIN_FILE C:\\Prog\\repos\\CheerfulDaisy\\lib\\vcpkg.windows\\scripts\\buildsystems\\vcpkg.cmake)

set(SOURCES CheerfulDaisy.cpp Interface/Window.cpp Engine/DaisyEngine.cpp)

add_executable(Renderer  ${SOURCES}) 
target_link_libraries(Renderer 
    PRIVATE
        glad glfw)