add_executable(${PROJECT_NAME}_test test.cpp)
target_compile_options(${PROJECT_NAME}_test PRIVATE -Wall -Wextra -Wpedantic -std=c++20)
target_link_libraries(${PROJECT_NAME}_test  PRIVATE ${PROJECT_NAME}_lib glad glfw GTest::gtest_main)
target_include_directories(${PROJECT_NAME}_test PRIVATE ../lib/ember/include)