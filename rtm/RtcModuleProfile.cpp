// -*- C++ -*-
/*!
 * @file RtcModuleProfile.cpp
 * @brief RTComponent profile class
 * @date $Date: 2005-05-16 06:26:07 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcModuleProfile.cpp,v 1.2 2005-05-16 06:26:07 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include "rtm/RtcModuleProfile.h"
#include <iostream>

using namespace std;

namespace RTM {


  RtcModuleProfile::RtcModuleProfile()
	: m_CompTypeSize(sizeof CompTypes / sizeof *CompTypes),
	  m_ActTypeSize(sizeof ActTypes / sizeof *ActTypes),
	  m_LangTypeSize(sizeof LangTypes / sizeof *LangTypes)
  {
	m_Profile.name                =  _CORBA_String_helper::empty_string;
	m_Profile.instance_id         =  _CORBA_String_helper::empty_string;
	m_Profile.implementation_id   =  _CORBA_String_helper::empty_string;
	m_Profile.description         =  _CORBA_String_helper::empty_string;
	m_Profile.version             =  _CORBA_String_helper::empty_string;
	m_Profile.maker               =  _CORBA_String_helper::empty_string;
	m_Profile.language            =  _CORBA_String_helper::empty_string;
	m_Profile.module_profile_file =  _CORBA_String_helper::empty_string;

	m_CompTypeMap = map<string, int>(CompTypes, CompTypes + m_CompTypeSize);
	m_ActTypeMap  = map<string, int>(ActTypes, ActTypes + m_ActTypeSize);
	m_LangTypeMap = map<string, int>(LangTypes, LangTypes + m_LangTypeSize);
	
	initTable();
  }
  
  RtcModuleProfile::RtcModuleProfile(RtcModuleProfSpec *spec)
	: m_CompTypeSize(sizeof CompTypes / sizeof *CompTypes),
	  m_ActTypeSize(sizeof ActTypes / sizeof *ActTypes),
	  m_LangTypeSize(sizeof LangTypes / sizeof *LangTypes)
  {
	m_Profile.name                =  _CORBA_String_helper::empty_string;
	m_Profile.instance_id         =  _CORBA_String_helper::empty_string;
	m_Profile.implementation_id   =  _CORBA_String_helper::empty_string;
	m_Profile.description         =  _CORBA_String_helper::empty_string;
	m_Profile.version             =  _CORBA_String_helper::empty_string;
	m_Profile.maker               =  _CORBA_String_helper::empty_string;
	m_Profile.language            =  _CORBA_String_helper::empty_string;
	m_Profile.module_profile_file =  _CORBA_String_helper::empty_string;

	m_CompTypeMap = map<string, int>(CompTypes, CompTypes + m_CompTypeSize);
	m_ActTypeMap  = map<string, int>(ActTypes, ActTypes + m_ActTypeSize);
	m_LangTypeMap = map<string, int>(LangTypes, LangTypes + m_LangTypeSize);
	
	initTable();
	initSpec(spec);
  }


  RTCProfile RtcModuleProfile::getProfile()
  {	
	return m_Profile;
  }

  void RtcModuleProfile::initTable()
  {
	_init_func[RTC_MODULE_NAME]      = &RtcModuleProfile::setImplementationId;
	_init_func[RTC_MODULE_DESC]      = &RtcModuleProfile::setDescription;
	_init_func[RTC_MODULE_VERSION]   = &RtcModuleProfile::setVersion;
	_init_func[RTC_MODULE_AUTHOR]    = &RtcModuleProfile::setAuthorName;
	_init_func[RTC_MODULE_COMPANY]   = &RtcModuleProfile::setAuthorCompany;
	_init_func[RTC_MODULE_CATEGORY]  = &RtcModuleProfile::setCategory;
	_init_func[RTC_MODULE_COMP_TYPE] = &RtcModuleProfile::setComponentType;
	_init_func[RTC_MODULE_ACT_TYPE]  = &RtcModuleProfile::setActivityType;
	_init_func[RTC_MODULE_MAX_INST]  = &RtcModuleProfile::setMaxInstance;
	_init_func[RTC_MODULE_LANG]      = &RtcModuleProfile::setLanguage;
	_init_func[RTC_MODULE_LANG_TYPE] = &RtcModuleProfile::setLanguageType;
  }	
 


  bool RtcModuleProfile::initSpec(RtcModuleProfSpec *spec)
  {
	bool retval(true);

	while (spec->type != RTC_MODULE_SPEC_END)
	  {
		bool ret = (this->*_init_func[spec->type])(spec->value);
		if (ret == false) retval = false;
		spec++;
	  }
	return retval;
  }	


  /*!------------------------------------------------------------
   * ImplementationId of a component
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setImplementationId(const char* name)
  {
	m_Profile.name = CORBA::string_dup(name);
	m_Profile.implementation_id = CORBA::string_dup(name);
	
	return true;
  }

  /*!------------------------------------------------------------
   * InstanceID of a component
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setInstanceId(const char* name)
  {
	m_Profile.instance_id = CORBA::string_dup(name);
	
	return true;
  }


  /*!------------------------------------------------------------
   * Description of a component
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setDescription(const char* desc)
  {
	m_Profile.description = CORBA::string_dup(desc);
	
	return true;
  }
  
  
  /*!------------------------------------------------------------
   * Version
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setVersion(const char* version)
  {
	m_Profile.version = CORBA::string_dup(version);
	
	return true;
  }
  
  
  /*!------------------------------------------------------------
   *  The author of this component
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setAuthorName(const char* author_name)
  {
	m_Profile.maker = CORBA::string_dup(author_name);
	
	return true;
  }
  
  
  /*!------------------------------------------------------------
   *  The author of this component
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setAuthorCompany(const char* author_company)
  {
	//	m_Profile.author.company = CORBA::string_dup(author_company);
	
	return true;
  }
  

  /*------------------------------------------------------------
   * Category
   *------------------------------------------------------------*/  
  bool RtcModuleProfile::setCategory(const char* category)
  {
	m_Profile.category = CORBA::string_dup(category);
	
	return true;
  }
  
  
  /*------------------------------------------------------------
   * Component type
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setComponentType(RTComponentType type)
  {
	m_Profile.component_type = type;
	
	return true;
  }
  bool RtcModuleProfile::setComponentType(const char *type_str)
  {
	string type(type_str);

	m_Profile.component_type = static_cast<RTComponentType>(m_CompTypeMap[type]);
	
	return true;
  }
  
  
  /*!------------------------------------------------------------
   * Activity type (periodic, sporadic, event_driven...)
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setActivityType(RTCActivityType type)
  {
	m_Profile.activity_type = type;
	
	return true;
  }
  bool RtcModuleProfile::setActivityType(const char *type_str)
  {
	string type(type_str);

	m_Profile.activity_type = static_cast<RTCActivityType>(m_ActTypeMap[type]);
	
	return true;
  }
  
  
  /*!------------------------------------------------------------
   * Maximum number of instance
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setMaxInstance(int max)
  {
	m_Profile.max_instance = max;
	
	return true;
  }
  bool RtcModuleProfile::setMaxInstance(const char *max_str)
  {
	int max = atoi(max_str);

	if (max > 0)
	  {
		m_Profile.max_instance = max;
		return true;
	  }
	
	return false;
  }
  
  
  /*!------------------------------------------------------------
   * Programming language
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setLanguage(const char* language)
  {
	m_Profile.language = CORBA::string_dup(language);
	
	return true;
  }
  
  
  /*!------------------------------------------------------------
   * Programming language type
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setLanguageType(RTCLangType type)
  {
	m_Profile.language_type = type;
	
	return true;
  }
  bool RtcModuleProfile::setLanguageType(const char *type_str)
  {
	string type(type_str);

	m_Profile.language_type = static_cast<RTCLangType>(m_LangTypeMap[type]);
	
	return true;
  }
  
  
  /*!------------------------------------------------------------
   * Icon image data
   *------------------------------------------------------------*/
  bool RtcModuleProfile::setIconImage(const char* image)
  {
	//	  
	return true;
  }
  
  bool RtcModuleProfile::appendInPortProfile(const PortProfile port_profile)
  {
	int len = m_Profile.inport_profile_list.length();
	// expand sequence (current length + 1)
	m_Profile.inport_profile_list.length(len + 1);
	// Append PortProfile as last item
	m_Profile.inport_profile_list[len] = port_profile;
	return true;
  }

  PortProfile RtcModuleProfile::getInPortProfile(const char* name)
  {
	PortProfileList& profile_list = m_Profile.inport_profile_list;
	unsigned int len = profile_list.length();

	for (CORBA::ULong i = 0; i < len; i++)
	  {
		if (strcmp(name, profile_list[i].name))
		  {
			return profile_list[i];
		  }
	  }
	PortProfile profile;
	return profile;
  }

  PortProfileList RtcModuleProfile::getInPortProfileList()
  {
	return m_Profile.inport_profile_list;
  }

  bool RtcModuleProfile::appendOutPortProfile(const PortProfile port_profile)
  {
	int len = m_Profile.outport_profile_list.length();
	// expand sequence (current length + 1)
	m_Profile.outport_profile_list.length(len + 1);
	// Append PortProfile as last item
	m_Profile.outport_profile_list[len] = port_profile;
	return true;
  }

  PortProfile RtcModuleProfile::getOutPortProfile(const char* name)
  {
	PortProfileList& profile_list = m_Profile.outport_profile_list;
	unsigned int len = profile_list.length();

	for (CORBA::ULong i = 0; i < len; i++)
	  {
		if (strcmp(name, profile_list[i].name))
		  {
			return profile_list[i];
		  }
	  }
	PortProfile profile;
	return profile;
  }

  PortProfileList RtcModuleProfile::getOutPortProfileList()
  {
	return m_Profile.outport_profile_list;
  }

}; // end of namespace RTM
