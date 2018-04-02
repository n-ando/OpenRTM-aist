#ifndef CAMERA_H_
#define CAMERA_H_

#include <hrtm/statechart.h>
#include <hrtm/idls/BasicDataType.h>
#include <hrtm/idls/ExtendedDataTypes.h>
#include <hrtm/idls/HRTM.h>
#include <iostream>
#include <vector>
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4512)
#endif
class Fsm;

////////////////////////////////////////////////////////
// State declarations

// Machine's top state
TOPSTATE(Top) {
  // Top state variables (visible to all substates)
  struct Data {
    Data() {}
  };

  STATE(Top)

  static void set_component(Fsm* component);
  static void notify_fsm_state_changed(const char* state);

  // Event handler
  virtual void on_do();

  virtual void EvOn(RTC::TimedLong param);
  virtual void EvOff(RTC::TimedLong param);
  virtual void EvConfig(RTC::TimedLong param);
  virtual void EvInFocus(RTC::TimedLong param);
  virtual void EvShutterHalf(RTC::TimedLong param);
  virtual void EvShutterFull(RTC::TimedLong param);
  virtual void EvShutterReleased(RTC::TimedLong param);

 protected:
   void on_entry();
   void on_init();
   void on_exit();
};

SUBSTATE(Off, Top) {
  STATE(Off)

  // Event handler
  void on_do();
  void EvOn(RTC::TimedLong param);

 private:
   // Entry and exit actions of state
   void on_entry();
   void on_exit();
};

// A substate
SUBSTATE(NotShooting, Top) {
  STATE(NotShooting)
  DEEPHISTORY()

  // Event handler
  void on_do();
  void EvOff(RTC::TimedLong param);
  void EvShutterHalf(RTC::TimedLong param);

 private:
   void on_entry();
   void on_init();
   void on_exit();
};

// A substate
SUBSTATE(Idle, NotShooting) {
  STATE(Idle)

  // Event handler
  void on_do();
  void EvConfig(RTC::TimedLong param);

 private:
   void on_entry();
   void on_exit();
};

// A substate
SUBSTATE(Configuring, NotShooting) {
  STATE(Configuring)

  // Event handler
  void on_do();
  void EvConfig(RTC::TimedLong param);

 private:
   void on_entry();
   void on_exit();
};

// A substate
SUBSTATE(ShootingCamera, Top) {
  STATE(ShootingCamera)

  // Event handler
  void on_do();
  void EvShutterReleased(RTC::TimedLong param);

 private:
   void on_entry();
   void on_init();
   void on_exit();
};

// A substate
SUBSTATE(ShootingCamera_Shooting, ShootingCamera) {
  STATE(ShootingCamera_Shooting)

  // Event handler
  void on_do();

 private:
   void on_entry();
   void on_init();
   void on_exit();
};

// A substate
SUBSTATE(ShootingCamera_Focusing, ShootingCamera_Shooting) {
  STATE(ShootingCamera_Focusing)

  // Event handler
  void on_do();
  void EvInFocus(RTC::TimedLong param);
  void EvShutterFull(RTC::TimedLong param);

 private:
   void on_entry();
   void on_exit();
};

// A substate
SUBSTATE(ShootingCamera_Focused, ShootingCamera_Shooting) {
  STATE(ShootingCamera_Focused)

  // Event handler
  void on_do();
  void EvShutterFull(RTC::TimedLong param);

 private:
   void on_entry();
   void on_exit();
};

// A substate
SUBSTATE(ShootingCamera_Storing, ShootingCamera_Shooting) {
  STATE(ShootingCamera_Storing)

  // Event handler
  void on_do();

 private:
   void on_entry();
   void on_exit();
};
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
#endif  // CAMERA_H_
