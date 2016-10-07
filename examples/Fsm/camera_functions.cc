#include "camera_functions.h"
#include "Fsm.h"

#include <assert.h>
#include <iostream>

static Fsm* s_component = NULL;

void set_component(Fsm* component) {
  std::cout << "set_component()" << std::endl;
  s_component = component;
}

Fsm* get_component() {
  assert(s_component);
  return s_component;
}

void OutputData(double val) {
  std::cout << "OutputData()" << std::endl;
  assert(get_component());
  get_component()->out_data_.data = static_cast<CORBA::Long>(val);
  get_component()->out_port_out_.write();
}

void DisplayFocused(RTC::TimedLong /* param */) {
  std::cout << "DisplayFocused()" << std::endl;
}

bool IsMemoryAvailable(RTC::TimedLong /* param */) {
  std::cout << "IsMemoryAvailable()" << std::endl;
  return true;
}
