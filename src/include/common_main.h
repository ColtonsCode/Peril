#pragma once

#include <string>

const int g_renderWidth = 1600;
const int g_renderHeight = 900;

// Initialized in the top of main()
extern std::string g_resourcePath;


struct GameState
{
    virtual void update() = 0;
    virtual void draw() = 0;
};

extern GameState* g_currentState;