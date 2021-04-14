#ifndef CIRCLOID_H
#define CIRCLOID_H

#include <math.h>

#include "raylib.h"

#include "auronacci.h"

class circloid
{
private:
  Color m_color
  { GRAY };

  const Vector3 m_pos
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_dir
  { 0.0f, 1.0f, 0.0f };

  const float m_static
  { 2.2f };

  const float m_ripple
  { 0.2f };

  float m_radius
  { m_static };

  float m_angle
  { 90.0f };

  const float m_scale
  { 100.0f };

  float m_angle_2
  { 0.0f };

  const float m_scale_2
  { 0.5f };

  float m_angle_3
  { 0.0f };

  const float m_scale_3
  { 2.5f*sqrt(2.0f) };

public:
  circloid()
  noexcept;

  circloid(auronacci &gold)
  noexcept;

  void recolor(auronacci &gold)
  noexcept;

  void display()
  const noexcept;

  void rotate(const float delta_angle)
  noexcept;
};

#endif // CIRCLOID_H
