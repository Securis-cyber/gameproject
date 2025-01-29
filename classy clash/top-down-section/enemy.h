#include "raylib.h"
#include "Base_Character.h"
#include "Character.h"

class Enemy : public Base_Character
{
public:
    Enemy(Vector2 position, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float delta_time) override;
    void set_target(Character* character) {target = character;}
    virtual Vector2 get_screen_position() override;
private:
    Character* target;
    float damage_per_second{10.f};
    float radius{25.f};
};