// -*- C++ -*-
/*!
 * @file InPortBase.cpp
 * @brief Base class of InPort
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <iostream>
#include <algorithm>

#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/InPortBase.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/OutPortConsumer.h>
#include <rtm/InPortPushConnector.h>
#include <rtm/InPortPullConnector.h>

namespace RTC
{

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  InPortBase::InPortBase(const char* name, const char* data_type)
    : PortBase(name), m_singlebuffer(true), m_thebuffer(0)
  {
    // PortProfile::properties を設定
    addProperty("port.port_type", "DataInPort");
    addProperty("dataport.data_type", data_type);
    addProperty("dataport.subscription_type", "Any");
  }

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  InPortBase::~InPortBase()
  {
  }

  void InPortBase::init()
  {
    if (m_singlebuffer)
      {
        m_thebuffer = CdrBufferFactory::instance().createObject("ring_buffer");
        if (m_thebuffer == 0)
          {
            std::cout << "default buffer creation failed" << std::endl;
          }
      }
    initProviders();
    initConsumers();
  }

  coil::Properties& InPortBase::properties()
  {
    return m_properties;
  }

  /*!
   * @if jp
   * @brief InPortを activates する
   * @else
   * @brief Activate all Port interfaces
   * @endif
   */
  void InPortBase::activateInterfaces()
  {
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        m_connectors[i]->activate();
      }
  }

  /*!
   * @if jp
   * @brief 全ての Port のインターフェースを deactivates する
   * @else
   * @brief Deactivate all Port interfaces
   * @endif
   */
  void InPortBase::deactivateInterfaces()
  {
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        m_connectors[i]->deactivate();
      }
  }

  //============================================================
  // protected interfaces
  //============================================================
  
  /*!
   * @if jp
   * @brief Interface情報を公開する
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t InPortBase::publishInterfaces(ConnectorProfile& cprof)
  {    
    RTC_TRACE(("publishInterfaces()"));

    coil::Properties conn_prop;
    NVUtil::copyToProperties(conn_prop, cprof.properties);

   // prop: [port.outport].
    coil::Properties prop(m_properties);
    prop << conn_prop.getNode("dataport"); // marge ConnectorProfile

    // getting dataflow type
    std::string& dflow_type(conn_prop["dataport.dataflow_type"]);
    std::string& iface_type(conn_prop["dataport.interface_type"]);

    coil::normalize(dflow_type);
    coil::normalize(iface_type);

    RTC_PARANOID(("dataflow_type: %s", dflow_type.c_str()));
    RTC_PARANOID(("interface_type: %s", iface_type.c_str()));

    if (dflow_type == "push")
      {
        RTC_PARANOID(("dataflow_type = pull .... create PushConnector"));

        InPortProvider* provider(createProvider(iface_type));
        if (provider == 0)
          {
            RTC_ERROR(("provider creation failed"));
            return RTC::BAD_PARAMETER;
          }
        RTC_ERROR(("provider created"));
        provider->init(prop.getNode("provider"));

        if (!provider->publishInterface(cprof.properties))
          {
            RTC_ERROR(("publishing interface information error"));
            deleteProvider(provider);
            return RTC::BAD_PARAMETER;
          }

        InPortConnector* connector;
        ConnectorBase::Profile profile(cprof.name,
                                       cprof.connector_id,
                                       CORBA_SeqUtil::refToVstring(cprof.ports),
                                       prop);
        try
          {
            if (m_singlebuffer)
              {
                connector = new InPortPushConnector(profile, provider,
                                                    m_thebuffer);
              }
            else
              {
                connector = new InPortPushConnector(profile, provider);
              }
            RTC_TRACE(("InPortPushConnector created"));

            m_connectors.push_back(connector);

            RTC_PARANOID(("current connectors: %d", m_connectors.size()));
            return RTC::RTC_OK;
          }
        catch (std::bad_alloc& e)
          {
            RTC_ERROR(("InPortPushConnector creation failed"));
            return RTC::RTC_ERROR;
          }
      }
    else if (dflow_type == "pull")
      {
        RTC_PARANOID(("dataflow_type = pull .... do nothing"));
        return RTC::RTC_OK;
      }

    RTC_ERROR(("unsupported dataflow_type"));
    return RTC::BAD_PARAMETER;
  }
  
  /*!
   * @if jp
   * @brief Interfaceに接続する
   * @else
   * @brief Subscribe to the interface
   * @endif
   */
  ReturnCode_t
  InPortBase::subscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("InPortBase::subscribeInterfaces()"));
    std::for_each(m_consumers.begin(), m_consumers.end(),
		  OutPortConsumer::subscribe(connector_profile.properties));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief Interfaceへの接続を解除する
   * @else
   * @brief Disconnect the interface connection
   * @endif
   */
  void
  InPortBase::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("InPortBase::unsubscribeInterfaces()"));
    std::for_each(m_consumers.begin(), m_consumers.end(),
		  OutPortConsumer::unsubscribe(connector_profile.properties));
  }

  /*!
   * @if jp
   * @brief InPort provider の初期化
   * @else
   * @brief InPort provider initialization
   * @endif
   */
  void InPortBase::initProviders()
  {
    // create InPort providers
    InPortProviderFactory& factory(InPortProviderFactory::instance());
    coil::vstring provider_types(factory.getIdentifiers());
    std::cout << "InPort providers: " << coil::flatten(provider_types) << std::endl;

    // InPortProvider supports "push" dataflow type
    if (provider_types.size() > 0)
      {
        appendProperty("dataport.dataflow_type", "push");
      }

#ifndef RTC_NO_DATAPORTIF_ACTIVATION_OPTION
    if (m_properties.hasKey("provider_types"))
      {
        coil::vstring temp_types(provider_types);
        provider_types.clear();
        coil::vstring
          active_types(coil::split(m_properties["provider_types"], ","));

        std::set_intersection(temp_types.begin(), temp_types.end(),
                              active_types.begin(), active_types.end(),
                              std::back_inserter(provider_types));
      }
#endif
    
    m_providers.reserve(provider_types.size());
    for (int i(0), len(provider_types.size()); i < len; ++i)
      {
        InPortProvider* provider = factory.createObject(provider_types[i]);
        if (provider != 0)
          {
            provider->publishInterfaceProfile(m_profile.properties);
            m_providers.push_back(provider);
          }
      }
  }

  /*!
   * @if jp
   * @brief OutPort consumer の初期化
   * @else
   * @brief OutPort consumer initialization
   * @endif
   */
  void InPortBase::initConsumers()
  {
    // create OuPort consumers
    OutPortConsumerFactory& factory(OutPortConsumerFactory::instance());
    coil::vstring consumer_types(factory.getIdentifiers());
    std::cout << "InPort consumers: " << coil::flatten(consumer_types) << std::endl;
    
    // OutPortConsumer supports "pull" dataflow type
    if (consumer_types.size() > 0)
      {
        appendProperty("dataport.dataflow_type", "pull");
      }

#ifndef RTC_NO_DATAPORTIF_ACTIVATION_OPTION
    if (m_properties.hasKey("consumer_types"))
      {
        coil::vstring temp_types(consumer_types);
        consumer_types.clear();
        coil::vstring
          active_types(coil::split(m_properties["consumer_types"], ","));

        std::set_intersection(temp_types.begin(), temp_types.end(),
                              active_types.begin(), active_types.end(),
                              std::back_inserter(consumer_types));
      }
#endif
    
    m_consumerTypes = consumer_types;

    m_consumers.reserve(consumer_types.size());
    for (int i(0), len(consumer_types.size()); i < len; ++i)
      {
        OutPortConsumer* consumer = factory.createObject(consumer_types[i]);
        if (consumer != 0)
          {
            //            consumer->publishInterfaceProfile(m_profile.properties);
            m_consumers.push_back(consumer);
          }
      }
  }

  /*!
   * @if jp
   * @brief InPort provider の生成
   * @else
   * @brief InPort provider creation
   * @endif
   */
  InPortProvider* InPortBase::createProvider(const std::string& iface_type)
  {
    const std::string& iface_types(m_properties["interface.types"]);

    if (!iface_types.empty() && !coil::includes(iface_types, iface_type))
      {
        return 0;
      }

    return InPortProviderFactory::instance().createObject(iface_type);
  }
  
  /*!
   * @if jp
   * @brief InPort provider の削除
   * @else
   * @brief InPort provider deletion
   * @endif
   */
  void InPortBase::deleteProvider(InPortProvider* provider)
  {
    InPortProviderFactory::instance().deleteObject(provider);
  }
  
};
