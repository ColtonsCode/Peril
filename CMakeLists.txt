# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name
project(Peril)

# Add your source files here
set (HEADERS 
    src/include/common_main.h
    src/include/state_manager.h
    src/include/states/config.h
    src/include/states/test_state.h
)

set(SOURCES
    src/main.cpp
    src/config.cpp
    src/state_manager.cpp
    src/test_state.cpp
)


# Add executable target
add_executable(Peril ${SOURCES} ${HEADERS})

# Add raylib files and link to it
target_include_directories(Peril PUBLIC src/include)
target_link_directories(Peril PUBLIC lib)
target_link_libraries(Peril PUBLIC raylib opengl32 gdi32 winmm user32 kernel32)