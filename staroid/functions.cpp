#include "functions.h"

float chronolizer(std::chrono::steady_clock::time_point &time)
{
  // return static_cast<float>(time);

  return 0.0f;
}

void millis_wait()
{
  std::chrono::steady_clock::time_point time_1
  { std::chrono::steady_clock::now() };

  std::chrono::steady_clock::time_point time_2
  { std::chrono::steady_clock::now() };

  std::chrono::steady_clock::duration delta
  { time_2 - time_1 };

  while (delta.count() <= 1000000)
  {
    time_2 = std::chrono::steady_clock::now();

    delta = time_2 - time_1;
  }
}

float theta_picker(const float fraction)
noexcept
{ return asin(2.0f*(fraction - 0.5f)); }

float phi_picker(const float fraction)
noexcept
{ return 2.0f*PI*(fraction - 1.0f); }

void rotate_vector2(Vector2 &vec2, const float angle)
{ vec2 = Vector2{ vec2.x*cos(angle) - vec2.y*sin(angle), vec2.y*cos(angle) + vec2.x*sin(angle) }; }

void rotate_vector3_xyz(Vector3 &vec3, const float angle,
                        const bool x, const bool y, const bool z)
{
  Vector2 vec2
  { 0.0f, 0.0f };

  if (x)
  { vec2 = Vector2{ vec3.y, vec3.z }; }
  else if (y)
  { vec2 = Vector2{ vec3.z, vec3.x }; }
  else if (z)
  { vec2 = Vector2{ vec3.x, vec3.y }; }

  rotate_vector2(vec2, angle);

  if (x)
  { vec3 = Vector3{ vec3.x, vec2.x, vec2.y }; }
  else if (y)
  { vec3 = Vector3{ vec2.y, vec3.y, vec2.x }; }
  else if (z)
  { vec3 = Vector3{ vec2.x, vec2.y, vec3.z }; }
}
