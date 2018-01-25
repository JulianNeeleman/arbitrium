cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(arbitrium VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

include(GNUInstallDirs)

add_subdirectory(games)
add_subdirectory(apps)
