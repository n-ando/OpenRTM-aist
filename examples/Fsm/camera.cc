#include "camera.h"
#include "camera_functions.h"
#include "Fsm.h"

#include <iostream>

#if defined(__vxworks)
template<> hrtm::sc::Key hrtm::sc::Machine<Top>::the_state_count_ = 1;
#endif

void Top::set_component(Fsm* component) {
  std::cout << "Top::set_component" << std::endl;
  ::set_component(component);
}
void Top::notify_fsm_state_changed(const char* state) {
  std::cout << "Top::notify_fsm_state_changed" << std::endl;
  ::get_component()->notify_fsm_state_changed(state);
}

////////////////////////////////////////////////////////
// Event handler implementations

// Top state
void Top::on_entry() {
  std::cout << "Top::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(0);
}
void Top::on_init() {
  std::cout << "Top::on_init" << std::endl;
  Off::set_state(machine(), new Off::Data());
}
void Top::on_do() {
  std::cout << "Top::on_do" << std::endl;
}
void Top::on_exit() {
  std::cout << "Top::exit" << std::endl;
}

void Top::EvOn(RTC::TimedLong /* param */) {
}
void Top::EvOff(RTC::TimedLong /* param */) {
}
void Top::EvConfig(RTC::TimedLong /* param */) {
}
void Top::EvInFocus(RTC::TimedLong /* param */) {
}
void Top::EvShutterHalf(RTC::TimedLong /* param */) {
}
void Top::EvShutterFull(RTC::TimedLong /* param */) {
}
void Top::EvShutterReleased(RTC::TimedLong /* param */) {
}

// Off state
void Off::on_entry() {
  std::cout << "Off::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(1);
}
void Off::on_exit() {
  std::cout << "Off::on_exit" << std::endl;
}
void Off::on_do() {
  std::cout << "Off::on_do" << std::endl;
}
void Off::EvOn(RTC::TimedLong /* param */) {
  std::cout << "Off::EvOn" << std::endl;
  NotShooting::set_state(machine(), new NotShooting::Data());
}

// NotShooting state
void NotShooting::on_entry() {
  std::cout << "NotShooting::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(2);
}
void NotShooting::on_init() {
  std::cout << "NotShooting::on_init" << std::endl;
  Idle::set_state(machine(), new Idle::Data());
}
void NotShooting::on_exit() {
  std::cout << "NotShooting::on_exit" << std::endl;
}
void NotShooting::on_do() {
  std::cout << "NotShooting::on_do" << std::endl;
}
void NotShooting::EvOff(RTC::TimedLong /* param */) {
  std::cout << "NotShooting::EvOff" << std::endl;
  Off::set_state(machine(), new Off::Data());
}
void NotShooting::EvShutterHalf(RTC::TimedLong /* param */) {
  std::cout << "NotShooting::EvShutterHalf" << std::endl;
  ShootingCamera::set_state(machine(), new ShootingCamera::Data());
}

// Idle state
void Idle::on_entry() {
  std::cout << "Idle::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(3);
}
void Idle::on_exit() {
  std::cout << "Idle::on_exit" << std::endl;
}
void Idle::on_do() {
  std::cout << "Idle::on_do" << std::endl;
}
void Idle::EvConfig(RTC::TimedLong /* param */) {
  std::cout << "Idle::EvConfig" << std::endl;
  Configuring::set_state(machine(), new Configuring::Data());
}

// Configuring state
void Configuring::on_entry() {
  std::cout << "Configuring::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(4);
}
void Configuring::on_exit() {
  std::cout << "Configuring::on_exit" << std::endl;
}
void Configuring::on_do() {
  std::cout << "Configuring::on_do" << std::endl;
}
void Configuring::EvConfig(RTC::TimedLong /* param */) {
  std::cout << "Configuring::EvConfig" << std::endl;
  Idle::set_state(machine(), new Idle::Data());
}

// ShootingCamera state
void ShootingCamera::on_entry() {
  std::cout << "ShootingCamera::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(5);
}
void ShootingCamera::on_init() {
  std::cout << "ShootingCamera::on_init" << std::endl;
  ShootingCamera_Shooting::set_state(machine(), new ShootingCamera_Shooting::Data());
}
void ShootingCamera::on_exit() {
  std::cout << "ShootingCamera::on_exit" << std::endl;
}
void ShootingCamera::on_do() {
  std::cout << "ShootingCamera::on_do" << std::endl;
}
void ShootingCamera::EvShutterReleased(RTC::TimedLong /* param */) {
  std::cout << "ShootingCamera::EvShutterReleased" << std::endl;
  NotShooting::set_state(machine(), new NotShooting::Data());
}

// ShootingCamera_Shooting state
void ShootingCamera_Shooting::on_entry() {
  std::cout << "ShootingCamera_Shooting::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(6);
}
void ShootingCamera_Shooting::on_init() {
  std::cout << "ShootingCamera_Shooting::on_init" << std::endl;
  ShootingCamera_Focusing::set_state(machine(), new ShootingCamera_Focusing::Data());
}
void ShootingCamera_Shooting::on_do() {
  std::cout << "ShootingCamera_Shooting::on_do" << std::endl;
}
void ShootingCamera_Shooting::on_exit() {
  std::cout << "ShootingCamera_Shooting::on_exit" << std::endl;
}

// ShootingCamera_Focusing state
void ShootingCamera_Focusing::on_entry() {
  std::cout << "ShootingCamera_Focusing::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(7);
}
void ShootingCamera_Focusing::on_do() {
  std::cout << "ShootingCamera_Focusing::on_do" << std::endl;
}
void ShootingCamera_Focusing::on_exit() {
  std::cout << "ShootingCamera_Focusing::on_exit" << std::endl;
}
void ShootingCamera_Focusing::EvInFocus(RTC::TimedLong param) {
  std::cout << "ShootingCamera_Focusing::EvInFocus" << std::endl;
  DisplayFocused(param);
  ShootingCamera_Focused::set_state(machine(), new ShootingCamera_Focused::Data());
}
void ShootingCamera_Focusing::EvShutterFull(RTC::TimedLong param) {
  std::cout << "ShootingCamera_Focusing::EvShutterFull" << std::endl;
  defer(hrtm::sc::Event(&Top::EvShutterFull, param));
}

// ShootingCamera_Focused state
void ShootingCamera_Focused::on_entry() {
  std::cout << "ShootingCamera_Focused::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(8);
}
void ShootingCamera_Focused::on_do() {
  std::cout << "ShootingCamera_Focused::on_do" << std::endl;
}
void ShootingCamera_Focused::on_exit() {
  std::cout << "ShootingCamera_Focused::on_exit" << std::endl;
}
void ShootingCamera_Focused::EvShutterFull(RTC::TimedLong param) {
  std::cout << "ShootingCamera_Focused::EvShutterFull" << std::endl;
  if (IsMemoryAvailable(param)) {
    ShootingCamera_Storing::set_state(machine(), new ShootingCamera_Storing::Data());
  }
}

// ShootingCamera_Storing state
void ShootingCamera_Storing::on_entry() {
  std::cout << "ShootingCamera_Storing::on_entry" << std::endl;
  notify_fsm_state_changed(state_name());
  OutputData(9);
}
void ShootingCamera_Storing::on_do() {
  std::cout << "ShootingCamera_Storing::on_do" << std::endl;
}
void ShootingCamera_Storing::on_exit() {
  std::cout << "ShootingCamera_Storing::on_exit" << std::endl;
}

