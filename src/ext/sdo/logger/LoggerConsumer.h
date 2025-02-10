// -*- C++ -*-
/*!
 * @file LoggerConsumer.h
 * @brief Component observer SDO service consumer implementation
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


#ifndef RTC_LOGGERCONSUMER_H
#define RTC_LOGGERCONSUMER_H

#include <coil/Factory.h>
#include <coil/stringutil.h>
#include <rtm/SdoServiceConsumerBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/idl/SDOPackageStub.h>

#include "LoggerStub.h"

namespace RTC
{

  /*!
   * @if jp
   * @else
   * @endif
   */
  class LoggerConsumer
    : public SdoServiceConsumerBase
  {
  public:
    /*!
     * @if jp
     * @brief ctor of LoggerConsumer
     * @else
     * @brief ctor of LoggerConsumer
     * @endif
     */
    LoggerConsumer();

    /*!
     * @if jp
     * @brief dtor
     * @else
     * @brief dtor
     * @endif
     */
    ~LoggerConsumer() override;

    /*!
     * @if jp
     * @brief 初期化
     * @else
     * @brief Initialization
     * @endif
     */
    bool init(RTObject_impl& rtobj,
                      const SDOPackage::ServiceProfile& profile) override;

    /*!
     * @if jp
     * @brief 再初期化
     * @else
     * @brief Re-initialization
     * @endif
     */
    bool reinit(const SDOPackage::ServiceProfile& profile) override;

    /*!
     * @if jp
     * @brief ServiceProfile を取得する
     * @else
     * @brief getting ServiceProfile
     * @endif
     */
    const SDOPackage::ServiceProfile& getProfile() const override;
    
    /*!
     * @if jp
     * @brief 終了処理
     * @else
     * @brief Finalization
     * @endif
     */
    void finalize() override;

  protected:

    RTC::RTObject_impl* m_rtobj{nullptr};
    SDOPackage::ServiceProfile m_profile;
    CorbaConsumer<OpenRTM::Logger> m_logger;
  };

} // namespace RTC

extern "C"
{
  DLL_EXPORT void LoggerConsumerInit();
}

#endif // RTC_LOGGERCONSUMER_H


