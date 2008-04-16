// -*- C++ -*-
/*!
 * @file RtcManager.i
 * @brief swig interface file for RtcManager
 * @date $Date: 2005-05-12 09:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

%module RtcManager

%{
#include "rtm/RtcManager.h"
#include "rtm/RtcBase.h"
#include "rtm/RtcFactory.h"
#include "rtm/RtcFactoryPy.h"
%}

%include "std_vector.i"

%inline %{
  using namespace RTM;
  using namespace std;
%}

%newobject RTM::RtcManager::create_component;
%newobject RTM::RtcManager::createComponent;
%newobject RTM::RtcManager::findComponents;




namespace RTM {
  class RtcManager 
  {
  public:
    RtcManager(int argc, char** argv);
    virtual ~RtcManager();
    virtual RtmRes load(const char* pathname, const char* initfunc);
    virtual RtmRes unload(const char* pathname);
    RTM::RTCBase* create_component(const char* comp_name,
								   const char* cat_name, 
								   char* OutChar);
    virtual RtmRes delete_component(const char* instance_name,
									const char* category_name);
    //	virtual ComponentFactoryList* component_factory_list();
    //	virtual RTComponentList* component_list();
    //	virtual RtmRes command(const char* cmd, CORBA::String_out ret);
    void initManager();
    bool activateManager();
    bool registerComponent(RtcFactoryBase* factory);
    void runManager();
    void runManagerNoBlocking();
    RTM::RtcBase* createComponent(const std::string& InString,
								  const std::string& InString,
								  std::string& OutString);
    std::vector<RTM::RTCBase_ptr> findComponents(const std::string& InString);
    std::string bindInOut(RTCBase_ptr comp_in,
			  const std::string& inp_name,
			  RTCBase_ptr comp_out,
			  const std::string& outp_name,
			  RTM::SubscriptionType sub_type = RTM::OPS_NEW);
    std::string bindInOutByName(const std::string& InString,
				const std::string& InString,
				const std::string& InString,
				const std::string& InString);
    //				RTM::SubscriptionType sub_type = RTM::OPS_NEW);
    /*
    std::string bindInOutByName(const std::string& comp_name_in,
				const std::string& inp_name,
				const std::string& comp_name_out,
				const std::string& outp_name,
				RTM::SubscriptionType sub_type = RTM::OPS_NEW);
    */

    CORBA::ORB_ptr getORB();
    PortableServer::POA_ptr getPOA();
  };
};



