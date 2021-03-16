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

// void rotate_

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

  Vector2Rotate(vec2, angle);

  if (x)
  {
    vec3.y = vec2.x;
    vec3.z = vec2.y;
  }
  else if (y)
  {
    vec3.z = vec2.x;
    vec3.x = vec2.y;
  }
  else if (z)
  {
    vec3.x = vec2.x;
    vec3.y = vec2.y;
  }
}
