#include "loop.h"

#include <charconv>
#include <iostream>

#include "raymath.h"


#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include "staroid.h"
#include "functions.h"
#include "auronacci.h"
#include "circloid.h"
#include "disk.h"


#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

loop::loop()
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(m_screen_width, m_screen_height, "STAROID");

  SetTargetFPS(100);


  m_camera.position = m_cam_pos;    // Camera position
  m_camera.target = m_cam_target;      // Camera looking at point
  m_camera.up = m_cam_up;          // Camera up vector (rotation towards target)
  m_camera.fovy = 45.0f;                                // Camera field-of-view Y
  m_camera.type = CAMERA_PERSPECTIVE;                  // Camera mode type

  m_stars_1 = star_nursery(m_aster_factor);
  stellarator(m_stars_1, m_gold);

  m_stars_2 = star_nursery(m_aster_factor);
  stellarator(m_stars_2, m_gold);

  m_lighting_shader = LoadShader("base_lighting.vs", "lighting.fs");

  m_lighting_shader.locs[LOC_MATRIX_MODEL] =
      GetShaderLocation(m_lighting_shader, "matModel");
  m_lighting_shader.locs[LOC_VECTOR_VIEW] =
      GetShaderLocation(m_lighting_shader, "viewPos");

  Light light
  { CreateLight(LIGHT_POINT, m_cam_pos, m_cam_target, WHITE, m_lighting_shader) };

  for (staroid &aster: m_stars_1)
  { aster.set_shading(m_lighting_shader); }

  for (staroid &aster: m_stars_2)
  { aster.set_shading(m_lighting_shader); }

  m_bloom_shader = LoadShader(0, "bloom.fs");

  m_gray_shader = LoadShader(0, "grayscale.fs");
}

void loop::run()
{
  std::chrono::steady_clock::time_point time_1
  { std::chrono::steady_clock::now() };

  std::chrono::steady_clock::time_point time_2
  { std::chrono::steady_clock::now() };

  RenderTexture2D render_area
  { LoadRenderTexture(m_screen_width, m_screen_height) };

  RenderTexture2D render_area_2
  { LoadRenderTexture(m_screen_width, m_screen_height) };


  while (!WindowShouldClose())            // Detect window close button or ESC key
  {
    time_2 = std::chrono::steady_clock::now();

    std::chrono::steady_clock::duration delta
    { time_2 - time_1 };

    time_1 = std::chrono::steady_clock::now();

    const float fraction
    { m_angle*float(delta.count())/1000000000.0f };

    astral_mechanics(m_stars_1, m_aster_factor, fraction);

    astral_mechanics(m_stars_2, m_aster_factor, fraction);

    if (m_tick == 0)
    {
      BeginDrawing();
      {


        ClearBackground(BLACK);


        BeginTextureMode(render_area);
        {
          ClearBackground(BLACK);

          BeginMode3D(m_camera);
          {
            for (unsigned count { 0 }; count < m_stars_1.size(); ++count)
            {
              m_stars_1[count].display();
            }
          }
          EndMode3D();
        }
        EndTextureMode();



        BeginShaderMode(m_gray_shader);
        {
          // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)

          DrawTextureRec(render_area.texture, (Rectangle){ 0, 0, (float)render_area.texture.width,
                         (float)-render_area.texture.height }, (Vector2){ 0, 0 }, Color{255, 255, 255, 255});
        }
        EndShaderMode();

        BeginShaderMode(m_bloom_shader);
        {
          // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)

          DrawTextureRec(render_area.texture, (Rectangle){ 0, 0, (float)render_area.texture.width,
                         (float)-render_area.texture.height }, (Vector2){ 0, 0 }, Color{255, 255, 255, 0});
        }
        EndShaderMode();



        DrawFPS(10, 10);
      }
      EndDrawing();
    }

    ++m_tick;
    m_tick %= m_tick_max;
  }
}





void looping()
{
  auronacci gold;

  const int screenWidth = 800;
  const int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
  InitWindow(screenWidth, screenHeight, "STAROID");

  Vector3 cam_pos
  { 0.0f, 0.0f, 12.0f };

  Vector3 cam_target
  { 0.0f, 0.0f, 0.0f };

  Vector3 cam_up
  { 0.0f, 1.0f, 0.0f };

  Camera camera
  { 0 };
  camera.position = cam_pos;    // Camera position
  camera.target = cam_target;      // Camera looking at point
  camera.up = cam_up;          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.type = CAMERA_PERSPECTIVE;                  // Camera mode type

  Model model
  { LoadModel("staroid_025.obj") };

  const std::vector <Color> pastels
  { pastelbow() };

  const float aster_factor
  { 0.015f };

  std::vector <staroid> stars
  { star_nursery(aster_factor) };

  stellarator(stars, gold);


  std::vector <Vector3> positions
  {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
  };

  const Vector3 rotate
  { 1.0f*PI/4.0f, 1.0f*PI/4.0f, 0.75f*PI/4.0f };

  model.transform = MatrixRotateXYZ(rotate);

  Shader shader
  {
    LoadShader("base_lighting.vs",
               "lighting.fs")
  };

  shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
  shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  int ambientLoc = GetShaderLocation(shader, "ambient");

  const float floats[4]
  { 0.0f, 0.0f, 0.0f, 1.0f };

  SetShaderValue(shader, ambientLoc, floats, UNIFORM_VEC4);

  model.materials[0].shader = shader;

  for (staroid &aster: stars)
  { aster.set_shading(shader); }

  const float star_factor
  { 0.05f };

  Light light
  { CreateLight(LIGHT_POINT, cam_pos, cam_target, WHITE, shader) };



  SetTargetFPS(10000);                       // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  const int frame_max
  { 100 };

  int frames
  { 0 };

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

  Shader post_shader
  { LoadShader(0, "bloom.fs") };

  RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

  circloid circle(gold);

  disk disc;

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

    circle.rotate(dialta);

    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);              // Update camera

    //----------------------------------------------------------------------------------

    if (IsKeyReleased(KEY_DELETE))
    {
      stellarator(stars, gold);
      circle.recolor(gold);
    }

    astral_mechanics(stars, aster_factor, dialta);

    // Draw
    //----------------------------------------------------------------------------------
    if (frames == 0)
    {
      BeginDrawing();
      {
        ClearBackground(BLACK);

        BeginTextureMode(target);
        {
          ClearBackground(BLACK);
        }
        EndTextureMode();

        BeginTextureMode(target);
        {
          BeginMode3D(camera);
          {
            for (staroid &aster: stars)
            { aster.display(); }
          }
          EndMode3D();
        }
        EndTextureMode();

        BeginShaderMode(post_shader);
        {
          // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)

          DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
        }
        EndShaderMode();

        BeginMode3D(camera);
          circle.display();
        EndMode3D();






        // DrawFPS(10, 10);

        /*

        const int max
        { 10 };

        const int number
        { int(delta.count()) };

        char num_char[max + sizeof(char)];

        std::to_chars(num_char, num_char + max, number);

        */

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
