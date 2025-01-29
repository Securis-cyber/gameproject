
#include "raylib.h"
#include "raymath.h"
#include "Base_Character.h"

Base_Character::Base_Character()
{

}

void Base_Character::undo_movement()
{
    world_position = last_world_position;
}

Rectangle Base_Character::get_collision_rectangle(){
    return Rectangle{
        get_screen_position().x,
        get_screen_position().y,
        width*scale,
        height*scale
    };
};

void Base_Character::tick(float delta_time)
{
    last_world_position = world_position;

    // update animation frame
    running_time += delta_time;
    if (running_time >= update_time)
    {
        frame++;
        running_time = 0.f;
        if (frame > max_frames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set position = position + direction
        world_position = Vector2Add(world_position, Vector2Scale(Vector2Normalize(velocity), speed));

        velocity.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // movement, character doesnt move, map does
    Rectangle source_rectangle{
        frame * width,      // x
        0.f,                                     // y
        right_left * width, // width
        height};                  // height

    Rectangle destination_rectangle{
        get_screen_position().x,
        get_screen_position().y,
        scale * width,
        scale * height};

    DrawTexturePro(texture, source_rectangle, destination_rectangle, Vector2{}, 0.f, WHITE);
}
