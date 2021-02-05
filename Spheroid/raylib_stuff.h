#ifndef RAYLIB_STUFF_H
#define RAYLIB_STUFF_H

#include <string>

#include "raylib.h"

float square_dist(const float x1, const float y1,
                  const float x2, const float y2)
noexcept;

void heart_fractal(float &xf, float &yf,
                   const float xf2, const float yf2,
                   const float real, const float imag);

void polar_fractal(float &xf, float &yf);

int fractaler(float &xf, float &yf);

Color color_mixer(const int x, const int y, const int image_size);

Image painter(const int image_size);

void shading();

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

#endif // RAYLIB_STUFF_H
