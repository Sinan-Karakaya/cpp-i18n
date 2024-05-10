cmake_minimum_required(VERSION 3.22.1)

project(cpp-i18n LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fdiagnostics-color=always")
endif()

# Build library
add_subdirectory(src)

# Fetch dependencies
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(cpp-i18n PUBLIC nlohmann_json::nlohmann_json)

# Build tests
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    if (BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()
