#ifndef _MAT3X2_H
#define _MAT2X2_H

#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vec3.h"

typedef GLfloat mat3x3[9];

#define mat3x3_identity() {\
	(GLfloat)1.f,(GLfloat)0.f,(GLfloat)0.f,\
	(GLfloat)0.f,(GLfloat)1.f,(GLfloat)0.f,\
	(GLfloat)0.f,(GLfloat)0.f,(GLfloat)1.f,\
}

#endif
