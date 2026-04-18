// File: physWorld.cpp

#include "physWorld.hpp"


void physWorld::addObject(Obj* object)
{
    mObjects.push_back(object);
}

void physWorld::removeObject(Obj* object)
{
    mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), object), mObjects.end());
}

void physWorld::free()
{
    mObjects.clear();
}

void physWorld::update(double dt, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    for (Obj* obj : mObjects)
    {
        obj->Force += obj->mass * mGravity;

        obj->Velocity += obj->Force / obj->mass * dt;
        obj->Trans->Position += obj->Velocity * dt * PIX_TO_M;

        // check for collisions with walls
        if (obj->Trans->Position.x < 0)
        {
            obj->Trans->Position.x = 0;
        }
        if (obj->Trans->Position.y < 0)
        {
            obj->Trans->Position.y = 0;
        }
        if (obj->Trans->Position.x + obj->Trans->Scale.x > SCREEN_WIDTH)
        {
            obj->Trans->Position.x = SCREEN_WIDTH - obj->Trans->Scale.x;
        }
        if (obj->Trans->Position.y + obj->Trans->Scale.y > SCREEN_HEIGHT)
        {
            obj->Trans->Position.y = SCREEN_HEIGHT - obj->Trans->Scale.y;
        }

        obj->Force = {0.0, 0.0};
    }
}