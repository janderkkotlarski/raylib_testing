#ifndef STAROID_H
#define STAROID_H

#include "raylib.h"

class staroid
{
private:
  float m_size
  { 1.0f };

  Vector3 m_pos
  { 0.0f, 0.0f, 0.0f };

  Model m_model;

public:
  staroid();

};

#endif // STAROID_H
