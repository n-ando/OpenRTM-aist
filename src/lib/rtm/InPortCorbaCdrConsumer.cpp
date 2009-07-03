// -*- C++ -*-
/*!
 * @file  InPortCorbaConsumer.h
 * @brief InPortCorbaConsumer class
 * @date  $Date: 2007-12-31 03:08:03 $
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
 * $Id: InPortCorbaConsumer.h 1255 2009-04-07 01:09:47Z kurihara $
 *
 */

#include <rtm/NVUtil.h>
#include <rtm/InPortCorbaCdrConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @param buffer The buffer object that is attached to this Consumer
   * @endif
   */
  InPortCorbaCdrConsumer::InPortCorbaCdrConsumer(void)
    : rtclog("InPortCorbaCdrConsumer")
  {
    rtclog.setLevel("PARANOID");
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  InPortCorbaCdrConsumer::~InPortCorbaCdrConsumer(void)
  {
    RTC_PARANOID(("~InPortCorbaCdrConsumer()"));
  }

  /*!
   * @if jp
   * @brief 設定初期化
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void InPortCorbaCdrConsumer::init(coil::Properties& prop)
  {
    m_properties = prop;
  }

  /*!
   * @if jp
   * @brief バッファへのデータ書込
   * @else
   * @brief Write data into the buffer
   * @endif
   */
  InPortConsumer::ReturnCode InPortCorbaCdrConsumer::
  put(const cdrMemoryStream& data)
  {
    RTC_PARANOID(("put()"));

    ::OpenRTM::CdrData tmp(data.bufSize(), data.bufSize(),
                           static_cast<CORBA::Octet*>(data.bufPtr()), 0);
    try
      {
        return (ReturnCode)_ptr()->put(tmp);
      }
    catch (...)
      {
        return CONNECTION_LOST;
      }
    return UNKNOWN_ERROR;
  }
  
  /*!
   * @if jp
   * @brief InterfaceProfile情報を公開する
   * @else
   * @brief Publish InterfaceProfile information
   * @endif
   */
  void InPortCorbaCdrConsumer::
  publishInterfaceProfile(SDOPackage::NVList& properties)
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
  bool InPortCorbaCdrConsumer::
  subscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    
    // getting InPort's ref from IOR string
    if (subscribeFromIor(properties)) { return true; }
    
    // getting InPort's ref from Object reference
    if (subscribeFromRef(properties)) { return true; }
    
    return false;;
  }
  
  /*!
   * @if jp
   * @brief データ送信通知からの登録解除
   * @else
   * @brief Unsubscribe the data send notification
   * @endif
   */
  void InPortCorbaCdrConsumer::
  unsubscribeInterface(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("unsubscribeInterface()"));
    RTC_DEBUG_STR((NVUtil::toString(properties)));
    
    if (unsubscribeFromIor(properties)) { return; }
    unsubscribeFromRef(properties);
  }
  
  //----------------------------------------------------------------------
  // private functions

  /*!
   * @if jp
   * @brief IOR文字列からオブジェクト参照を取得する
   * @else
   * @brief Getting object reference fromn IOR string
   * @endif
   */
  bool InPortCorbaCdrConsumer::
  subscribeFromIor(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeFromIor()"));
    
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.inport_ior");
    if (index < 0)
      {
        RTC_ERROR(("inport_ior not found"));
        return false;
      }
    
    const char* ior(0);
    if (!(properties[index].value >>= ior))
      {
        RTC_ERROR(("inport_ior has no string"));
        return false;
      }
    
    CORBA::ORB_ptr orb = RTC::Manager::instance().getORB();
    CORBA::Object_var obj = orb->string_to_object(ior);
    
    if (CORBA::is_nil(obj))
      {
        RTC_ERROR(("invalid IOR string has been passed"));
        return false;
      }
    
    if (!setObject(obj.in()))
      {
        RTC_WARN(("Setting object to consumer failed."));
        return false;
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief Anyから直接オブジェクト参照を取得する
   * @else
   * @brief Getting object reference fromn Any directry
   * @endif
   */
  bool InPortCorbaCdrConsumer::
  subscribeFromRef(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("subscribeFromRef()"));
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.inport_ref");
    if (index < 0)
      {
        RTC_ERROR(("inport_ref not found"));
        return false;
      }
    
    CORBA::Object_var obj;
    if (!(properties[index].value >>= CORBA::Any::to_object(obj.out())))
      {
        RTC_ERROR(("prop[inport_ref] is not objref"));
        return true;
      }
    
    if (CORBA::is_nil(obj))
      {
        RTC_ERROR(("prop[inport_ref] is not objref"));
        return false;
      }
    
    if (!setObject(obj.in()))
      {
        RTC_ERROR(("Setting object to consumer failed."));
        return false;
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief 接続解除(IOR版)
   * @else
   * @brief ubsubscribing (IOR version)
   * @endif
   */
  bool InPortCorbaCdrConsumer::
  unsubscribeFromIor(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("unsubscribeFromIor()"));
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.inport_ior");
    if (index < 0)
      {
        RTC_ERROR(("inport_ior not found"));
        return false;
      }
    
    const char* ior;
    if (!(properties[index].value >>= ior))
      {
        RTC_ERROR(("prop[inport_ior] is not string"));
        return false;
      }
    
    CORBA::ORB_ptr orb = RTC::Manager::instance().getORB();
    CORBA::Object_var var = orb->string_to_object(ior);
    if (!(_ptr()->_is_equivalent(var)))
      {
        RTC_ERROR(("connector property inconsistency"));
        return false;
      }
    
    releaseObject();
    return true;
  }
  
  /*!
   * @if jp
   * @brief 接続解除(Object reference版)
   * @else
   * @brief ubsubscribing (Object reference version)
   * @endif
   */
  bool InPortCorbaCdrConsumer::
  unsubscribeFromRef(const SDOPackage::NVList& properties)
  {
    RTC_TRACE(("unsubscribeFromRef()"));
    CORBA::Long index;
    index = NVUtil::find_index(properties,
                               "dataport.corba_cdr.inport_ref");
    if (index < 0) { return false; }
    
    CORBA::Object_var obj;
    if (!(properties[index].value >>= CORBA::Any::to_object(obj.out()))) 
      {
        return false;
      }
    
    if (!(_ptr()->_is_equivalent(obj.in()))) { return false; }
    
    releaseObject();
    return true;
  }
  
};     // namespace RTC

extern "C"
{
  void InPortCorbaCdrConsumerInit(void)
  {
    RTC::InPortConsumerFactory& factory(RTC::InPortConsumerFactory::instance());
    factory.addFactory("corba_cdr",
                       ::coil::Creator< ::RTC::InPortConsumer,
                                        ::RTC::InPortCorbaCdrConsumer>,
                       ::coil::Destructor< ::RTC::InPortConsumer,
                                           ::RTC::InPortCorbaCdrConsumer>);
  }
};
