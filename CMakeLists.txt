cmake_minimum_required(VERSION 3.21)
project(config_parse_example)

find_package(nlohmann_json REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(toml11 REQUIRED)
find_package(tinyxml2 REQUIRED)

add_executable(json_example src/json_example.cpp)
target_link_libraries(json_example PUBLIC nlohmann_json::nlohmann_json)
target_include_directories(json_example PUBLIC ${nlohmann_json_INCLUDE_DIRS})

add_executable(yaml_example src/yaml_example.cpp)
target_link_libraries(yaml_example PUBLIC yaml-cpp::yaml-cpp)
target_include_directories(yaml_example PUBLIC ${yaml-cpp_INCLUDE_DIRS})

add_executable(toml_example src/toml_example.cpp)
target_link_libraries(toml_example PUBLIC toml11::toml11)
target_include_directories(toml_example PUBLIC ${toml11_INCLUDE_DIRS})