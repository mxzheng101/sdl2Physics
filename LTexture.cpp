// File: LTexture.cpp

#include "LTexture.hpp"

LTexture::LTexture()
{
    mRenderer = nullptr;
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    free();
    mRenderer = renderer;

    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        printf("unable to load image %s. error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xff, 0xff));

    newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
    if (newTexture == nullptr)
    {
        printf("unable to create texture from %s. error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    mTexture = newTexture;
    return mTexture != nullptr;
}

void LTexture::free()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(mTexture, r, g, b);
}

void LTexture::setBlend(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, Vec2 size, double angle, SDL_Rect* clip, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad;
    if (size.x < 0 && size.y < 0)
    {
        renderQuad = {x, y, mWidth, mHeight};
    }
    else 
    {
        renderQuad = {x, y, (int)size.x, (int)size.y};
    }
    
    if (clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

// End File: LTexture.cpp