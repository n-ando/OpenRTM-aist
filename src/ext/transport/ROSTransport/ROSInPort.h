// -*- C++ -*-
/*!
 * @file  ROSInPort.h
 * @brief ROSInPort class
 * @date  $Date: 2018-01-15 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2018
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_ROSINPORT_H
#define RTC_ROSINPORT_H

#include <map>
#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>
#include <coil/Mutex.h>
#include <ros/connection.h>
#include <ros/transport/transport_tcp.h>
#include "ROSMessageInfo.h"


#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class ROSInPort
   * @brief ROSInPort クラス
   *
   * InPortProvider 
   *
   * データ転送に ROS の TCP、UDP通信を利用し
   * た、push 型データフロー型を実現する InPort プロバイダクラス。
   *
   * @since 2.0.0
   *
   * @else
   * @class ROSInPort
   * @brief ROSInPort class
   *
   * 
   *
   * @since 2.0.0
   *
   * @endif
   */
  class ROSInPort
    : public InPortProvider
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<coil::Mutex> Guard;
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    ROSInPort(void);
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~ROSInPort(void);

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * ROSInPort の各種設定を行う。与えられた
     * Propertiesから必要な情報を取得して各種設定を行う。この init() 関
     * 数は、InPortProvider生成直後および、接続時にそれぞれ呼ばれる可
     * 能性がある。したがって、この関数は複数回呼ばれることを想定して記
     * 述されるべきである。
     * 
     * @param prop 設定情報
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     * This function might be called right after instantiation and
     * connection sequence respectivly.  Therefore, this function
     * should be implemented assuming multiple call.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief バッファをセットする
     *
     * OutPortProvider がデータを取り出すバッファをセットする。
     * すでにセットされたバッファがある場合、以前のバッファへの
     * ポインタに対して上書きされる。
     * OutPortProviderはバッファの所有権を仮定していないので、
     * バッファの削除はユーザの責任で行わなければならない。
     *
     * @param buffer OutPortProviderがデータを取り出すバッファへのポインタ
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * A pointer to a buffer from which OutPortProvider retrieve data.
     * If already buffer is set, previous buffer's pointer will be
     * overwritten by the given pointer to a buffer.  Since
     * OutPortProvider does not assume ownership of the buffer
     * pointer, destructor of the buffer should be done by user.
     * 
     * @param buffer A pointer to a data buffer to be used by OutPortProvider
     *
     * @endif
     */
    virtual void setBuffer(BufferBase<ByteData>* buffer);

    /*!
     * @if jp
     * @brief リスナを設定する。
     *
     * InPort はデータ送信処理における各種イベントに対して特定のリスナ
     * オブジェクトをコールするコールバック機構を提供する。詳細は
     * ConnectorListener.h の ConnectorDataListener, ConnectorListener
     * 等を参照のこと。ROSInPort では、以下のコールバック
     * が提供される。
     * 
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_BUFFER_WRITE_TIMEOUT
     * - ON_BUFFER_OVERWRITE
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_TIMEOUT
     * - ON_RECEIVER_ERROR
     *
     * @param info 接続情報
     * @param listeners リスナオブジェクト
     *
     * @else
     * @brief Set the listener. 
     *
     * InPort provides callback functionality that calls specific
     * listener objects according to the events in the data publishing
     * process. For details, see documentation of
     * ConnectorDataListener class and ConnectorListener class in
     * ConnectorListener.h. In this ROSInPort provides
     * the following callbacks.
     * 
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_BUFFER_WRITE_TIMEOUT
     * - ON_BUFFER_OVERWRITE
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_TIMEOUT
     * - ON_RECEIVER_ERROR
     *
     * @param info Connector information
     * @param listeners Listener objects
     *
     * @endif
     */
    virtual void setListener(ConnectorInfo& info,
                             ConnectorListeners* listeners);

    /*!
     * @if jp
     * @brief Connectorを設定する。
     *
     * InPort は接続確立時に InPortConnector オブジェクトを生成し、生
     * 成したオブジェクトのポインタと共にこの関数を呼び出す。所有権は
     * InPort が保持するので InPortProvider は InPortConnector を削
     * 除してはいけない。
     *
     * @param connector InPortConnector
     *
     * @else
     * @brief set Connector
     *
     * InPort creates InPortConnector object when it establishes
     * connection between InPort and InPort, and it calls this
     * function with a pointer to the connector object. Since the
     * InPort has the ownership of this connector, InPortProvider
     * should not delete it.
     *
     * @param connector InPortConnector
     *
     * @endif
     */
    virtual void setConnector(InPortConnector* connector);

    /*!
     * @if jp
     * @brief ROSTCPでサブスクライバーとパブリッシャーを接続する
     *
     *
     * @param caller_id 呼び出しID
     * @param topic トピック名
     * @param xmlrpc_uri パブリッシャーのURI
     *
     * 
     * @else
     * @brief 
     *
     *
     * @param caller_id 
     * @param topic 
     * @param xmlrpc_uri 
     * 
     * @return
     *
     * @endif
     */
    void connectTCP(const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri);

    /*!
     * @if jp
     * @brief TCPコネクタの削除
     *
     *
     * @param caller_id 呼び出しID
     * @param topic トピック名
     * @param xmlrpc_uri パブリッシャーのURI
     *
     * 
     * @else
     * @brief 
     *
     *
     * @param caller_id 
     * @param topic 
     * @param xmlrpc_uri 
     * 
     * @return
     *
     * @endif
     */
    void deleteTCPConnector(const std::string &caller_id, const std::string &topic, const std::string &xmlrpc_uri);
    
    /*!
     * @if jp
     * @brief ヘッダ情報送信時のコールバック関数
     *
     *
     * @param conn ros::Connection
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
    void onHeaderWritten(const ros::ConnectionPtr& conn)
    {
      RTC_VERBOSE(("onHeaderWritten()"));
      (void)conn;
    };

    /*!
     * @if jp
     * @brief ヘッダ情報受信時のコールバック関数
     *
     *
     * @param conn ros::Connection
     * @param header ros::Header
     * 
     * @return
     *
     * 
     * @else
     * @brief 
     *
     *
     * @param conn
     * @param header
     * 
     * @return
     *
     * @endif
     */
    bool onHeaderReceived(const ros::ConnectionPtr& conn, const ros::Header& header)
    {
      RTC_VERBOSE(("onHeaderReceived()"));
      (void)header;
      conn->read(4, boost::bind(&ROSInPort::onMessageLength, this, _1, _2, _3, _4));
      return true;
    }

    /*!
     * @if jp
     * @brief メッセージ長さ読み込み時のコールバック関数
     *
     *
     * @param conn ros::Connection
     * @param buffer 受信データバッファ
     * @param size データサイズ
     * @param success 読み込み成功、失敗
     *
     * 
     * @else
     * @brief 
     *
     *
     * @param conn 
     * @param buffer 
     * @param size 
     * @param success 
     * 
     *
     * @endif
     */
    void onMessageLength(const ros::ConnectionPtr& conn, const boost::shared_array<uint8_t>& buffer, uint32_t size, bool success)
    {
      RTC_VERBOSE(("onMessageLength()"));
      if(!success)
      {
        RTC_ERROR(("Message read error"));
        return;
      }

      (void)size;

      uint32_t len = *((uint32_t*)buffer.get());

      
      conn->read(len, boost::bind(&ROSInPort::onMessage, this, _1, _2, _3, _4));
    };

    /*!
     * @if jp
     * @brief メッセージ読み込み時のコールバック関数
     *
     *
     * @param conn ros::Connection
     * @param buffer 受信データバッファ
     * @param size データサイズ
     * @param success 読み込み成功、失敗
     *
     * 
     * @else
     * @brief 
     *
     *
     * @param conn 
     * @param buffer 
     * @param size 
     * @param success 
     * 
     *
     * @endif
     */
    void onMessage(const ros::ConnectionPtr& conn, const boost::shared_array<uint8_t>& buffer, uint32_t size, bool success)
    {

      RTC_PARANOID(("ROSInPort::onMessage()"));

      if(!success)
      {
        RTC_ERROR(("disconnect topic"));
        return;
      }

      RTC_VERBOSE(("read data length:%d", size));

      if (m_connector == NULL)
      {
        ByteData cdr;
        cdr.setDataLength(size+4);
        memcpy(cdr.getBuffer()+4, buffer.get(), size);
        
        onReceiverError(cdr);
      }
      else
      {

        RTC_PARANOID(("received data size: %d", size));
        ByteData cdr;

        cdr.setDataLength(size+4);
        memcpy(cdr.getBuffer()+4, buffer.get(), size);

        RTC_PARANOID(("converted CDR data size: %d", cdr.getDataLength()));

        onReceived(cdr);
      
        BufferStatus::Enum ret = m_connector->write(cdr);

        switch (ret)
        {
          case BufferStatus::BUFFER_OK:
            RTC_VERBOSE(("BUFFER_OK"));
            break;
          case BufferStatus::BUFFER_EMPTY:
            RTC_ERROR(("BUFFER_EMPTY"));
            break;
          case BufferStatus::TIMEOUT:
            RTC_ERROR(("TIMEOUT"));
            break;
          case BufferStatus::PRECONDITION_NOT_MET:
            RTC_ERROR(("PRECONDITION_NOT_MET"));
          default:
            RTC_ERROR(("PORT_ERROR"));
        }


        conn->read(4, boost::bind(&ROSInPort::onMessageLength, this, _1, _2, _3, _4));
      }
    }
    
  private:


    
    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE のリスナへ通知する。 
     * @param data ByteData
     * @else
     * @brief Notify an ON_BUFFER_WRITE event to listeners
     * @param data ByteData
     * @endif
     */
    inline void onBufferWrite(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_FULL のリスナへ通知する。 
     * @param data ByteData
     * @else
     * @brief Notify an ON_BUFFER_FULL event to listeners
     * @param data ByteData
     * @endif
     */
    inline void onBufferFull(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_TIMEOUT のリスナへ通知する。 
     * @param data ByteData
     * @else
     * @brief Notify an ON_BUFFER_WRITE_TIMEOUT event to listeners
     * @param data ByteData
     * @endif
     */
    inline void onBufferWriteTimeout(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_OVERWRITE のリスナへ通知する。 
     * @param data ByteData
     * @else
     * @brief Notify an ON_BUFFER_WRITE_OVERWRITE event to listeners
     * @param data ByteData
     * @endif
     */
    inline void onBufferWriteOverwrite(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVED のリスナへ通知する。 
     * @param data ByteData
     * @else
     * @brief Notify an ON_RECEIVED event to listeners
     * @param data ByteData
     * @endif
     */
    inline void onReceived(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVED].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_FULL のリスナへ通知する。 
     * @param data ByteData
     * @else
     * @brief Notify an ON_RECEIVER_FULL event to listeners
     * @param data ByteData
     * @endif
     */
    inline void onReceiverFull(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_TIMEOUT のリスナへ通知する。 
     * @else
     * @brief Notify an ON_RECEIVER_TIMEOUT event to listeners
     * @endif
     */
    inline void onReceiverTimeout(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_ERRORのリスナへ通知する。 
     * @else
     * @Brief Notify an ON_RECEIVER_ERROR event to listeners
     * @endif
     */
    inline void onReceiverError(ByteData& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

  private:
    /*!
     * @if jp
     * @brief リターンコード変換
     * @else
     * @brief Return codes conversion
     * @endif
     */
    void convertReturn(BufferStatus::Enum status, ByteData& data);

    CdrBufferBase* m_buffer;
    ConnectorInfo m_profile;
    ConnectorListeners* m_listeners;
    InPortConnector* m_connector;

    
    std::string m_topic;
    std::string m_callerid;
    std::string m_messageType;
    Mutex m_mutex;
    std::map<std::string, ros::ConnectionPtr> m_tcp_connecters;
    std::string m_roscorehost;
    unsigned int m_roscoreport;
    


  };  // class InPortCorCdrbaProvider
};    // namespace RTC



#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_ROSINPORT_H

