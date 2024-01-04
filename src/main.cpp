#include <raylib.h>
#include <string>

std::string resourcePath = "../../resources/";


int main() {
    InitWindow(800, 600, "Peril");

    // Icon
    Image icon = LoadImage((resourcePath + "icon.png").c_str());
    SetWindowIcon(icon);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World", 10, 10, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}