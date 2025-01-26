#include "raylib.h"

class Character
{
public:
    Character();
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
    float width{};
    float height{};
};
