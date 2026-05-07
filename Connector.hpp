// File: Connector.hpp
#pragma once

#include "Obj.hpp"
#include "Vec2.hpp"

struct Connector
{
    Obj* parent;
    Obj* child;

    Vec2 localPos;
};
// End File: Connector.hpp