// File: Circle.hpp

#pragma once

#include <SDL.h>
#include "Trig.hpp"

inline void renderCircle(SDL_Renderer* renderer, int x, int y, int rad, SDL_Color color, int n = 50)
{
    SDL_Vertex *vertices = new SDL_Vertex[n + 1];
    int* indices = new int[n*3];

    vertices[0] = {{(float)x, (float)y}, color, {0.0, 0.0}};

    double PI = 3.1415927;
    double inc = (2*PI) / n;
    for (int i = 1; i <= n; ++i)
    {
        float xPos = (float) rad * (float) fastCosine((i-1) * inc) + x;
        float yPos = (float) rad * (float) fastSine((i-1)*inc) + y;
        vertices[i] = {xPos, yPos, color, {0.0, 0.0}};
        //printf("x: %f y: %f\n", xPos, yPos);
    }


    for (int i = 0; i < n - 1; ++i)
    {
        indices[i*3] = 0;
        indices[(i*3) + 1] = i + 1;
        indices[(i*3) + 2] = i + 2;
    }
    indices[(n-1)*3] = 0;
    indices[(n-1)*3 + 1] = n;
    indices[(n-1)*3 + 2] = 1;

    SDL_RenderGeometry(renderer, nullptr, vertices, n+1, indices, 3*n);
}

// End File: Circle.hpp