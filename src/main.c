#include <stdio.h>
#include "raylib.h"

#define FONT_SIZE 40
#define SPACING 33

#define KROWGRAY   CLITERAL(Color){ 35, 35, 35, 86 }

#define SHIFT 340
#define BACKSPACE  259
#define SPACE 320
#define ENTER 257
#define FULLSCREEN 300

int main(void)
{
    int width = 0;
    int posX = 0;
    int posY = 0;
    InitWindow(1200, 800, "Krow");
    Font f = GetFontDefault();
    ClearBackground(KROWGRAY);

    while (!WindowShouldClose())
    {
        EnableEventWaiting();
        BeginDrawing();

        int charKey = GetKeyPressed();

        if(charKey != 0) printf("|%d| ", charKey);

        if(charKey != 0 && charKey != SHIFT && charKey != BACKSPACE && charKey != ENTER) {
            Vector2 pos = { posX, posY };
            DrawTextCodepoint(f, charKey, pos, FONT_SIZE, PURPLE);
            posX += SPACING;
            width++;
        } else if(charKey == BACKSPACE && posX >= FONT_SIZE) {
            ClearBackground(KROWGRAY);
        } else if(charKey == ENTER) {
            posX = 0;
            posY += FONT_SIZE;
        } else if(charKey == FULLSCREEN) {
            // TODO: Get this working
            // SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
