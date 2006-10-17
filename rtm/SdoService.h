// -*- C++ -*-
/*!
 * @file SdoService.h
 * @brief SDO Service administration class
 * @date $Date: 2006-10-17 10:12:51 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoService.h,v 1.2 2006-10-17 10:12:51 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/09/11 18:48:08  n-ando
 * The first commit.
 *
 *
 */


namespace SDOPackage
{
  class SDOServiceProfile
    : public SDOpackage::ServiceProfile
  {
  public:
    SDOService(char* id = "", char type = "")
    {
    }

    inline const SDOPackage::Service getProfile()
    {
      return *this;
    }

    
    /*!
     * @if jp
     * @brief ServiceProfile.id をセットする
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
     * @else
     * @brief Getting RTCServiceProfile.serviceRef
     * @endif
     */
    RTCService_ptr getServiceRef() const
    {
      return this->serviceRef;
    }
  };
  
  
