cmake_minimum_required(VERSION 3.25.1)
project(crow_api)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Fetch Asio
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG        asio-1-18-2
)

FetchContent_MakeAvailable(asio)

# Set the ASIO_INCLUDE_DIR to the path where FetchContent has placed Asio
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

# Ensure Asio is included before Crow
include_directories(${ASIO_INCLUDE_DIR})

# Fetch Crow after setting Asio include path
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG        master
)

# Fetch libpqxx
FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG        7.6.0
)

FetchContent_MakeAvailable(crow libpqxx)

# Add executable
add_executable(crow_api src/main.cpp)

# Link libraries
target_link_libraries(crow_api Crow::Crow pqxx)

# Installation step (if needed)
install(TARGETS crow_api DESTINATION crow_api/usr/local/bin)
install(FILES ${CMAKE_SOURCE_DIR}/.env DESTINATION crow_api/usr/local/bin)
install(FILES ${CMAKE_SOURCE_DIR}/load_env.sh DESTINATION crow_api/usr/local/bin)
