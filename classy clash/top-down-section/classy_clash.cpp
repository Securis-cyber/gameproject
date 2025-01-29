#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

int main()
{

    const int window_dimensions[2]{384, 384};
    const float map_scale{4.0};
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    Vector2 map_position{0.0, 0.0};

    Character knight{window_dimensions[0], window_dimensions[1]};
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/log.png")}};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->set_target(&knight);
    }

    goblin.set_target(&knight);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // start drawing
        BeginDrawing();
        map_position = Vector2Scale(knight.get_world_position(), -1.f);
        ClearBackground(WHITE);
        DrawTextureEx(map, map_position, 0.0, map_scale, WHITE);

        // draw the props
        for (auto prop : props)
        {
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

        // check prop collisions
        for (auto prop : props)
        {

            if (CheckCollisionRecs(prop.get_collision_rectangle(knight.get_world_position()), knight.get_collision_rectangle()))
            {
                knight.undo_movement();
            }
        }

        if (!knight.get_alive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knights_health = "Health: ";
            knights_health.append(std::to_string(knight.get_health()), 0, 5);
            DrawText(knights_health.c_str(), 55.f, 45.f, 40, RED);
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // check if mouse button is clicked
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // check if weapon hit box connects with enemy
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->get_collision_rectangle(), knight.get_weapon_collision_rectangle()))
                {
                    enemy->set_alive(false);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
}