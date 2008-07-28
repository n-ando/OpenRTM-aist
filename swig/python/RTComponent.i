// -*- C++ -*-
/*!
 * @file RTComponent.i
 * @brief swig interface file for RTComponent
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
 * $Id$
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
  class RTComponent
  {
  public:
    RTM::RtmRes rtc_start();
    RTM::RtmRes rtc_stop();
    RTM::RtmRes rtc_reset();
    RTM::RtmRes rtc_exit();
    RTM::RtmRes rtc_kill();
    RTM::RtmRes rtc_worker();
    RTM::InPort_ptr get_inport(const char* name);
    RTM::OutPort_ptr get_outport(const char* name);
    RTM::OutPort_ptr rtc_state();
    RTM::InPortList* inports();
    RTM::OutPortList* outports();
    //    RTCProfile* profile();
    //    RTCConfiguration* configuration();

  protected:
    RTComponent();
    virtual ~RTComponent();
  };

};
