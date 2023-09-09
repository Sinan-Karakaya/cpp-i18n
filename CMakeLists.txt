cmake_minimum_required(VERSION 3.22.1)

project(cpp-i18n)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-color=always")

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(cpp-i18n ${SOURCES})
target_include_directories(cpp-i18n PUBLIC include)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(cpp-i18n PRIVATE nlohmann_json::nlohmann_json)

# tests

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()