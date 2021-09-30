cmake_minimum_required(VERSION 2.9)

project(LUCKY)

add_executable(LUCKY src/main.cpp src/log.cpp src/lexer.cpp src/expr.cpp)

include_directories(includes)
