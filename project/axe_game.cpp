#include "raylib.h"
// is this working?


int main()
{
    int width{1350};
    int height{1200};
    InitWindow(width, height, "WindowName");


    // circle coordinates
    int circle_x{675};
    int circle_y{600};
    

    SetTargetFPS(60);
    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLUE);

        // game logic begins
        DrawCircle(circle_x, circle_y, 25.0, RED);
        if (IsKeyDown(KEY_D) && circle_x < width)
        {
            circle_x += 10;
        }
        if (IsKeyDown(KEY_A) && circle_x > 0)
        {
            circle_x -= 10;
        }
        if (IsKeyDown(KEY_S) && circle_y < height)
        {
            circle_y += 10;
        }
        if (IsKeyDown(KEY_W) && circle_y > 0)
        {
            circle_y -= 10;
        }
        // game logic ends
        EndDrawing();
    }

} 