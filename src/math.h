#ifndef WEFX_MATH__H
#define WEFX_MATH__H

#ifndef EPSILON
#define EPSILON 0.000000954
#endif

#ifndef M_PI
// clang-format off
#define M_PI     3.141592653589
#define M_PI2    6.283185307179
#define M_PI_SQR 9.869604401089
#define M_PID2   1.570796326794
#define M_3PID2  4.712388980384
// clang-format on
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

float abs(float n);
float sqrt(float n);

float to_radian(float degree);
float to_degree(float radians);

float floor(float n);
float ceil(float n);
float round(float x);

float pow(float x, float y);

float cos(float x);
float sin(float x);
float tan(float x);

int rand(void);
void srand(unsigned int seed);

#endif // WEFX_MATH__H
