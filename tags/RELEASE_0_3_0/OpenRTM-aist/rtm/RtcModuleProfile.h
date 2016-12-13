// -*- C++ -*-
/*!
 * @file RtcModuleProfile.h
 * @brief RT component module's profile class
 * @date $Date: 2005-05-16 06:26:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcModuleProfile.h,v 1.2 2005-05-16 06:26:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcModuleProfile_h
#define RtcModuleProfile_h

// CORBA header include
#include "rtm/RTC.h"

// STL includes
#include <map>
#include <string>

// local includes 
#include "rtm/idl/RTCProfileSkel.h"
#include "rtm/idl/RTCProfileStub.h"
#include "rtm/idl/RTCBaseSkel.h"
#include "rtm/idl/RTCBaseStub.h"


namespace RTM {
  using namespace std;

  /*!------------------------------------------------------------
   * @typedef RtcModuleProfileType
   *
   * Type definition of RtcModuleProfile initialize table.
   *------------------------------------------------------------*/
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


  /*!------------------------------------------------------------
   * @typedef RtcModuleProfSpec
   *
   * Type definition of RtcModuleProfile initialize table.
   *------------------------------------------------------------*/
  typedef struct RtcModuleProfSpec_t {
	RtcModuleProfileType type;
	char* value;
  } RtcModuleProfSpec;


  typedef map<string, int>::value_type TypeMapValue;
  //  typedef map<string, int> TypeMap;
  /*!------------------------------------------------------------
   * Component type string to enum table
   *------------------------------------------------------------*/
  static TypeMapValue CompTypes[] = {
	TypeMapValue("STATIC", STATIC),
	TypeMapValue("UNIQUE", UNIQUE),
	TypeMapValue("COMMUTATIVE", COMMUTATIVE)
  };

  /*!------------------------------------------------------------
   * Activity type string to enum table
   *------------------------------------------------------------*/
  static TypeMapValue ActTypes[] = {
	TypeMapValue("PERIODIC", PERIODIC),
	TypeMapValue("SPORADIC", SPORADIC),
	TypeMapValue("EVENT_DRIVEN", EVENT_DRIVEN),
  };

  /*!------------------------------------------------------------
   * Language type string to enum table
   *------------------------------------------------------------*/
  static TypeMapValue LangTypes[] = {
	TypeMapValue("COMPILE", COMPILE),
	TypeMapValue("SCRIPT", SCRIPT),
  };


  
  /*!------------------------------------------------------------
   * @class RtcModuleProfile
   *
   * @brief Profile class of RTComponent Module
   *------------------------------------------------------------*/
  class EXPORTS RtcModuleProfile
  {
  public:

	/*!------------------------------------------------------------
	 * A Constructor
	 *------------------------------------------------------------*/
	RtcModuleProfile();

	/*!------------------------------------------------------------
	 * A Constructor
	 *
	 * @param spec static table of RtcModuleProfSpec
	 *------------------------------------------------------------*/
	RtcModuleProfile(RtcModuleProfSpec *spec);


	RTCProfile getProfile();

	/*!------------------------------------------------------------
	 * Initialization from RtcModuleProfSpec table
	 *
	 * @param spec static table of RtcModuleProfSpec
	 *------------------------------------------------------------*/
	bool initSpec(RtcModuleProfSpec *spec);



	/*!------------------------------------------------------------
	 * Name of component module
	 *
	 * @brief Module name
	 *------------------------------------------------------------*/
	bool setImplementationId(const char* implementation_id);
	const char* getImplementationId(){return m_Profile.implementation_id;};

	/*!------------------------------------------------------------
	 * Name of component module
	 *
	 * @brief Module name
	 *------------------------------------------------------------*/
	bool setInstanceId(const char* instance_id);
	const char* getInstanceId(){return m_Profile.instance_id;};

	/*!------------------------------------------------------------
	 * Description of component
	 *
	 * @brief Component description like "Mitsubishi PA10 endeffector
	 *        velocity control component", "BL autotec NANO sensor",
	 *        "Sensorble technology PHANToM desktop type", etc... 
	 *------------------------------------------------------------*/
	bool setDescription(const char* desc);
	const char* getDescription() {return m_Profile.description;};


	/*!------------------------------------------------------------
	 * Version
	 *
	 * @berief Version of this component.
	 *------------------------------------------------------------*/
	bool setVersion(const char* version);
	const char* getVersion() {return m_Profile.version;};


	/*!------------------------------------------------------------
	 * 	The author of this component
	 *
	 * @berief Author include authors' name and authros' company.
	 *------------------------------------------------------------*/
	bool setAuthorName(const char* author_name);
	const char* getAuthorName() {return m_Profile.maker;};
	bool setAuthorCompany(const char* author_company);
	const char* getAuthorCompany() {return m_Profile.maker;};


	/*------------------------------------------------------------
	 * Category
	 *
	 * @berief Category of this component, like "Motor controller",
	 *         "Image processing", etc..
	 *------------------------------------------------------------*/
	bool setCategory(const char* category);
	const char* getCategory() {return m_Profile.category;};


	/*------------------------------------------------------------
	 * Component type
	 *
	 * @berief Instance type of this component.
	 *         STATIC: Statically instantiated and no dynamic instance.
	 *         UNIQUE: Dynamically instantiated component. But each
	 *                 component should be handle a unique it.
	 *                 For example, the compopnent is statically
	 *                 bound to hardaware device.
	 *         COMMUTATIVE: Dynamically instantiated component.
	 *                 Each component is commutative. For example, 
	 *                 logic components are commutative.
	 *------------------------------------------------------------*/
	bool setComponentType(RTComponentType type);
	bool setComponentType(const char *type_str);
	RTComponentType getComponentType() {return m_Profile.component_type;};


	/*!------------------------------------------------------------
	 * Activity type (periodic, sporadic, event_driven...)
	 *
	 * @berief Activity type of the component.
	 *         PERIODIC: Periodic working activity. Period time is 
	 *                   is constant. For only realtime OS.
	 *         ITERATIVE: Iterative working activity. Period time is
	 *                   is constant but deadline will not be unbounded
	 *         SPORADIC: Sporadic working activity. Activity works
	 *                   depending on outside event or hardware event.
	 *         EVENT_DRIVEN: Activity works as event driven task.
	 *                   Events will raised from software
	 *                   (other components)
	 *------------------------------------------------------------*/
	bool setActivityType(RTCActivityType type);
	bool setActivityType(const char *type_str);
	RTCActivityType getActivityType() {return m_Profile.activity_type;};


	/*!------------------------------------------------------------
	 * Maximum number of instance
	 *
	 * @berief Maximum number of instance, which is instantiated
	 *         on a same manager
	 *------------------------------------------------------------*/
	bool setMaxInstance(int max);
	bool setMaxInstance(const char *max_str);
	int  getMaxInstance() {return m_Profile.max_instance;};


	/*!------------------------------------------------------------
	 * Programming language
	 *
	 * @berief Programming language which describes this component
	 *------------------------------------------------------------*/
	bool setLanguage(const char* langugae);
	const char* getLanguage() {return m_Profile.language;};


	/*!------------------------------------------------------------
	 * Programming language type
	 *
	 * @berief Programming language type.
	 *         COMPILED: Language type is compiled like C, C++ etc..
	 *         SCRIPT: Language type is script language like
	 *                 Perl, Python, Ruby, etc...
	 *------------------------------------------------------------*/
	bool setLanguageType(RTCLangType type);
	bool setLanguageType(const char *type_str);
	RTCLangType getLanguageType() {return m_Profile.language_type;};


	/*!------------------------------------------------------------
	 * Icon image data
	 *
	 * @berief Icon image data, which is used on component CAD, etc..
	 *------------------------------------------------------------*/
	bool setIconImage(const char* image);
	const char* getIconImage() {return NULL;};

	bool appendInPortProfile(const PortProfile port_profile);
	PortProfile getInPortProfile(const char* name);
	PortProfileList getInPortProfileList();

	bool appendOutPortProfile(const PortProfile port_profile);
	PortProfile getOutPortProfile(const char* name);
	PortProfileList getOutPortProfileList();



  private:
	void RtcModuleProfile::initTable();


	RTCProfile m_Profile;

	map<string, int> m_CompTypeMap;
	map<string, int> m_ActTypeMap;
	map<string, int> m_LangTypeMap;
	int m_CompTypeSize;
	int m_ActTypeSize;
	int m_LangTypeSize;

	typedef bool (RtcModuleProfile::*SpecInitFunc)(const char* );
	SpecInitFunc _init_func[RTC_MODULE_SPEC_END];

  };


};


#endif // RtcModuleProfile_h
