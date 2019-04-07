// -*- C++ -*-
/*!
 * @file  OpenSpliceOutPort.cpp
 * @brief OpenSpliceOutPort class
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




#include <rtm/NVUtil.h>
#include <rtm/InPortConsumer.h>
#include <rtm/SystemLogger.h>
#include <coil/Mutex.h>
#include <coil/UUID.h>
#include <coil/stringutil.h>
#include "OpenSpliceOutPort.h"
#include "OpenSpliceMessageInfo.h"
#include "OpenSpliceOutPort_Impl.h"





namespace RTC
{

    /*!
     * @if jp
     * @class OpenSpliceOutPort
     * @brief OpenSpliceOutPort クラス
     *
     * InPortConsumer
     *
     * データ転送に CORBA の OpenRTM::InPortCdr インターフェースを利用し
     * た、push 型データフロー型を実現する InPort コンシューマクラス。
     *
     * @since 2.0.0
     *
     * @else
     * @class OpenSpliceOutPort
     * @brief OpenSpliceOutPort class
     *
     * The InPort consumer class which uses the OpenRTM::InPortCdr
     * interface in CORBA for data transfer and realizes a push-type
     * dataflow.
     *
     * @since 2.0.0
     *
     * @endif
     */
    class OpenSpliceOutPort
        : public InPortConsumer
    {
    public:
        typedef coil::Mutex Mutex;
        typedef coil::Guard<coil::Mutex> Guard;
        DATAPORTSTATUS_ENUM
        /*!
         * @if jp
         * @brief コンストラクタ
         *
         * コンストラクタ
         *
         * @param buffer 当該コンシューマに割り当てるバッファオブジェクト
         *
         * @else
         * @brief Constructor
         *
         * Constructor
         *
         * @param buffer The buffer object that is attached to this Consumer
         *
         * @endif
         */
        OpenSpliceOutPort(void);

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
        virtual ~OpenSpliceOutPort(void);

        /*!
         * @if jp
         * @brief 設定初期化
         *
         * InPortConsumerの各種設定を行う。実装クラスでは、与えられた
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
         * @brief 接続先へのデータ送信
         *
         * 接続先のポートへデータを送信するための純粋仮想関数。
         *
         * この関数は、以下のリターンコードを返す。
         *
         * - PORT_OK:       正常終了。
         * - PORT_ERROR:    データ送信の過程で何らかのエラーが発生した。
         * - SEND_FULL:     データを送信したが、相手側バッファがフルだった。
         * - SEND_TIMEOUT:  データを送信したが、相手側バッファがタイムアウトした。
         * - UNKNOWN_ERROR: 原因不明のエラー
         *
         * @param data 送信するデータ
         * @return リターンコード
         *
         * @else
         * @brief Send data to the destination port
         *
         * Pure virtual function to send data to the destination port.
         *
         * This function might the following return codes
         *
         * - PORT_OK:       Normal return
         * - PORT_ERROR:    Error occurred in data transfer process
         * - SEND_FULL:     Buffer full although OutPort tried to send data
         * - SEND_TIMEOUT:  Timeout although OutPort tried to send data
         * - UNKNOWN_ERROR: Unknown error
         *
         * @endif
         */
        virtual ReturnCode put(ByteData& data);

        /*!
         * @if jp
         * @brief InterfaceProfile情報を公開する
         *
         * InterfaceProfile情報を公開する。
         * 引数で指定するプロパティ情報内の NameValue オブジェクトの
         * dataport.interface_type 値を調べ、当該ポートに設定されている
         * インターフェースタイプと一致する場合のみ情報を取得する。
         *
         * @param properties InterfaceProfile情報を受け取るプロパティ
         *
         * @else
         * @brief Publish InterfaceProfile information
         *
         * Publish interfaceProfile information.
         * Check the dataport.interface_type value of the NameValue object
         * specified by an argument in property information and get information
         * only when the interface type of the specified port is matched.
         *
         * @param properties Properties to get InterfaceProfile information
         *
         * @endif
         */
        virtual void publishInterfaceProfile(SDOPackage::NVList& properties);

        /*!
         * @if jp
         * @brief データ送信通知への登録
         *
         * 指定されたプロパティに基づいて、データ送出通知の受け取りに登録する。
         *
         * @param properties 登録情報
         *
         * @return 登録処理結果(登録成功:true、登録失敗:false)
         *
         * @else
         * @brief Subscribe to the data sending notification
         *
         * Subscribe to the data sending notification based on specified
         * property information.
         *
         * @param properties Information for subscription
         *
         * @return Subscription result (Successful:true, Failed:false)
         *
         * @endif
         */
        virtual bool subscribeInterface(const SDOPackage::NVList& properties);

        /*!
         * @if jp
         * @brief データ送信通知からの登録解除
         *
         * データ送出通知の受け取りから登録を解除する。
         *
         * @param properties 登録解除情報
         *
         * @else
         * @brief Unsubscribe the data send notification
         *
         * Unsubscribe the data send notification.
         *
         * @param properties Information for unsubscription
         *
         * @endif
         */
        virtual void unsubscribeInterface(const SDOPackage::NVList& properties);



    private:
        mutable Logger rtclog;
        coil::Properties m_properties;
        Mutex m_mutex;
        OpenSpliceOutPortBase* m_outport;

        
    };

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @param buffer The buffer object that is attached to this Consumer
   * @endif
   */
  OpenSpliceOutPort::OpenSpliceOutPort(void)
    : rtclog("OpenSpliceOutPort"), m_outport(nullptr)
  {
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  OpenSpliceOutPort::~OpenSpliceOutPort(void)
  {
    RTC_PARANOID(("~OpenSpliceOutPort()"));
    
  }

  /*!
   * @if jp
   * @brief 設定初期化
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void OpenSpliceOutPort::init(coil::Properties& prop)
  { 
    RTC_PARANOID(("ROSOutPort::init()"));
    
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

    m_outport = createOpenSpliceOutPort(dataType, idlPath, topic, endian, corbamode);

    if(m_outport == nullptr)
    {
        RTC_ERROR(("Failed initialize writer"));
    }
  }

  /*!
   * @if jp
   * @brief バッファへのデータ書込
   * @else
   * @brief Write data into the buffer
   * @endif
   */
  InPortConsumer::ReturnCode OpenSpliceOutPort::put(ByteData& data)
  {
    
    RTC_PARANOID(("put()"));
    RTC_VERBOSE(("Data size:%d", data.getDataLength()));

    if (m_outport == nullptr)
    {
        RTC_ERROR(("Failed write data"));
    }
    if (m_outport->write(data))
    {
        return PORT_OK;
    }
    else
    {
        return PORT_ERROR;
    }

    
    
  }

  /*!
   * @if jp
   * @brief InterfaceProfile情報を公開する
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void OpenSpliceOutPort::
  publishInterfaceProfile(SDOPackage::NVList& /*properties*/)
  {
    return;
  }

  /*!
   * @if jp
   * @brief データ送信通知への登録
   * @else
   * @brief Subscribe to the data sending notification
   * @endif
   */
  bool OpenSpliceOutPort::
  subscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    
    
    return true;
  }
  
  /*!
   * @if jp
   * @brief データ送信通知からの登録解除
   * @else
   * @brief Unsubscribe the data send notification
   * @endif
   */
  void OpenSpliceOutPort::
  unsubscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("unsubscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    
  }
  
} // namespace RTC


void OpenSpliceOutPortInit()
{
    RTC::InPortConsumerFactory& factory(RTC::InPortConsumerFactory::instance());
    factory.addFactory("opensplice",
        ::coil::Creator< ::RTC::InPortConsumer,
        ::RTC::OpenSpliceOutPort>,
        ::coil::Destructor< ::RTC::InPortConsumer,
        ::RTC::OpenSpliceOutPort>);
}