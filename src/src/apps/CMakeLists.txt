add_executable(info info.cpp)
target_link_libraries(info PUBLIC util_lib)

add_executable(analyze analyze.cpp)
target_link_libraries(analyze PUBLIC util_lib)

add_executable(program program.cpp)
target_link_libraries(program PUBLIC util_lib)

add_executable(scan scan/programmer_scan.cpp scan/openocd_scanner.cpp)
target_link_libraries(scan PUBLIC util_lib)