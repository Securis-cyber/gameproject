#include "raylib.h"
#include "raymath.h"

class Character
{
public:
private:
};


int main(){


    const int window_dimensions[2]{384,384};
    InitWindow(window_dimensions[0],window_dimensions[1],"Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    Vector2 map_position{0.0,0.0};
    float speed{4.0};


    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

    Vector2 knight_position{ 
        (float)window_dimensions[0]/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f), 
        (float)window_dimensions[1]/2.0f - 4.0f * (0.5f * (float)knight.height)};

    // 1 = facing right, -1 = facing left
    float right_left{1.f};

    float running_time{};
    int frame{};
    const int max_frames{6};
    const float update_time{1.f/12.f};

    SetTargetFPS(60);  

    while (!WindowShouldClose())
    {

        float dT = GetFrameTime();

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
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }
        
        
        // update animation frame
        running_time += dT;
        if (running_time >= update_time)
        {
            frame++;
            running_time = 0.f;
            if (frame > max_frames) frame = 0;
            
        }
        // top left corner
        
        Rectangle source_rectangle
        {
            frame * (float)knight.width/6.f, // x
            0.f, // y
            right_left * (float)knight.width/6.f, // width
            (float)knight.height}; // height

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