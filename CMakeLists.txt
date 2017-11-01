cmake_minimum_required (VERSION 3.5)
project (arbitrium)

# Current build version.
set (arbitrium_VERSION_MAJOR 1)
set (arbitrium_VERSION_MINOR 0)

# Compiler settings.
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add all modules to the build.
add_subdirectory (lib)



