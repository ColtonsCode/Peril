#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <string>

void setupWindow();
void DrawDebugText();

const std::string resourcePath = "../../resources/";

struct Player
{
    int x;
    int y;
};

int main() {
    setupWindow();

    Texture2D playerTexture = LoadTexture((resourcePath + "placeholder_player.png").c_str());
    Player player = {};
    player.x = GetScreenWidth() / 2;
    player.y = GetScreenHeight() / 2;
    

    // Main loop
    while (!WindowShouldClose()) {

        // update
        if (IsKeyDown(KEY_W)) {
            player.y -= 5;
        }
        if (IsKeyDown(KEY_S)) {
            player.y += 5;
        }
        if (IsKeyDown(KEY_A)) {
            player.x -= 5;
        }
        if (IsKeyDown(KEY_D)) {
            player.x += 5;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(playerTexture, player.x - (playerTexture.width / 2), player.y - (playerTexture.height / 2), WHITE);

        DrawDebugText();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void setupWindow()
{
    InitWindow(1600, 900, "Peril");

    SetTargetFPS(60);
    // Icon
    Image icon = LoadImage((resourcePath + "icon.png").c_str());
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void DrawDebugText()
{
    std::string fpsString = "FPS: " + std::to_string(GetFPS());
    DrawText(fpsString.c_str(), 10, 10, 40, WHITE);
}