cmake_minimum_required(VERSION 3.0)

add_compile_options(-Wall -Wextra -pedantic -std=c89 )
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(test_lib test.c driver/bitmap.c driver/files.c driver/filesystem.c driver/utils.c)
target_link_libraries(test_lib m)
