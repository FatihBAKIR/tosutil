add_executable(program program.cpp openocd_program.cpp avrdude_program.cpp)
target_link_libraries(program PUBLIC util_lib)
