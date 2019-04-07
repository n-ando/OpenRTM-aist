// -*- C++ -*-

/*!
 * @file  OpenSpliceInPort.cpp
 * @brief OpenSpliceInPort class
 * @date  $Date: 2019-01-31 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2019
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */


#include "OpenSpliceInPort.h"


#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>
#include <rtm/SystemLogger.h>
#include <coil/Mutex.h>
#include <coil/UUID.h>
#include "OpenSpliceMessageInfo.h"
#include "OpenSpliceInPort_Impl.h"





#ifdef WIN32
#pragma warning( disable : 4290 )
#endif



namespace RTC
{
    /*!
     * @if jp
     * @class OpenSpliceInPort
     * @brief OpenSpliceInPort クラス
     *
     * InPortProvider
     *
     * データ転送に OpenSplice の TCP、UDP通信を利用し
     * た、push 型データフロー型を実現する InPort プロバイダクラス。
     *
     * @since 2.0.0
     *
     * @else
     * @class OpenSpliceInPort
     * @brief OpenSpliceInPort class
     *
     *
     *
     * @since 2.0.0
     *
     * @endif
     */
    class OpenSpliceInPort
        : public InPortProvider, OpenSpliceInPortListenerBase
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
        OpenSpliceInPort(void);

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
        virtual ~OpenSpliceInPort(void);

        /*!
         * @if jp
         * @brief 設定初期化
         *
         * OpenSpliceInPort の各種設定を行う。与えられた
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
         * 等を参照のこと。OpenSpliceInPort では、以下のコールバック
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
         * ConnectorListener.h. In this OpenSpliceInPort provides
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
         * @brief 受信データをバッファに書き込む
         *
         *
         *
         * @param cdr データ
         *
         * @else
         * @brief
         *
         * @param cdr
         *
         *
         * @endif
         */
        void put(RTC::ByteData& cdr) override;

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

        Mutex m_mutex;

        OpenSpliceInPortBase* m_inport;

    };  // class InPortCorCdrbaProvider


  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  OpenSpliceInPort::OpenSpliceInPort(void)
   : m_buffer(0), m_inport(nullptr)
  {
    // PortProfile setting
    setInterfaceType("opensolice");
    // ConnectorProfile setting

  }

  

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  OpenSpliceInPort::~OpenSpliceInPort(void)
  {
    RTC_PARANOID(("~OpenSpliceInPort()"));


  }


  /*!
   * @if jp
   * @brief 設定初期化
   *
   * 
   * @param prop 設定情報
   *
   * @else
   *
   * @brief Initializing configuration
   *
   *
   * @param prop Configuration information
   *
   * @endif
   */
  void OpenSpliceInPort::init(coil::Properties& prop)
  {
      
    RTC_PARANOID(("OpenSpliceInPort::init()"));

    if(prop.propertyNames().size() == 0)
    {
      RTC_DEBUG(("Property is empty."));
      return;
    }

    

    std::string marshaling_type = prop.getProperty("marshaling_type", "corba");
    std::string topic = prop.getProperty("topic", "chatter");


    std::string dataname;
    bool corbamode;
    
    if (marshaling_type != "corba")
    {
        
        dataname = marshaling_type;
        corbamode = false;
    }
    else
    {
        dataname = prop.getProperty("data_type", "RTC::CDR_Data");
        corbamode = true;
    }
    

    OpenSpliceMessageInfoBase* info = OpenSpliceMessageInfoFactory::instance().createObject(dataname);

    if (!info)
    {
        RTC_ERROR(("Can not find message type(%s)", marshaling_type.c_str()));
        return;
    }

    std::string dataType = info->data_type();
    topic = info->topic_name(topic);
    std::string idlPath = info->idl_path();

    OpenSpliceMessageInfoFactory::instance().deleteObject(info);

    std::string endian_type(prop.getProperty("serializer.cdr.endian", ""));
    coil::normalize(endian_type);
    std::vector<std::string> endian_str(coil::split(endian_type, ","));

    bool endian;
    
    if (endian_str[0] == "little")
    {
        endian = true;
    }
    else if (endian_str[0] == "big")
    {
        endian = false;
    }

    m_inport = createOpenSpliceInPort(this, dataType, idlPath, topic, endian, corbamode);

    if (m_inport == nullptr)
    {
        RTC_ERROR(("Failed initialize inport"));
    }
   
  }


  /*!
   * @if jp
   * @brief バッファをセットする
   * @else
   * @brief Setting outside buffer's pointer
   * @endif
   */
  void OpenSpliceInPort::
  setBuffer(BufferBase<ByteData>* buffer)
  {
    m_buffer = buffer;
  }

  /*!
   * @if jp
   * @brief リスナを設定する
   * @else
   * @brief Set the listener
   * @endif
   */
  void OpenSpliceInPort::setListener(ConnectorInfo& info,
                                           ConnectorListeners* listeners)
  {
    m_profile = info;
    m_listeners = listeners;
  }

  /*!
   * @if jp
   * @brief Connectorを設定する。
   * @else
   * @brief set Connector
   * @endif
   */
  void OpenSpliceInPort::setConnector(InPortConnector* connector)
  {
    m_connector = connector;
  }

  /*!
   * @if jp
   * @brief 受信データをバッファに書き込む
   *
   *
   *
   * @param cdr データ
   *
   * @else
   * @brief
   *
   * @param cdr
   *
   *
   * @endif
   */
  void OpenSpliceInPort::put(RTC::ByteData& data)
  {
      RTC_PARANOID(("OpenSpliceInPort::put()"));
      RTC_VERBOSE(("read data length:%d", data.getDataLength()));

      if (m_connector == NULL)
      {
          onReceiverError(data);
      }
      else
      {
          
          onReceived(data);
          BufferStatus::Enum ret = m_connector->write(data);
          convertReturn(ret, data);
      }

  }

  /*!
   * @if jp
   * @brief リターンコード変換
   * @else
   * @brief Return codes conversion
   * @endif
   */
  void OpenSpliceInPort::convertReturn(BufferStatus::Enum status,
                                        ByteData& data)
  {
    switch (status)
      {
      case BufferStatus::BUFFER_OK:
        onBufferWrite(data);
        return;

      case BufferStatus::BUFFER_ERROR:
        onReceiverError(data);
        return;

      case BufferStatus::BUFFER_FULL:
        onBufferFull(data);
        onReceiverFull(data);
        return;

      case BufferStatus::BUFFER_EMPTY:
        // never come here
        return;

      case BufferStatus::PRECONDITION_NOT_MET:
        onReceiverError(data);
        return;

      case BufferStatus::TIMEOUT:
        onBufferWriteTimeout(data);
        onReceiverTimeout(data);
        return;

      default:
        onReceiverError(data);
        return;
      }
  }


} // namespace RTC


void OpenSpliceInPortInit()
{
    RTC::InPortProviderFactory& factory(RTC::InPortProviderFactory::instance());
    factory.addFactory("opensplice",
        ::coil::Creator< ::RTC::InPortProvider,
        ::RTC::OpenSpliceInPort>,
        ::coil::Destructor< ::RTC::InPortProvider,
        ::RTC::OpenSpliceInPort>);
}
