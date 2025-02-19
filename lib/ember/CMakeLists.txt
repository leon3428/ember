set(PROJECT_HEADERS 
    src/config.hpp

    src/core/utils.hpp
    src/core/event_bus.hpp
    src/core/key_codes.hpp
    src/core/mouse_button_codes.hpp
    src/core/window.hpp
    src/core/variant_hash_map.hpp
    src/core/project_loader.hpp
    src/core/bezier.hpp
    src/core/circle.hpp
    src/core/cubic_b_spline.hpp
    src/core/image.hpp
    src/core/curve.hpp

    src/graphics/node.hpp
    src/graphics/object3d.hpp
    src/graphics/renderable.hpp

    src/graphics/render_engine.hpp
    
    src/graphics/shader_program.hpp
    src/graphics/shader_program_loader.hpp
    src/graphics/shader.hpp
    src/graphics/vertex_types.hpp

    src/graphics/curve_node.hpp

    src/graphics/vertex_buffer.hpp
    src/graphics/vertex_array.hpp
    src/graphics/index_buffer.hpp
    src/graphics/uniform_buffer.hpp
    src/graphics/mesh.hpp
    src/graphics/dynamic_line_strip.hpp
    src/graphics/solid_color_material.hpp
    # src/graphics/vertex_color_material.hpp
    src/graphics/phong_material.hpp
    src/graphics/shadow_map_material.hpp
    src/graphics/material.hpp
    src/graphics/camera.hpp
    src/graphics/perspective_camera.hpp
    src/graphics/fps_camera_controller.hpp
    src/graphics/object_loader.hpp
    src/graphics/object_controller.hpp
    src/graphics/light.hpp
    src/graphics/texture.hpp
    src/graphics/texture_loader.hpp
    src/graphics/curve_loader.hpp

    src/resource_manager/resource_descriptions.hpp
    src/resource_manager/resource_manager.hpp
    src/resource_manager/resource_index.hpp
)

set(PROJECT_SOURCES 
    src/core/utils.cpp
    src/core/window.cpp
    src/core/project_loader.cpp
    src/core/bezier.cpp
    src/core/circle.cpp
    src/core/cubic_b_spline.cpp
    src/core/image.cpp

    src/graphics/node.cpp
    src/graphics/object3d.cpp
    src/graphics/renderable.cpp
    src/graphics/camera.cpp

    src/graphics/render_engine.cpp

    src/graphics/shader_program.cpp
    src/graphics/shader_program_loader.cpp
    src/graphics/shader.cpp
    src/graphics/vertex_types.cpp

    src/graphics/curve_node.cpp

    src/graphics/vertex_buffer.cpp
    src/graphics/vertex_array.cpp
    src/graphics/index_buffer.cpp
    src/graphics/uniform_buffer.cpp
    src/graphics/mesh.cpp
    src/graphics/solid_color_material.cpp
    # src/graphics/vertex_color_material.cpp
    src/graphics/phong_material.cpp
    src/graphics/shadow_map_material.cpp
    src/graphics/material.cpp
    src/graphics/perspective_camera.cpp
    src/graphics/fps_camera_controller.cpp
    src/graphics/object_loader.cpp
    src/graphics/object_controller.cpp
    src/graphics/light.cpp
    src/graphics/texture.cpp
    src/graphics/texture_loader.cpp
    src/graphics/curve_loader.cpp

    src/resource_manager/resource_descriptions.cpp
    src/resource_manager/resource_manager.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

add_library(${PROJECT_NAME}_lib STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_compile_options(${PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Wpedantic -std=c++20)
target_link_libraries(${PROJECT_NAME}_lib glad glfw glm assimp rapidjson stb_image_lib)
target_include_directories(${PROJECT_NAME}_lib  PRIVATE ../../external)