#ifndef _VEC2_H
#define _VEC2_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef GLfloat vec2[2];
#define vec2_empty() {(GLfloat)0.f, (GLfloat)0.f}
static inline void vec2_setXYf(vec2 v, GLfloat x, GLfloat y)
{
	v[0] = x;
	v[1] = y;
}
static inline void vec2_sub(vec2 a, const vec2 b)
{
	a[0] -= b[0];
	a[1] -= b[1];
}
static inline void vec2_mulf(vec2 v, GLfloat s)
{
	v[0] *= s;
	v[1] *= s;
}

#endif
