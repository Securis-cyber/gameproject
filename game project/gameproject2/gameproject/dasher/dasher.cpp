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
    animation_data nebula_one{
        {0.0,0.0,nebula.width/8,nebula.height/8}, // Rectangle rec
        {window_dimensions[0], window_dimensions[1] - nebula.height/8}, // Vector position
        0, // frame
        1.0/12, // update time
        0.0}; // running time

    
    // nebula x velocity pixels/sec
    animation_data nebula_two{
        {0.0,0.0,nebula.width/8,nebula.height/8}, // Rectangle rec
        {window_dimensions[0] + 300, window_dimensions[1] - nebula.height/8}, // Vector position
        0, // frame
        1.0/16, // update time
        0.0}; // running time

    animation_data nebulae[2]{nebula_one, nebula_two};
    
 
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
        

        nebulae[0].running_time += dT;
        nebulae[1].running_time += dT;
        // update nebula animation frame
        nebula_animation(nebulae[0]);
        nebula_animation(nebulae[1]);
        // if(nebula_two.running_time>= nebula_two.update_time)
        // {
        //     nebula_two.rectangle.x = nebula_two.frame*nebula_two.rectangle.width; 
        //     nebula_two.frame++;
        //     if (nebula_two.frame>7)
        //         {
        //             nebula_two.frame = 0;
        //         }
        //     nebula_two.running_time = 0;
        // }

        // draw nebula
        DrawTextureRec(nebula, nebulae[0].rectangle, nebulae[0].position, WHITE);
        // draw nebula2
        DrawTextureRec(nebula, nebulae[1].rectangle, nebulae[1].position, RED);
        // draw scarfyt
        DrawTextureRec(scarfy, scarfy_data.rectangle, scarfy_data.position, WHITE);
        
        // jump check
        if(IsKeyPressed(KEY_SPACE) && !is_in_air)
        {
            velocity += jump_velocity;
        }

        nebulae[0].position.x += nebula_velocity * dT;

        nebulae[1].position.x += nebula_velocity * dT;

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
