cmake_minimum_required(VERSION 3.9)
project(compiler_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler_project main.cpp Lexer.cpp Commons.h Token.h)