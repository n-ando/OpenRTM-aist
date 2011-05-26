// -*- C++ -*-
/*!
 * @file SdoServiceAdmin.cpp
 * @brief SDO service administration class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#include <memory>
#include <coil/UUID.h>
#include <coil/Guard.h>
#include <coil/stringutil.h>
#include <rtm/RTObject.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/SdoServiceAdmin.h>
#include <rtm/SdoServiceConsumerBase.h>

namespace RTC
{
  typedef coil::Guard<coil::Mutex> Guard;

  /*!
   * @if jp
   * @brief  ServiceProfile用functor
   * @else
   * @brief  Functor for ServiceProfile
   * @endif
   */
  struct service_id
  {
    service_id(const char* id) : m_id(id) {};
    bool operator()(const SDOPackage::ServiceProfile& s)
    {
      std::string id(s.id);
      return m_id == id;
    }
    const std::string m_id;
  };
  

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  SdoServiceAdmin::SdoServiceAdmin(::RTC::RTObject_impl& rtobj)
    : m_rtobj(rtobj), m_allConsumerAllowed(true),
      rtclog("SdoServiceAdmin")
  {
    RTC_TRACE(("SdoServiceAdmin::SdoServiceAdmin(%s)",
               rtobj.getProperties()["instance_name"].c_str()));

    // getting consumer types from RTC's properties
    ::coil::Properties& prop(m_rtobj.getProperties());
    ::std::string constypes = prop["sdo_service.consumer_types"];
    m_consumerTypes = ::coil::split(constypes, ",", true);
    RTC_DEBUG(("sdo_service.consumer_types: %s",
               coil::flatten(m_consumerTypes).c_str()));

    // If types include '[Aa][Ll][Ll]', all types allowed in this RTC
    for (size_t i(0); i < m_consumerTypes.size(); ++i)
      {
        std::string tmp(m_consumerTypes[i]);
        coil::toLower(tmp);
        if (tmp == "all")
          {
            m_allConsumerAllowed = true;
            RTC_DEBUG(("sdo_service.consumer_types: ALL"));
          }
      }
  }

  /*!
   * @if jp
   * @brief 仮想デストラクタ
   * @else
   * @brief Virtual destractor
   * @endif
   */
  SdoServiceAdmin::~SdoServiceAdmin()
  {
  }
  
  /*!
   * @if jp
   * @brief Service Consumer Factory を登録する
   * @else
   * @brief Add Service Consumer Factory
   * @endif
   */
  bool SdoServiceAdmin::addSdoServiceConsumerFactory()
  {
    return false;
  }

  /*!
   * @if jp
   * @brief Service Consumer Factory を削除する
   * @else
   * @brief Remove Service Consumer Factory
   * @endif
   */
  bool SdoServiceAdmin::removeSdoServiceConsumerFactory()
  {
    return false;
  }
    

  /*!
   * @if jp
   * @brief Service Consumer を追加する
   * @else
   * @brief Add Service Consumer
   * @endif
   */
  bool SdoServiceAdmin::
  addSdoServiceConsumer(const SDOPackage::ServiceProfile& sProfile)
  {
    Guard guard(m_consumer_mutex);
    RTC_TRACE(("addSdoServiceConsumer(IFR = %s)",
               static_cast<const char*>(sProfile.interface_type)));
    
    // Not supported consumer type -> error return
    if (!isAllowedConsumerType(sProfile))  { return false; }
    if (!isExistingConsumerType(sProfile)) { return false; }
    RTC_DEBUG(("Valid SDO service required"));
    if (strncmp(sProfile.id, "", 1) == 0)   
      {
        RTC_WARN(("No id specified. It should be given by clients."));
        return false;
      }
    RTC_DEBUG(("Valid ID specified"));
    { // re-initialization
      std::string id(sProfile.id);
      for (size_t i(0); i < m_consumers.size(); ++i)
        {
          if (id == static_cast<const char*>(m_consumers[i]->getProfile().id))
            {
              RTC_INFO(("Existing consumer is reinitilized."));
              RTC_DEBUG(("Propeteis are: %s",
                         NVUtil::toString(sProfile.properties).c_str()));
              return m_consumers[i]->reinit(sProfile);
            }
        }
    }
    RTC_DEBUG(("SDO service properly initialized."));

    // new pofile
    SdoServiceConsumerFactory& 
      factory(SdoServiceConsumerFactory::instance());
    const char* ctype = static_cast<const char*>(sProfile.interface_type);
    if (ctype == NULL) { return false; }
    SdoServiceConsumerBase* consumer(factory.createObject(ctype));
    if (consumer == NULL) 
      {
        RTC_ERROR(("Hmm... consumer must be created."));
        return false; 
      }
    RTC_DEBUG(("An SDO service consumer created."));

    // initialize
    if (!consumer->init(m_rtobj, sProfile))
      {
        RTC_WARN(("SDO service initialization was failed."));
        RTC_DEBUG(("id:         %s", static_cast<const char*>(sProfile.id)));
        RTC_DEBUG(("IFR:        %s",
                   static_cast<const char*>(sProfile.interface_type)));
        RTC_DEBUG(("properties: %s",
                   NVUtil::toString(sProfile.properties).c_str()));
        factory.deleteObject(consumer);
        RTC_INFO(("SDO consumer was deleted by initialization failure"));
        return false;
      }
    RTC_DEBUG(("An SDO service consumer initialized."));
    RTC_DEBUG(("id:         %s", static_cast<const char*>(sProfile.id)));
    RTC_DEBUG(("IFR:        %s",
               static_cast<const char*>(sProfile.interface_type)));
    RTC_DEBUG(("properties: %s",
               NVUtil::toString(sProfile.properties).c_str()));

    // store consumer
    m_consumers.push_back(consumer);
    
    return true;
  }
    
  /*!
   * @if jp
   * @brief Service Consumer を削除する
   * @else
   * @brief Remove Service Consumer
   * @endif
   */
  bool SdoServiceAdmin::removeSdoServiceConsumer(const char* id)
  {
    Guard guard(m_consumer_mutex);
    if (id == NULL || id[0] == '\0')
      {
        RTC_ERROR(("removeSdoServiceConsumer(): id is invalid."));
        return false;
      }
    RTC_TRACE(("removeSdoServiceConsumer(id = %s)", id));

    std::string strid(id);
    std::vector<SdoServiceConsumerBase*>::iterator it = m_consumers.begin();
    std::vector<SdoServiceConsumerBase*>::iterator it_end = m_consumers.end();
    while (it != it_end)
      {
        if (strid == static_cast<const char*>((*it)->getProfile().id))
          {
            (*it)->finalize();
            SdoServiceConsumerFactory& 
              factory(SdoServiceConsumerFactory::instance());
            factory.deleteObject(*it);
            m_consumers.erase(it);
            RTC_INFO(("SDO service has been deleted: %s", id));
            return true;
          }
        ++it;
      }
    RTC_WARN(("Specified SDO consumer not found: %s", id));
    return false;
  }
    
  //------------------------------------------------------------
  // protected functios
  //------------------------------------------------------------

  /*!
   * @if jp
   * @brief 許可されたサービス型かどうか調べる
   * @else
   * @brief If it is allowed service type
   * @endif
   */
  bool SdoServiceAdmin::
  isAllowedConsumerType(const SDOPackage::ServiceProfile& sProfile)
  {
    if (m_allConsumerAllowed) { return true; }

    for (size_t i(0); i < m_consumerTypes.size(); ++i)
      {
        if (m_consumerTypes[i] == 
            static_cast<const char*>(sProfile.interface_type))
          {
            RTC_DEBUG(("%s is supported SDO service.",
                       static_cast<const char*>(sProfile.interface_type)));
            return true;
          }
      }
    RTC_WARN(("Consumer type is not supported: %s",
              static_cast<const char*>(sProfile.interface_type)));
    return false;
  }

  /*!
   * @if jp
   * @brief 存在するサービス型かどうか調べる
   * @else
   * @brief If it is existing service type
   * @endif
   */
  bool SdoServiceAdmin::
  isExistingConsumerType(const SDOPackage::ServiceProfile& sProfile)
  {
    SdoServiceConsumerFactory& factory(SdoServiceConsumerFactory::instance());
    coil::vstring consumerTypes(factory.getIdentifiers());
    
    for (size_t i(0); i < consumerTypes.size(); ++i)
      {
        if (consumerTypes[i] == 
            static_cast<const char*>(sProfile.interface_type))
          {
            RTC_DEBUG(("%s exists in the SDO service factory.",
                       static_cast<const char*>(sProfile.interface_type)));
            RTC_PARANOID(("Available SDO serices in the factory: %s",
                          coil::flatten(consumerTypes).c_str()));
            return true;
          }
      }
    RTC_WARN(("No available SDO service in the factory: %s",
              static_cast<const char*>(sProfile.interface_type)));
    return false;
  }

  const std::string SdoServiceAdmin::getUUID() const
  {
    coil::UUID_Generator uugen;
    uugen.init();
    std::auto_ptr<coil::UUID> uuid(uugen.generateUUID(2,0x01));
    
    return (const char*) uuid->to_string();
  }


}; // end of namepsace RTC
