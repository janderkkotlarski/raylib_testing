#include "staroid.h"

#include "raymath.h"

staroid::staroid()
{ load(); }

void staroid::display()
{ DrawModel(m_model, m_pos, m_size, m_color);}

void staroid::load()
{ m_model = LoadModel("staroid.obj"); }

void staroid::texture(const Texture &texture)
{ m_model.materials[0].maps[MAP_DIFFUSE].texture = texture; }

void staroid::shading(Shader &shader)
{ m_model.materials[0].shader = shader; }

void staroid::color(const Color &color)
{ m_color = color; }

void staroid::pos(const Vector3 &pos)
{ m_pos = pos; }

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
