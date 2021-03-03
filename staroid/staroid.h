#ifndef STAROID_H
#define STAROID_H

#include "raylib.h"

class staroid
{
private:
  const bool m_central
  { false };

  float m_factor
  { 0.01f };

  Vector3 m_pos
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_rot
  { 0.0f, 0.0f, 0.0f };

  Model m_model;

  Color m_color
  { 63, 63, 63, 255 };

  void init();

public:
  staroid();

  staroid(const bool central);

  void display();

  void texture(const Texture &texture);

  void shading(Shader &shader);

  void color(const Color &color);

  void pos(const Vector3 &pos);

  void factor(const float factor);

  void rotate();

};

#endif // STAROID_H
