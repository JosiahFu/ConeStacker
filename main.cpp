#include "raylib.h"
#include <vector>
#include <algorithm>
#include <string>

void DrawCone(Vector3 position) {
    static Model coneModel = LoadModel("resources/coneModel.obj");
    
    DrawModelEx(coneModel, position, (Vector3){1.0f, 0.0f, 0.0f}, -90.0f, (Vector3){0.2f, 0.2f, 0.2f}, WHITE); // Draw cone
}

void DrawTextCentered(const char* text, int posX, int posY, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, posX-(textWidth/2), posY, fontSize, color);
}

// Program main entry point
int main(void)
{
    // Initialization
    const int screenWidth = 720;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "Cone Stacker");
    Image windowIcon = LoadImage("resources/icon.png");
    SetWindowIcon(windowIcon);
    
    InitAudioDevice();
    Sound coneDrop = LoadSound("resources/coneDrop.ogg");
    
    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    
    float targetFov = 45.0f;
    float floatingConeX = 0.0f;
    float floatingConeSpeed = 0.2f;
    float floatingConeHoverDistance = 4.0f;
    float floatingConeFallSpeed = 0.0f;
    bool floatingConeToRight = true;
    bool fail = false;
    
    std::vector<Vector3> coneYs;
    coneYs.push_back((Vector3){0.0f, 0.0f, 0.0f});

    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    SetCameraMode(camera, CAMERA_FREE);
    
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        UpdateCamera(&camera);
        
        if (IsKeyPressed(KEY_SPACE)) {
            if (fail) {
                fail = false;
                coneYs.clear();
                coneYs.push_back((Vector3){0.0f, 0.0f, 0.0f});
                floatingConeX = 0.0f;
                floatingConeSpeed = 0.2f;
                floatingConeFallSpeed = 0.0f;
                camera.fovy = 45.0f;
                camera.target = coneYs.back();
                targetFov = 45.0f;
                floatingConeHoverDistance = 4.0f;
            } 
            else {
                if (floatingConeX < 2.0f && floatingConeX > -2.0f) {
                    coneYs.push_back((Vector3) {0.0f, coneYs.back().y + 1.0f, 0.0f});
                    
                    camera.target = coneYs.back();
                    if (targetFov < 90.0f) {
                        targetFov += 1.0f;
                    }
                    
                    floatingConeX = 0.0f;
                    if (floatingConeSpeed < 1.0f) {
                        floatingConeSpeed += 0.025f;
                    }
                }
                else {
                    fail = true;
                    PlaySound(coneDrop);
                }
            }
        }
        
        if (!fail) {
            if (floatingConeToRight) {
                floatingConeX += floatingConeSpeed;
                if (floatingConeX >= 4.0f) {
                    floatingConeToRight = false;
                }
            } else {
                floatingConeX -= floatingConeSpeed;
                if (floatingConeX <= -4.0f) {
                    floatingConeToRight = true;
                }
            }
        } else {
            floatingConeFallSpeed += 0.01f;
            floatingConeHoverDistance -= floatingConeFallSpeed;
            camera.target = (Vector3){floatingConeX, coneYs.back().y + floatingConeHoverDistance, 0.0f};
        }
        
        if (targetFov > camera.fovy) {
            camera.fovy += 0.1f;
        } else if (targetFov < camera.fovy) {
            camera.fovy -= 0.1f;
        }
        
        // Draw
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            BeginMode3D(camera);
                
                DrawCube((Vector3){1.5f, -5.0f, 1.5f}, 5.0f, 10.0f, 5.0f, GRAY);
                
                std::for_each(coneYs.begin(), coneYs.end(), DrawCone);
                
                DrawCone((Vector3){floatingConeX, coneYs.back().y + floatingConeHoverDistance, 0.0f});

            EndMode3D();
            
            if (fail) {
                DrawTextCentered("Game Over", screenWidth/2, screenHeight/2-25, 50, BLACK);
                DrawTextCentered(("Score: " + std::to_string(coneYs.size()-1)).c_str(), screenWidth/2, screenHeight/2+25, 25, BLACK);
                DrawTextCentered("Press Space To Play Again", screenWidth/2, screenHeight/2+75, 25, BLACK);
            } else {
                DrawTextCentered(std::to_string(coneYs.size()-1).c_str(), screenWidth/2, 10, 50, BLACK);
            }
        EndDrawing();
        
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}