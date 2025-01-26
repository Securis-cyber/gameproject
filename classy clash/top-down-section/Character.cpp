#include "Character.h"
#include "raymath.h"


Character::Character(int window_width, int window_height)
{
    width = texture.width/max_frames;
    height = texture.height;
    screen_position = {(float)window_width / 2.0f - 4.0f * (0.5f * width),
                       (float)window_height / 2.0f - 4.0f * (0.5f * height)};
}

void Character::undo_movement()
{
    world_position = last_world_position;
}


// void Character::set_screen_position(int window_width, int window_height)
// {
//     screen_position = {(float)window_width / 2.0f - 4.0f * (0.5f * width),
//                        (float)window_height / 2.0f - 4.0f * (0.5f * height)};
// };

void Character::tick(float delta_time)
{
    last_world_position = world_position;
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
        frame * width,      // x
        0.f,                                     // y
        right_left * width, // width
        height};                  // height

    Rectangle destination_rectangle{
        screen_position.x,
        screen_position.y,
        4.0f * width,
        4.0f * height};

    DrawTexturePro(texture, source_rectangle, destination_rectangle, Vector2{}, 0.f, WHITE);
};