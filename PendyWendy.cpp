#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>

#include "PendulumCart.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

PendulumCart* gCarter;


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("window could not be created. %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("linear texture filtering not enabled");
    }

    gWindow = SDL_CreateWindow("Circle BOP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        printf("window could not be created. %s\n", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr)
    {
        printf("renderer could not be created. %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

    return true;
}

bool loadMedia()
{
    return true;
}

void createObjects()
{
    gCarter = new PendulumCart(gRenderer, 10.0, 0.5, 2.0, 1.5);
}

void close()
{
    delete gCarter;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[])
{

    (void) argc;
    (void) args;

    if (!init())
    {
        printf("failed to init.\n");
        return 1;
    }

    if (!loadMedia())
    {
        printf("unable to load media.\n");
        return 2;
    }

    createObjects();

    bool quit = false;
    SDL_Event e;

    uint32_t lastTime = SDL_GetPerformanceCounter();

    while (!quit)
    {
        bool leftDown{false}, rightDown{false};
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            leftDown = true;
                            break;
                        case SDLK_RIGHT:
                            rightDown = true;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            leftDown = false;
                            break;
                        case SDLK_RIGHT:
                            rightDown = false;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        uint32_t currentTime = SDL_GetPerformanceCounter();
        double dt = (double)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        if (leftDown)
        {
            gCarter->applyForce(-800);
        }
        if (rightDown)
        {
            gCarter->applyForce(800);
        }

        gCarter->update(dt);
        gCarter->render();

        SDL_RenderPresent(gRenderer);
    }


    close();

    return 0;
}