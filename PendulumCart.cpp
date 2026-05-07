// File: PendulumCart.cpp

#include "PendulumCart.hpp"

PendulumCart::PendulumCart(SDL_Renderer* renderer, double cMass, double pMass, double pLength, double initialAngle)
{
    mState[0] = 0.0;
    mState[1] = 0.0;
    mState[2] = initialAngle;
    mState[3] = 0.0;

    gRenderer = renderer;

    cartMassKG = cMass;
    pendulumMassKG = pMass;
    pendulumLengthM = pLength;

    mForce = 0.0;

    mInitialAngle = initialAngle;

    cartDamping = 3.0;
    pendulumDamping = 3.0;
}

PendulumCart::~PendulumCart()
{
    mState[0] = 0.0;
    mState[1] = 0.0;
    mState[2] = 0.0;
    mState[3] = 0.0;

    gRenderer = nullptr;
}

void PendulumCart::applyForce(double forceNewtons)
{
    mForce += forceNewtons;
}

void PendulumCart::printState()
{
    // KE of cart
    double keCart = 0.5 * cartMassKG * mState[1] * mState[1];
    
    // KE of pendulum bob (absolute velocity)
    double vBobX = mState[1] + pendulumLengthM * mState[3] * fastCosine(mState[2]);
    double vBobY = pendulumLengthM * mState[3] * fastSine(mState[2]);
    double kePend = 0.5 * pendulumMassKG * (vBobX*vBobX + vBobY*vBobY);

    // PE of pendulum (taking pivot as reference, upward positive)
    double pe = pendulumMassKG * 9.8 * pendulumLengthM * fastCosine(mState[2]);

    double totalEnergy = keCart + kePend + pe;

    printf("E=%.4f  x=%.3f  xDot=%.3f  theta=%.3f  thetaDot=%.3f\n",
           totalEnergy, mState[0], mState[1], mState[2], mState[3]);
}

void PendulumCart::printInfo()
{
    printf("PendulumCart Info:\nCart Mass (kg): %f\nPendulum Mass (kg): %f\nPendulum Length (m): %f\n", cartMassKG, pendulumMassKG, pendulumLengthM);
}

void PendulumCart::reset()
{
    mState[0] = 0.0;
    mState[1] = 0.0;
    mState[2] = mInitialAngle;
    mState[3] = 0.0;

    mForce = 0.0;
}

void PendulumCart::takeDers(double kValue[], double offset[])
{
    double tempState[4] = {mState[0], mState[1], mState[2], mState[3]};
    // state: [x xdot t tdot]
    if (offset != nullptr)
    {
        for (int i = 0; i < 4; ++i)
        {
            tempState[i] += offset[i];
        }
    }

    // pi wrapping for fast sine and cosine
    tempState[2] = tempState[2] - 2*M_PI * floor((tempState[2] + M_PI) / (2*M_PI));
    
    double sineT = fastSine(tempState[2]);
    double cosT = fastCosine(tempState[2]);

    double doubleDotX = (mForce - cartDamping*tempState[1] - 
                  pendulumMassKG*9.8*sineT*cosT +
                  pendulumMassKG*pendulumLengthM*tempState[3]*tempState[3]*sineT) /
                  ((cartMassKG + pendulumMassKG) - 
                  pendulumMassKG*cosT*cosT);
    
    double doubleDotTheta = ((cartMassKG + pendulumMassKG)*9.8*sineT +
                       (mForce - cartDamping*tempState[1])*cosT -
                       pendulumMassKG*pendulumLengthM*tempState[3]*tempState[3]*sineT*cosT -
                       pendulumDamping*tempState[3]) /
                     ((cartMassKG + pendulumMassKG)*pendulumLengthM -
                       pendulumMassKG*pendulumLengthM*cosT*cosT);
    
    kValue[0] = tempState[1];
    kValue[1] = doubleDotX;
    kValue[2] = tempState[3];
    kValue[3] = doubleDotTheta;
}

void PendulumCart::update(double dt)
{
    // Runge-Kutta 4 estimation
    double k1[4], k2[4], k3[4], k4[4];
    double k2Off[4], k3Off[4], k4Off[4];

    takeDers(k1);
    for (int i = 0; i < 4; ++i)
    {
        k2Off[i] = (dt/2.0) *  k1[i];
    }

    takeDers(k2, k2Off);
    for (int i = 0; i < 4; ++i)
    {
        k3Off[i] = (dt/2.0) * k2[i];
    }

    takeDers(k3, k3Off);
    for (int i = 0; i < 4; ++i)
    {
        k4Off[i] = dt * k3[i];
    }

    takeDers(k4, k4Off);

    // update state 
    for (int i = 0; i < 4; ++i)
    {
        mState[i] += (dt/6.0)*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
    }
    // wrap state theta
    mState[2] = mState[2] - 2*M_PI * floor((mState[2] + M_PI) / (2*M_PI));
   
    // reset force
    mForce = 0.0;
}

void PendulumCart::render()
{
    SDL_Rect cartRect = {(int) (mState[0] * PIX_PER_M + 500), 300, 200, 200};
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawRect(gRenderer, &cartRect);

    int armX1, armY1, armX2, armY2;

    armX1 = (int) (mState[0] * PIX_PER_M + 500);
    armY1 = 300;
    armX2 = armX1 + (int)(fastSine(mState[2]) * pendulumLengthM * PIX_PER_M);
    armY2 = armY1 + (int)(fastCosine(mState[2]) * pendulumLengthM * PIX_PER_M);

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderDrawLine(gRenderer, armX1, armY1, armX2, armY2);
    renderCircle(gRenderer, armX2, armY2, 10, {0x00, 0x00, 0x00, 0xff});
}
