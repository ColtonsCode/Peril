#pragma once

#include <common_main.h>
#include <raylib.h>

struct ConfigState : GameState
{
    std::string textInput;

    // Get character size
    float textInputBoxWidth = 750;
    float textInputBoxHeight = 50;
    // Centered box
    Rectangle textInputBox = { (g_renderWidth - textInputBoxWidth)/2, (g_renderHeight - textInputBoxHeight)/2, textInputBoxWidth, textInputBoxHeight };

    const std::string info_message = "No config file deteced. Please enter resource path:";

    void update();

    void draw();
};