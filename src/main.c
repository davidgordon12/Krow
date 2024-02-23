#include <stdio.h>
#include "raylib.h"

#define TITLE "Krow"
#define WIDTH      1200
#define HEIGHT     800

#define FONT GetFontDefault()
#define FONT_SIZE  40
#define SPACING    33

#define KROWGRAY   CLITERAL(Color){ 35, 35, 35, 86 }

#define SHIFT      340
#define BACKSPACE  259
#define SPACE      320
#define ENTER      257
#define FULLSCREEN 300
#define TAB        258

#define CURSOR     124

static void DrawBuffer(int* buf, int len);
static void DrawCursor(int* buf, int x, int y);

int main(void) {
    int buffer[1024000];
    int posX = 0;
    int posY = 0;
    int len = 0;

    InitWindow(WIDTH, HEIGHT, TITLE);
    ClearBackground(KROWGRAY);

    while (!WindowShouldClose()) {
        EnableEventWaiting();
        BeginDrawing();

        int charKey = GetKeyPressed();

        if(charKey != 0) printf("|%d| ", charKey);

        if(charKey >= 32 && charKey <= 255) {
            Vector2 pos = { posX, posY };
            posX += SPACING;
            buffer[len] = charKey;
            len++;
        } else {
            switch (charKey) {
            case BACKSPACE:
                if(posX > 0) {
                    len--;
                    posX -= SPACING;
                } else if(posX == 0 && posY >= FONT_SIZE) {
                    len--;
                    posY -= FONT_SIZE;
                    posX = len * SPACING;
                    int idx = 0;
                }
                break;
            case ENTER:
                posX = 0;
                posY += FONT_SIZE;
                buffer[len] = '\r';
                len++;
                break;
            case FULLSCREEN:
                SetWindowSize(1920, 1080);
                    
    int i = 0;
    while(i < len)
    {
        fprintf(stderr, "%c", buffer[i]);
        i++;
    }
                break;
            }
        }

        DrawBuffer(buffer, len);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

static void DrawBuffer(int* buf, int len) {
    ClearBackground(KROWGRAY);
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
    DrawCursor(buf, pos.x, pos.y);
}

static void DrawCursor(int* buf, int x, int y) {
       DrawTextCodepoint(FONT, CURSOR, (Vector2){ x, y }, FONT_SIZE, PURPLE); 
}
