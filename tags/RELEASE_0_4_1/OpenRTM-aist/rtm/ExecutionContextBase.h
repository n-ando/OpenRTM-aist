// -*- C++ -*-
/*!
 * @file ExecutionContextBase.h
 * @brief ExecutionContext base class
 * @date $Date: 2007-04-13 16:07:22 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ExecutionContextBase.h,v 1.1 2007-04-13 16:07:22 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef ExecutionContextBase_h
#define ExecutionContextBase_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>

namespace RTC
{
  class ExecutionContextBase
    : public virtual POA_RTC::ExtTrigExecutionContextService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    virtual ~ExecutionContextBase(){};
    virtual void tick(){};
  };
};
#endif // ExecutionContextBase_h
