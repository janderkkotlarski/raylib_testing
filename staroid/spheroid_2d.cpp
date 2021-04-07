#include "spheroid_2d.h"

#include <math.h>

spheroid_2d::spheroid_2d()
noexcept
{}

void spheroid_2d::display()
const noexcept
{ DrawCircle3D(m_pos, m_radius, m_dir, m_angle, BLUE); }

void spheroid_2d::rotate(const float delta_angle)
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

  m_dir.y = cos(sqrt(2.0f)*m_angle_2);
  m_dir.z = sin(0.9f*m_angle_2);
}
