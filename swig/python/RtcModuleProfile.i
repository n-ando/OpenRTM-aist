// -*- C++ -*-
/*!
 * @file RtcModuleProfile.i
 * @brief swig interface file for RtcModuleProfile
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

%module RtcModuleProfile

%{
#include "rtm/RtcBase.h"
#include "rtm/RtcModuleProfile.h"
#include "rtm/idl/RTComponentSkel.h"
%}


%inline %{
using namespace std;
using namespace RTM;
%}


namespace RTM {

  typedef enum RtcModuleProfileType {
	RTC_MODULE_NAME,
	RTC_MODULE_DESC,
	RTC_MODULE_VERSION,
	RTC_MODULE_AUTHOR,
	RTC_MODULE_COMPANY,
	RTC_MODULE_CATEGORY,
	RTC_MODULE_COMP_TYPE,
	RTC_MODULE_ACT_TYPE,
	RTC_MODULE_MAX_INST,
	RTC_MODULE_LANG,
	RTC_MODULE_LANG_TYPE,
	RTC_MODULE_SPEC_END
  };

  
  typedef struct RtcModuleProfSpec {
	RtcModuleProfileType type;
	char* value;
  };

  class RtcModuleProfile
  {
  public:
	//	RtcModuleProfile();
	RtcModuleProfile(RtcModuleProfSpec *spec);
	bool initSpec(RtcModuleProfSpec *spec);

	bool setImplementationId(const char* implementation_id);
	const char* getImplementationId();

	bool setInstanceId(const char* instance_id);
	const char* getInstanceId();

	bool setDescription(const char* desc);
	const char* getDescription();

	bool setVersion(const char* version);
	const char* getVersion();

	bool setAuthorName(const char* author_name);
	const char* getAuthorName();

	bool setAuthorCompany(const char* author_company);
	const char* getAuthorCompany();

	bool setCategory(const char* category);
	const char* getCategory();

	bool setComponentType(RTComponentType type);
	bool setComponentType(const char *type_str);
	RTComponentType getComponentType();

	bool setActivityType(RTCActivityType type);
	bool setActivityType(const char *type_str);
	RTCActivityType getActivityType();

	bool setMaxInstance(int max);
	bool setMaxInstance(const char *max_str);
	int  getMaxInstance();

	bool setLanguage(const char* langugae);
	const char* getLanguage();

	bool setLanguageType(RTCLangType type);
	bool setLanguageType(const char *type_str);
	RTCLangType getLanguageType();

	bool setIconImage(const char* image);
	const char* getIconImage();

	bool appendInPortProfile(const PortProfile port_profile);
	PortProfile getInPortProfile(const char* name);
	PortProfileList getInPortProfileList();

	bool appendOutPortProfile(const PortProfile port_profile);
	PortProfile getOutPortProfile(const char* name);
	PortProfileList getOutPortProfileList();
  };


};
