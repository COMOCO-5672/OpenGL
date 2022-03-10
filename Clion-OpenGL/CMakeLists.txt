cmake_minimum_required(VERSION 3.16)
project(Clion_OpenGL)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}/glew-2.2.0/include/GLEW
        ${PROJECT_SOURCE_DIR}/glfw-3.3.2.bin.WIN64/include
        )

link_libraries(
        ${PROJECT_SOURCE_DIR}/glew-2.2.0/lib/Release/x64)

add_executable(Clion_OpenGL source/main.cpp)
target_link_directories(Clion_OpenGL -lopengl32 ${PROJECT_SOURCE_DIR}/glew-2.2.0/lib/Release/x64/glew32.lib)