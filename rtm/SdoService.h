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
 * $Id: SdoService.h,v 1.2.4.1 2007-12-31 03:08:07 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/17 10:12:51  n-ando
 * Small fixes.
 *
 * Revision 1.1  2006/09/11 18:48:08  n-ando
 * The first commit.
 *
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
     * @brief Setting ServiceProfile.id
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
     * @brief Getting ServiceProfile.id
     * @endif
     */
    inline const char* getName() const
    {
      return this->id;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.interfaceType をセットする
     * 
     * SDO Service のinterfaceTypeをセットする
     * 
     * @param interfaceType Service のinterfaceType
     * 
     * @else
     * @brief Setting RTCServiceProfile.interfaceType
     * @endif
     */
    inline void setInterfaceType(char* interfaceType)
    {
      this->interfaceType = interfaceType;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.interfaceType を取得する
     * 
     * SDO Service のinterfaceTypeを取得する
     * 
     * @return Service のinterfaceType
     * 
     * @else
     * @brief Getting RTCServiceProfile.interfaceType
     * @endif
     */
    inline const char* getInterfaceType() const
    {
      return this->interfaceType;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.idlDefinition をセットする
     * 
     * SDO Service のidlDefinitionをセットする
     * 
     * @param idlDefinition Service のidlDefinition
     * 
     * @else
     * @brief Setting RTCServiceProfile.idlDefnition
     * @endif
     */
    inline void setIdlDefinition(char* idlDefinition)
    {
      this->idlDefinition = idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.idlDefinition を取得する
     * 
     * SDO Service のidlDefinitionを取得する
     * 
     * @return Service のidlDefinition
     * 
     * @else
     * @brief Getting RTCServiceProfile.idlDefnition
     * @endif
     */
    inline const char* getIdlDefinition() const
    {
      return this->idlDefinition;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.properties をセットする
     * 
     * SDO Service のpropertiesをセットする
     * 
     * @param properties Service のproperties
     * 
     * @else
     * @brief Setting RTCServiceProfile.properties
     * @endif
     */
    inline void setProperties(NVList properties)
    {
      this->properties = properties;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.properties を取得する
     * 
     * SDO Service のpropertiesを取得する
     * 
     * @return Service のproperties
     * 
     * @else
     * @brief Getting RTCServiceProfile.properties
     * @endif
     */
    inline const NVList getProperties() const
    {
      return this->properties;
    }
    
    //	bool addProperty(char* name, CORBA::Any data);
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.serviceRef をセットする
     * 
     * SDO Service のserviceRefをセットする
     * 
     * @param serviceRef Serviceへの参照
     * 
     * @else
     * @brief Setting RTCServiceProfile.serviceRef
     * @endif
     */
    inline void setServiceRef(RTCService_ptr serviceRef)
    {
      this->serviceRef = serviceRef;
    }
    
    /*!
     * @if jp
     * @brief RTCServiceProfile.serviceRef を取得する
     * 
     * SDO Service への参照を取得する
     * 
     * @return Serviceへの参照
     * 
     * @else
     * @brief Getting RTCServiceProfile.serviceRef
     * @endif
     */
    RTCService_ptr getServiceRef() const
    {
      return this->serviceRef;
    }
  };
};
