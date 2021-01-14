// -*- C++ -*-
/*!
 * @file  SubscriberLink.h
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

#ifndef RTC_SUBSCRIBERLINK_H
#define RTC_SUBSCRIBERLINK_H

#include <ros/transport/transport_tcp.h>
#include <xmlrpcpp/XmlRpc.h>
#include <rtm/ByteData.h>


namespace RTC
{
  /*!
  * @if jp
  * @class SubscriberLink
  * @brief SubscriberLink クラス
  *
  * Publisher側でSubscriberとの接続情報(ros::Connection、接続先のノード名、コネクタのID)を格納するクラス
  *
  * @since 2.0.0
  *
  * @else
  * @class SubscriberLink
  * @brief SubscriberLink class
  *
  * 
  *
  * @since 2.0.0
  *
  * @endif
  */
  class SubscriberLink
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
      SubscriberLink();
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
      SubscriberLink(ros::ConnectionPtr conn, int num);
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
      SubscriberLink(const SubscriberLink &obj);
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
      ~SubscriberLink();
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
      void setNoneName(std::string& name);
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
      const std::string getNodeName() const;
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
      void setConnection(ros::ConnectionPtr conn);
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
      ros::ConnectionPtr getConnection();
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
      void setCallerID(const std::string &callerid);
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
      const std::string getCallerID() const;
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
      void setTopic(const std::string &topic);
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
      const std::string getTopic() const;
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
      void getInfo(XmlRpc::XmlRpcValue& data);
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
      void getStats(XmlRpc::XmlRpcValue& data);
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
      void setStatBytes(const uint64_t size);


      /*!
       * @if jp
       * @brief データの送信
       *
       *
       * @param buffer 送信データ
       * @param length データ長さ
       * @return true：送信成功
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
      bool write(boost::shared_array<uint8_t>& buffer, const uint32_t &length);

      /*!
       * @if jp
       * @brief メッセージ送信時のコールバック関数
       *
       *
       * @param conn ros::Connectionオブジェクト
       *
       * 
       * @else
       * @brief 
       *
       *
       * @param conn 
       * 
       * @return
       *
       * @endif
       */
      void onMessageWritten(const ros::ConnectionPtr& /*conn*/)
      {
      }
  private:
      std::string m_nodename;
      ros::ConnectionPtr m_conn;
      int m_num;
      std::string m_callerid;
      std::string m_topic;
      uint64_t m_bytes_sent;
      uint64_t m_message_data_sent;
      uint64_t m_messages_sent;
  };  // class SubscriberLink
} // namespace RTC



#endif // RTC_SUBSCRIBERLINK_H

