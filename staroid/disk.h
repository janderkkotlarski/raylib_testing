#ifndef DISK_H
#define DISK_H

#include "raylib.h"

class disk
{
private:
  const int m_width
  { 400 };

  const int m_height
  { 400 };

  const int m_radius
  { 200 };

  Image m_image
  { GenImageColor(m_width, m_height, WHITE) };

  Texture2D m_texture
  { LoadTextureFromImage(m_image) };

public:
  disk();

  void display();
};

#endif // DISK_H
