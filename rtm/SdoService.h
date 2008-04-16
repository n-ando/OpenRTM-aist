// -*- C++ -*-
/*!
 * @file SdoService.h
 * @brief SDO Service administration class
 * @date $Date: 2007-12-31 03:08:07 $
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

/*!
 * @if jp
 * @namespace SDOPackage
 *
 * @brief SDO パッケージ
 *
 * @else
 *
 * @namespace SDOPackage
 *
 * @brief SDO package
 *
 * @endif
 */
namespace SDOPackage
{
  /*!
   * @if jp
   *
   * @class SDOServiceProfile
   * @brief SDO Service Profileクラス
   *
   * SDO Service Profile は SDO Service の情報を保持するためのクラスである。
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class SDOServiceProfile
   * @brief SDO Service Profile class
   *
   * SDO Service Profile is a class to hold information of SDO Service.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class SDOServiceProfile
    : public SDOpackage::ServiceProfile
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     * 
     * コンストラクタ
     *
     * @param id Service のID(デフォルト値:"")
     * @param type Service の型(デフォルト値:"")
     *
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     *
     * @param id ID of the Service(The default value:"")
     * @param type Type of the Service(The default value:"")
     *
     * @endif
     */
    SDOService(char* id = "", char type = "")
    {
    }
    
    /*!
     * @if jp
     *
     * @brief Service Profileを取得する
     * 
     * Service Profileを取得する
     * 
     * @return Service Profile
     * 
     * @else
     *
     * @brief Get Service Profile
     * 
     * Get Service Profile.
     * 
     * @return Service Profile
     * 
     * @endif
     */
    inline const SDOPackage::Service getProfile()
    {
      return *this;
    }
    
    /*!
     * @if jp
     * @brief ServiceProfile.id をセットする
     * 
     * SDO Service のIDをセットする
     * 
     * @param id Service のID
     * 
     * @else
     * @brief Set ServiceProfile.id
     * 
     * Set ID of SDO Service.
     * 
     * @param id ID of the Service
     * 
     * @endif
     */
    inline void setName(char* id)
    {
      // this->name is CORBA::string member of the struct
      this->id = id;
    }
    
    /*!
     * @if jp
     * @brief ServiceProfile.id を取得
     * 
     * SDO Service のIDを取得する
     * 
     * @return Service のID
     * 
     * @else
     * @brief Get ServiceProfile.id
     * 
     * Get ID of SDO Service.
     * 
     * @return ID of the Service
     * 
     * @endif
     */
    inline const char* getName() const
    {
      return this->id;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.interfaceType をセットする
     * 
     * SDO Service のinterfaceTypeをセットする
     * 
     * @param interfaceType Service のinterfaceType
     * 
     * @else
     * @brief Set SDOServiceProfile.interfaceType
     * 
     * Set interfaceType of SDO Service.
     * 
     * @param interfaceType interfaceType of the Service
     * 
     * @endif
     */
    inline void setInterfaceType(char* interfaceType)
    {
      this->interfaceType = interfaceType;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.interfaceType を取得する
     * 
     * SDO Service のinterfaceTypeを取得する
     * 
     * @return Service のinterfaceType
     * 
     * @else
     * @brief Get SDOServiceProfile.interfaceType
     * 
     * Get interfaceType of SDO Service
     * 
     * @return interfaceType of the Service
     * 
     * @endif
     */
    inline const char* getInterfaceType() const
    {
      return this->interfaceType;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.idlDefinition をセットする
     * 
     * SDO Service のidlDefinitionをセットする
     * 
     * @param idlDefinition Service のidlDefinition
     * 
     * @else
     * @brief Set SDOServiceProfile.idlDefnition
     * 
     * Set idlDefinition of SDO Service
     * 
     * @param idlDefinition idlDefinition of the Service
     * 
     * @endif
     */
    inline void setIdlDefinition(char* idlDefinition)
    {
      this->idlDefinition = idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.idlDefinition を取得する
     * 
     * SDO Service のidlDefinitionを取得する
     * 
     * @return Service のidlDefinition
     * 
     * @else
     * @brief Get SDO ServiceProfile.idlDefnition
     * 
     * Get idlDefinition of SDO Service
     * 
     * @return idlDefinition of the Service
     * 
     * @endif
     */
    inline const char* getIdlDefinition() const
    {
      return this->idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.properties をセットする
     * 
     * SDO Service のpropertiesをセットする
     * 
     * @param properties Service のproperties
     * 
     * @else
     * @brief Set SDO ServiceProfile.properties
     * 
     * Set properties of SDO Service
     * 
     * @param properties Properties of the Service
     * 
     * @endif
     */
    inline void setProperties(NVList properties)
    {
      this->properties = properties;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.properties を取得する
     * 
     * SDO Service のpropertiesを取得する
     * 
     * @return Service のproperties
     * 
     * @else
     * @brief Get SDO ServiceProfile.properties
     * 
     * Get properties of SDO Service
     * 
     * @return Properties of the Service
     * 
     * @endif
     */
    inline const NVList getProperties() const
    {
      return this->properties;
    }
    
    //	bool addProperty(char* name, CORBA::Any data);
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.serviceRef をセットする
     * 
     * SDO Service のserviceRefをセットする
     * 
     * @param serviceRef Serviceへの参照
     * 
     * @else
     * @brief Set SDO ServiceProfile.serviceRef
     * 
     * Set serviceRef of SDO Service.
     * 
     * @param serviceRef The reference to Service
     * 
     * @endif
     */
    inline void setServiceRef(RTCService_ptr serviceRef)
    {
      this->serviceRef = serviceRef;
    }
    
    /*!
     * @if jp
     * @brief SDO ServiceProfile.serviceRef を取得する
     * 
     * SDO Service への参照を取得する
     * 
     * @return Serviceへの参照
     * 
     * @else
     * @brief Get SDO ServiceProfile.serviceRef
     * 
     * Get the reference to SDO Service
     * 
     * @return The reference to Service
     * 
     * @endif
     */
    RTCService_ptr getServiceRef() const
    {
      return this->serviceRef;
    }
  };
};
