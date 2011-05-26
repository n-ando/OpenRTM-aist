// -*- C++ -*-
/*!
 * @file SdoServiceConsumerBase.h
 * @brief SDO service consumer base class and its factory
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */


#ifndef RTC_SDOSERVICECONSUMERBASE_H
#define RTC_SDOSERVICECONSUMERBASE_H

#include <coil/Mutex.h>
#include <coil/Factory.h>
#include <rtm/RTObject.h>
#include <rtm/idl/SDOPackageStub.h>
#include <coil/Timer.h>
namespace RTC
{

  /*!
   * @if jp
   *
   * ::RTC::SdoServiceConsumerFactory&
   *                     factory(::RTC::SdoServiceConsumerFactory::instance());
   *
   * factory.addFactory(toRepositoryId<IDL Type>(),
   *                   ::coil::Creator< ::RTC::SdoServiceConsumerBase,
   *                                    your_sdo_service_consumer_subclass>,
   *                   ::coil::Destructor< ::RTC::SdoServiceConsumerBase,
   *                                    your_sdo_service_consumer_subclass>);
   *
   * @else
   *
   *
   *
   * @endif
   *
   */
  class SdoServiceConsumerBase
  {
  public:
    virtual ~SdoServiceConsumerBase() {};
    virtual bool init(RTObject_impl& rtobj,
                      const SDOPackage::ServiceProfile& profile) = 0;
    virtual bool reinit(const SDOPackage::ServiceProfile& profile) = 0;
    virtual const SDOPackage::ServiceProfile& getProfile() const = 0;
    virtual void finalize() = 0;
  };

  typedef ::coil::GlobalFactory<
    ::RTC::SdoServiceConsumerBase > SdoServiceConsumerFactory;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  EXTERN template class DLL_PLUGIN 
                     ::coil::GlobalFactory< ::RTC::SdoServiceConsumerBase >;
#endif
  
}; // namespace RTC

#endif // RTC_SDOSERVICECONSUMERBASE_H
