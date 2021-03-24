#ifndef STAROID_H
#define STAROID_H

#include <chrono>

#include "raylib.h"

class staroid
{
private:

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

  const float m_mass
  { 0.0f };

  float m_dist
  { 0.0f };

  Vector3 m_rot
  // Spatial orientation
  { 0.0f, 0.0f, 0.0f };

  Model m_model;
  // 3D model

  Color m_color
  // Color
  { 63, 63, 63, 255 };

  const std::chrono::steady_clock::duration m_duration
  // Visibility duration
  { 500000000 };

  std::chrono::steady_clock::duration m_time
  // Duration
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

  staroid(const float mass);

  float get_mass()
  const noexcept;

  Vector3 get_pos()
  const noexcept;

  float get_dist()
  const noexcept;

  void display()
  noexcept;

  void set_texture(const Texture &texture);

  void set_shading(Shader &shader);

  void set_color(const Color &color);

  void set_pos(const Vector3 &pos);

  void set_vel(const Vector3 &vel);

  void set_factor(const float factor);

  void rotate();

  void accelerate(const staroid &star);

  void accelerate(const float mass);

  void fall(const float slice);

};

#endif // STAROID_H
