// File: LTexture.hpp
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Vec2.hpp"


class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile( std::string path, SDL_Renderer* renderer );

    void free();

    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void setBlend(SDL_BlendMode blending);
    void setAlpha (Uint8 alpha);

    void render(int x, int y, Vec2 size = {-1, -1}, double angle = 0.0, SDL_Rect* clip = nullptr, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

private:

    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;

    int mWidth;
    int mHeight;
};

// End File: LTexture.hpp