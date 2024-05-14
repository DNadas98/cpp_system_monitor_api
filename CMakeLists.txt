cmake_minimum_required(VERSION 3.25.1)
project(crow_api)

set(CMAKE_CXX_STANDARD 23)
include_directories(${PROJECT_SOURCE_DIR}/src/includes)

add_executable(crow_api src/main.cpp)
