cmake_minimum_required(VERSION 3.19)
project(ruan C)

set(CMAKE_C_STANDARD 11)

add_executable(ruan main.c tga.h types.h)