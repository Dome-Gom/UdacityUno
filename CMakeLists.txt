set( CMAKE_CXX_FLAGS "-g " )
cmake_minimum_required(VERSION 3.7)

project(Uno)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

add_executable(Uno ${project_SRCS})
