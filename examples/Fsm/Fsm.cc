/*
 Copyright 2010 Honda R&D Co.,Ltd.
*/
#if defined(_MSC_VER)
  __pragma(warning(push))
  __pragma(warning(disable:4702))
#if defined(HRTM_DLL)
#define USE_stub_in_nt_dll
#endif
#endif
#include "Fsm.h"  // NOLINT
#include "camera.h"  // NOLINT

#include <hrtm/utils.h>
#include <hrtm/idls/HRTM.h>
#include <iostream>  // NOLINT
#include <map>  // NOLINT

#if defined(_MSC_VER)
  __pragma(warning(pop))
#endif
static const char* const fsm_spec[] = {
  "implementation_id", "Fsm",
  "type_name",         "Fsm",
  "description",       "Fsm component",
  "version",           "1.0",
  "vendor",            "Toyotaka Torii",
  "category",          "example",
  "activity_type",     "DataFlowComponent",
  "max_instance",      "10",
  "language",          "C++",
  "lang_type",         "compile",
  ""
};

Fsm::Fsm()
    : DataFlowComponent(),
    in_port_ev_config_("EvConfig", ev_config_data_),
    in_port_ev_in_focus_("EvInFocus", ev_in_focus_data_),
    in_port_ev_off_("EvOff", ev_off_data_),
    in_port_ev_on_("EvOn", ev_on_data_),
    in_port_ev_shutter_full_("EvShutterFull", ev_shutter_full_data_),
    in_port_ev_shutter_half_("EvShutterHalf", ev_shutter_half_data_),
    in_port_ev_shutter_released_("EvShutterReleased", ev_shutter_released_data_),
    out_port_out_("out", out_data_)
{
}

Fsm::~Fsm() {
}

RTC::ReturnCode_t Fsm::onInitialize() {
  getInstanceName();
  addInPort("EvConfig", in_port_ev_config_);
  addInPort("EvInFocus", in_port_ev_in_focus_);
  addInPort("EvOff", in_port_ev_off_);
  addInPort("EvOn", in_port_ev_on_);
  addInPort("EvShutterFull", in_port_ev_shutter_full_);
  addInPort("EvShutterHalf", in_port_ev_shutter_half_);
  addInPort("EvShutterReleased", in_port_ev_shutter_released_);
  addOutPort("out", out_port_out_);

  Top::set_component(this);
  machine_ = new hrtm::sc::Machine<Top>(new Top::Data());

  return RTC::RTC_OK;
}

RTC::ReturnCode_t Fsm::onExecute(RTC::ExecutionContextHandle_t) {
  static const int NSEC_TO_USEC = 1/1000;
  EventQueue q;

  if (in_port_ev_config_.isNew())
  {
    in_port_ev_config_.read();
    q.insert(
      EventPair(
        Poco::Timespan(ev_config_data_.tm.sec, ev_config_data_.tm.nsec*NSEC_TO_USEC),
        hrtm::sc::Event(&Top::EvConfig, ev_config_data_)));
  }
  if (in_port_ev_in_focus_.isNew())
  {
    in_port_ev_in_focus_.read();
    q.insert(
      EventPair(
        Poco::Timespan(ev_in_focus_data_.tm.sec, ev_in_focus_data_.tm.nsec*NSEC_TO_USEC),
        hrtm::sc::Event(&Top::EvInFocus, ev_in_focus_data_)));
  }
  if (in_port_ev_off_.isNew())
  {
    in_port_ev_off_.read();
    q.insert(
      EventPair(
        Poco::Timespan(ev_off_data_.tm.sec, ev_off_data_.tm.nsec*NSEC_TO_USEC),
        hrtm::sc::Event(&Top::EvOff, ev_off_data_)));
  }
  if (in_port_ev_on_.isNew())
  {
    in_port_ev_on_.read();
    q.insert(
      EventPair(
        Poco::Timespan(ev_on_data_.tm.sec, ev_on_data_.tm.nsec*NSEC_TO_USEC),
        hrtm::sc::Event(&Top::EvOn, ev_on_data_)));
  }
  if (in_port_ev_shutter_full_.isNew())
  {
    in_port_ev_shutter_full_.read();
    q.insert(
      EventPair(
        Poco::Timespan(ev_shutter_full_data_.tm.sec, ev_shutter_full_data_.tm.nsec*NSEC_TO_USEC),
        hrtm::sc::Event(&Top::EvShutterFull, ev_shutter_full_data_)));
  }
  if (in_port_ev_shutter_half_.isNew())
  {
    in_port_ev_shutter_half_.read();
    q.insert(
      EventPair(
        Poco::Timespan(ev_shutter_half_data_.tm.sec, ev_shutter_half_data_.tm.nsec*NSEC_TO_USEC),
        hrtm::sc::Event(&Top::EvShutterHalf, ev_shutter_half_data_)));
  }
  if (in_port_ev_shutter_released_.isNew())
  {
    in_port_ev_shutter_released_.read();
    q.insert(
      EventPair(
        Poco::Timespan(ev_shutter_released_data_.tm.sec, ev_shutter_released_data_.tm.nsec*NSEC_TO_USEC),
        hrtm::sc::Event(&Top::EvShutterReleased, ev_shutter_released_data_)));
  }

#if 0
  q.insert(
    EventPair(
      Poco::Timespan(0, 4),
      hrtm::sc::Event(&Top::EvInFocus, ev_in_focus_data_)));
  q.insert(
    EventPair(
      Poco::Timespan(0, 1),
      hrtm::sc::Event(&Top::EvOn, ev_on_data_)));
  q.insert(
    EventPair(
      Poco::Timespan(0, 3),
      hrtm::sc::Event(&Top::EvShutterFull, ev_shutter_full_data_)));
  q.insert(
    EventPair(
      Poco::Timespan(0, 2),
      hrtm::sc::Event(&Top::EvShutterHalf, ev_shutter_half_data_)));
  q.insert(
    EventPair(
      Poco::Timespan(0, 5),
      hrtm::sc::Event(&Top::EvShutterReleased, ev_shutter_released_data_)));
#endif

  for (EventQueue::iterator it = q.begin(); it != q.end(); ++it)
  {
      (*machine_).dispatch(it->second);
  }

  (*machine_)->on_do();

  return RTC::RTC_OK;
}

RTC::ReturnCode_t Fsm::notify_fsm_state_changed(const char* state) {
  updateFsmStatus(RTC::FSM_STATUS, CORBA::string_dup(state));
  return RTC::RTC_OK;
}

void ComponentInit(hrtm::ComponentManager* manager) {
  hrtm::utils::Properties profile(fsm_spec);
  manager->regist<Fsm>(&profile, 0, 0);
}

const char* ComponentName() {
  return COMPONENT_NAME(Fsm);
}

void ModuleInit(hrtm::ComponentManager* manager) {
#if !defined(__vxworks)
  using hrtm::operator<<;  // NOLINT
#endif

  ComponentInit(manager);
  std::cout << "Creating a component: \"Fsm\"...." << std::endl;
  hrtm::DataFlowComponent* comp(manager->create_component(COMPONENT_NAME(Fsm)));
  if (!comp) {
    return;
  }
  comp->initialize(manager);
  std::cout << "succeed." << std::endl;
  RTC::ComponentProfile* prof(comp->get_component_profile());
  std::cout <<
    "=================================================" << std::endl;
  std::cout << " Component Profile" << std::endl;
  std::cout <<
    "-------------------------------------------------" << std::endl;
  std::cout << "InstanceID:     " << prof->instance_name.in() << std::endl;
  std::cout << "Implementation: " << prof->type_name.in() << std::endl;
  std::cout << "Description:    " << prof->description.in() << std::endl;
  std::cout << "Version:        " << prof->version.in() << std::endl;
  std::cout << "Maker:          " << prof->vendor.in() << std::endl;
  std::cout << "Category:       " << prof->category.in() << std::endl;
  std::cout << "  Other properties   " << std::endl;
#if !defined(__vxworks)
  std::cout <<  prof->properties << std::endl;
#endif
  std::cout <<
      "=================================================" << std::endl;
  RTC::PortServiceList* portlist(comp->get_ports());
  for (CORBA::ULong i(0), n(portlist->length()); i < n; ++i) {
    RTC::PortService_ptr port((*portlist)[i]);
    std::cout << "================================================="
      << std::endl;
    std::cout << "Port" << i << " (name): ";
    std::cout << port->get_port_profile()->name.in() << std::endl;
    std::cout << "-------------------------------------------------"
      << std::endl;
    RTC::PortInterfaceProfileList iflist(port->get_port_profile()->interfaces);
    for (CORBA::ULong i(0), n(iflist.length()); i < n; ++i) {
      std::cout << "I/F name: ";
      std::cout << iflist[i].instance_name.in() << std::endl;
      std::cout << "I/F type: ";
      std::cout << iflist[i].type_name.in() << std::endl;
      const char* pol(iflist[i].polarity == 0 ? "PROVIDED" : "REQUIRED");
      std::cout << "Polarity: " << pol << std::endl;
    }
    std::cout << "- properties -" << std::endl;
#if !defined(__vxworks)
    std::cout << port->get_port_profile()->properties << std::endl;
#endif
    std::cout <<
        "-------------------------------------------------" << std::endl;
  }
  return;
}
