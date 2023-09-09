cmake_minimum_required(VERSION 3.22.1)

add_library(cpp-i18n Translator.cpp)
target_include_directories(cpp-i18n PUBLIC ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(cpp-i18n PRIVATE nlohmann_json::nlohmann_json)