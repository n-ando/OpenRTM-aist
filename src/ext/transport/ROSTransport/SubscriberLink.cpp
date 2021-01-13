// -*- C++ -*-

/*!
 * @file  SubscriberLink.cpp
 * @brief SubscriberLink class
 * @date  $Date: 2021-01-08 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2021
 *     Nobuhiko Miyamoto
 *     Industrial Cyber-Physical Systems Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#include <xmlrpcpp/XmlRpc.h>
#include <ros/connection_manager.h>
#include "SubscriberLink.h"



namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   *
   * @else
   * @brief Constructor
   *
   * @endif
   */
  SubscriberLink::SubscriberLink() : m_num(0),
                                     m_bytes_sent(0),
                                     m_message_data_sent(0),
                                     m_messages_sent(0)
  {
  }

  /*!
   * @if jp
   * @brief コンストラクタ
   *
   * @param conn ros::Connectionオブジェクト
   * @param num コネクタのID
   *
   * @else
   * @brief Constructor
   *
   * @param conn 
   * @param num 
   *
   * @endif
   */
  SubscriberLink::SubscriberLink(ros::ConnectionPtr conn, int num) : m_bytes_sent(0),
                                                                     m_message_data_sent(0),
                                                                     m_messages_sent(0)
  {
    m_conn = conn;
    m_num = num;
  }
  /*!
   * @if jp
   * @brief コピーコンストラクタ
   *
   * @param obj コピー元 
   *
   * @else
   * @brief Copy Constructor
   *
   * @param obj
   *
   * @endif
   */
  SubscriberLink::SubscriberLink(const SubscriberLink &obj)
  {
    m_conn = obj.m_conn;
    m_nodename = obj.m_nodename;
    m_num = obj.m_num;
    m_callerid = obj.m_callerid;
    m_topic = obj.m_topic;
    m_bytes_sent = obj.m_bytes_sent;
    m_message_data_sent = obj.m_message_data_sent;
    m_messages_sent = obj.m_messages_sent;
  }
  /*!
   * @if jp
   * @brief デストラクタ
   *
   *
   * @else
   * @brief Destructor
   *
   *
   * @endif
   */
  SubscriberLink::~SubscriberLink()
  {

  }
  /*!
   * @if jp
   * @brief 接続先のノード名を設定
   *
   * @param name ノード名
   *
   * @else
   * @brief 
   *
   * @param name
   *
   * @endif
   */
  void SubscriberLink::setNoneName(std::string& name)
  {
    m_nodename = name;
  }
  /*!
   * @if jp
   * @brief 接続先のノード名を取得
   *
   * @return ノード名
   *
   * @else
   * @brief 
   *
   * @return
   *
   * @endif
   */
  const std::string SubscriberLink::getNodeName() const
  {
    return m_nodename;
  }
  /*!
   * @if jp
   * @brief ros::Connectionオブジェクトを設定
   *
   * @param conn ros::Connectionオブジェクト
   *
   * @else
   * @brief 
   *
   * @param conn
   *
   * @endif
   */
  void SubscriberLink::setConnection(ros::ConnectionPtr conn)
  {
    m_conn = conn;
  }
  /*!
   * @if jp
   * @brief ros::Connectionオブジェクトを取得
   *
   * @return ros::Connectionオブジェクト
   *
   * @else
   * @brief 
   *
   * @return
   *
   * @endif
   */
  ros::ConnectionPtr SubscriberLink::getConnection()
  {
    return m_conn;
  }
  /*!
   * @if jp
   * @brief コネクタのID取得
   *
   * @return コネクタのID
   *
   * @else
   * @brief 
   *
   * @return
   *
   * @endif
   */
  int SubscriberLink::getNum()
  {
    return m_num;
  }

  /*!
  * @if jp
  * @brief 呼び出しIDを設定
  *
  * @param caller_id 呼び出しID
  *
  * @else
  * @brief 
  *
  * @param conn
  *
  * @endif
  */
  void SubscriberLink::setCallerID(const std::string &callerid)
  {
    m_callerid = callerid;
  }
  /*!
  * @if jp
  * @brief 呼び出しIDを取得
  *
  * @return 呼び出しID
  *
  * @else
  * @brief 
  *
  * @return
  *
  * @endif
  */
  const std::string SubscriberLink::getCallerID() const
  {
    return m_callerid;
  }

  /*!
   * @if jp
   * @brief 呼び出しIDを設定
   *
   * @param topic 呼び出しID
   *
   * @else
   * @brief 
   *
   * @param conn
   *
   * @endif
   */
  void SubscriberLink::setTopic(const std::string &topic)
  {
    m_topic = topic;
  }

  /*!
   * @if jp
   * @brief 呼び出しIDを取得
   *
   * @return 呼び出しID
   *
   * @else
   * @brief 
   *
   * @return
   *
   * @endif
   */
  const std::string SubscriberLink::getTopic() const
  {
    return m_topic;
  }

  /*!
   * @if jp
   * @brief コネクタの情報を取得
   *
   *
   * @param data 情報を格納する変数
   * data[0]：コネクタID
   * data[1]：接続先のノード名
   * data[2]："o"
   * data[3]：TCPROS or UDPROS
   * data[4]：トピック名
   * data[5]：true
   * data[6]：接続情報
   * 
   * @else
   * @brief 
   *
   *
   * @param info
   * 
   *
   * @endif
   */
  void SubscriberLink::getInfo(XmlRpc::XmlRpcValue& data)
  {
    data[0] = m_num;
    data[1] = m_callerid;
    data[2] = std::string("o");
    data[3] = std::string(m_conn->getTransport()->getType());
    data[4] = m_topic;
    data[5] = true;
    data[6] = m_conn->getTransport()->getTransportInfo();
  }

  /*!
   * @if jp
   * @brief 送信データの統計情報取得
   *
   *
   * @param data 送信データの統計情報
   * 
   * @else
   * @brief 
   *
   * 
   * @param data
   *
   * @endif
   */
  void SubscriberLink::getStats(XmlRpc::XmlRpcValue& data)
  {
    data[0] = m_num;
    data[1] = (int)m_bytes_sent;
    data[2] = (int)m_messages_sent;
    data[3] = 0;
  }

  /*!
   * @if jp
   * @brief 過去に送信したデータ量(byte)を設定する
   *
   *
   * @param size データ量(byte)
   * 
   * @else
   * @brief 
   *
   * 
   * @param size
   *
   * @endif
   */
  void SubscriberLink::setStatBytes(const uint64_t size)
  {
    m_bytes_sent = size;
    m_messages_sent = 1;
  }

  /*!
   * @if jp
   * @brief データの送信
   *
   *
   * @param buffer 送信データ
   * @param length データ長さ
   * @return true：送信成功
   * 
   * @else
   * @brief 
   *
   * 
   * @param buffer 
   * @param length 
   * @return 
   *
   * @endif
   */
  bool SubscriberLink::write(boost::shared_array<uint8_t>& buffer, const uint32_t &length)
  {
    if(!m_conn->isDropped())
    {
      m_conn->write(buffer, length, boost::bind(&SubscriberLink::onMessageWritten, this, _1), true);
      m_message_data_sent += static_cast<uint64_t>(length);
      m_bytes_sent += static_cast<uint64_t>(length);
      m_messages_sent++;
      return true;
    }
    else
    {
      return false;
    }
  }

} // namespace RTC
