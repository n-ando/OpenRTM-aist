// -*- C++ -*-
/*!
 * @file RTCOutPort.i
 * @brief swig interface file for RTCOutPort
 * @date $Date: 2005-05-27 15:49:29 $
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

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:19  n-ando
 * Public release.
 *
 *
 */

%module RTCOutPort


%{
#include "rtm/idl/RTCInPortSkel.h"
#include "rtm/idl/RTCOutPortSkel.h"
%}


namespace RTM
{
  class OutPort
  {
  public:
    CORBA::Any* get();
	//	RTM::RtmRes subscribe(RTM::InPort_ptr in_port, RTM::SubscriptionID_out id,
	//						  const RTM::SubscriberProfile& profile );
    RTM::RtmRes unsubscribe(const char* id);
    RTM::PortProfile* profile();
    
  protected:
    OutPort();
    virtual ~OutPort();
  };
};
