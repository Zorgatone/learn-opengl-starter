cmake_minimum_required(VERSION 3.21)
project(test_glfw)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_glfw src/gl3w.c src/LoadShaders.cpp src/main.cpp)

target_include_directories(test_glfw PRIVATE include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.3.6)
target_link_libraries(test_glfw glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(test_glfw OpenGL::GL)

#add_subdirectory(freeglut-3.2.1)
#target_include_directories(test_glfw PRIVATE freeglut-3.2.1/include)
#target_link_libraries(test_glfw freeglut)
