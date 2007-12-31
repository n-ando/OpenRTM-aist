// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DataInPort.h,v 1.6.4.2 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6.4.1  2007/10/06 12:23:26  n-ando
 * TCP socket data port was added.
 *
 * Revision 1.6  2007/01/21 17:16:58  n-ando
 * Invalid kanji code was deleted.
 *
 * Revision 1.5  2007/01/21 09:43:22  n-ando
 * - A bug about memory access violation to m_providers still exists.
 *   This bug arises on Fedora5/gcc4 environment.
 *   To escape the bug temporarily dummy variable (m_dummy) is defined.
 * - Some functors were moved to cpp file.
 *
 * Revision 1.4  2007/01/14 22:57:48  n-ando
 * A bug fix about template argument for buffer-type in constructor.
 *
 * Revision 1.3  2007/01/12 14:29:48  n-ando
 * A trivial bug fix.
 *
 * Revision 1.2  2007/01/06 17:43:39  n-ando
 * The behavior on notify_connect() and notify_disconnect() are now
 * implemented in protected functions(ex. publisherInterfaces()).
 *
 * Revision 1.1  2006/12/02 18:27:49  n-ando
 * The first commitment.
 *
 *
 */

#ifndef DataInPort_h
#define DataInPort_h

#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/OutPortCorbaConsumer.h>
#include <rtm/InPortTcpSockProvider.h>
#include <rtm/NVUtil.h>
#include <rtm/InPort.h>
#include <stdio.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント
 *
 * @else
 *
 * @namespace RTC
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   * @class DataInPort
   * @brief InPort 用 Port
   *
   * データ入力ポートの実装クラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class DataInPort
   * @brief InPort abstruct class
   * @endif
   */
  class DataInPort
    : public virtual PortBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param name ポート名称
     * @param inport 当該データ入力ポートに関連付けるInPortオブジェクト
     *               InPortオブジェクトで扱うデータ型、バッファタイプも指定する
     * @param prop ポート設定用プロパティ
     *
     * @else
     * @brief Constructor
     * @endif
     */
    template <class DataType, template <class DataType> class Buffer>
    DataInPort(const char* name, InPort<DataType, Buffer>& inport,
	       Properties& prop)
      : PortBase(name)
    {
      // PortProfile::properties を設定
      addProperty("port.port_type", "DataInPort");
      
      // CORBA InPort Provider
      m_providers.push_back(new InPortCorbaProvider<DataType>(inport));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      
      // TCP Socket InPort Provider
      m_providers.push_back(new InPortTcpSockProvider<DataType>(inport, prop));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      
      // CORBA OutPort Consumer
      m_consumers.push_back(new OutPortCorbaConsumer<DataType>(inport));
      
      // dummy var
      m_dummy.push_back(1);
    }
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~DataInPort();
    
  protected:
    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する。
     * このPortが所有しているプロバイダ(Provider)に関する情報を、
     * ConnectorProfile#propertiesに代入します。
     *
     * @param connector_profile コネクタプロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interfaceに接続する
     *
     * Interfaceに接続する。
     * Portが所有するConsumerに適合するProviderに関する情報を 
     * ConnectorProfile#properties から抽出し、
     * ConsumerにCORBAオブジェクト参照を設定する。
     *
     * @param connector_profile コネクタ・プロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interfaceへの接続を解除する
     *
     * Interfaceへの接続を解除する。
     * 与えられたConnectorProfileに関連するConsumerに設定された全てのObjectを
     * 解放し接続を解除する。
     *
     * @param connector_profile コネクタ・プロファイル
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interface公開用Functor
     *
     * Interface公開処理を実行するためのFunctor。
     *
     * @else
     *
     * @endif
     */
    struct publish;
    
    /*!
     * @if jp
     * @brief Interface接続用Functor
     *
     * Interface接続処理を実行するためのFunctor。
     *
     * @else
     *
     * @endif
     */
    struct subscribe;
    
    /*!
     * @if jp
     * @brief Interface接続解除用Functor
     *
     * Interface接続解除処理を実行するためのFunctor。
     *
     * @else
     *
     * @endif
     */
    struct unsubscribe;
    
  private:
    /*
     * Bug
     *
     * Fedora5/gcc4.1.1. にて DataInPort の先頭領域のメモリ破壊が
     * 起こっている模様。
     * (gdbでかなり粘って追ってみたが断念)
     * もともともは std::vector<InPortProvider*> m_providers が先頭
     * このままだと、
     * $vec->_M_impl._M_start:  begin() に相当？
     * $vec->_M_impl._M_finish: end() に相当？
     * においてい _M_start が不可解な位置を指すため、
     * m_providers に対して for_each を適用するとSegvで落ちる。
     *
     * FreeBSD6.0/gcc3.4.4ではこの現象は発生せず。
     */
    std::vector<int> m_dummy;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
  };
}; // namespace RTC

#endif // DataInPort_h
