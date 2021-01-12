// -*- C++ -*-

/*!
 * @file  PublisherLink.cpp
 * @brief PublisherLink class
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
#include "PublisherLink.h"



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
  PublisherLink::PublisherLink() : m_num(0)
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
  PublisherLink::PublisherLink(ros::ConnectionPtr conn, int num, const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri)
  : m_bytes_received(0), m_messages_received(0), m_drops(0)
  {
    m_conn = conn;
    m_num = num;
    m_caller_id = caller_id;
    m_topic = topic;
    m_xmlrpc_uri = xmlrpc_uri;
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
  PublisherLink::PublisherLink(const PublisherLink &obj)
  {
    m_conn = obj.m_conn;
    m_num = obj.m_num;
    m_caller_id = obj.m_caller_id;
    m_topic = obj.m_topic;
    m_xmlrpc_uri = obj.m_xmlrpc_uri;
    m_bytes_received = obj.m_bytes_received;
    m_messages_received = obj.m_messages_received;
    m_drops = obj.m_drops;
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
  PublisherLink::~PublisherLink()
  {

  }
  /*!
   * @if jp
   * @brief ros::Connectionを取得
   *
   * @return ros::Connection
   *
   * @else
   * @brief 
   *
   * @return
   *
   * @endif
   */
  ros::ConnectionPtr PublisherLink::getConnection()
  {
    return m_conn;
  }
  /*!
   * @if jp
   * @brief ros::Connectionを設定
   *
   * @param conn ros::Connection
   *
   * @else
   * @brief 
   *
   * @param conn
   *
   * @endif
   */
  void PublisherLink::setConnection(ros::ConnectionPtr conn)
  {
    m_conn = conn;
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
  int PublisherLink::getNum()
  {
    return m_num;
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
  const std::string PublisherLink::getCallerID() const
  {
    return m_caller_id;
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
  const std::string PublisherLink::getTopic() const
  {
    return m_topic;
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
  const std::string PublisherLink::getURI() const
  {
    return m_xmlrpc_uri;
  }
  /*!
   * @if jp
   * @brief コネクタのID取得
   *
   * @param caller_id 
   * @param topic 
   * @param xmlrpc_uri 
   *
   * @else
   * @brief 
   *
   * @param caller_id 
   * @param topic 
   * @param xmlrpc_uri 
   *
   * @endif
   */
  void PublisherLink::setInfo(const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri)
  {
    m_caller_id = caller_id;
    m_topic = topic;
    m_xmlrpc_uri = xmlrpc_uri;
  }

  /*!
   * @if jp
   * @brief コネクタのID取得
   *
   * @param rhs 
   *
   * @else
   * @brief 
   *
   * @param rhs
   *
   * @endif
  */
  bool PublisherLink::operator==(const PublisherLink& rhs) const
  {
    if(m_caller_id == rhs.m_caller_id && m_topic == rhs.m_topic && m_xmlrpc_uri == rhs.m_xmlrpc_uri)
    {
      return true;
    }
    else
    {
      return false;
    }
    
  }

  /*!
   * @if jp
   * @brief コネクタの情報を取得
   *
   *
   * @param data 情報を格納する変数
   * data[0]：コネクタID
   * data[1]：接続先のXML-RPCサーバーのアドレス
   * data[2]："i"
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
  void PublisherLink::getInfo(XmlRpc::XmlRpcValue& data)
  {
    data[0] = m_num;
    data[1] = m_xmlrpc_uri;
    data[2] = std::string("i");
    data[3] = std::string(m_conn->getTransport()->getType());
    data[4] = m_topic;
    data[5] = true;
    data[6] = m_conn->getTransport()->getTransportInfo();
  }

  /*!
   * @if jp
   * @brief 受信データの統計情報取得
   *
   *
   * @param data 受信データの統計情報
   * 
   * @else
   * @brief 
   *
   * 
   * @param data
   *
   * @endif
   */
  void PublisherLink::getStats(XmlRpc::XmlRpcValue& data)
  {
    data[0] = m_num;
    data[1] = (int)m_bytes_received;
    data[2] = (int)m_messages_received;
    data[3] = (int)m_drops;
    data[4] = 0;
  }

  /*!
   * @if jp
   * @brief データ受信時に受信したデータサイズを受け取る
   *
   *
   * @param size データサイズ
   * 
   * @else
   * @brief 
   *
   * 
   * @param size
   *
   * @endif
   */
  void PublisherLink::notifyRead(const uint32_t& size)
  {
    m_bytes_received += size;
    m_messages_received++;
  }

} // namespace RTC
