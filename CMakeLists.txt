cmake_minimum_required(VERSION 3.5)
project(ember VERSION 0.1)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(lib/ember)
add_subdirectory(src)