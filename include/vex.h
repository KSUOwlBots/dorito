#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#include "v5.h"
#include "v5_vcs.h"


//////////////////////////////////////////

//includes
#include "helpers/timer.h"
#include "robotConfig.h"
#include "opcontrol.h"
#include "gui.h"
#include "auton.h"
#include "chassis/gps.h"
#include "chassis/drivetrain.h"

/////////////////////////////////////////

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)