#include "math.h"

//                           s|-exp--||---mantissa----------|
static int MANTISSA_MASK = 0b00000000011111111111111111111111;

float abs(float n)
{
	if(n<0) {
		return n * -1;
	}
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

// XXX: Could be better
float floor(float shift)
{
	if(shift < 0)
	    return (float)((int)(shift + 0.5));
	else
	    return (float)((int)(shift - 0.5));
}

float ceil(float shift)
{
	if(shift < 0)
	    return (float)((int)(shift - 0.5));
	else 
	    return (float)((int)(shift + 0.5));
}

// XXX: This is pretty rough.
float round(float x)
{
    float mantissa = (float) ((int)x & MANTISSA_MASK);
    if (mantissa < 0.5)
        return floor(x);
    else
        return ceil(x);
}

float cos(float x) 
{
	float p = x / (2. * M_PI);
	float r = p - .25 - floor(p + .25);
	float y = r * 16 * (abs(r) - 0.5);
	return y;
}

float sin(float x)
{
	return cos(x - (M_PI / 2));
}
