#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <chrono>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "auronacci.h"
#include "staroid.h"

float chronolizer(std::chrono::steady_clock::time_point &time);

void millis_wait();

float theta_picker(const float fraction)
noexcept;

float phi_picker(const float fraction)
noexcept;

Vector3 sphere_pos(const float radius, const float theta, const float phi)
noexcept;

Vector3 sphere_vector(auronacci &gold, const float radius_min, const float radius_delta);

void rotate_vector2(Vector2 &vec2, const float angle);

void rotate_vector3_xyz(Vector3 &vec3, const float angle,
                        const bool x, const bool y, const bool z);

std::vector <Color> pastelbow()
noexcept;

std::vector <staroid> star_nursery(const float factor)
noexcept;

void stellarator(std::vector<staroid> &stars,
                 auronacci &gold)
noexcept;

#endif // FUNCTIONS_H


