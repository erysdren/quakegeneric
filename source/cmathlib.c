
float ceil(float f)
{
	int i = (int)f;

	if (f == (float)i)
		return i;

	return i + 1;
}

float floor(float f)
{
	int i = (int)f;

	if (f == (float)i)
		return i;

	return i;
}

float sqrt(float a) { return __builtin_sqrt(a); }
float sin(float radians) { return __builtin_sinf(radians); }
float cos(float radians) { return __builtin_cosf(radians); }
float tan(float radians) { return __builtin_tanf(radians); }
float asin(float a) { return __builtin_asinf(a); }
float acos(float a) { return __builtin_acosf(a); }
float atan(float a) { return __builtin_atanf(a); }
float atan2(float y, float x) { return __builtin_atan2f(y, x); }
