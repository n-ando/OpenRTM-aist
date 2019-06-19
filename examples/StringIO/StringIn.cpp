// -*- C++ -*-
/*!
 * @file StringIn.cpp
 * @brief Sample string in component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * $Id$
 */



#include "StringIn.h"
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

StringIn::StringIn(RtcManager* manager)
  : RtcBase(manager) ,
    m_string_inIn("string_in", m_string_in)

{
  registerInPort(m_string_inIn);
  appendAlias("/example/StringIn|rtc");
}

RtmRes StringIn::rtc_active_do()
{
  while (!m_string_inIn.isNew()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
  m_string_inIn.read();
  std::cout << m_string_in.data << std::endl;
  return RTM_OK;
}

extern "C" {
  
  RtcBase* StringInNew(RtcManager* manager)
  {
	return new StringIn(manager);
  }
  
  
  void StringInDelete(RtcBase* p)
  {
	delete (StringIn *)p;
	return;
  }
  
  
  void StringInInit(RtcManager* manager)
  {
	RtcModuleProfile profile(stringin_spec);
	manager->registerComponent(profile, StringInNew, StringInDelete);
  }
};

