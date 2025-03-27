#ifndef _LINMATH_H
#define _LINMATH_H

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
