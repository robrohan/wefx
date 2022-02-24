#include "math.h"

// Params for the random number generator (lcg below)
// See this paper for more info:
// https://epub.wu.ac.at/1288/1/document.pdf
#define RND_2_31_MINUS_ONE 2147483647
#define RND_PARK_MILLER 16807

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
    float p = x / M_PI2;
    float r = p - .25 - floor(p + .25);
    float y = r * 16 * (abs(r) - 0.5);
    return y;
}

// XXX: Remove the division?
float sin(float x)
{
    return cos(x - M_PID2);
}

static unsigned int SEED = 9035768;
void srand(unsigned int seed)
{
    SEED = seed;
}

/**
 * Very basic random number generator. Linear
 * congruential generator
 *
 * If the increment (inc) = 0, the generator is a
 * multiplicative congruential generator (MCG)
 *
 * If inc != 0, the method is called a mixed
 * congruential generator.
 */
int lcg(int md, int mult, int inc, int seed)
{
    SEED = (mult * seed + inc) % md;
    return SEED;
}

int rand()
{
    return lcg(RND_2_31_MINUS_ONE, RND_PARK_MILLER, 0, SEED);
}
