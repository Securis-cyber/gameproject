#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 get_world_position() { return world_position; }
    void set_screen_position(int window_width, int window_height);
    void tick(float delta_time);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screen_position{};
    Vector2 world_position{};
    float right_left{1.f};
    float running_time{};
    int frame{};
    const int max_frames{6};
    const float update_time{1.f / 12.f};
    const float speed{4.f};
};

void Character::set_screen_position(int window_width, int window_height)
{
    screen_position = {(float)window_width / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
                       (float)window_height / 2.0f - 4.0f * (0.5f * (float)texture.height)};
};

void Character::tick(float delta_time)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x = +1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set position = position + direction
        world_position = Vector2Add(world_position, Vector2Scale(Vector2Normalize(direction), speed));

        direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    // update animation frame
    running_time += delta_time;
    if (running_time >= update_time)
    {
        frame++;
        running_time = 0.f;
        if (frame > max_frames)
            frame = 0;
    }
    // movement, character doesnt move, map does
    Rectangle source_rectangle{
        frame * (float)texture.width / 6.f,      // x
        0.f,                                     // y
        right_left * (float)texture.width / 6.f, // width
        (float)texture.height};                  // height

    Rectangle destination_rectangle{
        screen_position.x,
        screen_position.y,
        4.0f * (float)texture.width / 6.0f,
        4.0f * (float)texture.height};

    DrawTexturePro(texture, source_rectangle, destination_rectangle, Vector2{}, 0.f, WHITE);
};

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