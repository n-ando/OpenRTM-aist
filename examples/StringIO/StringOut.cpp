// -*- C++ -*-
/*!
 * @file StringOut.cpp
 * @brief Sample string out component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * $Id$
 */



#include "StringOut.h"
#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

StringOut::StringOut(RtcManager* manager)
  : RtcBase(manager) ,
     m_string_outOut("string_out", m_string_out)
{
  registerOutPort(m_string_outOut);
  appendAlias("/example/StringOut|rtc");
}

RtmRes StringOut::rtc_active_do()
{
  std::string s;
  std::cout << "Please input string: ";
  std::getline(cin, s);
  m_string_out.data = CORBA::string_dup(s.c_str());
  m_string_outOut.write();
  return RTM_OK;
}

extern "C" {
  
  RtcBase* StringOutNew(RtcManager* manager)
  {
	return new StringOut(manager);
  }
  
  
  void StringOutDelete(RtcBase* p)
  {
	delete (StringOut *)p;
	return;
  }
  
  
  void StringOutInit(RtcManager* manager)
  {
	RtcModuleProfile profile(stringout_spec);
	manager->registerComponent(profile, StringOutNew, StringOutDelete);
  }
};

