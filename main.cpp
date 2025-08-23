// not my code, it's for testing Makefile

#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "raylib works!");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}