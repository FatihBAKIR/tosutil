add_library(util_lib src/util.cpp include/tut/util.hpp include/tut/loaders.hpp src/json_loaders.cpp)
target_include_directories(util_lib PUBLIC include)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(util_lib PUBLIC spdlog::spdlog)

find_path(JSON_INCLUDE_DIR nlohmann/json.hpp)
target_include_directories(util_lib PUBLIC ${JSON_INCLUDE_DIR})

find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(util_lib PUBLIC Boost::boost Boost::system Boost::filesystem)

#target_link_libraries(util_lib PUBLIC pthread)
add_subdirectory(src/apps)