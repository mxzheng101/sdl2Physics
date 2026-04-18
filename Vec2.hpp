// File: Vec2.hpp
#pragma once

struct Vec2
{
    double x;
    double y;

    Vec2 operator+(const Vec2& other) const
    {
        return {x + other.x, y + other.y};
    }

    Vec2 operator*(double scalar) const
    {
        return {x * scalar, y * scalar};
    }

    Vec2 operator/(double scalar) const
    {
        return {x / scalar, y / scalar};
    }

    Vec2& operator+=(const Vec2& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Vec2& operator *=(const Vec2& other)
    {
        this->x *= other.x;
        this->y *= other.y;

        return *this;
    }
};

inline Vec2 operator*(double scalar, Vec2&v)
{
    return {v.x * scalar, v.y * scalar};
}
// End File: Vec2.hpp