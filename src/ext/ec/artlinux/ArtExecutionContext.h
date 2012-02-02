// -*- C++ -*-
/*!
 * @file ArtExecutionContext.h
 * @brief ArtExecutionContext class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
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
 * $Log$
 */

#ifndef ArtExecutionContext_h
#define ArtExecutionContext_h

#include <rtm/RTC.h>


#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

namespace RTC
{
  class ArtExecutionContext
    : public virtual PeriodicExecutionContext
  {
  public:
    ArtExecutionContext();
    virtual ~ArtExecutionContext();
    virtual int svc(void);
  };
};

extern "C"
{
  void ArtExecutionContextInit(RTC::Manager* manager);
};

#endif // ArtExecutionContext_h

