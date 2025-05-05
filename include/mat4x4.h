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

static inline void mat4x4_translateXYZf_right(mat4x4 m, float x, float y, float z)
{
  m[12] += m[0] * x + m[4] * y + m[8] * z;
  m[13] += m[1] * x + m[5] * y + m[9] * z;
  m[14] += m[2] * x + m[6] * y + m[10] * z;
}
static inline void mat4x4_translateXYZvec3_right(mat4x4 m, vec3 v)
{
  mat4x4_translateXYZf_right(m, v[0], v[1], v[2]);
}

static inline void mat4x4_rotateXf_left(mat4x4 m, float a)
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
static inline void mat4x4_rotateYf_left(mat4x4 m, float a)
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
static inline void mat4x4_rotateZf_left(mat4x4 m, float a)
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

static inline void mat4x4_rotateXYZf_left(mat4x4 m, float x, float y, float z)
{
  float cx = cos(x), sx = sin(x);
  float cy = cos(y), sy = sin(y);
  float cz = cos(z), sz = sin(z);

  float a = cz * cy, b = sz * cy, c = -sy;
  float e = cz * sy * sx - sz * cx, f = sz * sy * sx + cz * cx, g = cy * sx;
  float i = cz * sy * cx + sz * sx, j = sz * sy * cx - cz * sx, k = cy * cx;

  float t1 = m[0], t2 = m[1];
  m[0] = a * t1 + e * t2 + i * m[2];
  m[1] = b * t1 + f * t2 + j * m[2];
  m[2] = c * t1 + g * t2 + k * m[2];

  t1 = m[4], t2 = m[5];
  m[4] = a * t1 + e * t2 + i * m[6];
  m[5] = b * t1 + f * t2 + j * m[6];
  m[6] = c * t1 + g * t2 + k * m[6];

  t1 = m[8], t2 = m[9];
  m[8] = a * t1 + e * t2 + i * m[10];
  m[9] = b * t1 + f * t2 + j * m[10];
  m[10] = c * t1 + g * t2 + k * m[10];

  t1 = m[12], t2 = m[13];
  m[12] = a * t1 + e * t2 + i * m[14];
  m[13] = b * t1 + f * t2 + j * m[14];
  m[14] = c * t1 + g * t2 + k * m[14];
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
