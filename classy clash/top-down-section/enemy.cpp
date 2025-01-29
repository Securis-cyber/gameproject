#include "enemy.h"
#include "raymath.h"
#include "raylib.h"


Enemy::Enemy(Vector2 position, Texture2D idle_texture, Texture2D run_texture)
{
    world_position = position;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / max_frames;
    height = texture.height;
    speed = 2.5f;
}

void Enemy::tick(float delta_time) 
{
    if (!get_alive()) return;
    // get to target vector
    velocity = Vector2Subtract(target->get_screen_position(), get_screen_position());
    Base_Character::tick(delta_time);

    if (CheckCollisionRecs(target->get_collision_rectangle(), get_collision_rectangle()))
    {
        target->take_damage(damage_per_second * delta_time);
    }
    
}

Vector2 Enemy::get_screen_position()
{
    return Vector2Subtract(world_position, target->get_world_position());
}
