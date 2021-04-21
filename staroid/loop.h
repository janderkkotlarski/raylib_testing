#ifndef LOOP_H
#define LOOP_H

#include <vector>
#include <chrono>

#include "raylib.h"

#include "auronacci.h"
#include "functions.h"

class loop
{
private:

  const float m_angle
  { 0.1f*2.0f*PI };

  int m_tick
  { 0 };

  const int m_tick_max
  { 100 };

  const int m_fps
  { 100 };

  auronacci m_gold;
  // The fibonacci sequence pseudo-random generator

  const int m_screen_width = 800;
  const int m_screen_height = 800;

  Vector3 m_cam_pos
  { 0.0f, 0.0f, 12.0f };

  Vector3 m_cam_target
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_cam_up
  { 0.0f, 1.0f, 0.0f };

  Camera m_camera
  { 0 };

  // Model m_star_model
  // { LoadModel("staroid.obj") };



  const std::vector <Color> m_pastels
  { pastelbow() };



  const float m_aster_factor
  { 0.015f };



  std::vector <staroid> m_stars;

  Shader m_lighting_shader;

  // Light m_light;

  /*
  Shader m_lighting_shader
  {
    LoadShader("base_lighting.vs",
               "lighting.fs")
  };
  */

  void tick();

public:
  loop();

  void run();
};

void looping();

#endif // LOOP_H
