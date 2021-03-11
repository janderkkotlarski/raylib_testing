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

void rotate_vector3_xyz(Vector3 &vec, const float angle,
                        const bool x, const bool y, const bool z)
{


  // if (x)
  // { Vector2Rotate(Vector2{})
}
