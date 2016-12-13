// -*- C++ -*-
/*!
 * @file ConsoleOut.cpp
 * @brief Sample Component: Console In
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * Copyright (c) 2003 Noriaki Ando <n-ando@aist.go.jp>
 *          National Institute of Industrial Science (AIST), Japan. All rights reserved.
 *
 * $Id: ConsoleOut.cpp,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */



#include "ConsoleOut.h"
#include <iostream>

using namespace std;

ConsoleOut::ConsoleOut(RtcManager* manager)
  : RtcBase(manager), 
	m_In("in", in, 8)
{
  in.data = 0;
  m_In.initBuffer(in);
  registerPort(m_In);
  appendAlias("example/ConsoleOut|rtc");
}

RtmRes ConsoleOut::rtc_active_do()
{
  m_In.read();
  cout << "Received: " << in.data << endl;
  cout << "TimeStamp: " << in.tm.sec << "[s] " << in.tm.nsec << "[ns]" << endl;
  sleep(1);
  return RTM_OK;
}

extern "C" {
  
  RtcBase* ConsoleOutNew(RtcManager* manager)
  {
	return new ConsoleOut(manager);
  }
  
  
  void ConsoleOutDelete(RtcBase* p)
  {
	delete p;
	return;
  }
  
  
  void ConsoleOutInit(RtcManager* manager)
  {
	RtcModuleProfile profile(consolein_spec);
	manager->registerComponent(profile, ConsoleOutNew, ConsoleOutDelete);
	
  }
  
};
