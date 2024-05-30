add_library(stb_image_lib STATIC 
  include/stbimage/stb_image.hpp
  src/stb_image.cpp
)
target_compile_options(stb_image_lib PRIVATE -Wall -Wextra -Wpedantic -Werror -std=c++20)
target_include_directories(stb_image_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)