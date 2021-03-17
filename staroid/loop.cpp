#include "loop.h"

#include <vector>
#include <chrono>
#include <charconv>

#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include "staroid.h"
#include "functions.h"

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
  { 8.0f, 0.0f, 0.0f };

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

  staroid star(100.0f);

  Model model
  { LoadModel("staroid.obj") };

  const Color pastel_red
  { 255, 63, 63, 255 };

  const Color pastel_orange
  { 255, 160, 63, 255 };

  const Color pastel_yellow
  { 255, 255, 63, 255 };

  const Color pastel_lime
  { 160, 255, 63, 255 };

  const Color pastel_green
  { 63, 255, 63, 255 };

  const Color pastel_viridian
  { 63, 255, 160, 255 };

  const Color pastel_turquoise
  { 63, 255, 255, 255 };

  const Color pastel_electric
  { 63, 160, 255, 255 };

  const Color pastel_blue
  { 63, 63, 255, 255 };

  const Color pastel_indigo
  { 160, 63, 255, 255 };

  const Color pastel_violet
  { 255, 63, 255, 255 };

  const Color pastel_purple
  { 255, 63, 160, 255 };


  const std::vector <Color> pastels
  {
    pastel_red, pastel_orange, pastel_yellow, pastel_lime,
    pastel_green, pastel_viridian, pastel_turquoise, pastel_electric,
    pastel_blue, pastel_indigo, pastel_violet, pastel_purple
  };

  const int amount
  { int(pastels.size()) };

  const int amax
  { 11 };

  const float rotation
  { 2.0f*PI/amount };

  float vactor
  { 0.005f };

  const float grow
  { 1.1f };

  Vector3 place
  { 0.0f, 0.0f, 2.0f };

  std::vector <staroid> stars;

  for (const Color &pastel: pastels)
  {
    staroid star;

    star.pos(place);

    star.color(pastel);

    star.factor(vactor);

    stars.push_back(star);

    vactor *= grow;

    rotate_vector3_xyz(place, rotation, true, false, false);
  }



  const Texture texture
  { LoadTextureFromImage(GenImageColor(1000, 1000, WHITE)) };

  model.materials[0].maps[MAP_DIFFUSE].texture = texture;

  star.texture(texture);

  std::vector <Vector3> positions
  {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
  };

  const Vector3 rotate
  { PI/4.0f, PI/4.0f, 0.0f*PI/4.0f };

  model.transform = MatrixRotateXYZ(rotate);

  const float factor
  { 0.02f };

  Shader shader
  {
    LoadShader(TextFormat("base_lighting.vs", GLSL_VERSION),
               TextFormat("lighting.fs", GLSL_VERSION))
  };

  shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  int ambientLoc = GetShaderLocation(shader, "ambient");

  const float floats[4]
  { 0.0f, 0.0f, 0.0f, 1.0f };

  SetShaderValue(shader, ambientLoc, floats, UNIFORM_VEC4);

  model.materials[0].shader = shader;

  star.shading(shader);

  for (staroid &aster: stars)
  { aster.shading(shader); }

  Light light
  { CreateLight(LIGHT_POINT, cam_pos, cam_target, WHITE, shader) };

  SetTargetFPS(10000);                       // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  const int frame_max
  { 100 };

  int frames
  { 0 };

  const float star_factor
  { 0.005f };

  float star_phi
  { 0.0f };

  const float delta_phi
  { 2.0f };

  std::chrono::steady_clock::time_point time_1
  { std::chrono::steady_clock::now() };

  std::chrono::steady_clock::time_point time_2
  { std::chrono::steady_clock::now() };

  const float dial
  { 0.1f*2.0f*PI };

  // Main game loop
  while (!WindowShouldClose())            // Detect window close button or ESC key
  {    
    time_2 = std::chrono::steady_clock::now();

    std::chrono::steady_clock::duration delta
    { time_2 - time_1 };

    time_1 = std::chrono::steady_clock::now();

    const float dialta
    { dial*float(delta.count())/1000000000.0f };

    star_phi += dialta*delta_phi;

    if (star_phi > 2.0f*PI)
    { star_phi -= 2.0f*PI; }

    const float act_factor
    { abs(star_factor*sin(star_phi)) };

    star.factor(act_factor);

    star.color(WHITE);

    star.pos(positions[1]);

    star.rotate();

    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);              // Update camera

    //----------------------------------------------------------------------------------


    for (staroid &aster: stars)
    {
      aster.accelerate(star);
      aster.fall(dialta);
    }


    // Draw
    //----------------------------------------------------------------------------------
    if (frames == 0)
    {
      BeginDrawing();
      {
        ClearBackground(BLACK);

        BeginMode3D(camera);
        {
          // DrawModel(model, positions[0], factor, pastel_electric);

          star.display();

          for (staroid &aster: stars)
          { aster.display(); }
        }

        EndMode3D();

        // DrawFPS(10, 10);

        const int max
        { 10 };

        const int number
        { int(delta.count()) };

        char num_char[max + sizeof(char)];

        std::to_chars(num_char, num_char + max, number);

        // DrawText(num_char, 10, 50, 20, WHITE);
      }
      EndDrawing();
    }
    //----------------------------------------------------------------------------------
    ++frames;
    frames %= frame_max;
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------

  UnloadMaterial(model.materials[0]); // Unload material: shader and textures
  UnloadModel(model);         // Unload model
  CloseWindow();
}
