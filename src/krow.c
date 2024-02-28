#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "krow.h"

#define TITLE "Krow"
#define WIDTH       1200
#define HEIGHT      800

#define FILE_MAX    1024000

#define FONT        GetFontDefault()
#define FONT_SIZE   40
#define SPACING     33

#define KROWGRAY    CLITERAL(Color){ 35, 35, 35, 86 }

#define SHIFT       340
#define BACKSPACE   259
#define SPACE       320
#define ENTER       257
#define FULLSCREEN  300
#define TAB         258
#define F5          294

#define RIGHT_ARROW 262
#define LEFT_ARROW  263
#define DOWN_ARROW  264
#define UP_ARROW    265

#define CURSOR      124

static int LoadBuffer(char* buf, char* fileBuffer);
static void DrawBuffer(char* buf, int len, int startX, int startY);
static void DrawCursor(char* buf, int x, int y);

void OpenFile(const char* path, char* fileBuffer) {
    // On each key press, we will insert the char (if it is in range defined below)
    // into our buffer to be printed each frame.
    char buffer[FILE_MAX];

    int len = LoadBuffer(buffer, fileBuffer);

    // posX and posY keep track of the cursor locally.
    // This stops us from deleting characters from an empty line.
    int posX = len * SPACING;
    int posY = 0;

    // startX and startY define from which coordinate we should begin printing the text buffer.
    // They are only affected by our scroll logic.
    int startX = 0;
    int startY = 0;

    InitWindow(WIDTH, HEIGHT, TITLE);
    ClearBackground(KROWGRAY);

    while (!WindowShouldClose()) {
        EnableEventWaiting();
        BeginDrawing();

        int charKey = GetCharPressed();
        int controlKey = GetKeyPressed();

        if(controlKey == 17) {
            fprintf(stderr, "HIIIIIII");
        }

        Vector2 scroll = GetMouseWheelMoveV();

        // Controls window scrolling
        if(scroll.x > 0)
            startX -= SPACING;
        else if(scroll.x < 0)
            startX += SPACING;
        else if(scroll.y > 0)
            startY -= FONT_SIZE;
        else if(scroll.y < 0)
            startY += FONT_SIZE;

        // Don't allow scrolling past 0,0 (Nothing can go there)
        if(startX > 0) startX = 0;
        if(startY > 0) startY = 0;

        // Printable ASCII range
        if(charKey >= 32 && charKey <= 255) {
            posX += SPACING;
            buffer[len] = charKey;
            len++;
        } else if(IsKeyPressed(BACKSPACE)) {
            if(posX > 0) {
                len--;
                buffer[len] = '\0';
                posX -= SPACING;
            } else if(posX == 0 && posY >= FONT_SIZE) {
                len--;
                buffer[len] = '\0';
                posY -= FONT_SIZE;
                posX = len * SPACING;
                int idx = 0;
            }
        } else if(IsKeyPressed(ENTER)) {
            posX = 0;
            posY += FONT_SIZE;
            buffer[len] = '\n';
            len++;
        } else if(IsKeyPressed(FULLSCREEN)) {
            Vector2 pos = GetWindowPosition();
            if(pos.x == 0 && pos.y == 0)
                SetWindowSize(WIDTH, HEIGHT);
            else 
                ToggleFullscreen();
        } else if(IsKeyPressed(F5) && strlen(path) > 0) {
            SaveFileText(path, buffer);
        }

        DrawBuffer(buffer, len, startX, startY);
        EndDrawing();
    }

    CloseWindow();
}

// Loads the buffer with text from fileBuffer and returns the new length of the local buffer.
static int LoadBuffer(char* buf, char* fileBuffer) {
    int idx = 0;

    while(fileBuffer[idx] != '\0') {
        buf[idx] = fileBuffer[idx];
        idx++;
    }

    return idx;
}

// Clears the background, then begins drawing from our startX and startY coordinates
static void DrawBuffer(char* buf, int len, int startX, int startY) {
    ClearBackground(KROWGRAY);
    Vector2 pos = { startX, startY };
    for(int i = 0; i < len; ++i) {
        if(buf[i] >= 32 && buf[i] != '\n') {
            DrawTextCodepoint(FONT, buf[i], pos, FONT_SIZE, WHITE);
            pos.x += SPACING;
        }
        else if(buf[i] == '\n') {
            pos.x = startX;
            pos.y += FONT_SIZE;
        }
    }

    DrawCursor(buf, pos.x, pos.y);
}

// Draws a pipe character right where the next character should be printed
static void DrawCursor(char* buf, int x, int y) {
    DrawTextCodepoint(FONT, CURSOR, (Vector2){ x, y }, FONT_SIZE, WHITE); 
}
