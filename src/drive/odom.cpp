#include "vex.h"


using namespace vex;

void odom::set_physical_distances(float xTrackerError, float yTrackerError){
  this->xTrackerError = xTrackerError;
  this->yTrackerError = yTrackerError;
}

void odom::set_position(float X_position, float Y_position, float orientation_deg, float leftTrackerPosition, float rightTrackerPosition){
  this->leftTrackerPosition = leftTrackerPosition;
  this->rightTrackerPosition = rightTrackerPosition;
  this->X_position = X_position;
  this->Y_position = Y_position;
  this->orientation_deg = orientation_deg;
}

void odom::update_position(float leftTrackerPosition, float rightTrackerPosition, float orientation_deg){
  float leftTrackerDelta = leftTrackerPosition-this->leftTrackerPosition;
  float rightTrackerDelta = rightTrackerPosition-this->rightTrackerPosition;
  this->leftTrackerPosition=leftTrackerPosition;
  this->rightTrackerPosition=rightTrackerPosition;
  float orientation_rad = deg2rad(orientation_deg);
  float prev_orientation_rad = deg2rad(this->orientation_deg);
  float orientation_delta_rad = orientation_rad-prev_orientation_rad;
  this->orientation_deg=orientation_deg;
  //do funni math here for tracker angles
  float Forward_delta = (-cos(rightTrackerDelta) - cos(leftTrackerDelta));
  float Sideways_delta = (sin(rightTrackerDelta) - sin(leftTrackerDelta));

  float local_X_position;
  float local_Y_position;

  if (orientation_delta_rad == 0) {
    local_X_position = Sideways_delta;
    local_Y_position = Forward_delta;
  } 
  else {
    local_X_position = (2*sin(orientation_delta_rad/2))*((Sideways_delta/orientation_delta_rad) + xTrackerError); 
    local_Y_position = (2*sin(orientation_delta_rad/2))*((Forward_delta/orientation_delta_rad) + yTrackerError);
  }

  float local_polar_angle;
  float local_polar_length;

  if (local_X_position == 0 && local_Y_position == 0){
    local_polar_angle = 0;
    local_polar_length = 0;
  } 
  else {
    local_polar_angle = atan2(local_Y_position, local_X_position); 
    local_polar_length = sqrt(pow(local_X_position, 2) + pow(local_Y_position, 2)); 
  }

  float global_polar_angle = local_polar_angle - prev_orientation_rad - (orientation_delta_rad/2);

  float X_position_delta = local_polar_length*cos(global_polar_angle); 
  float Y_position_delta = local_polar_length*sin(global_polar_angle);

  X_position+=X_position_delta;
  Y_position+=Y_position_delta;
}