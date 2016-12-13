// -*- C++ -*-
/*!
 * @file  OutPortCorbaProvider.h
 * @brief OutPortCorbaProvider class
 * @date  $Date: 2008-01-14 07:52:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortCorbaProvider.h 1244 2009-03-13 07:25:42Z n-ando $
 *
 */

#ifndef RTC_OUTPORTCORBACDRPROVIDER_H
#define RTC_OUTPORTCORBACDRPROVIDER_H

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/OutPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortCorbaCdrProvider
   * @brief OutPortCorbaCdrProvider クラス
   *
   * 通信手段に CORBA を利用した出力ポートプロバイダーの実装クラス。
   *
   * @param DataType 当該プロバイダに割り当てたバッファが保持するデータ型
   *
   * @since 0.4.0
   *
   * @else
   * @class OutPortCorbaCdrProvider
   * @brief OutPortCorbaCdrProvider class
   *
   * This is an implementation class of OutPort Provider that uses 
   * CORBA for mean of communication.
   *
   * @param DataType Data type held by the buffer that is assigned to this 
   *        provider
   *
   * @since 0.4.0
   *
   * @endif
   */
  class OutPortCorbaCdrProvider
    : public OutPortProvider,
      public virtual ::POA_OpenRTM::OutPortCdr,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param buffer 当該プロバイダに割り当てるバッファオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer Buffer object that is assigned to this provider
     *
     * @endif
     */
    OutPortCorbaCdrProvider(void);

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
    virtual ~OutPortCorbaCdrProvider(void);

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * InPortConsumerの各種設定を行う。実装クラスでは、与えられた
     * Propertiesから必要な情報を取得して各種設定を行う。この init() 関
     * 数は、OutPortProvider生成直後および、接続時にそれぞれ呼ばれる可
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
     * OutPortProviderがデータを取り出すバッファをセットする。
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
    virtual void setBuffer(BufferBase<cdrMemoryStream>* buffer);
    
    /*!
     * @if jp
     * @brief [CORBA interface] バッファからデータを取得する
     *
     * 設定された内部バッファからデータを取得する。
     *
     * @return 取得データ
     *
     * @else
     * @brief [CORBA interface] Get data from the buffer
     *
     * Get data from the internal buffer.
     *
     * @return Data got from the buffer.
     *
     * @endif
     */
    virtual ::OpenRTM::PortStatus get(::OpenRTM::CdrData_out data);

    
  private:
    BufferBase<cdrMemoryStream>* m_buffer;
    ::OpenRTM::OutPortCdr_var m_objref;
  };  // class OutPortCorbaCdrProvider
};     // namespace RTC

extern "C"
{
  void OutPortCorbaCdrProviderInit(void);
};

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

#endif // RTC_OUTPORTCORBACDRPROVIDER_H
