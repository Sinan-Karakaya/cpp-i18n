cmake_minimum_required(VERSION 3.22.1)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests basic.cpp parameters.cpp)
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE cpp-i18n)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:tests>/assets)