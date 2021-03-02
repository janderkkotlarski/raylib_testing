#ifndef STAROID_H
#define STAROID_H

#include "raylib.h"

class staroid
{
private:
  float m_size
  { 1.0f };

  Vector3 m_pos
  { 0.0f, 0.0f, 0.0f };

  Model m_model;

  Color m_color
  { 63, 63, 63, 255 };

  void load();

public:
  staroid();

  void display();

  void shading(const Shader &shader);

  void color(const Color &color);

  void pos(const Vector3 &pos);

};

#endif // STAROID_H
