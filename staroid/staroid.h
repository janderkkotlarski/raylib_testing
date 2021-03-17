#ifndef STAROID_H
#define STAROID_H

#include <chrono>

#include "raylib.h"

class staroid
{
private:
  const bool m_central
  { false };

  float m_factor
  // Scale factor for the 3D model
  { 0.01f };

  Vector3 m_pos
  // Position
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_vel
  // Velocity
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_acc
  // Acceleration
  { 0.0f, 0.0f, 0.0f };

  Vector3 m_rot
  { 0.0f, 0.0f, 0.0f };

  Model m_model;

  Color m_color
  { 63, 63, 63, 255 };

  const std::chrono::steady_clock::duration m_duration
  { 500000000 };

  std::chrono::steady_clock::duration m_time
  { 0 };

  const std::chrono::steady_clock::time_point m_start
  { std::chrono::steady_clock::now() };

  bool m_exist
  { true };

  void init();

  void timer();

  void reset();

public:
  staroid();

  staroid(const bool central);

  Vector3 get_pos();

  void display()
  const noexcept;

  void texture(const Texture &texture);

  void shading(Shader &shader);

  void color(const Color &color);

  void pos(const Vector3 &pos);

  void factor(const float factor);

  void rotate();



};

#endif // STAROID_H
