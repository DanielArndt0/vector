cmake_minimum_required(VERSION 3.16)

project(Vector VERSION 1.0.0 LANGUAGES CXX)

add_library(Vector INTERFACE)
add_library(Vector::Vector ALIAS Vector)

target_compile_features(Vector INTERFACE cxx_std_11)

target_include_directories(Vector INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_executable(vector_basic examples/basic.cpp)
    target_link_libraries(vector_basic PRIVATE Vector::Vector)
endif()
