cmake_minimum_required(VERSION 3.10)

project(elf-reader CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(elf-reader tools/driver/elf-reader.cpp) 