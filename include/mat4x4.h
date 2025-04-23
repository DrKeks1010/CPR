#ifndef _MAT4X4_H
#define _MAT4X4_H

#include <math.h>
#include "vec3.h"

typedef float mat4x4[16];

#define mat4x4_identity() {\
  1.f,0.f,0.f,0.f,\
  0.f,1.f,0.f,0.f,\
  0.f,0.f,1.f,0.f,\
  0.f,0.f,0.f,1.f\
}

static inline void mat4x4_translateXf(mat4x4 m, float x)
{
  m[12] += m[0] * x;
  m[13] += m[1] * x;
  m[14] += m[2] * x;
}
static inline void mat4x4_translateYf(mat4x4 m, float y)
{
  m[12] += m[4] * y;
  m[13] += m[5] * y;
  m[14] += m[6] * y;
}
static inline void mat4x4_translateZf(mat4x4 m, float z)
{
  m[12] += m[8] * z;
  m[13] += m[9] * z;
  m[14] += m[10] * z;
}
static inline void mat4x4_translateXYZf(mat4x4 m, float x, float y, float z)
{
  m[12] += m[0] * x + m[4] * y + m[8] * z;
  m[13] += m[1] * x + m[5] * y + m[9] * z;
  m[14] += m[2] * x + m[6] * y + m[10] * z;
}
static inline void mat4x4_translateXYZvec3(mat4x4 m, vec3 v)
{
  m[12] += m[0] * v[0] + m[4] * v[1] + m[8] * v[2];
  m[13] += m[1] * v[0] + m[5] * v[1] + m[9] * v[2];
  m[14] += m[2] * v[0] + m[6] * v[1] + m[10] * v[2];
}

static inline void mat4x4_rotateXf(mat4x4 m, float a)
{
  float c = cos(a);
  float s = sin(a);

  float tmp = m[1];
  m[1] = c * tmp - s * m[2];
  m[2] = c * m[2] + s * tmp;

  tmp = m[5];
  m[5] = c * tmp - s * m[6];
  m[6] = c * m[6] + s * tmp;

  tmp = m[9];
  m[9] = c * tmp - s * m[10];
  m[10] = c * m[10] + s * tmp;

  tmp = m[13];
  m[13] = c * tmp - s * m[14];
  m[14] = c * m[14] + s * tmp;  
}
static inline void mat4x4_rotateYf(mat4x4 m, float a)
{
  float c = cos(a);
  float s = sin(a);

  float tmp = m[0];
  m[0] = c * tmp + s * m[2];
  m[2] = c * m[2] - s * tmp;

  tmp = m[4];
  m[4] = c * tmp + s * m[6];
  m[6] = c * m[6] - s * tmp;

  tmp = m[8];
  m[8] = c * tmp + s * m[10];
  m[10] = c * m[10] - s * tmp;

  tmp = m[12];
  m[12] = c * tmp + s * m[14];
  m[14] = c * m[14] - s * tmp;
}
static inline void mat4x4_rotateZf(mat4x4 m, float a)
{
  float c = cos(a);
  float s = sin(a);

  float tmp = m[0];
  m[0] = c * tmp - s * m[1];
  m[1] = c * m[1] + s * tmp;

  tmp = m[4];
  m[4] = c * tmp - s * m[5];
  m[5] = c * m[5] + s * tmp;

  tmp = m[8];
  m[8] = c * tmp - s * m[9];
  m[9] = c * m[9] + s * tmp;

  tmp = m[12];
  m[12] = c * tmp - s * m[13];
  m[13] = c * m[13] + s * tmp;
}

static inline void mat4x4_mulXYZf(const mat4x4 m, vec3 out, float x, float y, float z)
{
  out[0] = x * m[0] + y * m[4] + z * m[8] + m[12];
  out[1] = x * m[1] + y * m[5] + z * m[9] + m[13];
  out[2] = x * m[2] + y * m[6] + z * m[10] + m[14];
}

static inline void mat4x4_projection(mat4x4 m, float fov, float aspectRatio, float nearPlane, float farPlane)
{
  float val = tanf(M_PI / 360.f * fov);

  m[0] = val;
  m[5] = val * aspectRatio;
  m[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
  m[11] = -1;
  m[14] = 2 * farPlane * nearPlane / (nearPlane - farPlane);
  m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[12] = m[13] = m[15] = 0;
}

#endif
