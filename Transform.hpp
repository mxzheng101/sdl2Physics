// File: Transform.hpp
#pragma once

#include "Vec2.hpp"

struct CollisionPoints
{
    Vec2 A; // farthest point of a into b
    Vec2 B; // farthest point of b into a
    Vec2 Normal; // B - A normalized
    double depth; // length of B - A
    bool HasCollision;
};

struct Transform
{
    Vec2 Position;
    Vec2 Scale;
    double Rotation;
};