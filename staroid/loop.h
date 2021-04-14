#ifndef LOOP_H
#define LOOP_H

#include <vector>

#include "raylib.h"


#include "auronacci.h"
#include "functions.h"

class loop
{
private:

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

  Model m_star_model
  { LoadModel("staroid.obj") };

  const std::vector <Color> m_pastels
  { pastelbow() };

  const float m_aster_factor
  { 0.015f };

  std::vector <staroid> m_stars
  { star_nursery(m_aster_factor) };

  Shader m_lighting_shader
  {
    LoadShader("base_lighting.vs",
               "lighting.fs")
  };

};

void loop();

#endif // LOOP_H
