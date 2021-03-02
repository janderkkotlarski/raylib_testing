#include "staroid.h"

staroid::staroid()
{ load(); }

void staroid::display()
{ DrawModel(m_model, m_pos, m_size, m_color);}

void staroid::load()
{
  m_model = LoadModel("staroid.obj");

  m_model.materials[0].maps[MAP_DIFFUSE].texture =
    LoadTextureFromImage(GenImageColor(1000, 1000, WHITE));
}

void staroid::shading(const Shader &shader)
{ m_model.materials[0].shader = shader; }

void staroid::color(const Color &color)
{ m_color = color; }

void staroid::pos(const Vector3 &pos)
{ m_pos = pos; }
