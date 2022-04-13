/*

# Math Functions

First we include the header file which define some constants and macros.

*/
#include "math.h"
/*

Params for the random number generator (lcg below)
See this paper for more info: https://epub.wu.ac.at/1288/1/document.pdf

*/
#define RND_2_31_MINUS_ONE 2147483647
#define RND_PARK_MILLER 16807
/*

## Abs function

*/
float abs(float n)
{
    if (n < 0)
        return n * -1;
    return n;
}
/*

## Degree To Radians

*/
float to_radian(float degree)
{
    return degree * (M_PI / 180);
}
/*

## Radians To Degrees

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

First we define the curve we're going to use to emulate cosine

$$p = \frac{x}{\pi^{2}}$$

recursively split the line and tilt it so the our fake wave starts and
stops at about the right place

$$r = p - 0.25 -  \lfloor p + 0.25 \rfloor $$

now put it together and make sure the ends touch

$$y = r \times 16 \times \lvert r - 0.5 \rvert$$

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

## Seed Random

Here we can seed the random number generator, or just use the
default seed if one isn't provided

*/
static unsigned int SEED = 9035768;
void srand(unsigned int seed)
{
    SEED = seed;
}
/*

## Random

Basic random number generator. Linear congruential generator

If the increment (inc) = 0, the generator is a multiplicative
congruential generator (MCG)

If inc != 0, the method is called a mixed congruential generator.

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
