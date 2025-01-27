#include "raylib.h"

class Prop
{
    public:
        Prop(Vector2 pos, Texture2D tex);
        void Render(Vector2 knight_position);
        Rectangle get_collision_rectangle(Vector2 knight_position);
    private:
        Texture2D texture{};
        Vector2 world_position{};
        float scale{4.0f};
};