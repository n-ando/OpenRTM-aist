// -*- C++ -*-
/*!
 * @file  InPortCorbaCdrProvider.h
 * @brief InPortCorbaCdrProvider class
 * @date  $Date: 2008-01-14 07:49:59 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortCorbaProvider.h 1244 2009-03-13 07:25:42Z n-ando $
 *
 */

#ifndef RTC_INPORTCORBAPROVIDER_H
#define RTC_INPORTCORBAPROVIDER_H

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class InPortCorbaProvider
   * @brief InPortCorbaProvider クラス
   *
   * 通信手段に CORBA を利用した入力ポートプロバイダーの実装クラス。
   *
   * @param DataType 当該プロバイダに割り当てたバッファが保持するデータ型
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortCorbaProvider
   * @brief InPortCorbaProvider class
   *
   * This is an implementation class of the input port Provider 
   * that uses CORBA for means of communication.
   *
   * @param DataType Data type held by the buffer that attached 
   *                 to this provider.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortCorbaCdrProvider
    : public InPortProvider,
      public virtual POA_OpenRTM::InPortCdr,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     * ポートプロパティに以下の項目を設定する。
     *  - インターフェースタイプ : CORBA_Any
     *  - データフロータイプ : Push, Pull
     *  - サブスクリプションタイプ : Any
     *
     * @param buffer 当該プロバイダに割り当てるバッファオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     * Set the following items to port properties
     *  - Interface type : CORBA_Any
     *  - Data flow type : Push, Pull
     *  - Subscription type : Any
     *
     * @param buffer Buffer object that is attached to this provider
     *
     * @endif
     */
    InPortCorbaCdrProvider(void);
    
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
    virtual ~InPortCorbaCdrProvider(void);

    virtual void init(coil::Properties& prop);
    virtual void setBuffer(BufferBase<cdrMemoryStream>* buffer);

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
    virtual ::OpenRTM::PortStatus put(const ::OpenRTM::CdrData& data)
      throw (CORBA::SystemException);
    
  private:
    BufferBase<cdrMemoryStream>* m_buffer;
    ::OpenRTM::InPortCdr_var m_objref;
  };  // class InPortCorbaProvider
};     // namespace RTC

#ifdef WIN32
#pragma warning( default : 4290 )
#endif

extern "C"
{
  void InPortCorbaCdrProviderInit(void);
};

#endif // InPortCorbaProvider_h

