#ifndef _LINMATH_H
#define _LINMATH_H

#include <math.h>

typedef float vec3[3];

typedef float mat4x4[16];

#define mat4x4_identity() {\
  1.f,0.f,0.f,0.f,\
  0.f,1.f,0.f,0.f,\
  0.f,0.f,1.f,0.f,\
  0.f,0.f,0.f,1.f\
}

static inline void mat4x4_translate3f(mat4x4 m, float x, float y, float z)
{
  m[12] += m[0] * x + m[4] * y + m[8] * z;
  m[13] += m[1] * x + m[5] * y + m[9] * z;
  m[14] += m[2] * x + m[6] * y + m[10] * z;
}
static inline void mat4x4_projection(mat4x4 m, float fov, float aspectRatio, float nearPlane, float farPlane)
{
  float right = tanf(M_PI / 360.0f * fov) * nearPlane;
  float top = right / aspectRatio;

  m[0] = nearPlane / right; 
  m[5] = nearPlane / top;
  m[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
  m[11] = -1;
  m[14] = 2 * farPlane * nearPlane / (nearPlane - farPlane);
  m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[12] = m[13] = m[15] = 0;
}

#endif
