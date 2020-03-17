cmake_minimum_required(VERSION 3.15)
project(types CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(types src/main.cpp include/integral.hpp)
target_include_directories(types PUBLIC include/)