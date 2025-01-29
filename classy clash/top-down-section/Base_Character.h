#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class Base_Character
{
public:
    Base_Character();
    void undo_movement();
    Rectangle get_collision_rectangle();
    Vector2 get_world_position() { return world_position; }
    virtual void tick(float delta_time);
    virtual Vector2 get_screen_position() = 0;
    bool get_alive(){ return alive;}
    void set_alive(bool is_alive) { alive = is_alive;}
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screen_position{};
    Vector2 world_position{};
    Vector2 last_world_position{};
    float right_left{1.f};
    float running_time{};
    int frame{};
    const int max_frames{6};
    const float update_time{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif