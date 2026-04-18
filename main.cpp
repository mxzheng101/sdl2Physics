#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>

#include "LTexture.hpp"
#include "Circle.hpp"
#include "Obj.hpp"
#include "Vec2.hpp"
#include "physWorld.hpp"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

std::vector<Obj*> gObjectList;

physWorld gWorld;

LTexture gDotTexture;

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

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("could not intialize img. %s\n", IMG_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

    return true;
}

bool loadMedia()
{
    if (!gDotTexture.loadFromFile("dot.bmp", gRenderer))
    {
        printf("failed to load dot texture.\n");
        return false;
    }
    return true;
}

void createObjects()
{
    Transform* dotTrans = new Transform{{0.0, 0.0}, {25.0, 25.0}, 0.0};
    Obj* dot = new Obj{dotTrans, {0.0, 0.0}, {0.0, 0.0}, 10, &gDotTexture};
    gObjectList.push_back(dot);
    gWorld.addObject(dot);
}

void render(int screenX, int screenY)
{
    for (Obj* object : gObjectList)
    {
        object->Texture->render(object->Trans->Position.x - screenX, object->Trans->Position.y - screenY, object->Trans->Scale, object->Trans->Rotation);
    }
}

void close()
{
    gDotTexture.free();
    for (Obj* object : gObjectList)
    {
        delete object;
    }
    gObjectList.clear();

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
        printf("unable to laod media.\n");
        return 2;
    }

    createObjects();

    bool quit = false;
    SDL_Event e;

    uint32_t lastTime = SDL_GetTicks();

    int relScreenX = -SCREEN_WIDTH / 2;
    int relScreenY = -SCREEN_HEIGHT / 2;
    int lastScreenAbsX;
    int lastScreenAbsY;
    SDL_GetWindowPosition(gWindow, &lastScreenAbsX, &lastScreenAbsY);
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_WINDOWEVENT)
            {
                if (e.window.event == SDL_WINDOWEVENT_MOVED)
                {
                    relScreenX += (e.window.data1 - lastScreenAbsX);
                    relScreenY += (e.window.data2 - lastScreenAbsY);

                    lastScreenAbsX = e.window.data1;
                    lastScreenAbsY = e.window.data2;
                }
            }
        }

        uint32_t currentTime = SDL_GetTicks();
        double dt = (double)(currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gWorld.update(dt, SCREEN_WIDTH, SCREEN_HEIGHT, relScreenX, relScreenY);
        render(relScreenX, relScreenY);

        SDL_RenderPresent(gRenderer);
    }


    close();

    return 0;
}