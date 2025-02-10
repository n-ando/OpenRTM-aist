#ifndef SAMPLES_FSM_FSM_H_
#define SAMPLES_FSM_FSM_H_
/*
 Copyright 2010 Honda R&D Co.,Ltd.
*/
/*!
 @file
 @author Makoto Sekiya
 @version 1.0
 @date 2011/09/26
 @brief Fsm サンプルコンポーネント

 データポートからの入力によって状態を変えるコンポーネント
*/
#if defined(USE_SHAREDLIB) && defined(_MSC_VER)
#  if defined(LIBFSM_EXPORTS)
#    define EXTERN_LIBFSM __declspec(dllexport)
#  else
#    define EXTERN_LIBFSM __declspec(dllimport)
#  endif
#else
#  define EXTERN_LIBFSM
#endif

#include <hrtm/idls/BasicDataType.h>
#include <hrtm/idls/ExtendedDataTypes.h>
#include <hrtm/data_flow_component.h>
#include <hrtm/out_port.h>
#include <Poco/Timespan.h>

#include "camera_functions.h"

#include <map>

namespace hrtm {
namespace sc {
template<class T>
class Machine;
template<class T>
class EventParamBase;
}
}

struct Top;

/*!
 @brief Fsm クラス
*/
__pragma(warning(push))
__pragma(warning(disable:4250))
class EXTERN_LIBFSM Fsm : public hrtm::DataFlowComponent {
 public:
  Fsm();
  ~Fsm();
  virtual RTC::ReturnCode_t onInitialize();
  virtual RTC::ReturnCode_t onExecute(RTC::ExecutionContextHandle_t id);
  virtual RTC::ReturnCode_t notify_fsm_state_changed(const char* state);
 protected:
  using EventQueue = std::multimap<Poco::Timespan, hrtm::sc::EventParamBase<Top>*>;
  using EventPair = std::pair<Poco::Timespan, hrtm::sc::EventParamBase<Top>*>;

  friend void OutputData(double val);
  friend void DisplayFocused(RTC::TimedLong param);
  friend bool IsMemoryAvailable(RTC::TimedLong param);

  RTC::TimedLong ev_config_data_;
  RTC::TimedLong ev_in_focus_data_;
  RTC::TimedLong ev_off_data_;
  RTC::TimedLong ev_on_data_;
  RTC::TimedLong ev_shutter_full_data_;
  RTC::TimedLong ev_shutter_half_data_;
  RTC::TimedLong ev_shutter_released_data_;

  RTC::TimedLong out_data_;

  hrtm::InPort<RTC::TimedLong> in_port_ev_config_;
  hrtm::InPort<RTC::TimedLong> in_port_ev_in_focus_;
  hrtm::InPort<RTC::TimedLong> in_port_ev_off_;
  hrtm::InPort<RTC::TimedLong> in_port_ev_on_;
  hrtm::InPort<RTC::TimedLong> in_port_ev_shutter_full_;
  hrtm::InPort<RTC::TimedLong> in_port_ev_shutter_half_;
  hrtm::InPort<RTC::TimedLong> in_port_ev_shutter_released_;

  hrtm::OutPort<RTC::TimedLong> out_port_out_;

  hrtm::sc::Machine<Top>* machine_;

};
__pragma(warning(pop))
extern "C" EXTERN_LIBFSM const char* ComponentName();
extern "C" EXTERN_LIBFSM void ModuleInit(hrtm::ComponentManager* manager);

#endif  // SAMPLES_SIMPLEIO_CONSOLEIN_CONSOLEIN_H_
