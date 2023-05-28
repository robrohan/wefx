/*

# Math Functions

First we include the header file which define some constants and macros.

*/
#include "math.h"
/*

Params for the random number generator (lcg below)

*/
#define RND_2_31_MINUS_ONE 2147483647
#define RND_PARK_MILLER 16807
/*

## Abs function

The _abs_ function will return the absolute value of the given number.

*/
float abs(float n)
{
    if (n < 0)
        return n * -1;
    return n;
}
/*

## Degree To Radians

The _to\_radian_ function converts a degree value to a radian value. This is simply:

$$ r = d \cdot \left(\pi / 180\right)$$

*/
float to_radian(float degree)
{
    return degree * (M_PI / 180);
}
/*

## Radians To Degrees

The _to\_degree_ function converts a radian value to a degree value. This is simply:

$$ d = r \cdot \left(180 / \pi\right)$$

*/
float to_degree(float radian)
{
    return radian * (180 / M_PI);
}
/*

## Power

*/
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
/*

## Floor

*/
float floor(float n)
{
    float base = (float)(int)(n - ((int)n % 1));
    if (n < 0)
        return base - 1;
    return base;
}
/*

## Ceiling

*/
float ceil(float n)
{
    float base = (float)(int)(n - ((int)n % 1));
    if (n > 0)
        return base + 1;
    return base;
}
/*

## Round

*/
float round(float x)
{
    float m = x - (int)x;
    if (m < 0.5)
        return floor(x);
    return ceil(x);
}
/*

## Cosine function

This function produces a cosine approximation [@FastAccurateSineCosine_2017_Nick].

First we define the curve we're going to use to emulate cosine:

$$y = x \cdot 16 \cdot \left(\left|x\right|-w\right) $$

This curve looks close to cosine, but it does not repeat. So we
recursively split a line and tilt it so the our cosine-like curve starts
and stops at about the right place.

$$p = \frac{x}{\pi^{2}}$$

$$r = p - 0.25 -  \lfloor p + 0.25 \rfloor $$

now put it together and make sure the ends touch:

$$y = r \times 16 \times \lvert r - 0.5 \rvert$$

You can play more with the way this works on the Desmos website [@HandmadeCosine__Rohan]

*/
float cos(float x)
{
    float p = x / M_PI2;
    float r = p - .25 - floor(p + .25);
    float y = r * 16 * (abs(r) - 0.5);
    return y;
}
/*

## Sine function

The sine function is just cos shifted on the x axis

$$ sin\left(x\right) = cos\left(x - \frac{\pi}{2}\right) $$

*/
float sin(float x)
{
    return cos(x - M_PID2);
}
/*

## Tangent function

*/
float tan(float x)
{
    return sin(x) / cos(x);
}
/*

## Seed Random

Here we can seed the random number generator, or just use the
default seed if one isn't provided. The default seed has no special
meaning or value, it was just chosen at random.

*/
static unsigned int SEED = 9035768;
void srand(unsigned int seed)
{
    SEED = seed;
}
/*

## Random - rand()

Basic random number generator. Linear congruential generator

If the increment parameter is set to zero _inc = 0_, the generator is a _multiplicative
congruential generator (MCG)_. If the _inc_ parameter is not 0, the method is
called a mixed congruential generator [@PortableUniformRandomNumber__Hormann].

By default, when you call _rand()_ the increment value is set to zero.

*/
static int lcg(int md, int mult, int inc, int seed)
{
    SEED = (mult * seed + inc) % md;
    return SEED;
}

int rand()
{
    return lcg(RND_2_31_MINUS_ONE, RND_PARK_MILLER, 0, SEED);
}
/*

## Square root

Algorithm from an unknown Babylonian mathematician [@BabylonianSqareRoot_2023]

*/
float sqrt(float n)
{
    float z = 1.0;
    for (int i = 1; i <= 10; i++)
    {
        z -= (z * z - n) / (2 * z);
    }
    return z;
}
