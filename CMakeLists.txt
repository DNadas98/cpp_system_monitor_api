cmake_minimum_required(VERSION 3.25.1)
project(crow_api)

set(CMAKE_CXX_STANDARD 23)
include_directories(${PROJECT_SOURCE_DIR}/src/includes)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)
pkg_check_modules(PQ REQUIRED IMPORTED_TARGET libpq)

include(FetchContent)

FetchContent_Declare(
  cpp_dotenv
  GIT_REPOSITORY https://github.com/adeharo9/cpp-dotenv.git
  GIT_TAG        master  # or use a specific commit/tag to ensure reproducibility
)

FetchContent_MakeAvailable(cpp_dotenv)

add_executable(crow_api
  src/main.cpp
  src/service/data_reader/SystemDataReader.cpp
)
target_link_libraries(crow_api cpp_dotenv PkgConfig::PQXX PkgConfig::PQ)
