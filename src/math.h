#ifndef WEFX_MATH__H
#define WEFX_MATH__H

#ifndef EPSILON
#define EPSILON 0.000000954
#endif

#ifndef M_PI

#define M_PI     3.141592653589
#define M_PI2    6.283185307179
#define M_PI_SQR 9.869604401089
#define M_PID2   1.570796326794

#endif

float abs(float n);

float to_radian(float degree);
float to_degree(float radians);

float floor(float n);
float ceil(float n);
float round(float x);

float pow(float x, float y);

float cos(float x);
float sin(float x);

#endif // WEFX_MATH__H
