cmake_minimum_required(VERSION 3.12)
project(maze)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Python3 and its libraries
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Execute Python script to find pybind11's CMake directory
execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import pybind11; print(pybind11.get_cmake_dir())"
        OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Set the CMAKE_PREFIX_PATH to include pybind11's CMake directory
list(APPEND CMAKE_PREFIX_PATH ${PYBIND11_CMAKE_DIR})

find_package(pybind11 REQUIRED)

pybind11_add_module(maze bindings.cpp Maze.cpp)
