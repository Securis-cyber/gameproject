#include "raylib.h"

struct animation_data
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float update_time;
    float running_time;

};

void nebula_animation(animation_data &nebula_object);

int main()
{
    // window dimensions
    int window_dimensions[2];
    window_dimensions[0] = 512;
    window_dimensions[1] = 380;\

    InitWindow(window_dimensions[0], window_dimensions[1], "Dapper Dasher");
    
    // acceleration due to gravity (pixels/sec)/sec
    const int gravity{1000};

    int velocity{ 0 }; // pixels/frame

     // jumping logic
    bool is_in_air{};
    const int jump_velocity{-600}; // pixels per second
    int nebula_velocity{-200};


    // initialise scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    animation_data scarfy_data{
        {0,0,scarfy.width/6,scarfy.height}, // Rectangle
        {window_dimensions[0]/2 - scarfy_data.rectangle.width/2, window_dimensions[1] - scarfy_data.rectangle.height}, // Vector2 Position
        0, // Frame
        1.0/12, // Update time
        0.0}; // Running time

    // initialise nebula 
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int number_of_nebulae{3};
    animation_data nebulae[number_of_nebulae]{};
    
    for (int i = 0; i < number_of_nebulae; i++)
    {
        nebulae[i].rectangle.x = 0.0;
        nebulae[i].rectangle.y = 0.0;
        nebulae[i].rectangle.width = nebula.width/8;
        nebulae[i].rectangle.height = nebula.height/8;
        nebulae[i].position.x = window_dimensions[0] + i*300;
        nebulae[i].position.y = window_dimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].running_time = 0.0;
        nebulae[i].update_time = 1.0/16.0;
    }



    SetTargetFPS(60);
    while (!WindowShouldClose()){

        // delta time, time since last frame
        float dT{GetFrameTime()};
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        
        // game logic begins
        
        if(scarfy_data.position.y >= window_dimensions[1] - scarfy_data.rectangle.height)
        {
            // rectangle on ground
            velocity = 0;
            is_in_air = false;
        }
        else
        {
            // rectangle in air
            velocity += gravity * dT;
            is_in_air = true;
        }


        // update scarfy animation frame
        scarfy_data.running_time += dT;
        
        if(scarfy_data.running_time>= scarfy_data.update_time && !is_in_air)
        {
            scarfy_data.rectangle.x = scarfy_data.frame*scarfy_data.rectangle.width;
            scarfy_data.frame++;
            if (scarfy_data.frame>5)
                {
                    scarfy_data.frame = 0;
                }
            scarfy_data.running_time = 0;
        }
        
        for(int i = 0; i<number_of_nebulae; i++)
        {
            nebulae[i].running_time += dT;
            nebula_animation(nebulae[i]);
            DrawTextureRec(nebula, nebulae[i].rectangle, nebulae[i].position, WHITE);
            nebulae[i].position.x += nebula_velocity * dT;
        }


        // draw scarfy
        DrawTextureRec(scarfy, scarfy_data.rectangle, scarfy_data.position, WHITE);
        
        // jump check
        if(IsKeyPressed(KEY_SPACE) && !is_in_air)
        {
            velocity += jump_velocity;
        }

        scarfy_data.position.y += velocity * dT;
        // game logic ends
        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

void nebula_animation(animation_data &obstacle)
{
    if (obstacle.running_time >= obstacle.update_time)
    {
        obstacle.rectangle.x = obstacle.frame * obstacle.rectangle.width;
        obstacle.frame++;
        if (obstacle.frame > 7)
        {
            obstacle.frame = 0;
        }
        obstacle.running_time = 0;
    }
}
