#include "raylib.h"

int main(void)
{
    // Window initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Unboxing - 2D Raylib");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
            ClearBackground(DARKGRAY);
            
            // Draw a simple rectangle
            DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 100, 100, RAYWHITE);
            
            // Draw some text
            DrawText("Hello, Unboxing!", 10, 10, 20, LIGHTGRAY);
            DrawText("ESC to exit", 10, 40, 16, GRAY);
            
            // Draw FPS
            DrawFPS(screenWidth - 80, 10);
            
        EndDrawing();
    }
    
    // Clean up
    CloseWindow();
    
    return 0;
}
