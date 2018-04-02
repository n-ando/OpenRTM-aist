#ifndef CAMERA_FUNCTIONS_H_
#define CAMERA_FUNCTIONS_H_

#include <hrtm/idls/BasicDataType.h>
#include <hrtm/idls/ExtendedDataTypes.h>

class Fsm;

void set_component(Fsm* component);
Fsm* get_component();

void OutputData(double val);
void DisplayFocused(RTC::TimedLong param);
bool IsMemoryAvailable(RTC::TimedLong param);

#endif  // CAMERA_FUNCTIONS_H_
