/*! -*- C++ -*-
 *
 * @file OutPortPullConnector.h
 * @brief OutPortPull type connector class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_OUTPORTPULLCONNECTOR_H
#define RTC_OUTPORTPULLCONNECTOR_H

#include <rtm/OutPortConnector.h>

namespace RTC
{
  class OutPortProvider;

  class OutPortPullConnector
    : public OutPortConnector
  {
  public:
    DATAPORTSTATUS_ENUM

    OutPortPullConnector(Profile profile,
                         OutPortProvider* provider,
                         CdrBufferBase* buffer);

    virtual ~OutPortPullConnector();

    virtual ReturnCode write(const cdrMemoryStream& data);
    
    virtual ReturnCode disconnect();

    virtual void activate(){}; // do nothing
    virtual void deactivate(){}; // do nothing
  protected:
    OutPortProvider* m_provider;
  };
}; // namespace RTC

#endif  // RTC_PULL_CONNECTOR_H
