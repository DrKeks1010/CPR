#ifndef _VEC3_H
#define _VEC3_H

#include <math.h>

typedef float vec3[3];

#define vec3_empty() {0.f,0.f,0.f}
static inline void vec3_addXf(vec3 v, float x)
{
	v[0] += x;
}
static inline void vec3_addYf(vec3 v, float y)
{
	v[1] += y;
}
static inline void vec3_addZf(vec3 v, float z)
{
	v[2] += z;
}
static inline void vec3_add(vec3 a, const vec3 b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

static inline void vec3_mulf(vec3 v, float f)
{
	v[0] *= f;
	v[1] *= f;
	v[2] *= f;
}

static inline void vec3_normalize(vec3 v)
{
	float len_sq = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	if (len_sq < 0.001f) return;

	vec3_mulf(v, 1 / len_sq);
}

#endif
