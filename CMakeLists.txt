cmake_minimum_required(VERSION 3.17.0)

project(CheerfulDaisy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_TOOLCHAIN_FILE C:\\Prog\\repos\\CheerfulDaisy\\lib\\vcpkg.windows\\scripts\\buildsystems\\vcpkg.cmake)

#LIBRARIES
add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)

#MAIN PROJECT
add_subdirectory(src)