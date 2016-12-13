// -*- C++ -*-
/*!
 * @file ConsoleIn.cpp
 * @brief Sample Component: Console In
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * Copyright (c) 2003 Noriaki Ando <n-ando@aist.go.jp>
 *          National Institute of Industrial Science (AIST), Japan. All rights reserved.
 *
 * $Id: ConsoleIn.cpp,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */



#include "ConsoleIn.h"
#include <iostream>

using namespace std;

ConsoleIn::ConsoleIn(RtcManager* manager)
  : RtcBase(manager),
	m_Out("out", out, 100)
{
  registerPort(m_Out);
  appendAlias("/example/ConsoleIn|rtc");
}

RtmRes ConsoleIn::rtc_active_do()
{
  cout << "Please input number: ";
  cin >> out.data;
  cout << "Sending to subscriber: " << out.data << endl;
  m_Out << out;

  return RTM_OK;
}




extern "C" {
  
  RtcBase* ConsoleInNew(RtcManager* manager)
  {
	return new ConsoleIn(manager);
  }
  
  
  void ConsoleInDelete(RtcBase* p)
  {
	delete p;
	return;
  }
  
  
  void ConsoleInInit(RtcManager* manager)
  {
	RtcModuleProfile profile(consolein_spec);
	manager->registerComponent(profile, ConsoleInNew, ConsoleInDelete);
  }
  
};
