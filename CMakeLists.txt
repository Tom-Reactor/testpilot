cmake_minimum_required(VERSION 3.5)

project(testpilot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")

add_subdirectory(src/simulator)
add_subdirectory(src/stack)
add_subdirectory(src/demo)
