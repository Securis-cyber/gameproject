#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
int main()
{

    const int window_dimensions[2]{384, 384};
    const float map_scale{4.0};
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    Vector2 map_position{0.0, 0.0};
    

    Character knight{window_dimensions[0],window_dimensions[1]};

    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/log.png")}
    };


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        map_position = Vector2Scale(knight.get_world_position(), -1.f);
        ClearBackground(WHITE);
        DrawTextureEx(map, map_position, 0.0, map_scale, WHITE);
        

        // draw the props
        for(auto prop : props){
            prop.Render(knight.get_world_position());
        }
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