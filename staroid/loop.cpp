#include "loop.h"

#include <vector>

#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include "staroid.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

void loop()
{
  const int screenWidth = 800;
  const int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(screenWidth, screenHeight, "STAROID");

  Vector3 cam_pos
  { 4.0f, 0.0f, 0.0f };

  Vector3 cam_target
  { 0.0f, 0.0f, 0.0f };

  Vector3 cam_up
  { 0.0f, 0.0f, 1.0f };

  Camera camera
  { 0 };
  camera.position = cam_pos;    // Camera position
  camera.target = cam_target;      // Camera looking at point
  camera.up = cam_up;          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

  staroid star;

  Model model
  { LoadModel("staroid.obj") };


  const Color star_color
  { 255, 63, 63, 255 };

  Image image
  { GenImageColor(1000, 1000, star_color) };

  model.materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(image);

  std::vector <Vector3> positions
  {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 1.0f }
  };

  const float factor
  { 0.01f };

  Shader shader
  {
    LoadShader(TextFormat("base_lighting.vs", GLSL_VERSION),
               TextFormat("lighting.fs", GLSL_VERSION))
  };

  shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  int ambientLoc = GetShaderLocation(shader, "ambient");

  const float floats[4]
  { 1.0f, 1.0f, 1.0f, 1.0f };

  SetShaderValue(shader, ambientLoc, floats, UNIFORM_VEC4);

  model.materials[0].shader = shader;

  Light light
  { CreateLight(LIGHT_POINT, cam_pos, cam_target, WHITE, shader) };

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
        DrawModel(model, positions[0], factor, WHITE);

        DrawModel(model, positions[1], factor, WHITE);
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
}
