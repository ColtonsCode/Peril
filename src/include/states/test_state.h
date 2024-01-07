#pragma once

#include <common_main.h>
#include <raylib.h>

struct Player
{
    int x;
    int y;
    Texture2D texture;
};

struct TestState : GameState
{
    Player player;


    TestState();

    void update();

    void draw();
};