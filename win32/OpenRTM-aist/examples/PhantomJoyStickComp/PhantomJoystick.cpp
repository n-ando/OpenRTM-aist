// -*- C++ -*-
/*!
 * @file  PhantomJoystick.cpp
 * @brief PhantomJoystick component
 * $Date$
 *
 * $Id$
 */

#include "PhantomJoystick.h"
#include "VectorConvert.h"

// Module specification
static const char* phantomjoystick_spec[] =
  {
    "implementation_id", "PhantomJoystick",
    "type_name",         "PhantomJoystick",
    "description",       "PhantomJoystick component",
    "version",           "0.1",
    "vendor",            "S.Kurihara",
    "category",          "Generic",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.force_gain", "1.0,1.0,1.0",
    "conf.default.vel_gain", "1.0,1.0,1.0",

    ""
  };

PhantomJoystick::PhantomJoystick(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_forceIn("force", m_force),
    m_velOut("vel", m_vel),
	dummy(0)
{
  // Registration: InPort/OutPort/Service
  // Set InPort buffers
  registerInPort("force", m_forceIn);
  
  // Set OutPort buffer
  registerOutPort("vel", m_velOut);

  m_vel.data.length(phantom_control::VelEle+phantom_control::AngEle);
  m_pc = new phantom_control();

}



RTC::ReturnCode_t PhantomJoystick::onInitialize()
{
  // Bind variables and configuration variable
  bindParameter("force_gain", m_force_gain, "1.0,1.0,1.0");
  bindParameter("vel_gain", m_vel_gain, "1.0,1.0,1.0");
  
  std::cout << std::endl;
  std::cout << "Please change configuration values from RtcLink" << std::endl; 
  std::cout << std::endl;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t PhantomJoystick::onActivated(RTC::UniqueId ec_id)
{
  m_pc->initialize();
  return RTC::RTC_OK;
}



RTC::ReturnCode_t PhantomJoystick::onDeactivated(RTC::UniqueId ec_id)
{
  m_pc->finalize();

  for(int i = 0; i < (phantom_control::VelEle+phantom_control::AngEle); i++)
    m_vel.data[i] = 0.0;

  m_velOut << m_vel;

  return RTC::RTC_OK;
}



RTC::ReturnCode_t PhantomJoystick::onExecute(RTC::UniqueId ec_id)
{
  m_forceIn.read();

  int i(0);
  
  vector<float> force(phantom_control::ForceEle, 0.0);
  

  if (m_force.data.length() == (phantom_control::ForceEle)) {
    data_mul(force, m_force.data, m_force_gain, (int)phantom_control::ForceEle);
    m_pc->set_data(force);
  }
  
  for(int i = 0; i < (phantom_control::VelEle+phantom_control::AngEle); i++) {
    m_vel.data[i] = 0.0;
  }
  
  vector<float> vel =  m_pc->get_data();
  
  data_mul(m_vel.data, vel, m_vel_gain, (int)phantom_control::VelEle);
  data_copy(m_vel.data, vel, (int)phantom_control::AngEle, (int)phantom_control::AngEle, (int)phantom_control::AngEle);
  m_velOut << m_vel;

  return RTC::RTC_OK;
}


extern "C"
{
 
  void PhantomJoystickInit(RTC::Manager* manager)
  {
    RTC::Properties profile(phantomjoystick_spec);
    manager->registerFactory(profile,
                             RTC::Create<PhantomJoystick>,
                             RTC::Delete<PhantomJoystick>);
  }
  
};


