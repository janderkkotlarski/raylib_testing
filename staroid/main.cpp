#include <iostream>



// #include "staroid.h"

#include "raylib.h"

int main()
{
  // staroid star;

  const int screenWidth = 800;
  const int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(screenWidth, screenHeight, "STAROID");

  Camera camera
  { 0 };
  camera.position = (Vector3){ 400.0f, 400.0f, 400.0f };    // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

  // Load model and PBR material
  Model model
  { LoadModel("staroid.obj") };


  const Image image
  { GenImageColor(100, 100, WHITE) };

  for (int x{ 0 }; x < image.width; ++x)
  {
    for (int y{ 0 }; y < image.height; ++y)
    {

    }
  }


  model.materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(image);


  Vector3 position
  { 0.0f, 0.0f, 0.0f };

  SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())            // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);              // Update camera

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    {
      ClearBackground(BLACK);

      BeginMode3D(camera);
      {
        DrawModel(model, position, 1.0f, WHITE);
      }

      EndMode3D();

      DrawFPS(10, 10);
    }
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------

  UnloadMaterial(model.materials[0]); // Unload material: shader and textures
  UnloadModel(model);         // Unload model
  CloseWindow();

  // star.run();

  std::cout << "STAROID!" << std::endl;
  return 0;
}
