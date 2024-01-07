#pragma once

#include <string>
#include <state_manager.h>

const int g_renderWidth = 1600;
const int g_renderHeight = 900;

// Initialized in the top of main()
extern std::string g_resourcePath;

extern StateManager g_stateManager;