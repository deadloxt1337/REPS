cmake_minimum_required(VERSION 3.25)
project(REPS)

et(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")  # provide a json file with the compile commands so clangd can use it

add_subdirectory(src)
add_subdirectory(vendor)
