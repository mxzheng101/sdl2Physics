// File: Trig.hpp
#pragma once

// fast approximations of trig functions
// rust implementation for fast sine
/*
fn sine(x: f32) -> f32 {
    let coeffs = [
        -0.10132118f32,          // x
         0.0066208798f32,        // x^3
        -0.00017350505f32,       // x^5
         0.0000025222919f32,     // x^7
        -0.000000023317787f32,   // x^9
         0.00000000013291342f32, // x^11
    ];
    let pi_major = 3.1415927f32;
    let pi_minor = -0.00000008742278f32;
    let x2 = x*x;
    let p11 = coeffs[5];
    let p9  = p11*x2 + coeffs[4];
    let p7  = p9*x2  + coeffs[3];
    let p5  = p7*x2  + coeffs[2];
    let p3  = p5*x2  + coeffs[1];
    let p1  = p3*x2  + coeffs[0];
    (x - pi_major - pi_minor) *
    (x + pi_major + pi_minor) * p1 * x
}*/

double fastSine(double x)
{
    double coeffs[] = {
        -0.10132118,          // x
         0.0066208798,        // x^3
        -0.00017350505,       // x^5
         0.0000025222919,     // x^7
        -0.000000023317787,   // x^9
         0.00000000013291342 // x^11
    };
    double pi_major = 3.1415927;
    double pi_minor = -0.00000008742278;
    double x2 = x*x;
    double p11 = coeffs[5];
    double p9 = p11*x2 + coeffs[4];
    double p7 = p9*x2 + coeffs[3];
    double p5 = p7*x2 + coeffs[2];
    double p3 = p5*x2 + coeffs[1];
    double p1 = p3*x2 + coeffs[0];

    return (x - pi_major - pi_minor) * (x + pi_major + pi_minor) * p1 * x;
}

double fastCosine(double x)
{
    return fastSine(x - 1.570796);
}