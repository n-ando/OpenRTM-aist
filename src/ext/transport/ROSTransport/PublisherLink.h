// -*- C++ -*-
/*!
 * @file  PublisherLink.h
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

#ifndef RTC_PUBLISHERLINK_H
#define RTC_PUBLISHERLINK_H

#include <ros/transport/transport_tcp.h>
#include <xmlrpcpp/XmlRpc.h>


namespace RTC
{
  /*!
  * @if jp
  * @class PublisherLink
  * @brief PublisherLink クラス
  *
  * Subscriber側でPublisherとの接続情報(ros::Connection、接続先のノード名、コネクタのID)を格納するクラス
  *
  * @since 2.0.0
  *
  * @else
  * @class PublisherLink
  * @brief PublisherLink class
  *
  * 
  *
  * @since 2.0.0
  *
  * @endif
  */
  class PublisherLink
  {
  public:
      /*!
      * @if jp
      * @brief コンストラクタ
      *
      * @else
      * @brief Constructor
      *
      * @endif
      */
      PublisherLink(void);
      /*!
      * @if jp
      * @brief コンストラクタ
      *
      * @param conn ros::Connection
      * @param num コネクタのID
      * @param caller_id 呼び出しID
      * @param topic トピック名
      * @param xmlrpc_uri 接続先のURI
      *
      * @else
      * @brief Constructor
      *
      * @param conn 
      * @param num 
      * @param caller_id 
      * @param topic 
      * @param xmlrpc_uri 
      *
      * @endif
      */
      PublisherLink(ros::ConnectionPtr conn, int num, const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri);
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
      PublisherLink(const PublisherLink &obj);
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
      ~PublisherLink();
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
      ros::ConnectionPtr getConnection();
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
      void setConnection(ros::ConnectionPtr conn);
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
      int getNum();
      /*!
      * @if jp
      * @brief 呼び出しID取得
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
      const std::string getCallerID() const;
      /*!
      * @if jp
      * @brief トピック名取得
      *
      * @return トピック名
      *
      * @else
      * @brief 
      *
      * @return
      *
      * @endif
      */
      const std::string getTopic() const;
      /*!
      * @if jp
      * @brief 接続先のURI取得
      *
      * @return 接続先のURI
      *
      * @else
      * @brief 
      *
      * @return
      *
      * @endif
      */
      const std::string getURI() const;
      /*!
      * @if jp
      * @brief 呼び出しID、トピック名、接続先のURIを設定する
      *
      * @param caller_id 呼び出しID
      * @param topic トピック名
      * @param xmlrpc_uri 接続先のURI
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
      void setInfo(const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri);
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
      void getInfo(XmlRpc::XmlRpcValue& data);
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
      void getStats(XmlRpc::XmlRpcValue& data);
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
      void notifyRead(const uint32_t& size);
      /*!
       * @if jp
       * @brief 等価比較演算子
       * 呼び出しID、トピック名、接続先のURIが一致した場合に等価と判定する
       *
       * @param rhs 比較対象のオブジェクト
       *
       * @else
       * @brief 
       *
       * @param rhs
       *
       * @endif
      */
      bool operator==(const PublisherLink& rhs) const;
  private:
      ros::ConnectionPtr m_conn;
      int m_num;
      std::string m_caller_id;
      std::string m_topic;
      std::string m_xmlrpc_uri;
      uint64_t m_bytes_received;
      uint64_t m_messages_received;
      uint64_t m_drops;
  };  // class PublisherLink
} // namespace RTC



#endif // RTC_PUBLISHERLINK_H

