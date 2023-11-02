cmake_minimum_required(VERSION 3.26)
project(KATE)

set(CMAKE_CXX_STANDARD 11)

add_executable(KATE src/main.cpp
        src/k_bin.cpp
        src/k_bin.h)
