// -*- C++ -*-
/*!
 * @file RTCInPort.i
 * @brief swig interface file for RTCInPort
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

/*
 * $Log: not supported by cvs2svn $
 *
 */

%module RTCInPort


%{
#include "rtm/idl/RTCInPortSkel.h"
%}


namespace RTM
{
  class InPort
  {
  public:
    void put(const CORBA::Any& data);
    RTM::PortProfile* profile();
    
  protected:
    InPort();
    virtual ~InPort();
  };
};
