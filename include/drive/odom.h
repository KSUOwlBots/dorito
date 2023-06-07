#ifndef GPS_H_
#define GPS_H_
#include <math.h>

class odom{
private:
  float leftTrackerCenterDistance;
  float rightTrackerCenterDistance;
  float leftTrackerPosition;
  float rightTrackerPosition;
public:
  float X_position;
  float Y_position;
  float orientation_deg;
  void set_position(float X_position, float Y_position, float orientation_deg, float leftTrackerPosition, float rightTrackerPosition);
  void update_position(float leftTrackerPosition, float rightTrackerPosition, float orientation_deg);
  void set_physical_distances(float leftTrackerCenterDistance, float rightTrackerCenterDistance);
};




#endif