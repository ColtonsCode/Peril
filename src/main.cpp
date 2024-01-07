#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <string>
#include <algorithm>

#include <common_main.h>
#include <states/config.h>
#include <states/test_state.h>

void setupWindow();
void DrawDebugText();

// GLOBAL VARIABLES
std::string g_resourcePath = "../../resources/";
StateManager g_stateManager;

int main() {

    setupWindow();

    RenderTexture2D renderTarget = LoadRenderTexture(g_renderWidth, g_renderHeight);
    SetTextureFilter(renderTarget.texture, TEXTURE_FILTER_BILINEAR);

    // Starting state
    if (FileExists("config.txt"))
    {
        g_stateManager.pushState(new TestState());
    }
    else
    {
        g_stateManager.pushState(new ConfigState());
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
        g_stateManager.updateCurrentState();

        BeginTextureMode(renderTarget);
        ClearBackground(BLACK);
        DrawDebugText();

        //Draw
        g_stateManager.drawCurrentState();
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