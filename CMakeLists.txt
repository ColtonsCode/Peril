# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name
project(Peril)

# Add your source files here
set(SOURCES
    src/main.cpp
    src/config.cpp
    src/include/common_main.h
    src/include/states/config.h
)

# Add executable target
add_executable(Peril ${SOURCES} ${HEADERS})

# Add raylib files and link to it
target_include_directories(Peril PUBLIC src/include)
target_link_directories(Peril PUBLIC lib)
target_link_libraries(Peril PUBLIC raylib opengl32 gdi32 winmm user32 kernel32)