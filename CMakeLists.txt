cmake_minimum_required(VERSION 3.22.1)

project(cpp-i18n LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-color=always")

add_subdirectory(src)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    if (BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()