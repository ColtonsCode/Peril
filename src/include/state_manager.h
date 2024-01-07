#pragma once

#include <stack>
#include <queue>

struct GameState
{
    virtual void update() = 0;
    virtual void draw() = 0;
};

struct StateManager
{
    std::stack<GameState*> states;

    StateManager() {}
    
    void pushState(GameState* state);

    void popState();

    void updateCurrentState();

    void drawCurrentState();
};