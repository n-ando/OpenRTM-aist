// -*- C++ -*-
/*!
 * @file  OutPortCorbaCdrProvider.cpp
 * @brief OutPortCorbaCdrProvider class
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
 * $Id: OutPortCorbaCdrProvider.cpp 1244 2009-03-13 07:25:42Z n-ando $
 *
 */

#include <rtm/OutPortCorbaCdrProvider.h>

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  OutPortCorbaCdrProvider::OutPortCorbaCdrProvider(void)
   : m_buffer(0) 
  {
    // PortProfile setting
    setInterfaceType("corba_cdr");
    
    // ConnectorProfile setting
    m_objref = this->_this();
    
    // set outPort's reference
    CORBA::ORB_ptr orb = ::RTC::Manager::instance().getORB();
    CORBA::String_var ior = orb->object_to_string(m_objref.in());
    CORBA_SeqUtil::
      push_back(m_properties,
                NVUtil::newNV("dataport.corba_cdr.outport_ior", ior));
    CORBA_SeqUtil::
      push_back(m_properties,
                NVUtil::newNV("dataport.corba_cdr.outport_ref", m_objref));
  }
  
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
  OutPortCorbaCdrProvider::~OutPortCorbaCdrProvider(void)
  {
  }
  
  /*!
   * @if jp
   * @brief 設定初期化
   * @else
   * @brief Initializing configuration
   * @endif
   */
  void OutPortCorbaCdrProvider::init(coil::Properties& prop)
  {
  }

  /*!
   * @if jp
   * @brief バッファをセットする
   * @else
   * @brief Setting outside buffer's pointer
   * @endif
   */
  void OutPortCorbaCdrProvider::setBuffer(BufferBase<cdrMemoryStream>* buffer)
  {
    m_buffer = buffer;
  }

  /*!
   * @if jp
   * @brief コネクタをセットする
   * @else
   * @brief Setting outside connector's pointer
   * @endif
   */
  void OutPortCorbaCdrProvider::setConnector(OutPortConnector* connector)
  {
    m_connector = connector;
  }

  /*!
   * @if jp
   * @brief [CORBA interface] バッファからデータを取得する
   * @else
   * @brief [CORBA interface] Get data from the buffer
   * @endif
   */
  ::OpenRTM::PortStatus
  OutPortCorbaCdrProvider::get(::OpenRTM::CdrData_out data)
  {
    RTC_PARANOID(("get()"));

    data = new ::OpenRTM::CdrData();
    if (m_buffer == 0)
      {
        return ::OpenRTM::UNKNOWN_ERROR;
      }

    if (m_buffer->empty())
      {
        return ::OpenRTM::BUFFER_EMPTY;
      }

    cdrMemoryStream cdr;

    BufferBase<cdrMemoryStream>::ReturnCode ret(m_buffer->read(cdr));
    if (ret == 0)
      {
        int len(cdr.bufSize());
        RTC_PARANOID(("converted CDR data size: %d",len));
        // set endian type
        bool endian_type = m_connector->isLittleEndian();
        RTC_TRACE(("connector endian: %s", endian_type ? "little":"big"));
        cdr.setByteSwapFlag(endian_type);
        data->length(len);
        cdr.get_octet_array(&((*data)[0]), len);
        return ::OpenRTM::PortStatus(ret);
      }
    return ::OpenRTM::PortStatus(ret);
  }

};     // namespace RTC

extern "C"
{
  void OutPortCorbaCdrProviderInit(void)
  {
    RTC::OutPortProviderFactory& factory(RTC::OutPortProviderFactory::instance());
    factory.addFactory("corba_cdr",
                       ::coil::Creator< ::RTC::OutPortProvider,
                                        ::RTC::OutPortCorbaCdrProvider>,
                       ::coil::Destructor< ::RTC::OutPortProvider,
                                           ::RTC::OutPortCorbaCdrProvider>);
  }
};
