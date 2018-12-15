cmake_minimum_required(VERSION 3.9)
project(tosutil)

set(CMAKE_CXX_STANDARD 17)

add_executable(tosutil main.cpp)

add_subdirectory(src)
target_link_libraries(tosutil PUBLIC util_lib)
