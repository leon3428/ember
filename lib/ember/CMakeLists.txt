set(PROJECT_HEADERS 
    src/config.hpp

    src/core/utils.hpp
    src/core/event_bus.hpp
    src/core/key_codes.hpp
    src/core/mouse_button_codes.hpp
    src/core/window.hpp
    src/core/conflict_free_variant_hash_map.hpp

    src/graphics/render_engine.hpp
    src/graphics/render_group.hpp

    src/graphics/shader_program.hpp
    src/graphics/shader_program_loader.hpp
    src/graphics/shader.hpp
    src/graphics/vertex_types.hpp
    src/graphics/static_mesh.hpp
    src/graphics/dynamic_mesh.hpp

    src/graphics/mesh.hpp
    src/graphics/solid_color_material.hpp
    src/graphics/material.hpp

    src/resource_manager/resource_manager.hpp
    src/resource_manager/resource_map.hpp
)

set(PROJECT_SOURCES 
    src/core/utils.cpp
    src/core/window.cpp

    src/graphics/render_engine.cpp

    src/graphics/shader_program.cpp
    src/graphics/shader_program_loader.cpp
    src/graphics/shader.cpp
    src/graphics/vertex_types.cpp
    src/graphics/static_mesh.cpp

    src/graphics/mesh.cpp
    src/graphics/solid_color_material.cpp
    src/graphics/material.cpp

    src/resource_manager/resource_manager.cpp
    src/resource_manager/resource_map.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

add_library(${PROJECT_NAME}_lib STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_compile_options(${PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic -std=c++20)
target_link_libraries(${PROJECT_NAME}_lib glad glfw glm)
target_include_directories(${PROJECT_NAME}_lib  PRIVATE ../../external)