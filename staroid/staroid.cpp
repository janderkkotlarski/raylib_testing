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

float staroid::get_dist()
const noexcept
{ return m_dist; }

float staroid::get_factor()
const noexcept
{ return m_factor; }

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

void staroid::set_texture(const Texture &texture)
{ m_model.materials[0].maps[MAP_DIFFUSE].texture = texture; }

void staroid::set_shading(Shader &shader)
{ m_model.materials[0].shader = shader; }

void staroid::set_color(const Color &color)
{ m_color = color; }

void staroid::set_pos(const Vector3 &pos)
{ m_pos = pos; }

void staroid::set_vel(const Vector3 &vel)
{ m_vel = vel; }

void staroid::set_factor(const float factor)
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
    { Vector3Length(difference) + 1.0f };

    const float acceleration
    { star.get_mass()*distance };

    m_acc = Vector3Scale(difference, acceleration);
  }
}

void staroid::accelerate(const float mass)
{
  if (mass > 0.0f)
  {
    const float distance
    { m_dist + 1.0f };

    const float acceleration
    { -mass*distance };

    m_acc = Vector3Scale(m_pos, acceleration);
  }
}

void staroid::fall(const float slice)
{
  m_vel = Vector3Add(m_vel, Vector3Scale(m_acc, slice));

  m_pos = Vector3Add(m_pos, Vector3Scale(m_vel, slice));

  m_dist = Vector3Length(get_pos());
}
