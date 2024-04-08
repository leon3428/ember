set(PROJECT_HEADERS 
    src/core/utils.hpp
    src/core/event_bus.hpp
    src/core/key_codes.hpp
    src/core/mouse_button_codes.hpp
    src/core/window.hpp

    src/graphics/shader_program.hpp
    src/graphics/shader.hpp
    src/graphics/vertex_types.hpp
    src/graphics/base_mesh.hpp
    src/graphics/static_mesh.hpp
    src/graphics/dynamic_mesh.hpp
)

set(PROJECT_SOURCES 
    src/core/utils.cpp
    src/core/window.cpp

    src/graphics/shader_program.cpp
    src/graphics/shader.cpp
    src/graphics/vertex_types.cpp
    src/graphics/base_mesh.cpp
    src/graphics/static_mesh.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

add_library(${PROJECT_NAME}_lib STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_compile_options(${PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic -std=c++20)
target_link_libraries(${PROJECT_NAME}_lib glad glfw glm)
target_include_directories(${PROJECT_NAME}_lib  PRIVATE ../../external)