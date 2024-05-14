FROM gcc:latest as build

# Dependencies
RUN apt-get update && apt-get install -y \
    cmake libboost-dev libboost-regex-dev libasio-dev libpqxx-dev pkg-config

# Copy project files
WORKDIR /app
COPY CMakeLists.txt .
COPY src ./src

# Compile
RUN mkdir build && cd build && cmake .. && make

# Run
CMD ["./build/crow_api"]
