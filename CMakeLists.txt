cmake_minimum_required(VERSION 3.9)
project(compiler_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler_project src/main.cpp src/Lexer.cpp)