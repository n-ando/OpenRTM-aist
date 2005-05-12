// -*- C++ -*-
/*!
 * @file RtcBase.i
 * @brief swig interface file for RtcBase
 * @date $Date: 2005-05-12 09:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcBase.i,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

%module(directors="1") RtcBasePy


%{
#include "rtm/RtcBase.h"
#include "rtm/RtcInPort.h"
#include "rtm/RtcOutPort.h"
#include "rtm/idl/RTComponentSkel.h"
%}

%import "rtm/idl/RTCBaseSkel.h"


//%exception {
//	Py_BEGIN_ALLOW_THREADS
//	$function
//	Py_END_ALLOW_THREADS
//}


%inline %{
using namespace std;
using namespace RTM;
%}

// RtcBase is inherited by user define component classes.
// A director class have to be generated.
%feature("director") RtcBase;

namespace RTM {
  
  class RtcBase
  {
  public:
	RtcBase(RtcManager* manager);
	virtual ~RtcBase();
	
	RtmRes rtc_start();
	RtmRes rtc_stop();
	RtmRes rtc_reset();
	RtmRes rtc_exit();
	RtmRes rtc_kill();
	RtmRes rtc_worker();
	
	virtual RtmRes rtc_ready_entry();
	virtual RtmRes rtc_ready_do();
	virtual RtmRes rtc_ready_exit();
	virtual RtmRes rtc_active_entry();
	virtual RtmRes rtc_active_do();
	virtual RtmRes rtc_active_exit();
	virtual RtmRes rtc_error_entry();
	virtual RtmRes rtc_error_do();
	virtual RtmRes rtc_error_exit();
	virtual RtmRes rtc_fatal_entry();
	virtual RtmRes rtc_fatal_do();
	virtual RtmRes rtc_fatal_exit();
	virtual RtmRes rtc_init_entry();
	virtual RtmRes rtc_starting_entry();
	virtual RtmRes rtc_stopping_entry();
	virtual RtmRes rtc_aborting_entry();
	virtual RtmRes rtc_exiting_entry();

	RTM::OutPort_ptr rtc_state();
	RTM::InPortList* inports();
	RTM::InPort_ptr get_inport(const char* name);
	RTM::OutPortList* outports();
	RTM::OutPort_ptr get_outport(const char* name);
	RTM::RTCProfile* profile();

	void initModuleProfile(RTM::RtcModuleProfile prof);
	//	virtual string setComponentName(int num);
	bool registerInPort(RTM::InPortBase& in_ch);
	bool deleteInPort(RTM::InPortBase& in_ch);
	bool deleteInPortByName(char* ch_name);
	bool registerOutPort(RTM::OutPortBase& out_ch);
	bool deleteOutPort(RTM::OutPortBase& out_ch);
	bool deleteOutPortByName(char* ch_name);
	void appendAlias(const char* alias);
	std::list<string> getAliases();
  };
};
	
