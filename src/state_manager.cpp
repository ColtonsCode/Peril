#include <state_manager.h>

void StateManager::pushState(GameState* state)
{
    states.push(state);
}

void StateManager::popState()
{
    states.pop();
}

void StateManager::updateCurrentState()
{
    states.top()->update();
}

void StateManager::drawCurrentState()
{
    states.top()->draw();
}