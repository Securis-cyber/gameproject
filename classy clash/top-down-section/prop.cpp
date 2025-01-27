#include "raylib.h"
#include "prop.h"
#include "raymath.h"


Prop::Prop(Vector2 pos, Texture2D tex) : 
world_position(pos), texture(tex)
{

};

void Prop::Render(Vector2 knight_position)
{
    // sticks the rock to the map and moves it according to player movement
    Vector2 screen_position{Vector2Subtract(world_position, knight_position) };
    DrawTextureEx(texture, screen_position, 0.f, scale, WHITE);
}

Rectangle Prop::get_collision_rectangle(Vector2 knight_position)
{
     Vector2 screen_position{Vector2Subtract(world_position, knight_position) };
     return Rectangle{
        screen_position.x,
        screen_position.y,
        texture.width*scale,
        texture.height*scale
     };

}