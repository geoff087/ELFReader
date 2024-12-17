cmake_minimum_required(VERSION 3.10)

project(elf-reader CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/elf)

set(SOURCES
lib/binary_context.cpp
lib/binary_function.cpp
lib/rewrite_instance.cpp
tools/driver/elf_reader.cpp
)

add_executable(elf-reader ${SOURCES}) 