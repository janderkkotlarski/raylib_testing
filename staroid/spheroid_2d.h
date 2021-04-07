#ifndef SPHEROID_2D_H
#define SPHEROID_2D_H

#include "raylib.h"

class spheroid_2d
{
private:
  const Vector3 m_pos
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_dir
  { 0.0f, 1.0f, 0.0f };

  const float m_radius
  { 2.0f };

  float m_angle
  { 90.0f };

  const float m_scale
  { 200.0f };

  float m_angle_2
  { 0.0f };

  const float m_scale_2
  { 1.0f };

public:
  spheroid_2d()
  noexcept;

  void display()
  const noexcept;

  void rotate(const float delta_angle)
  noexcept;
};

#endif // SPHEROID_2D_H
