// -*- C++ -*-
/*!
 * @file  InPortSHMProvider.h
 * @brief InPortSHMProvider class
 * @date  $Date: 2017-10-30 07:49:59 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017 Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_INPORTSHMPROVIDER_H
#define RTC_INPORTSHMPROVIDER_H

#include <rtm/SharedMemoryPort.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class InPortSHMProvider
   * @brief InPortSHMProvider クラス
   *
   * InPortProvider 
   *
   * 通信手段に 共有メモリ を利用した入力ポートプロバイダーの実装クラス。
   *
   * @since 1.2.0
   *
   * @else
   * @class InPortSHMProvider
   * @brief InPortSHMProvider class
   *
   * 
   *
   * @since 1.2.0
   *
   * @endif
   */
  class InPortSHMProvider
    : public InPortProvider,
      public virtual SharedMemoryPort
  {
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
    InPortSHMProvider();
    
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
    virtual ~InPortSHMProvider();

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * 
     * 
     * @param prop 設定情報
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * 
     *
     * @endif
     */
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief バッファをセットする
     *
     * 
     *
     * @param buffer OutPortProviderがデータを取り出すバッファへのポインタ
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * 
     *
     * @endif
     */
    virtual void setBuffer(BufferBase<cdrMemoryStream>* buffer);

    /*!
     * @if jp
     * @brief リスナを設定する。
     *
     * 
     *
     * @param info 接続情報
     * @param listeners リスナオブジェクト
     *
     * @else
     * @brief Set the listener. 
     *
     * 
     * 
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
	*
	*
	* @param connector OutPortConnector
	*
	* @else
	* @brief set Connector
	*
	* 
	*
	* @param connector OutPortConnector
	*
	* @endif
	*/
	virtual void setConnector(InPortConnector* connector);

    /*!
     * @if jp
     * @brief [CORBA interface] バッファにデータを書き込む
     *
     * 設定されたバッファにデータを書き込む。
     *
     * @param data 書込対象データ
     *
     * @else
     * @brief [CORBA interface] Write data into the buffer
     *
     * Write data into the specified buffer.
     *
     * @param data The target data for writing
     *
     * @endif
     */
    virtual ::OpenRTM::PortStatus put()
      throw (CORBA::SystemException);
    
  private:

    ::OpenRTM::PortStatus
    convertReturn(BufferStatus::Enum status,
                  const cdrMemoryStream& data);

    
    inline void onBufferWrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    }

    inline void onBufferFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    }

    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    }

    inline void onBufferWriteOverwrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
    }

    inline void onReceived(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVED].notify(m_profile, data);
    }

    inline void onReceiverFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
    }

    inline void onReceiverTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
    }

    inline void onReceiverError(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

  private:
    CdrBufferBase* m_buffer;
	::OpenRTM::PortSharedMemory_var  m_objref;
    ConnectorListeners* m_listeners;
    ConnectorInfo m_profile;
    InPortConnector* m_connector;

  };  // class InPortCorCdrbaProvider
};    // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   *
   * InPortSHMProvider のファクトリを登録する初期化関数。
   *
   * @else
   * @brief Module initialization
   *
   * This initialization function registers InPortSHMProvider's factory.
   *
   * @endif
   */
  void InPortSHMProviderInit();
};

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_INPORTCORBACDRPROVIDER_H

