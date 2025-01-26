#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{

    const int window_dimensions[2]{384, 384};
    const float map_scale{4.0};
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    Vector2 map_position{0.0, 0.0};
    

    Character knight{window_dimensions[0],window_dimensions[1]};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        map_position = Vector2Scale(knight.get_world_position(), -1.f);
        ClearBackground(WHITE);
        DrawTextureEx(map, map_position, 0.0, map_scale, WHITE);
        knight.tick(GetFrameTime());
        // check map boundaries
        if (knight.get_world_position().x < 0.f ||
            knight.get_world_position().y < 0.f ||
            knight.get_world_position().x + window_dimensions[0] > map.width * map_scale ||
            knight.get_world_position().y + window_dimensions[1] > map.height * map_scale)
            {
                knight.undo_movement();
            }

        EndDrawing();
    }
    CloseWindow();
}