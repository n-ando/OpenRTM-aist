// -*- C++ -*-
/*!
 * @file Timestamp.h
 * @brief Timestamp listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Noriaki Ando
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTM_TIMESTAMP_H
#define RTM_TIMESTAMP_H

#include <rtm/ConnectorListener.h>
#include <chrono>

/*!
 * @if jp
 * @brief データにタイムスタンプをセットする
 *
 * データポートのデータに対してタイムスタンプをセットする。データポート
 * のデータは構造体のメンバーとして tm.sec, tm.nsec を持つ必要がある。
 *
 * @param data タイムスタンプをセットするデータ。実行後実行時のタイムス
 *             タンプがセットされる
 *
 * @else
 * @brief Setting timestamp to data
 *
 * This function sets timestamp to data of data port. This data should
 * have tm.sec, tm.nsec as members of the structure.
 *
 * @param data Data to be set timestamp. After executing this
 *             function, current timestamp is set to the data.
 *
 * @endif
 */
template <class DataType>
void setTimestamp(DataType& data)
{
  auto now = std::chrono::system_clock::now().time_since_epoch();
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(now);
  auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - sec);
// We do not consider overflow of tm.sec.
  data.tm.sec  = static_cast<decltype(data.tm.sec)>(sec.count());
  data.tm.nsec = static_cast<decltype(data.tm.nsec)>(nsec.count());
}

namespace RTC
{
  template <class DataType>
  class Timestamp
    : public ConnectorDataListenerT<DataType>
  {
    USE_CONNLISTENER_STATUS;
  public:
    Timestamp(const char* ts_type) : m_tstype(ts_type) {}
    ~Timestamp() override = default;
    ReturnCode operator()(ConnectorInfo& info, DataType& data) override
    {
      if (info.properties["timestamp_policy"] != m_tstype)
        {
          return NO_CHANGE;
        }
      setTimestamp<DataType>(data);
      return DATA_CHANGED;
    }
    std::string m_tstype;
  };
} // namespace RTC

#endif // RTM_TIMESTAMP_H
