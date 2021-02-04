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

Vector3 delta_rotate(const Vector3 &vec_cos, const Vector3 &vec_sin)
{
  const float theta
  { 0.03f };

  return Vector3Add(Vector3Scale(vec_cos, cos(theta)), Vector3Scale(vec_sin, sin(theta)));
}

void rotate(Vector3 &vec_x1, Vector3 &vec_y1)
{
  Vector3 vec_x2
  { Vector3Normalize(delta_rotate(vec_x1, vec_y1)) };

  Vector3 vec_y2
  { Vector3Normalize(delta_rotate(vec_y1, Vector3Negate(vec_x1))) };

  Vector3OrthoNormalize(&vec_x2, &vec_y2);

  vec_x1 = vec_x2;
  vec_y1 = vec_y2;
}

void movement(Vector3 &position, Vector3 &forward,
              Vector3 &rightward, Vector3 &upward)
{
  if (IsKeyDown('W'))
  { rotate(position, upward); }

  if (IsKeyDown('S'))
  { rotate(upward, position); }

  if (IsKeyDown('D'))
  { rotate(position, rightward); }

  if (IsKeyDown('A'))
  { rotate(rightward, position); }

  if (IsKeyDown('E'))
  { rotate(upward, rightward); }

  if (IsKeyDown('Q'))
  { rotate(rightward, upward); }

}

std::string vector2string(const Vector3 &vec)
noexcept
{
  std::string coords;

  coords += "[" + std::to_string(vec.x) + "]";
  coords += "[" + std::to_string(vec.y) + "]";
  coords += "[" + std::to_string(vec.z) + "]";

  return coords;
}

void display_string(const std::string str,
                    const std::string &message,
                    const int x,
                    const int y,
                    const int size)
noexcept
{
  if (str.size() > 0)
  {
    std::string info_string
    { str };

    info_string += message;

    const char *info_array
    { info_string.c_str() };
    DrawText(info_array, x, y, size, SKYBLUE);
  }
}

void display_text(const Vector3 &center, const Vector3 &position,
                  const Vector3 &forward, const Vector3 &rightward, const Vector3 &upward)
{
  const int x
  { 20 };

  int y
  { 20 };

  const int size
  { 20 };

  const int step
  { 30 };

  display_string("center:   ", vector2string(center), x, y, size);

  y += step;
  display_string("position:  ", vector2string(position), x, y, size);

  y += step;
  display_string("forward:   ", vector2string(forward), x, y, size);

  y += step;
  display_string("rightward: ", vector2string(rightward), x, y, size);

  y += step;
  display_string("upward:    ", vector2string(upward), x, y, size);
}

void shading()
{

  const int screen_size
  { 800 }; // Size in pixels of the square screen

  const int image_size
  { 400 }; // Size in pizels of the image of the texture

  const float zero
  { 0.0f };

  const float unit
  { 1.0f };

  const float sphere_size
  { 0.35f };

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)

  InitWindow(screen_size, screen_size, "Spheroid");
  // Initialize window with width and height in pixels and a text message.

  const Vector3 center // Center of rotation and sphere
  {zero, zero, zero };

  Vector3 position // Camera position
  { unit, zero, zero };

  Vector3 forward // Position of forward direction
  { -unit, zero, zero };

  Vector3 rightward // Position of rightward direction
  { zero, unit, zero };

  Vector3 upward // Position of upward direction
  { zero, zero, unit };

  const float fov // Field of View
  { 45.0f };

  Camera camera // Initialize camera
  { position, forward, upward,
    fov, CAMERA_PERSPECTIVE };

  Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 60, 60));
  // Initialize a sphere with a spherical mesh.

  Texture texture = LoadTextureFromImage(painter(image_size));
  // Assign texture to default model material
  sphere.materials[0].maps[MAP_DIFFUSE].texture = texture;



  SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())            // Detect window close button or ESC key
  {
    movement(position, forward, rightward, upward);

    camera.position = position;
    camera.target = center;
    camera.up = upward;

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

      display_text(center, position, forward, rightward, upward);

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

