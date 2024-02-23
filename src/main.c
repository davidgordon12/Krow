#include <stdio.h>
#include "raylib.h"

#define TITLE "Krow"
#define WIDTH 1200
#define HEIGHT 800

#define FONT GetFontDefault()
#define FONT_SIZE 40
#define SPACING 33

#define KROWGRAY   CLITERAL(Color){ 35, 35, 35, 86 }

#define SHIFT      340
#define BACKSPACE  259
#define SPACE      320
#define ENTER      257
#define FULLSCREEN 300
#define TAB        258

static void DrawBuffer(int* buf, int len);
static int GetLineLength(int* buf);

int main(void)
{
    int width = 0;
    int posX = 0;
    int posY = 0;
    int len = 0;
    InitWindow(WIDTH, HEIGHT, TITLE);
    Font f = GetFontDefault();
    ClearBackground(KROWGRAY);
    int buffer[1024000];
    while (!WindowShouldClose())
    {
        EnableEventWaiting();
        BeginDrawing();

        int charKey = GetKeyPressed();

        if(charKey != 0) printf("|%d| ", charKey);

        if(charKey >= 32 && charKey <= 255) {
            Vector2 pos = { posX, posY };
            DrawTextCodepoint(f, charKey, pos, FONT_SIZE, PURPLE);
            posX += SPACING;
            buffer[len] = charKey;
            width++;
            len++;
        } else {
            switch (charKey) {
            case BACKSPACE:
                if(posX > 0) {
                    ClearBackground(KROWGRAY);
                    len--;
                    DrawBuffer(buffer, len);
                    posX -= SPACING;
                } else if(posX == 0 && posY >= FONT_SIZE) {
                    ClearBackground(KROWGRAY);
                    len--;
                    DrawBuffer(buffer, len);
                    posY -= FONT_SIZE;
                    // posX = amount between the last two newLines, or if its the first line,
                    // 0 -> first newLine
                    // len should be set according to the new posX
                    // this way we can delete things in previous lines
                }
                break;
            case ENTER:
                posX = 0;
                posY += FONT_SIZE;
                buffer[len] = '\r';
                len++;
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void DrawBuffer(int* buf, int len) {
    Vector2 pos = { 0, 0 };
    for(int i = 0; i < len; ++i) {
        if(buf[i] >= 32 && buf[i] <= 255 && buf[i] != '\n') {
            DrawTextCodepoint(FONT, buf[i], pos, FONT_SIZE, PURPLE);
            pos.x += SPACING;
        }
        else if(buf[i] == '\r') {
            pos.x = 0;
            pos.y += FONT_SIZE;
        }
    }
}

int GetLineLength(int* buf) {
    return 0;
}
