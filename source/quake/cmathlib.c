
#include <stdio.h>

double ceil(double a) { return __builtin_ceil(a); }
double floor(double a) { return __builtin_floor(a); }
double sqrt(double a) { return __builtin_sqrt(a); }
double sin(double a) { return __builtin_sin(a); }
double cos(double a) { return __builtin_cos(a); }
double tan(double a) { return __builtin_tan(a); }
double asin(double a) { return __builtin_asin(a); }
double acos(double a) { return __builtin_acos(a); }
double atan(double a) { return __builtin_atan(a); }
double atan2(double x, double y) { return __builtin_atan2(x, y); }

float ceilf(float a) { return __builtin_ceilf(a); }
float floorf(float a) { return __builtin_floorf(a); }
float sqrtf(float a) { return __builtin_sqrtf(a); }
float sinf(float a) { return __builtin_sinf(a); }
float cosf(float a) { return __builtin_cosf(a); }
float tanf(float a) { return __builtin_tanf(a); }
float asinf(float a) { return __builtin_asinf(a); }
float acosf(float a) { return __builtin_acosf(a); }
float atanf(float a) { return __builtin_atanf(a); }
float atan2f(float x, float y) { return __builtin_atan2f(x, y); }

int fscanf(FILE *file, const char *format, ...)
{
	return 0;
}
