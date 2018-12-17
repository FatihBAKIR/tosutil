add_executable(info info.cpp)
target_link_libraries(info PUBLIC util_lib)

add_executable(scan scan/programmer_scan.cpp scan/openocd_scanner.cpp)
target_link_libraries(scan PUBLIC util_lib)

add_subdirectory(program)
add_subdirectory(analyze)