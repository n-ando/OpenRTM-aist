// -*- C++ -*-
/*!
 * @file  SimpleService.cpp
 * @brief Simple service example component
 * $Date: 2005-09-08 13:04:22 $
 *
 * $Id: SimpleService.cpp,v 1.1 2005-09-08 13:04:22 n-ando Exp $
 */

#include "SimpleService.h"

using namespace std;

SimpleService::SimpleService(RtcManager* manager)
  : RtcBase(manager),
    // <rtc-template block="initializer">
    m_RefIn("Ref", m_Ref),
    m_GaindRefOut("GaindRef", m_GaindRef),
    m_GainOut("Gain", m_Gain),
    m_MyServiceProfile("MySVC", "MySVC", ""),
    // </rtc-template>
	dummy(0)
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  registerInPort(m_RefIn);
  registerOutPort(m_GaindRefOut);
  registerOutPort(m_GainOut);
  registerService(m_MySVC, m_MyServiceProfile);
  // </rtc-template>
  // MunyaMunya
}



/*
RtmRes SimpleService::rtc_init_entry()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_ready_entry()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_ready_do()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_ready_exit()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_starting_entry()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_active_entry()
{
  return RTM_OK;
}
*/


RtmRes SimpleService::rtc_active_do()
{
  // Copy InPort data from InPort buffer to m_Ref
  m_RefIn.read();

  // Examine data length of InPort data
  int length;
  length = m_Ref.data.length();
  if (length > 0)
	{
	  m_GaindRef.data.length(length);
	}
  else
	{
	  return RTM_OK;
	}

  // Get gain from MyService
  m_Gain.data = m_MySVC.getGain();

  // Copy gaind data from InPort to OutPort
  for (CORBA::ULong i = 0; i < length; i++)
	{
	  m_GaindRef.data[i] = m_Ref.data[i] * m_Gain.data;
	}

  // Write data to OutPort
  m_GaindRefOut.write();
  m_GainOut.write();
	  
  return RTM_OK;
}


/*
RtmRes SimpleService::rtc_active_exit()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_stopping_entry()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_aborting_entry()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_error_entry()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_error_do()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_error_exit()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_fatal_entry()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_fatal_do()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_fatal_exit()
{
  return RTM_OK;
}
*/

/*
RtmRes SimpleService::rtc_exiting_entry()
{
  return RTM_OK;
}
*/



extern "C"
{

  RtcBase* SimpleServiceNew(RtcManager* manager)
  {
	return new SimpleService(manager);
  }


  void SimpleServiceDelete(RtcBase* p)
  {
	delete (SimpleService *)p;
	return;
  }


  void SimpleServiceInit(RtcManager* manager)
  {
	RtcModuleProfile profile(simpleservice_spec);
	manager->registerComponent(profile, SimpleServiceNew, SimpleServiceDelete);
  }

};


