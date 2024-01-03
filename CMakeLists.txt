# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name
project(Peril)

# Add your source files here
set(SOURCES
    main.cpp
)

# Add executable target
add_executable(Peril WIN32 ${SOURCES} ${HEADERS})
