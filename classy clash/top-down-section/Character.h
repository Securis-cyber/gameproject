#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "Base_Character.h"
class Character : public Base_Character
{
public:
    Character(int window_width, int window_height);
    virtual void tick(float delta_time) override;
    virtual Vector2 get_screen_position() override;
    Rectangle get_weapon_collision_rectangle() { return weapon_collision_rectangle;}
    float get_health() const {return health;}
    void take_damage(float damage);
private:
    int window_width{};
    int window_height{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weapon_collision_rectangle{};
    float health{100.f};
    
};

#endif