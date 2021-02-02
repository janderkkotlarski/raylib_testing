#include "raylib_stuff.h"

#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
// #include "rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

Image painter(const int image_size)
{
  Image image = GenImageColor(image_size, image_size, BLACK);

  for (int x{ 0 }; x < image_size; ++x)
  {
    const int x_color
    { int(255.0f*float(x)/float(image_size))};

    for (int y{ 0 }; y < image_size; ++y)
    {
      const int y_color
      { int(255.0f*float(y)/float(image_size))};

      Color color{0, 127, 0, 255};

      color.r = x_color;
      color.b = y_color;

      ImageDrawPixel(&image, x, y, color);
    }
  }

  return image;
}

void rotation(Vector3 &forward, Vector3 &upward)
{
  if (KeyboardKey::)

}

void shading()
{

  const int screen_size
  { 800 }; // Size in pixels of the square screen

  const int image_size
  { 400 }; // Size in pizels of the image of the texture

  const float unit
  { 1.0f };

  const float sphere_size
  { 0.1f };

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)

  InitWindow(screen_size, screen_size, "Spheroid");
  // Initialize window with width and height in pixels and a text message.

  const Vector3 position // Camera position
  { unit, 0.0f, 0.0f };

  const Vector3 forward // Position of forward direction
  { 0.0f, 0.0f, 0.0f };

  const Vector3 upward // Position of upward direction
  { 0.0f, 0.0f, unit };

  const float fov // Field of View
  { 45.0f };

  Camera camera // Initialize camera
  { position, forward, upward,
    fov, CAMERA_PERSPECTIVE };

  Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 100, 100));
  // Initialize a sphere with a spherical mesh.

  Texture texture = LoadTextureFromImage(painter(image_size));
  // Assign texture to default model material
  sphere.materials[0].maps[MAP_DIFFUSE].texture = texture;



  SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())            // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);              // Update camera

    /*

    if (IsKeyDown(KEY_UP))
    {
        fogDensity += 0.001;
        if (fogDensity > 1.0) fogDensity = 1.0;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        fogDensity -= 0.001;
        if (fogDensity < 0.0) fogDensity = 0.0;
    }

    SetShaderValue(shader, fogDensityLoc, &fogDensity, UNIFORM_FLOAT);


    // Update the light shader with the camera view position
    SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &camera.position.x, UNIFORM_VEC3);
    //----------------------------------------------------------------------------------

    */

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

      ClearBackground(BLACK);

      BeginMode3D(camera);

        // Draw the three models
        DrawModel(sphere, (Vector3){ 0.0f, 0.0f, 0.0f }, sphere_size, WHITE);

      EndMode3D();

      // DrawText(TextFormat("Use KEY_UP/KEY_DOWN to change fog density [%.2f]", fogDensity), 10, 10, 20, RAYWHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModel(sphere);        // Unload the model C
  UnloadTexture(texture);     // Unload the texture
  // UnloadShader(shader);       // Unload shader

  CloseWindow();              // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}

