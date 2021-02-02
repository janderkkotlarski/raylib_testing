#include "raylib_stuff.h"

#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
// #include "rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif



void shading()
{

  const int screensize
  { 800 }; // Size in pixels of the square screen

  const int imagesize
  { 400 }; // Size in pizels of the image of the texture

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)

  InitWindow(screensize, screensize, "Spheroid");
  // Initialize window with width and height in pixels and a text message.

  const Vector3 position // Camera position
  { 10.0f, 0.0f, 0.0f };

  const Vector3 forward // Position of forward direction
  { 0.0f, 0.0f, 0.0f };

  const Vector3 upward // Position of upward direction
  { 0.0f, 0.0f, 1.0f };

  const float fov // Field of View
  { 45.0f };

  Camera camera // Initialize camera
  { position, forward, upward,
    fov, CAMERA_PERSPECTIVE };

  Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 100, 100));
  // Initialize a sphere with a spherical mesh.

  Image image = GenImageColor(imagesize, imagesize, BLACK);



  for (int x{ 0 }; x < imagesize; ++x)
  {
    const int x_color
    { int(255.0f*float(x)/float(imagesize))};

    for (int y{ 0 }; y < imagesize; ++y)
    {
      const int y_color
      { int(255.0f*float(y)/float(imagesize))};

      Color color{0, 127, 0, 255};

      color.r = x_color;
      color.b = y_color;

      ImageDrawPixel(&image, x, y, color);
    }
  }





  Texture texture = LoadTextureFromImage(image);
  // Assign texture to default model material
  sphere.materials[0].maps[MAP_DIFFUSE].texture = texture;

  // Load shader and set up some uniforms
  Shader shader = LoadShader(TextFormat("resources/shaders/glsl%i/base_lighting.vs", GLSL_VERSION),
                             TextFormat("resources/shaders/glsl%i/fog.fs", GLSL_VERSION));
  shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  // Ambient light level
  // int ambientLoc = GetShaderLocation(shader, "ambient");

  // const float ambient_density[4]
  // { 0.0f, 0.0f, 0.2f, 1.0f };

  // SetShaderValue(shader, ambientLoc, ambient_density, UNIFORM_VEC4);

  // float fogDensity = 0.15f;
  // int fogDensityLoc = GetShaderLocation(shader, "fogDensity");
  // SetShaderValue(shader, fogDensityLoc, &fogDensity, UNIFORM_FLOAT);

  // NOTE: All models share the same shader
  // sphere.materials[0].shader = shader;

  // Using just 1 point lights
  // CreateLight(LIGHT_POINT, (Vector3){ 0, 2, 6 }, Vector3Zero(), WHITE, shader);



  // SetCameraMode(camera, CAMERA_ORBITAL);  // Set an orbital camera mode

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
        DrawModel(sphere, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

      EndMode3D();

      // DrawText(TextFormat("Use KEY_UP/KEY_DOWN to change fog density [%.2f]", fogDensity), 10, 10, 20, RAYWHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModel(sphere);        // Unload the model C
  UnloadTexture(texture);     // Unload the texture
  UnloadShader(shader);       // Unload shader

  CloseWindow();              // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}

