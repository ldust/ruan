cmake_minimum_required(VERSION 3.19)
project(ruan_core)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCE_CODES "*.h" "*.c")

add_library(ruan_core ${SOURCE_CODES})