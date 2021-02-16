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

void heart_fractal(float &xf, float &yf,
                   const float xf2, const float yf2,
                   const float real, const float imag)
{
  xf = xf2*xf2 - yf2 + real;
  yf = xf2*yf2 + imag;
}

void polar_globe(float &xf, float &yf)
{
  xf = cos(256.0f*PI*xf);
  yf = cos(256.0f*PI*yf);
}

void renormalizer(float &xf, float &yf, const int x, const int y, const int image_size)
{
  const float xmin
  { -0.5f*PI };

  const float xmax
  { 0.5f*PI };

  const float ymin
  { -PI };

  const float ymax
  { PI };

  xf = (xmin + (xmax - xmin)*float(x)/float(image_size));

  yf = (ymin + (ymax - ymin)*float(y)/float(image_size));
}

Color colorizer(const float xf, const float yf)
{
  Color dot;

  dot.r = 0*int(255.0f*0.5f*(1.0f + 1.0f*yf));
  dot.g = int(255.0f*0.5f*(1.0f + 1.0f*xf));;
  dot.b = 0;
  dot.a = 255;

  return dot;
}

int fractaler(float &xf, float &yf)
{
  int count
  { 0 };

  const int count_max
  { 1 };

  const float real
  { xf };

  const float imag
  { yf };

  float xf2
  { xf };

  float yf2
  { yf };

  const float dist_max
  { 100.0f };

  while (square_dist(real, imag, xf2, yf2) <= dist_max &&
         count < count_max)
  {
    xf2 = xf;
    yf2 = yf;

    // heart_fractal(xf, yf, xf2, yf2, real, imag);

    // polar_globe(xf, yf);

    ++count;
  }

  return count;
}

Color color_mixer(const int x, const int y, const int image_size)
{
  assert(x >= 0);
  assert(y >= 0);
  assert(image_size >= 0);
  assert(x <= image_size);
  assert(y <= image_size);

  float xf
  { 0.0f };

  float yf
  { 0.0f };

  renormalizer(xf, yf, x, y, image_size);

  return colorizer(xf, yf);
}

Image painter(const int image_size)
{
  Image image = GenImageColor(image_size, image_size, GREEN);

  for (int x{ 0 }; x < image_size; ++x)
  {
    for (int y{ 0 }; y < image_size; ++y)
    {
      Color dot{ color_mixer(x, y, image_size) };

      ImageDrawPixel(&image, x, y, dot);
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
              const int image_size)
{
   const int x
   { int(std::chrono::system_clock::now().time_since_epoch().count()) % image_size };

   theta = thetanizer(x, image_size);

   const int y
   { int(std::chrono::system_clock::now().time_since_epoch().count()) % image_size };

   phi = phinizer(y, image_size);
}

Image filling(const int image_size)
{
  Image image
  { GenImageColor(image_size, image_size, BLACK) };

  const float tripe
  { 1.0f/sqrt(3.0f) };

  const Vector3 tripel
  { tripe, tripe, tripe };

  const float psi_max
  { 0.15f*PI };

  for (int x{ 0 }; x < image_size; ++x)
  {
    const float theta
    { thetanizer(x, image_size) };

    for (int y{ 0 }; y < image_size; ++y)
    {
      const float phi
      { phinizer(y, image_size) };

      const Color dot
      { RED };

      const Vector3 spherical
      { cos(theta)*cos(phi), cos(theta)*sin(phi), sin(theta) };

      const float cos_psi
      { Vector3DotProduct(tripel, spherical) };

      const float psi
      { acos(cos_psi) };

      if (psi < psi_max)
      { ImageDrawPixel(&image, x, y, dot); }
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

  Texture texture = LoadTextureFromImage(filling(image_size));
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

        // Draw the three models
        DrawModel(sphere, (Vector3){ 0.0f, 0.0f, 0.0f }, sphere_size, WHITE);

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

