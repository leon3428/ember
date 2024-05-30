find_package(Eigen3 3.3 REQUIRED)

add_executable(${PROJECT_NAME}_bench main.cpp)
target_compile_options(${PROJECT_NAME}_bench PRIVATE -Wall -Wextra -Wpedantic -std=c++20)
target_link_libraries(${PROJECT_NAME}_bench  PRIVATE ${PROJECT_NAME}_lib glad glfw rapidjson)
target_include_directories(${PROJECT_NAME}_bench PRIVATE ../lib/ember/include)
target_include_directories(${PROJECT_NAME}_bench PRIVATE ${EIGEN3_INCLUDE_DIR})