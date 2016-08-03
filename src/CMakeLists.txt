cmake_minimum_required(VERSION 3.0)

add_compile_options(-Wall -Wextra -std=c89 -pedantic)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")


add_executable(test_lib test.c)
target_link_libraries(test_lib m)
