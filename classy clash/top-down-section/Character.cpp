#include "Character.h"
#include "raymath.h"


Character::Character(int window_width, int window_height) : 
    window_width(window_width),
    window_height(window_height)
{
    width = texture.width/max_frames;
    height = texture.height;
}


void Character::tick(float delta_time)
{
    if (!get_alive()) return;
    // last_world_position = world_position;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x = +1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    Base_Character::tick(delta_time);


    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

    if (right_left > 0.f)
    {
        origin = {0.f, weapon.height*scale};
        offset = {35.f, 55.f};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
        // rotation = 35.f;
        weapon_collision_rectangle = {
            get_screen_position().x + offset.x,
            get_screen_position().y + offset.y - weapon.height*scale,
            weapon.width * scale,
            weapon.height * scale
        };
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
        weapon_collision_rectangle = {
            get_screen_position().x + offset.x - weapon.width * scale,
            get_screen_position().y + offset.y - weapon.height*scale,
            weapon.width * scale,
            weapon.height * scale
        };
    }
    
    // draw the sword
    Rectangle source{0.f,0.f, static_cast<float>(weapon.width)*right_left, static_cast<float>(weapon.height)};
    Rectangle dest{get_screen_position().x + offset.x, get_screen_position().y + offset.y, weapon.width*scale, weapon.height*scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

 
}

Vector2 Character::get_screen_position()
{
    return Vector2{static_cast<float>(window_width) / 2.0f - scale * (0.5f * width),
                    static_cast<float>(window_height) / 2.0f - scale * (0.5f * height)};
}


void Character::take_damage(float damage)
{
    health -= damage;
    if(health <= 0.f)
    {
        set_alive(false);
    }
}