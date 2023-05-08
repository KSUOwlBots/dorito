#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#include "v5.h"
#include "v5_vcs.h"


//////////////////////////////////////////

//includes
#include "robotConfig.h"
#include "opcontrol.hpp"

/////////////////////////////////////////

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)