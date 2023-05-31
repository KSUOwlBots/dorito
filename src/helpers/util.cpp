#include "vex.h"
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