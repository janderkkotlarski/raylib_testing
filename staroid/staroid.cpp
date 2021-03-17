#include "staroid.h"

#include "raymath.h"

staroid::staroid()
{ init(); }

staroid::staroid(const float mass)
  : m_mass(mass)
{ init(); }

float staroid::get_mass()
const noexcept
{ return m_mass; }

Vector3 staroid::get_pos()
const noexcept
{ return m_pos; }

void staroid::display()
noexcept
{
  // timer();

  if (m_exist)
  { DrawModel(m_model, m_pos, m_factor, m_color); }
}

void staroid::init()
{
  if (m_mass > 0.0f)
  {
    m_pos = (Vector3){ 0.0f, 0.0f, 0.0f };
    m_factor *= 4.0f;
  }

  m_model = LoadModel("staroid.obj");
}

void staroid::timer()
{
  m_time = std::chrono::steady_clock::now() - m_start;

  if (m_time > m_duration)
  { m_exist = false; }
}

void staroid::reset()
{
  m_time = std::chrono::steady_clock::duration{ 0 };

  m_exist = true;
}

void staroid::texture(const Texture &texture)
{ m_model.materials[0].maps[MAP_DIFFUSE].texture = texture; }

void staroid::shading(Shader &shader)
{ m_model.materials[0].shader = shader; }

void staroid::color(const Color &color)
{ m_color = color; }

void staroid::pos(const Vector3 &pos)
{ m_pos = pos; }

void staroid::factor(const float factor)
{ m_factor = factor; }

void staroid::rotate()
{
  if (IsKeyDown('L'))
  { m_rot.x += 0.01; }
  else if (IsKeyDown('J'))
  { m_rot.x -= 0.01; }
  else if (IsKeyDown('I'))
  { m_rot.y += 0.01; }
  else if (IsKeyDown('K'))
  { m_rot.y -= 0.01; }
  else if (IsKeyDown('O'))
  { m_rot.z += 0.01; }
  else if (IsKeyDown('U'))
  { m_rot.z -= 0.01; }

  m_model.transform = MatrixRotateXYZ(m_rot);
}

void staroid::accelerate(const staroid &star)
{
  if (star.get_mass() > 0.0f)
  {
    const Vector3 difference
    { Vector3Subtract(star.get_pos(), m_pos) };

    const float distance
    { Vector3Length(difference) + 0.1f };

    const float acceleration
    { star.get_mass()/(distance*distance) };

    m_acc = Vector3Scale(difference, acceleration);
  }
}

void staroid::fall(const float slice)
{
  m_vel = Vector3Add(m_vel, Vector3Scale(m_acc, slice));

  m_pos = Vector3Add(m_pos, Vector3Scale(m_vel, slice));
}
