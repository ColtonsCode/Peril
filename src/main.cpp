#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <string>
#include <algorithm>

#include <stack>

#include <common_main.h>
#include "states/config.h"

void setupWindow();
void DrawDebugText();

// GLOBAL VARIABLES
std::string g_resourcePath = "../../resources/";

struct Player
{
    int x;
    int y;
    Texture2D texture;
};

struct TestState : GameState
{
    Player player;

    TestState()
    {

        player.x = GetScreenWidth() / 2;
        player.y = GetScreenHeight() / 2;
        player.texture = LoadTexture((g_resourcePath + "placeholder_player.png").c_str());
    }

    void update()
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

    void draw()
    {
        DrawTexture(player.texture, player.x - (player.texture.width / 2), player.y - (player.texture.height / 2), WHITE);
    }
};

struct StateManager
{

    std::stack<GameState*> states;

    void pushState(GameState* state)
    {
        states.push(state);
    }

    void popState()
    {
        states.pop();
    }

    void updateCurrentState()
    {
        states.top()->update();
    }

    void drawCurrentState()
    {
        states.top()->draw();
    }
}

int main() {

    setupWindow();

    RenderTexture2D renderTarget = LoadRenderTexture(g_renderWidth, g_renderHeight);
    SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_BILINEAR);

    GameState* g_currentState = nullptr;
    // Starting state
    if (FileExists("config.txt"))
    {
        g_currentState = new TestState();
    }
    else
    {
        g_currentState = new ConfigState();
    }

    // Main loop
    while (!WindowShouldClose()) {
        float scale = std::min((float)GetScreenWidth()/g_renderWidth, (float)GetScreenHeight()/g_renderHeight);

         // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = { 0 };
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (g_renderWidth*scale))*0.5f)/scale;
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (g_renderHeight*scale))*0.5f)/scale;
        virtualMouse = Vector2Clamp(virtualMouse, Vector2{ 0, 0 }, Vector2{ (float)g_renderWidth, (float)g_renderHeight });

        // Apply the same transformation as the virtual mouse to the real mouse (i.e. to work with raygui)
        SetMouseOffset(-(GetScreenWidth() - (g_renderWidth*scale))*0.5f, -(GetScreenHeight() - (g_renderHeight*scale))*0.5f);
        SetMouseScale(1/scale, 1/scale);

        // Update
        g_currentState->update();

        BeginTextureMode(renderTarget);
        ClearBackground(BLACK);
        DrawDebugText();

        //Draw
        g_currentState->draw();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            renderTarget.texture,
            Rectangle{
                0.0f,
                0.0f,
                (float)renderTarget.texture.width,
                (float)-renderTarget.texture.height
            },
            Rectangle{
                (GetScreenWidth() - ((float)g_renderWidth*scale))*0.5f,
                (GetScreenHeight() - ((float)g_renderHeight*scale))*0.5f,
                (float)g_renderWidth*scale,
                (float)g_renderHeight*scale
            },
            Vector2{ 0, 0 },
            0.0f,
            WHITE
        );
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void setupWindow()
{
    InitWindow(1600, 900, "Peril");

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    SetWindowMinSize(320, 240);
    // Icon
    Image icon = LoadImage((g_resourcePath + "icon.png").c_str());
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void DrawDebugText()
{
    std::string fpsString = "FPS: " + std::to_string(GetFPS());
    DrawText(fpsString.c_str(), 10, 10, 20, WHITE);
}