#include <common_main.h>

#include <states/config.h>

void ConfigState::update()
{
    // Get text input
    int key = GetCharPressed();
    if (IsKeyPressed(KEY_ENTER))
    {
        g_resourcePath = textInput;
    }
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (textInput.length() > 0)
        {
            textInput.pop_back();
        }
    }
    else if ((key >= 32) && (key <= 125) && (MeasureText(textInput.c_str(), 40) < (textInputBoxWidth-30)))
        textInput += (char)key;
}

void ConfigState::draw()
{
    // Draw Centered info message
    DrawText(info_message.c_str(), (g_renderWidth - MeasureText(info_message.c_str(), 25))/2, (g_renderHeight - 125)/2, 25, WHITE);

    // Draw text input box
    DrawRectangle((int)textInputBox.x, (int)textInputBox.y, (int)textInputBox.width, (int)textInputBox.height, LIGHTGRAY);
    DrawText(textInput.c_str(), textInputBox.x + 5, textInputBox.y + 8, 40, RED);

    // Draw "current working directory" under the box centered
    char* message2 = "Current working directory:";
    DrawText(message2, (g_renderWidth - MeasureText(message2, 15))/2, textInputBox.y + 75, 15, WHITE);

    // Draw current working directory under box centered
    DrawText(GetWorkingDirectory(), (g_renderWidth - MeasureText(GetWorkingDirectory(), 15))/2, textInputBox.y + 100, 15, WHITE);
}