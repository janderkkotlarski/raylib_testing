#include "raylib_stuff.h"

#include <cassert>
#include <chrono>

#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
// #include "rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

float square_dist(const float x1, const float y1,
                  const float x2, const float y2)
noexcept
{ return (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1); }

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

bool spherical_circle()
{
  return false;
}

float phinizer(const int x, const int image_size)
{
  const float phi_min
  { -PI };

  const float phi_range
  { 2.0f*PI };

  const float phi
  { phi_min + phi_range*float(x)/float(image_size) };

  return phi;
}

float thetanizer(const int y, const int image_size)
{
  const float theta_min
  { -0.5f*PI };

  const float theta_range
  { PI };

  const float theta
  { theta_min + theta_range*float(y)/float(image_size) };

  return theta;
}

void rancords(float &phi, float &theta,
              const int image_size,
              auronacci &gold)
{
  const int x
  { gold.get_number() % image_size };

  gold.cycle(100);

  theta = thetanizer(x, image_size);

  const int y
  { gold.get_number() % image_size };

  phi = phinizer(y, image_size);
}

Vector3 spherinizer(const float phi, const float theta)
{
  return { cos(theta)*cos(phi), cos(theta)*sin(phi), sin(theta) };
}

void compare_psi(Image &image, const int x, const int y,
                 const float psi, const float psi_max)
{
  if (psi < 0.1f*psi_max)
  { ImageDrawPixel(&image, x, y, WHITE); }
  else if (psi < 0.2f*psi_max)
  { ImageDrawPixel(&image, x, y, PURPLE); }
  else if (psi < 0.3f*psi_max)
  { ImageDrawPixel(&image, x, y, VIOLET); }
  else if (psi < 0.4f*psi_max)
  { ImageDrawPixel(&image, x, y, BLUE); }
  else if (psi < 0.5f*psi_max)
  { ImageDrawPixel(&image, x, y, Color{ 0, 255, 255, 255 }); }
  else if (psi < 0.6f*psi_max)
  { ImageDrawPixel(&image, x, y, GREEN); }
  else if (psi < 0.7f*psi_max)
  { ImageDrawPixel(&image, x, y, YELLOW); }
  else if (psi < 0.8f*psi_max)
  { ImageDrawPixel(&image, x, y, ORANGE); }
  else if (psi < 0.9f*psi_max)
  { ImageDrawPixel(&image, x, y, RED); }
  else if (psi < 1.0f*psi_max)
  { ImageDrawPixel(&image, x, y, GRAY); }
}

std::vector <Vector3> dot_coordinator(const int image_size)
{
  const unsigned amount
  { 10 };

  float phi_ran
  { 0 };

  float theta_ran
  { 0 };

  auronacci gold;

  std::vector <Vector3> dotcoords;

  for (unsigned count{ 0 }; count < amount; ++count)
  {
    rancords(phi_ran, theta_ran, image_size, gold);

    dotcoords.push_back(spherinizer(phi_ran, theta_ran));
  }

  return dotcoords;
}

Image filling(const int image_size)
{
  const Color color
  { 0, 0, 0, 0 };

  Image image
  { GenImageColor(image_size, image_size, color) };

  float phi_ran
  { 0 };

  float theta_ran
  { 0 };

  const int dot_count
  { 10 };

  const Vector3 up_north
  { 0.0f, 0.0f, 1.0f };

  std::vector <Vector3> dotcoords
  { dot_coordinator(image_size) };

  const float psi_max
  { 0.15f*PI };

  const float spike_fraction
  { 0.5f };

  const float mult
  { 3.0f };

  const float power
  { 20.0f };

  for (int x{ 0 }; x < image_size; ++x)
  {
    const float theta
    { thetanizer(x, image_size) };

    for (int y{ 0 }; y < image_size; ++y)
    {
      const float phi
      { phinizer(y, image_size) };

      const Vector3 spherical
      { spherinizer(phi, theta) };



      for (const Vector3 &coords: dotcoords)
      {
        const Vector3 north_perp
        { Vector3Normalize(Vector3CrossProduct(coords, up_north)) };

        const Vector3 spheri_perp
        { Vector3Normalize(Vector3CrossProduct(coords, spherical)) };

        const float cos_perp
        { Vector3DotProduct(north_perp, spheri_perp) };

        const float cos_perp_abc
        { pow(abs(cos(mult*acos(cos_perp))), power) };

        const float cos_psi
        { Vector3DotProduct(coords, spherical) };

        const float psi
        { acos(cos_psi) };

        compare_psi(image, x, y, psi, ((1.0 - spike_fraction) + spike_fraction*cos_perp_abc)*psi_max);
      }
    }
  }

  return image;
}

void shading()
{

  const int screen_size
  { 800 }; // Size in pixels of the square screen

  const int image_size
  { 3200 }; // Size in pizels of the image of the texture

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



  const float phi_min
  { -PI };

  const float phi_max
  { PI };

  const float theta_min
  { -0.5f*PI };

  const float theta_max
  { 0.5f*PI };

  const float fov // Field of View
  { 45.0f };


  Camera camera // Initialize camera
  { position, forward, upward,
    fov, CAMERA_PERSPECTIVE };

  Model sphere = LoadModelFromMesh(GenMeshSphere(1.0f, 60, 60));
  // Initialize a sphere with a spherical mesh.

  const Texture texture = LoadTextureFromImage(filling(image_size));
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

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(camera);
    {

      DrawModel(sphere, (Vector3){ 0.0f, 0.0f, 0.0f }, sphere_size, WHITE);

    }
    EndMode3D();

    display_text(center, position, forward, rightward, upward);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadModel(sphere);        // Unload the model C
  UnloadTexture(texture);     // Unload the texture

  CloseWindow();              // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
}

