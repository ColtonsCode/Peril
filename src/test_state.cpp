#include <states/test_state.h>

TestState::TestState()
{

    player.x = GetScreenWidth() / 2;
    player.y = GetScreenHeight() / 2;
    player.texture = LoadTexture((g_resourcePath + "placeholder_player.png").c_str());
}

void TestState::update()
{
    if (IsKeyDown(KEY_W))
    {
        player.y -= 5;
    }
    if (IsKeyDown(KEY_S))
    {
        player.y += 5;
    }
    if (IsKeyDown(KEY_A))
    {
        player.x -= 5;
    }
    if (IsKeyDown(KEY_D))
    {
        player.x += 5;
    }
}

void TestState::draw()
{
    DrawTexture(player.texture, player.x - (player.texture.width / 2), player.y - (player.texture.height / 2), WHITE);
}