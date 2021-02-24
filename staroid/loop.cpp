#include "loop.h"

#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

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
  { 4.0f, 4.0f, 4.0f };

  Camera camera
  { 0 };
  camera.position = cam_pos;    // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

  Model model
  { LoadModel("staroid.obj") };

  Image image
  { GenImageColor(1000, 1000, BLACK) };

  for (int x{ 0 }; x < image.width; ++x)
  {
    for (int y{ 0 }; y < image.height; ++y)
    {
      Color color
      { 0, 0, 0, 255 };

      color.r = 127 + x;
      color.b = y;

      ImageDrawPixel(&image, x, y, color);
    }
  }

  model.materials[0].maps[MAP_DIFFUSE].texture = LoadTextureFromImage(image);

  Vector3 position
  { 0.0f, 0.0f, 0.0f };

  Shader shader
  {
    LoadShader(TextFormat("base_lighting.vs", GLSL_VERSION),
               TextFormat("lighting.fs", GLSL_VERSION))
  };

  shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  int ambientLoc = GetShaderLocation(shader, "ambient");

  const float floats[4]
  { 0.2f, 0.2f, 0.2f, 1.0f };

  SetShaderValue(shader, ambientLoc, floats, UNIFORM_VEC4);

  model.materials[0].shader = shader;

  Light light
  { CreateLight(LIGHT_POINT, cam_pos, Vector3Zero(), WHITE, shader) };

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
        DrawModel(model, position, 0.01f, WHITE);
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
