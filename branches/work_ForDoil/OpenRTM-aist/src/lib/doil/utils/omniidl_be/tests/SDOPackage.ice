//Platform Independent Model (PIM) and Platform Specific Model (PSM)
//for Super Distributed Objects (SDO) Specification, v1.1 - OMG IDL Summary File
//Object Management Group, Inc.
//Copyright (c) 2003, Fraunhofer FOKUS
//Copyright (c) 2003, Hitachi, Ltd.
//The companies listed above have granted to the Object Management Group, Inc. 
//(OMG) a nonexclusive, royalty-free, paid up, worldwide license to copy and 
//distribute this document and to modify this document and distribute copies of 
//the modified version. Each of the copyright holders listed above has agreed 
//that no person shall be deemed to have infringed the copyright in the included 
//material of any such copyright holder by reason of having used the 
//specification set forth herein or having conformed any computer software to 
//the specification. 
//
//This file contains OMG IDL from the Naming Service Specification, v1.2.
//OMG regularly publishes a summary file that contains all the "code" parts of 
//an OMG formal document. Every formal document line that is IDL, PIDL, or 
//language code is included in the summary file. The reason for such a listing 
//is to give readers an electronic version of the "code" so that they can 
//extract pieces of it. Readers might want to test an example, include it in 
//their own code, or use it for documentation purposes. Having the code lines 
//available electronically means there is less likelihood of a transcription 
//error. 
//
// ver 1.0  formal/2004-11-02
// ver 1.1  (RTF report: dtc/2008-03-05)
//
//SDOPackage.idl

#ifndef    _SDO_PACKAGE_IDL_
#define    _SDO_PACKAGE_IDL_

#ifdef TAO_IDL
#include <orb.idl>
#endif
#ifdef USE_MONITORING
#include <CosNotifyComm.idl>
#endif

/** CORBA specific model for SDOs */

//#pragma prefix "org.omg"
#define exception_body { string description; }

module SDOPackage
{
  interface SDO;
  interface SDOService;
  interface SDOSystemElement;
  interface Configuration;
  interface Monitoring;
  interface Organization;

  /** ------- Data Types -------*/
  sequence<string>       StringList;
  sequence<SDO>          SDOList;
  sequence<Organization> OrganizationList;
  //typedef sequence<SDO>          SDOList;
  //typedef sequence<Organization> OrganizationList;
  //typedef string                 UniqueIdentifier;

  struct NameValue
  {
    string name;
    string value;
  };

  sequence<NameValue>   NVList;

  enum NumericType
  {
    SHORT_TYPE,
    LONG_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE
  };

  class Numeric
  {
  short short_value;
  long long_value;
  float float_value;
  double double_value;
  };
/*
  union Numeric switch (NumericType)
  {
  case SHORT_TYPE:  short short_value;
  case LONG_TYPE: long long_value;
  case FLOAT_TYPE: float float_value;
  case DOUBLE_TYPE: double double_value;
  };
*/

  struct EnumerationType
  {
    StringList enumerated_values;
  };

  struct RangeType
  {
    Numeric min;
    Numeric max;
    bool min_inclusive;
    bool max_inclusive;
  };

  struct IntervalType
  {
    Numeric min;
    Numeric max;
    bool min_inclusive;
    bool max_inclusive;
    Numeric step;
  };

  enum ComplexDataType
  {
    ENUMERATION, RANGE, INTERVAL
  };

  class AllowedValues
  {
  EnumerationType allowed_enum;
  IntervalType allowed_interval;
  RangeType   allowed_range;
  };
/*
  union AllowedValues switch (ComplexDataType)
  {
  case ENUMERATION:    EnumerationType allowed_enum;
  case INTERVAL:       IntervalType allowed_interval;
  case RANGE:          RangeType   allowed_range;
  };
*/

  struct Parameter
  {
    string         name;

    string  type;



    AllowedValues  allowed_values;
  };

  sequence<Parameter> ParameterList;
  struct OrganizationProperty
  {
    NVList properties;
  };
  enum DependencyType
  {
    OWN,
    OWNED,
    NO_DEPENDENCY
  };

  struct DeviceProfile
  {
    string device_type;
    string manufacturer;
    string model;
    string version;
    NVList properties;
  };

  struct ServiceProfile
  {
    string id;
    string interface_type;
    NVList properties;
    SDOService service;
  };

  sequence <ServiceProfile> ServiceProfileList;
  struct ConfigurationSet
  {
    string id;
    string description;
    NVList configuration_data;
  };

  sequence<ConfigurationSet> ConfigurationSetList;


  /** ------- Exceptions -------*/
  exception NotAvailable             exception_body;
  exception InterfaceNotImplemented  exception_body;
  exception InvalidParameter         exception_body;
  exception InternalError            exception_body;

  /** ------- Interfaces -------*/
  interface SDOSystemElement
  {
    OrganizationList get_owned_organizations()
      throws NotAvailable,InternalError;
  };
  interface SDO extends SDOSystemElement
  {
    string get_sdo_id()
      throws NotAvailable, InternalError;
    string get_sdo_type()
      throws NotAvailable, InternalError;
    DeviceProfile get_device_profile ()
      throws NotAvailable, InternalError;
    ServiceProfileList get_service_profiles ()
      throws NotAvailable, InternalError;
    ServiceProfile get_service_profile ( string id)
      throws InvalidParameter, NotAvailable, InternalError;
    SDOService get_sdo_service ( string id) 
      throws InvalidParameter, NotAvailable, InternalError;
    Configuration get_configuration ()
      throws InterfaceNotImplemented, NotAvailable, InternalError;
    Monitoring get_monitoring ()
      throws InterfaceNotImplemented, NotAvailable, InternalError;
    OrganizationList get_organizations ()
      throws NotAvailable, InternalError;
    NVList get_status_list ()
      throws NotAvailable, InternalError;
    string get_status ( string nme)
      throws InvalidParameter, NotAvailable, InternalError;
  };


  interface Configuration
  {
    bool set_device_profile ( DeviceProfile dProfile)
      throws InvalidParameter, NotAvailable, InternalError;
    bool add_service_profile ( ServiceProfile sProfile)
      throws InvalidParameter, NotAvailable, InternalError;
    bool add_organization ( Organization organization_object)
      throws InvalidParameter, NotAvailable, InternalError;
    bool remove_service_profile ( string id)
      throws InvalidParameter, NotAvailable, InternalError;
    bool remove_organization ( string organization_id)
      throws InvalidParameter, NotAvailable, InternalError;
    ParameterList get_configuration_parameters ()
      throws NotAvailable, InternalError;
    NVList get_configuration_parameter_values ()
      throws NotAvailable, InternalError;
    string get_configuration_parameter_value ( string name)
      throws InvalidParameter, NotAvailable, InternalError;
    bool set_configuration_parameter ( string name,
                                          string value)
      throws InvalidParameter, NotAvailable, InternalError;
    ConfigurationSetList get_configuration_sets ()
      throws NotAvailable, InternalError;
    ConfigurationSet get_configuration_set ( string config_id)
      throws NotAvailable, InternalError;
    bool set_configuration_set_values ( ConfigurationSet configuration_set)
      throws InvalidParameter, NotAvailable, InternalError;
    ConfigurationSet get_active_configuration_set ()
      throws NotAvailable, InternalError;
    bool add_configuration_set ( ConfigurationSet configuration_set)
      throws InvalidParameter, NotAvailable, InternalError;
    bool remove_configuration_set ( string config_id)
      throws InvalidParameter, NotAvailable, InternalError;
    bool activate_configuration_set ( string config_id)
      throws InvalidParameter, NotAvailable, InternalError;
  };


#ifdef USE_MONITORING
  interface Monitoring : CosNotifyComm::StructuredPushConsumer,
    CosNotifyComm::StructuredPushSupplier
  {
    string get_monitoring_parameter_value ( string name)
      throws InvalidParameter, NotAvailable, InternalError;
    ParameterList get_monitoring_parameters ()
      throws NotAvailable, InternalError;
    NVList get_monitoring_parameter_values ()
      throws NotAvailable, InternalError;
  };
#else
  interface Monitoring {};
#endif

  interface SDOService {};

  interface Organization
  {
    string get_organization_id ()
      throws InvalidParameter, NotAvailable, InternalError;
    OrganizationProperty get_organization_property ()
      throws NotAvailable, InternalError;
    string get_organization_property_value ( string name)
      throws InvalidParameter, NotAvailable, InternalError;
    bool add_organization_property ( OrganizationProperty organization_property)
      throws InvalidParameter, NotAvailable, InternalError;
    bool set_organization_property_value ( string name,
                                              string value)
      throws InvalidParameter, NotAvailable, InternalError;
    bool remove_organization_property (  string name )
      throws InvalidParameter, NotAvailable, InternalError;
    SDOSystemElement get_owner ()
      throws NotAvailable, InternalError;
    bool set_owner ( SDOSystemElement sdo) 
      throws InvalidParameter, NotAvailable, InternalError;
    SDOList get_members ()
      throws NotAvailable, InternalError;
    bool set_members ( SDOList sdos) 
      throws InvalidParameter, NotAvailable, InternalError;
    bool add_members ( SDOList sdo_list)
      throws InvalidParameter, NotAvailable, InternalError;
    bool remove_member ( string id)
      throws InvalidParameter, NotAvailable, InternalError;
    DependencyType get_dependency()
      throws NotAvailable, InternalError;
    bool set_dependency ( DependencyType dependency) 
      throws NotAvailable, InternalError;
  };
};
#endif //_SDO_PACKAGE_IDL_
