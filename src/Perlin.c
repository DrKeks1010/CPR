#include "Perlin.h"
#include "math.h"

// Code from https://de.wikipedia.org/wiki/Perlin-Noise#Programmierung

static float random(int ix, int iy)
{
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;
    b ^= a << s | a >> (w-s);
    b *= 1911520717;
    a ^= b << s | b >> (w-s);
    a *= 2048419325;
    return a * (3.14159265 / ~(~0u >> 1));
}

static float dotGridGradient(int ix, int iy, float x, float y)
{
    float angel = random(ix, iy);

    float dx = x - (float) ix;
    float dy = y - (float) iy;
    return dx * cos(angel) + dy * sin(angel);
}

static inline float interpolate(float a0, float a1, float x)
{
    float g = (3.0 - x * 2.0) * x * x;
    return (a1 - a0) * g + a0;
}

double Perlin_get(double x, double y)
{
    x *= 1.0 / 16.0;
    y *= 1.0 / 16.0;

    const float sq2 = sqrt(2.0);

    int x0 = (int) x;
    int x1 = x0 + 1;
    int y0 = (int) y;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1;
    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    return interpolate(ix0, ix1, sy) * sq2 * 4;
}