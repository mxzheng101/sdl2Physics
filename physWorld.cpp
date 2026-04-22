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

void physWorld::update(double dt, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, int screenX, int screenY)
{
    if (dt < 1e-6) return;
    const double RESTITUTION = 0.3; // 1.0 = perfectly elastic, 0.0 = no bounce

    double wallVelX = (screenX - mPrevScreenX) / (PIX_TO_M * dt);
    double wallVelY = (screenY - mPrevScreenY) / (PIX_TO_M * dt);

    for (Obj* obj : mObjects)
    {
        obj->Force += obj->mass * mGravity;
        obj->Velocity += obj->Force / obj->mass * dt;
        obj->Trans->Position += obj->Velocity * dt;

        // Left wall
        if (obj->Trans->Position.x * PIX_TO_M < screenX)
        {
            obj->Trans->Position.x = (double) screenX / PIX_TO_M; 

            // first find the relative vel of ball vs wall, to calculate bouncing
            // add wall vel back to impart wall velocity
            double relVelX = obj->Velocity.x - wallVelX;
            if (relVelX < 0)
            {
                obj->Velocity.x = (-relVelX * RESTITUTION) + wallVelX;
            }
        }

        // Right wall
        if (obj->Trans->Position.x * PIX_TO_M + obj->Trans->Scale.x > screenX + SCREEN_WIDTH)
        {
            obj->Trans->Position.x = (double)(screenX + SCREEN_WIDTH - obj->Trans->Scale.x) / PIX_TO_M;
            double relVelX = obj->Velocity.x - wallVelX;
            if (relVelX > 0)
            {
                obj->Velocity.x = (-relVelX * RESTITUTION) + wallVelX;
            }
        }

        // Top wall
        if (obj->Trans->Position.y * PIX_TO_M < screenY)
        {
            obj->Trans->Position.y = (double)screenY / PIX_TO_M;
            double relVelY = obj->Velocity.y - wallVelY;
            if (relVelY < 0)
            {
                obj->Velocity.y = (-relVelY * RESTITUTION) + wallVelY;
            }
        }

        // Bottom wall (floor)
        if (obj->Trans->Position.y * PIX_TO_M + obj->Trans->Scale.y > (screenY + SCREEN_HEIGHT))
        {
            obj->Trans->Position.y = (double)(screenY + SCREEN_HEIGHT - obj->Trans->Scale.y) / PIX_TO_M;
            double relVelY = obj->Velocity.y - wallVelY;
            if (relVelY > 0)
            {
                obj->Velocity.y = (-relVelY * RESTITUTION) + wallVelY;
            }
        }

        if (DEBUG)
        {
            printf("x: %f, y: %f, xVel: %f, yVel: %f, wallX: %f, wallY: %f, dt: %f\n",
                obj->Trans->Position.x, obj->Trans->Position.y,
                obj->Velocity.x, obj->Velocity.y,
                wallVelX, wallVelY,
                dt);
        }

        obj->Force = {0.0, 0.0};
    }

    mPrevScreenX = screenX;
    mPrevScreenY = screenY;
}