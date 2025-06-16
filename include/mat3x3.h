#ifndef _MAT3X2_H
#define _MAT2X2_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vec3.h"
#include "mat4x4.h"

typedef GLfloat mat3x3[9];

#define mat3x3_identity() {\
	(GLfloat)1.f,(GLfloat)0.f,(GLfloat)0.f,\
	(GLfloat)0.f,(GLfloat)1.f,(GLfloat)0.f,\
	(GLfloat)0.f,(GLfloat)0.f,(GLfloat)1.f,\
}

static inline void mat3x3_copyMat4x4(mat3x3 to, const mat4x4 from)
{
	vec3_copy(to, from);
	vec3_copy(to + 3, from + 4);
	vec3_copy(to + 6, from + 8);
}

static inline void mat3x3_mulf(mat3x3 m, GLfloat f)
{
	vec3_mulf(m, f);
	vec3_mulf(m + 3, f);
	vec3_mulf(m + 6, f);
}

#endif
