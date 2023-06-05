#include "vex.h"
#include <cmath>
float clamp(float val, float min, float max) {
  // Return the minimum value if val is less than min
  if (val < min) {
    return min;
  }

  // Return the maximum value if val is greater than max
  if (val > max) {
    return max;
  }

  // Otherwise, return val
  return val;
}

int sign(double x)
{
    return (x > 0) - (x < 0);
}

int sign(float x)
{
    return (x > 0) - (x < 0);
}

double rad2deg(double rad)
{
    return rad / M_PI * 180.0;
}

double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}