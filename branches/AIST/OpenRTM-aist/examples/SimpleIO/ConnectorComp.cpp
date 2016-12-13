// -*- C++ -*-
/*!
 * @file ConnectorComp.cpp
 * @brief connector application
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * Copyright (c) 2003 Noriaki Ando <n-ando@aist.go.jp>
 *          Task-intelligence Research Group,
 *          Intelligent System Research Institute,
 *          National Institute of Industrial Science (AIST), Japan
 *          All rights reserved.
 *
 * $Id: ConnectorComp.cpp,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */

#include <iostream>
#include <vector>
#include <RtcManager.h>
#include <RtcBase.h>
#include <RTComponentStub.h>

using namespace std;

int main (int argc, char** argv)
{
  RTM::RtcManager manager(argc, argv);

  // Initialize manager
  manager.initManager();

  // Activate manager and register to naming service
  manager.activateManager();

  // Initialize my module on this maneger

  vector<RTM::RTCBase_ptr> in_comps, out_comps;
  cout << "Finding component .*/.*/example/ConsoleIn/ConsoleIn0" << endl;
  in_comps = manager.findComponents(".*/.*/example/ConsoleIn/ConsoleIn0");

  if (in_comps.size() > 0)
	{
	  if (CORBA::is_nil(in_comps[0]))
		{
		  cout << "Invalid object reference: ConsoleIn0." << endl;
		  exit(1);
		}
	  cout << "ConsoleIn0 found: " << in_comps.size() << "." << endl;
	}
  else
	{
	  exit(1);
	}

  cout << "Finding component .*/.*/example/ConsoleIn/ConsoleOut0" << endl;
  out_comps = manager.findComponents(".*/.*/example/ConsoleOut/ConsoleOut0");

  if (out_comps.size() > 0)
	{
	  if (CORBA::is_nil(out_comps[0]))
		{
		  cout << "Invalid object reference: ConsoleOut0." << endl;
		  exit(1);
		}
	  cout << "ConsoleOut0 found: " << out_comps.size() << "." << endl;
	}
  else
	{
	  exit(1);
	}

  try
	{
	  cout << "Starting components" << endl;
	  in_comps[0]->rtc_start();
	  out_comps[0]->rtc_start();
	}
  catch (...)
	{
	  cout << "exception was cought" << endl;
	}
  
  
  // Get OutPort of ConsoleIn0
  RTM::OutPort_var outp_obj = in_comps[0]->get_outport("out");
  RTM::PortProfile_var port_prof;
  port_prof = outp_obj->profile();

  cout << "Get outport: " << port_prof->name << "." << endl;
  if (CORBA::is_nil(outp_obj))
	{
	  cerr << "Invalid outport" << endl;
	  exit(1);
	}

  // Get InPort of ConsoleOut0
  RTM::InPort_var inp_obj  = out_comps[0]->get_inport("in");
  port_prof = inp_obj->profile();
  cout << "Get inport: " << port_prof->name << "." << endl;
  if (CORBA::is_nil(inp_obj))
	{
	  cerr << "Invalid inport" << endl;
	  exit(1);
	}
  
  // Subscription
  RTM::SubscriberProfile sub_prof;
  sub_prof.subscription_type = RTM::OPS_NEW;
  cout << "Connect OutPort and InPort...";
  char* uuid;
  if (outp_obj->subscribe(inp_obj,
						  uuid,
						  sub_prof) == RTM::RTM_OK)
	{
	  cout << "succeed." << endl;
	  cout << "Subscription ID is " << uuid << endl;
	  CORBA::string_free(uuid);
	}
  else
	{ 
	  cout << "failed." << endl;
	}

  // Main loop
  manager.runManager();

  return 0;
}

