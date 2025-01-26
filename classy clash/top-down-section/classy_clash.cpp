#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{

    const int window_dimensions[2]{384, 384};
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    Vector2 map_position{0.0, 0.0};

    Character knight;
    knight.set_screen_position(window_dimensions[0],window_dimensions[1]);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        map_position = Vector2Scale(knight.get_world_position(), -1.f);
        ClearBackground(WHITE);
        DrawTextureEx(map, map_position, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}