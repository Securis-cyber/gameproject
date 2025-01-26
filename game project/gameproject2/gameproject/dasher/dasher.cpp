#include "raylib.h"

struct animation_data
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float update_time;
    float running_time;

};

bool is_on_ground(animation_data data, int window_height)
{
    return data.position.y >= window_height - data.rectangle.height;
}

animation_data update_animation_data(animation_data data, float delta_time, int maximum_frame)
{
    data.running_time += delta_time;
    if (data.running_time >= data.update_time)
    {
        data.running_time = 0.0;
        data.rectangle.x = data.frame*data.rectangle.width;
        data.frame++;
        if(data.frame > maximum_frame)
        {
            data.frame = 0;
        }
    }
    return data;
}


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


    // background initialisation 
    Texture2D array_of_backgrounds[3]{};
    array_of_backgrounds[0] = LoadTexture("textures/far-buildings.png");
    array_of_backgrounds[1] = LoadTexture("textures/back-buildings.png");
    array_of_backgrounds[2] = LoadTexture("textures/foreground.png");
    float background_x_positions[3]{};
    int background_velocity[3]{20, 40, 80};
    int number_of_backgrounds{3};
    
    
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
    const int number_of_nebulae{4};
    animation_data nebulae[number_of_nebulae]{};

    // create_nebulae(number_of_nebulae, nebulae, nebula, window_dimensions);
     for (int i = 0; i < number_of_nebulae; i++)
        {
            nebulae[i].rectangle.x = 0.0;
            nebulae[i].rectangle.y = 0.0;
            nebulae[i].rectangle.width = nebula.width / 8;
            nebulae[i].rectangle.height = nebula.height / 8;
            nebulae[i].position.x = window_dimensions[0] + i * 300;
            nebulae[i].position.y = window_dimensions[1] - nebula.height / 8;
            nebulae[i].frame = 0;
            nebulae[i].running_time = 0.0;
            nebulae[i].update_time = 1.0 / 16.0;
        }

    float finish_line{ nebulae[number_of_nebulae - 1].position.x};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        // delta time, time since last frame
        float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        
        // scroll background
        for (int i = 0; i<3; i++)
        {
            background_x_positions[i] -= background_velocity[i] * dT;
            if (background_x_positions[i] <= -array_of_backgrounds[i].width*2)
            {
                background_x_positions[i] = 0.0;
            }
        }

        // draw backgrounds

        for(int i = 0; i<number_of_backgrounds;i++)
        {
            Vector2 background_position_one{background_x_positions[i],0.0};
            Vector2 background_position_two{background_x_positions[i] + array_of_backgrounds[i].width*2,0.0};
            DrawTextureEx(array_of_backgrounds[i], background_position_one, 0.0, 2.0, WHITE);
            DrawTextureEx(array_of_backgrounds[i], background_position_two, 0.0, 2.0, WHITE);
        }

        
        // game logic begins
        
        if(is_on_ground(scarfy_data, window_dimensions[1]))
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

        if(IsKeyPressed(KEY_SPACE) && !is_in_air)
            {
                velocity += jump_velocity;
            }
   

        bool collision{};
        for (animation_data nebula: nebulae)
        {   
            float pad{50};
            Rectangle nebula_rec{
                nebula.position.x + pad,
                nebula.position.y + pad,
                nebula.rectangle.width - 2*pad,
                nebula.rectangle.height - 2*pad
            };
            Rectangle scarfy_rec{
                scarfy_data.position.x,
                scarfy_data.position.y,
                scarfy_data.rectangle.width,
                scarfy_data.rectangle.height
            };

            if (CheckCollisionRecs(nebula_rec, scarfy_rec))
            {
                collision = true;
            }
        } 
        
        // update scarfy animation frame
        if(collision)
        {
            DrawText("YOU LOSE", window_dimensions[0]/4,window_dimensions[1]/2,50,RED);           
        }else if(scarfy_data.position.x >= finish_line)
        {
            DrawText("You win!", window_dimensions[0]/4,window_dimensions[1]/2,50,GREEN);
        }
        else
        {  
            if(!is_in_air)
            {
                scarfy_data = update_animation_data(scarfy_data, dT, 5);
            }

            for(int i = 0; i<number_of_nebulae; i++)
            {
                nebulae[i] = update_animation_data(nebulae[i], dT, 7);
            }

            for(int i = 0; i<number_of_nebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rectangle, nebulae[i].position, WHITE);
                nebulae[i].position.x += nebula_velocity * dT;
            }

        

            // update finish line
            finish_line += nebula_velocity * dT;


            // draw scarfy
            DrawTextureRec(scarfy, scarfy_data.rectangle, scarfy_data.position, WHITE);
            
            // jump check
           

            scarfy_data.position.y += velocity * dT;
            // game logic ends
            // stop drawing
        }
      
            EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(array_of_backgrounds[0]);
    UnloadTexture(array_of_backgrounds[1]);
    UnloadTexture(array_of_backgrounds[2]);
    CloseWindow();
}