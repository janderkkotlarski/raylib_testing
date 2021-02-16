#ifndef RAYLIB_STUFF_H
#define RAYLIB_STUFF_H

#include <string>

#include "raylib.h"

Vector3 delta_rotate(const Vector3 &vec_cos, const Vector3 &vec_sin);

void rotate(Vector3 &vec_x1, Vector3 &vec_y1);

void movement(Vector3 &position, Vector3 &forward,
              Vector3 &rightward, Vector3 &upward);

std::string vector2string(const Vector3 &vec)
noexcept;

void display_string(const std::string str,
                    const std::string &message,
                    const int x,
                    const int y,
                    const int size)
noexcept;

void display_text(const Vector3 &center, const Vector3 &position,
                  const Vector3 &forward, const Vector3 &rightward, const Vector3 &upward);

bool spherical_circle();

float phinizer(const int x, const int image_size);

float thetanizer(const int y, const int image_size);

void rancords(float &phi, float &theta,
              const int image_size);

Vector3 spherinizer(const float phi, const float theta);

Image filling(const int image_size);


void shading();

#endif // RAYLIB_STUFF_H
