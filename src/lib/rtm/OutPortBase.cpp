/*! -*- C++ -*-
 *
 * @file OutPortBase.cpp
 * @brief Output porty base class
 * @date $Date: 2007-12-31 03:08:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
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
#include <functional>
#include <coil/stringutil.h>

#include <rtm/ConnectorBase.h>
#include <rtm/OutPortPushConnector.h>
#include <rtm/OutPortPullConnector.h>
#include <rtm/OutPortBase.h>
#include <rtm/PublisherBase.h>


namespace RTC
{
  /*!
   * @if jp
   * @brief Provider を削除するための Functor
   * @else
   * @brief Functor to delete Providers
   * @endif
   */
  struct OutPortBase::provider_cleanup
  {
    provider_cleanup()
      : m_factory(OutPortProviderFactory::instance())
    {
    }
    void operator()(OutPortProvider* p)
    {
      m_factory.deleteObject(p);
    }
    OutPortProviderFactory& m_factory;
  };

  /*!
   * @if jp
   * @brief Connector を削除するための Functor
   * @else
   * @brief Functor to delete Connectors
   * @endif
   */
  struct OutPortBase::connector_cleanup
  {
    connector_cleanup()
    {
    }
    void operator()(OutPortConnector* c)
    {
      delete c;
    }
  };


  /*!------------------------------------------------------------
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  OutPortBase::OutPortBase(const char* name, const char* data_type)
    : PortBase(name), m_name(name)
  {
    rtclog.setLevel("PARANOID");

    RTC_PARANOID(("Port name: %s", name));

    RTC_PARANOID(("setting port.port_type: DataOutPort"));
    addProperty("port.port_type", "DataOutPort");

    RTC_PARANOID(("setting dataport.data_type: %s", data_type));
    addProperty("dataport.data_type", data_type);

    // publisher list
    PublisherFactory& factory(PublisherFactory::instance());
    std::string pubs = coil::flatten(factory.getIdentifiers());

    // blank characters are deleted for RTSE's bug
    coil::eraseBlank(pubs);
    RTC_PARANOID(("available subscription_type: %s",  pubs.c_str()));
    addProperty("dataport.subscription_type", pubs.c_str());

    initConsumers();
    initProviders();
  };
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  OutPortBase::~OutPortBase(void)
  {
    RTC_TRACE(("~OutPortBase()"));
    // provider のクリーンナップ
    std::for_each(m_providers.begin(),
                  m_providers.end(),
                  provider_cleanup());
    // connector のクリーンナップ
    std::for_each(m_connectors.begin(),
                  m_connectors.end(),
                  connector_cleanup());
  }
             
  /*!
   * @if jp
   * @brief プロパティの初期化
   * @else
   * @brief Initializing properties
   * @endif
   */
  void OutPortBase::init(coil::Properties& prop)
  {
    RTC_TRACE(("init()"));

    RTC_PARANOID(("given properties:"));
    rtclog.level(Logger::RTL_PARANOID) << prop;
    m_properties << prop;

    RTC_PARANOID(("updated properties:"));
    rtclog.level(Logger::RTL_PARANOID) << m_properties;

    configure();

  }

  /*!
   * @if jp
   * @brief OutPort名称の取得
   * @else
   * @brief Retrieve OutPort name
   * @endif
   */
  const char* OutPortBase::name() const
  {
    RTC_TRACE(("name() = %s", m_name.c_str()));
    return m_name.c_str();
  }

  /*!
   * @if jp
   * @brief プロパティを取得する
   * @else
   * @brief Get properties
   * @endif
   */
  coil::Properties& OutPortBase::properties()
  {
    RTC_TRACE(("properties()"));
    return m_properties;
  }

  /*!
   * @if jp
   * @brief Connector を取得
   * @else
   * @brief Connector list
   * @endif
   */
  const std::vector<OutPortConnector*>& OutPortBase::connectors()
  {
    RTC_TRACE(("connectors(): size = %d", m_connectors.size()));
    return m_connectors;
  }

  /*!
   * @if jp
   * @brief ConnectorProfile を取得
   * @else
   * @brief ConnectorProfile list
   * @endif
   */
  ConnectorBase::ProfileList OutPortBase::getConnectorProfiles()
  {
    RTC_TRACE(("getConnectorProfiles(): size = %d", m_connectors.size()));
    ConnectorBase::ProfileList profs;
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        profs.push_back(m_connectors[i]->profile());
      }
    return profs;
  }

  /*!
   * @if jp
   * @brief ConnectorId を取得
   * @else
   * @brief ConnectorId list
   * @endif
   */
  coil::vstring OutPortBase::getConnectorIds()
  {
    coil::vstring ids;
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        ids.push_back(m_connectors[i]->id());
      }
    RTC_TRACE(("getConnectorIds(): %s", coil::flatten(ids).c_str()));
    return ids;
  }

  /*!
   * @if jp
   * @brief Connectorの名前を取得
   * @else
   * @brief Connector name list
   * @endif
   */
  coil::vstring OutPortBase::getConnectorNames()
  {
    coil::vstring names;
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        names.push_back(m_connectors[i]->name());
      }
    RTC_TRACE(("getConnectorNames(): %s", coil::flatten(names).c_str()));
    return names;
  }

  /*!
   * @if jp
   * @brief ConnectorProfileをIDで取得
   * @else
   * @brief Getting ConnectorProfile by name
   * @endif
   */
  bool OutPortBase::getConnectorProfileById(const char* id,
                               ConnectorBase::Profile& prof)
  {
    RTC_TRACE(("getConnectorProfileById(id = %s)", id));

    std::string sid(id);
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        if (sid  == m_connectors[i]->id())
          {
            prof = m_connectors[i]->profile();
            return true;
          }
      }
    return false;
  }

  /*!
   * @if jp
   * @brief ConnectorProfileを名前で取得
   * @else
   * @brief Getting ConnectorProfile by name
   * @endif
   */
  bool OutPortBase::getConnectorProfileByName(const char* name,
                                 ConnectorBase::Profile& prof)
  {
    RTC_TRACE(("getConnectorProfileById(id = %s)", name));

    std::string sname(name);
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        if (sname  == m_connectors[i]->name())
          {
            prof = m_connectors[i]->profile();
            return true;
          }
      }
    return false;
  }


  /*!
   * @if jp
   * @brief インターフェースプロファイルを公開する
   * @else
   * @brief Publish interface profile
   * @endif
   */
  bool OutPortBase::publishInterfaceProfiles(SDOPackage::NVList& properties)
  {
    RTC_TRACE(("publishInterfaceProfiles()"));

    std::for_each(m_providers.begin(), m_providers.end(),
                  OutPortProvider::publishInterfaceProfileFunc(properties));
    return true;
  }

  /*!
   * @if jp
   * @brief OutPortを activates する
   * @else
   * @brief Activate all Port interfaces
   * @endif
   */
  void OutPortBase::activateInterfaces()
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
  void OutPortBase::deactivateInterfaces()
  {
    for (int i(0), len(m_connectors.size()); i < len; ++i)
      {
        m_connectors[i]->deactivate();
      }
  }
  

  //======================================================================
  // protected member functions
  //======================================================================
  /*!
   * @if jp
   * @brief OutPortの設定を行う
   * @else
   * @brief Configureing outport
   * @endif
   */
  void OutPortBase::configure()
  {

  }


  /*!
   * @if jp
   * @brief Interface情報を公開する
   * @else
   * @brief Publish interface information
   * @endif
   */
  ReturnCode_t OutPortBase::publishInterfaces(ConnectorProfile& cprof)
  {
    RTC_TRACE(("publishInterfaces()"));

    NVList& nv(cprof.properties);
    std::string val(NVUtil::toString(nv, "dataport.dataflow_type"));

    if (val.empty()) { return RTC::BAD_PARAMETER; }
    coil::eraseBothEndsBlank(val);
    coil::toLower(val);

    RTC_PARANOID(("publish dataflow_type: %s", val.c_str()));

    if (val == "push")
      {
        RTC_PARANOID(("dataflow_type = push .... do nothing here"));

        return RTC::RTC_OK;
      }
    else if (val == "pull")
      {
        RTC_PARANOID(("dataflow_type = pull .... create PullConnector"));

        OutPortProvider::publishInterfaceFunc pubif(nv);
        std::for_each(m_providers.begin(), m_providers.end(), pubif);
        
        if (pubif.provider_ == 0)
          {
            RTC_ERROR(("no interface to be published"));
            return RTC::UNSUPPORTED;
          }

        //        ConnectorBase* connector;
        ConnectorBase::Profile profile(cprof.connector_id,
                                       cprof.name,
                                       CORBA_SeqUtil::refToVstring(cprof.ports),
                                       NVUtil::toProperties(cprof.properties));
                                       
        //        connector = new PullConnector(profile, pubif.provider_);
        //        if (connector == NULL) { return false; }
        //        m_connectors.push_back(connector);

        return RTC::RTC_OK;
      }

    RTC_ERROR(("unsupported dataflow_type"));

    return RTC::BAD_PARAMETER;
  }

  /*!
   * @if jp
   * @brief Interface情報を取得する
   * @else
   * @brief Subscribe interface
   * @endif
   */
  ReturnCode_t OutPortBase::subscribeInterfaces(const ConnectorProfile& cprof)
  {
    RTC_TRACE(("subscribeInterfaces()"));

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
        RTC_PARANOID(("dataflow_type = push .... create PushConnector"));

        // interface
        InPortConsumer* consumer(createConsumer(iface_type));
        if (consumer == 0)
          {
            RTC_ERROR(("consumer creation failed"));
            return RTC::BAD_PARAMETER;
          }
        consumer->init(prop.getNode("consumer"));
        if (!consumer->subscribeInterface(cprof.properties))
          {
            RTC_ERROR(("no interface to be matched available consumers"));
            delete consumer;
            return RTC::BAD_PARAMETER;
          }

        // connector creation
        OutPortConnector* connector;
        ConnectorBase::Profile profile(cprof.name,
                                       cprof.connector_id,
                                       CORBA_SeqUtil::refToVstring(cprof.ports),
                                       prop);

        try
          {
            connector = new OutPortPushConnector(profile, consumer);
            RTC_TRACE(("PushConnector created"));

            m_connectors.push_back(connector);

            RTC_PARANOID(("current connectors: %d", m_connectors.size()));
            return RTC::RTC_OK;
          }
        catch (std::bad_alloc& e)
          {
            RTC_ERROR(("PushConnector creation failed"));
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
   * @brief 登録されているInterface情報を解除する
   * @else
   * @brief Unsubscribe interface
   * @endif
   */
  void
  OutPortBase::unsubscribeInterfaces(const ConnectorProfile& connector_profile)
  {
    RTC_TRACE(("unsubscribeInterfaces()"));

    std::string id(connector_profile.connector_id);
    RTC_PARANOID(("connector_id: %s", id.c_str()));

    std::vector<OutPortConnector*>::iterator it, it_end;
    it     = m_connectors.begin();
    it_end = m_connectors.end();

    while (it != it_end)
      {
        if (id == (*it)->id())
          {
            m_connectors.erase(it);
            if (*it == 0) { RTC_FATAL(("hmm.. *it should not be 0")); }

            // Connector's dtor must call disconnect()
            delete *it;
            RTC_TRACE(("delete connector: %s", id.c_str()));
            return;
          }
        ++it;
      }
    RTC_ERROR(("specified connector not found: %s", id.c_str()));
    return;
  }


  /*!
   * @if jp
   * @brief OutPort provider の初期化
   * @else
   * @brief OutPort provider initialization
   * @endif
   */
  void OutPortBase::initProviders()
  {
    // create OutPort providers
    OutPortProviderFactory& factory(OutPortProviderFactory::instance());
    coil::vstring provider_types(factory.getIdentifiers());

    RTC_PARANOID(("available OutPortProviders: %s",
                  coil::flatten(provider_types).c_str()));

    // OutPortProvider supports "pull" dataflow type
    if (provider_types.size() > 0)
      {
        RTC_PARANOID(("dataflow_type pull is supported"));
        appendProperty("dataport.dataflow_type", "pull");
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
        std::cout << "provider: " << i << ", " << provider_types[i] << std::endl;
        OutPortProvider* provider = factory.createObject(provider_types[i]);
        if (provider != 0)
          {
            provider->publishInterfaceProfile(m_profile.properties);
            m_providers.push_back(provider);
            RTC_TRACE(("provider creation succeeded: %s",
                       provider_types[i].c_str()));
          }
        else
          {
            RTC_ERROR(("provider creation failed: %s",
                       provider_types[i].c_str()));
          }
      }
  }

  /*!
   * @if jp
   * @brief InPort consumer の初期化
   * @else
   * @brief InPort consumer initialization
   * @endif
   */
  void OutPortBase::initConsumers()
  {
    // create InPort consumers
    InPortConsumerFactory& factory(InPortConsumerFactory::instance());
    coil::vstring consumer_types(factory.getIdentifiers());

    RTC_PARANOID(("available InPortConsumer: %s",
                  coil::flatten(consumer_types).c_str()));

    // InPortConsumer supports "push" dataflow type
    if (consumer_types.size() > 0)
      {
        RTC_PARANOID(("dataflow_type push is supported"));
        appendProperty("dataport.dataflow_type", "push");
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
        InPortConsumer* consumer = factory.createObject(consumer_types[i]);
        if (consumer != 0)
          {
            RTC_TRACE(("consumer creation succeeded: %s",
                       consumer_types[i].c_str()));
            //            consumer->publishInterfaceProfile(m_profile.properties);
            m_consumers.push_back(consumer);
          }
        else
          {
            RTC_ERROR(("consumer creation failed: %s",
                       consumer_types[i].c_str()));
          }
      }
  }

  /*!
   * @if jp
   * @brief InPort consumer の生成
   * @else
   * @brief InPort consumer creation
   * @endif
   */
  InPortConsumer* OutPortBase::createConsumer(std::string& iface_type)
  {
    const std::string& iface_types(m_properties["interface.types"]);

    if (!iface_types.empty() && !coil::includes(iface_types, iface_type))
      {
        return 0;
      }

    coil::normalize(iface_type);
    return InPortConsumerFactory::instance().createObject(iface_type);
  }

  /*!
   * @if jp
   * @brief Publisher の生成
   * @else
   * @brief Publihser creation
   * @endif
   */
//  PublisherBase* OutPortBase::createPublisher(std::string& pub_type)
//  {
//    const std::string& pub_types(m_properties["publisher.types"]);
//
//    if (!pub_types.empty() && !coil::includes(pub_types, pub_type))
//      {
//        return 0;
//      }
//
//    coil::normalize(pub_type);
//    return PublisherFactory::instance().createObject(pub_type);
//  }

  /*!
   * @if jp
   * @brief Buffer の生成
   * @else
   * @brief Buffer creation
   * @endif
   */
//  CdrBufferBase* OutPortBase::createBuffer(std::string& buf_type)
//  {
//    const std::string& buf_types(m_properties["buffer.types"]);
//
//    if (!buf_types.empty() && !coil::includes(buf_types, buf_type))
//      {
//        return 0;
//      }
//
//    coil::normalize(buf_type);
//    return CdrBufferFactory::instance().createObject(buf_type);
//  }

}; // end of namespace RTM
