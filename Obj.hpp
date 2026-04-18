// File: Obj.hpp
#pragma once

#include "Vec2.hpp"
#include "LTexture.hpp"
#include "Transform.hpp"

struct Obj
{
    Transform* Trans;
    Vec2 Velocity;
    Vec2 Force;
    double mass;

    LTexture* Texture;
};