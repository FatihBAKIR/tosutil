add_executable(info info.cpp)
target_link_libraries(info PUBLIC util_lib)

add_executable(analyze analyze.cpp)
target_link_libraries(analyze PUBLIC util_lib)