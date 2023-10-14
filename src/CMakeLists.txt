cmake_minimum_required(VERSION 3.22.1)

add_library(cpp-i18n Translator.cpp)
target_include_directories(cpp-i18n PRIVATE ${CMAKE_SOURCE_DIR}/include)