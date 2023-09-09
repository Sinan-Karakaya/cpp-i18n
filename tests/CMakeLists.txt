cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-color=always")

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(tests src/basic.cpp)
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE cpp-i18n)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:tests>/assets)