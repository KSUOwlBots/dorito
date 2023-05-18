#include "vex.h"

MyTimer::MyTimer()
{
    startTime = Brain.Timer.value();
}

void MyTimer::reset()
{
    startTime = Brain.Timer.value();
}

int MyTimer::getTimeMsec() const
{
    return floor((Brain.Timer.value() - startTime) * 1000); // return time (msec) from startTime
}

double MyTimer::getTimeSec() const
{
    return Brain.Timer.value() - startTime; // return time (sec) from startTime
}