// -*- C++ -*-
/*!
 * @file RTCBase.i
 * @brief swig interface file for RTCBase
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
 * $Id: RTCBase.i,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

%module RTComponent

%{
#include "rtm/RtcInPortBase.h"
#include "rtm/RtcOutPortBase.h"
#include "rtm/idl/RTComponentSkel.h"
%}


%inline %{
using namespace std;
using namespace RTM;
%}


namespace RTM
{

  class RTCBase
	: public RTComponent
  {
  public:
    RTM::RtmRes rtc_ready_entry();
    RTM::RtmRes rtc_ready_do();
    RTM::RtmRes rtc_ready_exit();
    RTM::RtmRes rtc_active_entry();
    RTM::RtmRes rtc_active_do();
    RTM::RtmRes rtc_active_exit();
    RTM::RtmRes rtc_error_entry();
    RTM::RtmRes rtc_error_do();
    RTM::RtmRes rtc_error_exit();
    RTM::RtmRes rtc_fatal_entry();
    RTM::RtmRes rtc_fatal_do();
    RTM::RtmRes rtc_fatal_exit();
    RTM::RtmRes rtc_init_entry();
    RTM::RtmRes rtc_starting_entry();
    RTM::RtmRes rtc_stopping_entry();
    RTM::RtmRes rtc_aborting_entry();
    RTM::RtmRes rtc_exiting_entry();
    RTM::RtmRes rtc_stop_thread();
    RTM::RtmRes rtc_start_thread();
    RTM::RtmRes rtc_set_parent(RTCBase_ptr comp);
    RTM::RtmRes rtc_add_component(RTCBase_ptr comp);
    RTM::RtmRes rtc_delete_component(RTCBase_ptr comp);
    RTM::RtmRes rtc_replace_component(RTCBase_ptr comp1, RTCBase_ptr comp2);
    RTM::RtmRes rtc_replace_component_by_name(const char* name1,
											  const char* name2);
	RTM:: RTCBaseList* rtc_components();
    RTCBase_ptr rtc_get_component(const char* name);
    RTM::RtmRes rtc_attach_inport(InPort_ptr in_port);
    RTM::RtmRes rtc_attach_inport_by_name(RTCBase_ptr comp, const char* name);
    RTM::RtmRes rtc_detatch_inport(InPort_ptr in_port);
    RTM::RtmRes rtc_detatch_inport_by_name(const char* name);
    RTM::RtmRes rtc_attach_outport(OutPort_ptr out_port);
    RTM::RtmRes rtc_attach_outport_by_name(RTCBase_ptr comp, const char* name);
    RTM::RtmRes rtc_detatch_outport(OutPort_ptr out_port);
    RTM::RtmRes rtc_detatch_outport_by_name(const char* name);
    RTCProfile* profile();

  protected:
    RTCBase();
    virtual ~RTCBase();
  };

};
