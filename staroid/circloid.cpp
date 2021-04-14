#include "circloid.h"

#include "functions.h"

circloid::circloid()
noexcept
{}

circloid::circloid(auronacci &gold)
noexcept
{ recolor(gold); }

void circloid::recolor(auronacci &gold)
noexcept
{ m_color = random_pastel(gold); }

void circloid::display()
const noexcept
{ DrawCircle3D(m_pos, m_radius, m_dir, m_angle, m_color); }

void circloid::rotate(const float delta_angle)
noexcept
{
  m_angle += m_scale*delta_angle;

  const float full_circle
  { 360.0f };

  if (m_angle > full_circle)
  m_angle -= full_circle;

  m_angle_2 += m_scale_2*delta_angle;

  const float two_pi
  { 2.0f*PI };

  if (m_angle_2 > PI)
  { m_angle_2 -= two_pi; }

  m_dir.x = cos(m_angle_2);
  m_dir.y = sin(m_angle_2);

  m_angle_3 += m_scale_3*delta_angle;

  if (m_angle_3 > PI)
  { m_angle_3 -= two_pi; }

  m_radius = m_static + m_ripple*sin(m_angle_3);
}
