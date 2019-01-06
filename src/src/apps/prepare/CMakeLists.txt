add_executable(prepare_lin prepare_lin.cpp)
target_link_libraries(prepare_lin PUBLIC util_lib)

add_executable(prepare_win prepare_win.cpp)
target_link_libraries(prepare_win PUBLIC util_lib)