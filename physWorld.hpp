// File: physWorld.hpp
#pragma once

#include <vector>
#include <algorithm>
#include "Vec2.hpp"
#include "Obj.hpp"

#define PIX_TO_M 75

class physWorld
{
private:
    std::vector<Obj*> mObjects;
    Vec2 mGravity = {0.0, 9.81};

    int mPrevScreenX = 0;
    int mPrevScreenY = 0;

public:
    void addObject(Obj* object);
    void removeObject(Obj* object);

    void free();
    void update(double dt, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, int screenX, int screenY);
};