#include "raylib.h"
#include "raymath.h"

int main(){


    const int window_dimensions[2]{384,384};
    InitWindow(window_dimensions[0],window_dimensions[1],"Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    Vector2 map_position{0.0,0.0};
    float speed{4.0};


    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knight_position{ 
        (float)window_dimensions[0]/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f), 
        (float)window_dimensions[1]/2.0f - 4.0f * (0.5f * (float)knight.height)};

    // 1 = facing right, -1 = facing left
    float right_left{1.f};

    SetTargetFPS(60);  

    while (!WindowShouldClose())
    {

        // float dt = GetFrameTime();

         // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextureEx(map, map_position,0.0,4.0,WHITE);
        
        // movement, character doesnt move, map does
        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x =+ 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            // set position = position - direction
            map_position = Vector2Subtract(map_position, Vector2Scale(Vector2Normalize(direction), speed));
            
            direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
        }
        // top left corner
        
        Rectangle source_rectangle{0.f, 0.f, right_left * (float)knight.width/6.f, (float)knight.height};
        Rectangle destination_rectangle
        {
            knight_position.x, 
            knight_position.y, 
            4.0f * (float)knight.width/6.0f, 
            4.0f * (float)knight.height
        };




        DrawTexturePro(knight, source_rectangle, destination_rectangle, Vector2{},0.f,WHITE);

        EndDrawing();

    }
    CloseWindow();
}