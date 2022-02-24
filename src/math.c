#include "math.h"

float abs(float n)
{
    if (n < 0)
        return n * -1;
    return n;
}

float to_radian(float degree)
{
    return degree * (M_PI / 180);
}

float to_degree(float radian)
{
    return radian * (180 / M_PI);
}

// XXX: Is there a better way to do this?
float pow(float x, float y)
{
    float rtn = x;
    while (y > 1)
    {
        rtn *= x;
        y--;
    }
    return rtn;
}

float floor(float n)
{
    float base = (float)(int)(n - ((int)n % 1));
    if (n < 0)
        return base - 1;
    return base;
}

float ceil(float n)
{
    float base = (float)(int)(n - ((int)n % 1));
    if (n > 0)
        return base + 1;
    return base;
}

float round(float x)
{
    float m = x - (int)x;
    if (m < 0.5)
        return floor(x);
    return ceil(x);
}

// XXX: Simplify?
float cos(float x)
{
    float p = x / (2. * M_PI);
    float r = p - .25 - floor(p + .25);
    float y = r * 16 * (abs(r) - 0.5);
    return y;
}

// XXX: Remove the division?
float sin(float x)
{
    return cos(x - (M_PI / 2));
}
