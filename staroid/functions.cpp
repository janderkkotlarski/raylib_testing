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

Vector3 sphere_pos(const float radius, const float theta, const float phi)
noexcept
{
  return Vector3{ radius*cos(theta)*cos(phi),
                  radius*cos(theta)*sin(phi),
                  radius*sin(theta)};
}

Vector3 sphere_vector(auronacci &gold, const float radius_min, const float radius_delta)
{
  const float radius
  { radius_min + radius_delta*gold.get_fraction() };

  const float theta
  { PI*(0.5f + theta_picker(gold.get_fraction())) };

  const float phi
  { phi_picker(gold.get_fraction()) };

  return sphere_pos(radius, theta, phi);
}

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

std::vector <Color> pastelbow()
noexcept
{
  const Color pastel_red
  { 255, 63, 63, 255 };

  const Color pastel_orange
  { 255, 160, 63, 255 };

  const Color pastel_yellow
  { 255, 255, 63, 255 };

  const Color pastel_lime
  { 160, 255, 63, 255 };

  const Color pastel_green
  { 63, 255, 63, 255 };

  const Color pastel_viridian
  { 63, 255, 160, 255 };

  const Color pastel_turquoise
  { 63, 255, 255, 255 };

  const Color pastel_electric
  { 63, 160, 255, 255 };

  const Color pastel_blue
  { 63, 63, 255, 255 };

  const Color pastel_indigo
  { 160, 63, 255, 255 };

  const Color pastel_violet
  { 255, 63, 255, 255 };

  const Color pastel_purple
  { 255, 63, 160, 255 };


  return  std::vector <Color>
  {
    pastel_red, pastel_orange, pastel_yellow, pastel_lime,
    pastel_green, pastel_viridian, pastel_turquoise, pastel_electric,
    pastel_blue, pastel_indigo, pastel_violet, pastel_purple
  };
}

std::vector <staroid> star_nursery(const float factor)
noexcept
{
  const int star_max
  { 200 };

  const std::vector <Color> pastels
  { pastelbow() };

  std::vector <staroid> stars;

  for (int count{ 0 }; count < star_max; ++count)
  {
    staroid aster;

    aster.set_color(pastels[count % pastels.size()]);
    aster.set_factor(factor);

    stars.push_back(aster);
  }

  return stars;
}

void stellarator(std::vector <staroid> &stars,
                 auronacci &gold)
noexcept
{
  const float radius_min
  { 1.5f };

  const float radius_delta
  { 0.0f };

  const float velocity_min
  { 5.000f };

  const float velocity_delta
  { 5.000f };

  for (staroid &aster: stars)
  {
    aster.set_pos(sphere_vector(gold, radius_min, radius_delta));
    aster.set_vel(sphere_vector(gold, velocity_min, velocity_delta));
  }
}

void astral_mechanics(std::vector <staroid> &stars,
                      const float factor,
                      const float time_slice)
noexcept
{
  for (staroid &aster: stars)
  {
    const float mass
    { 2.0f };

    const float horizon
    { 2.75f };

    aster.accelerate(mass);
    aster.fall(time_slice);

    const float dist
    { aster.get_dist() - horizon };

    if (dist > 0.0f)
    { aster.set_factor((1.0f - exp(-0.5f*dist))*factor); }
    else
    { aster.set_factor(0.0f); }
  }
}
