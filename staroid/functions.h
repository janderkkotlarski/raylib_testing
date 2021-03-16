#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <chrono>

#include "raylib.h"
#include "raymath.h"

float chronolizer(std::chrono::steady_clock::time_point &time);

void millis_wait();

void rotate_vector3_xyz(Vector3 &vec3, const float angle,
                        const bool x, const bool y, const bool z);

#endif // FUNCTIONS_H


