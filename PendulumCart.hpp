// File: PendulumCart.hpp
#pragma once

#include <SDL.h>
#include <cmath>
#include <array>
#include "Circle.hpp"

#define PIX_PER_M 150

class PendulumCart
{
private:
    double mState[4];
    double cartMassKG, pendulumMassKG, pendulumLengthM;

    double mForce;

    SDL_Renderer* gRenderer;

    double mInitialAngle;

    void takeDers(double kValue[], double offset[] = nullptr);

    double cartDamping;
    double pendulumDamping;

public:
    PendulumCart(SDL_Renderer* renderer, double cMass, double pMass, double pLength, double initialAngle = 0);
    ~PendulumCart();

    void applyForce(double forceNewtons);
    void update(double dt);
    void render();

    void printState();
    void printInfo();
    
    void reset();
};