cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")  # provide a json file with the compile commands so clangd can use it
project(REPS LANGUAGES C CXX)

add_subdirectory(vendor)
add_subdirectory(src)
