#ifndef SPHEROID_2D_H
#define SPHEROID_2D_H

#include "raylib.h"

class spheroid_2d
{
private:
  const Vector3 m_pos
  { 0.0f, 0.0f, 0.0f };

  const Vector3 m_dir
  { 1.0f, 0.0f, 0.0f };

  const float m_radius
  { 1.0f };

public:
  spheroid_2d();

  void display();
};

#endif // SPHEROID_2D_H
