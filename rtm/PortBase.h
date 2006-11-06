// -*- C++ -*-
/*!
 * @file PortBase.h
 * @brief RTC's Port base class
 * @date $Date: 2006-11-06 01:16:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PortBase.h,v 1.3 2006-11-06 01:16:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/17 19:06:45  n-ando
 * connect(), disconnect() and disconnect_all() was implemented.
 *
 * Revision 1.1  2006/10/17 10:22:24  n-ando
 * The first commitment.
 *
 */

#ifndef PortBase_h
#define PortBase_h

#include <rtm/idl/RTCSkel.h>
#include <string>
#include <ace/Guard_T.h>
#include <ace/Recursive_Thread_Mutex.h>

namespace RTC
{
  /*
    1. RTC内でインスタンス宣言
    2. RTCコンストラクタで初期化
     - name
     - properties 設定
    3. regsiterPortでactivateおよびリストに登録
     - port_ref 設定
     - owner 設定
    4. 

   */  
  class PortBase
    : public virtual POA_RTC::Port,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    PortBase(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa){};

    /*!
     * @if jp
     *
     * @brief [CORBA interface] PortProfileを取得する
     *
     * Portが保持するPortProfileを返す。
     *
     * @return この Port の PortProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the PortProfile of the Port
     *
     * This operation returns the PortProfile of the Port.
     *
     * @return the PortProfile of the Port
     *
     * @endif
     */
    virtual PortProfile* get_port_profile();


    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfileListを取得する
     *
     * Portが保持する ConnectorProfileList を返す。
     *
     * @return この Port の ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfileList of the Port
     *
     * This operation returns a list of the ConnectorProfiles of the Port.
     *
     * @return the ConnectorProfileList of the Port
     *
     * @endif
     */
    virtual ConnectorProfileList* get_connector_profiles();


    /*!
     * @if jp
     *
     * @brief [CORBA interface] ConnectorProfile を取得する
     *
     * connector_id で指定された ConnectorProfile を返す。
     *
     * @param connector_id ConnectorProfile の ID
     * @return connector_id を持つ ConnectorProfile
     *
     * @else
     *
     * @brief [CORBA interface] Get the ConnectorProfile
     *
     * This operation returns the ConnectorProfiles specified connector_id.
     *
     * @param connector_id ID of the ConnectorProfile
     * @return the ConnectorProfile identified by the connector_id
     *
     * @endif
     */
    virtual ConnectorProfile* get_connector_profile(const char* connector_id);


    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の接続を行う
     *
     * 与えられた ConnectoionProfile によってこのPortと対応するピアPortの
     * 接続を確立する。
     * ConnectorProfile は Port 参照のシーケンスを持つ。
     * Port は ConnectionProfile を保持するとともに、ピア Port の connect()
     * を ConnectionProfile を引数として与えて呼び出し、双方向関連を確立する。
     *
     * @param connector_profile ConnectorProfile
     * @return ReturnCode_t オペレーションのリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation establishes connection between this port and the peer
     * ports according to given ConnectionProfile.
     * A ConnectorProfile has a sequence of port references.
     * This port stores the ConnectorProfile and calls the peer ports'
     * "connect()" operation with the ConnectorProfile to make a
     * bidirectional association.
     *
     * @param connector_profile The ConnectorProfile.
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t connect(ConnectorProfile& connector_profile);


    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の接続を解除する
     *
     * このオペレーションは接続確立時に接続に対して与えられる connector_id に
     * 対応するピア Port との接続を解除する。
     * Port は接続が解除されたことをピア Port に対して "disconnect()" を
     * 呼び出すことで通知する。このオペレーションは戻り値 ReturnCode_t を返す。
     *
     * @param connector_id ConnectorProfile の ID
     * @return ReturnCode_t オペレーションのリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation destroys connection between this port and the peer port
     * according to given id that is given when the connection established.
     * The port notifies that connection is destroyed to call peer ports
     * disconnect operation. This operation returns ReturnCode_t return codes.
     *
     * @param connector_id The ID of the ConnectorProfile.
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect(const char* connector_id);

    /*!
     * @if jp
     *
     * @brief [CORBA interface] Port の全接続を解除する
     *
     * このオペレーションはこの Port に関連した全ての接続を解除する。
     *
     * @return ReturnCode_t オペレーションのリターンコード
     *
     * @else
     *
     * @brief [CORBA interface] Connect the Port
     *
     * This operation destroys all connection channels owned by the Port.
     *
     * @return ReturnCode_t The return code of this operation.
     *
     * @endif
     */
    virtual ReturnCode_t disconnect_all();

    //============================================================
    // Local operations
    //============================================================

    /*!
     * @if jp
     *
     * @brief PortProfileを設定する
     *
     * Portが保持するPortProfileを上書きして新しいPortProfileを与える。
     * 既存のPortProfileは上書きされ内容は破棄される。
     * 新しい PortProfile の内容は適切に設定されていなければならない。
     *
     * @param profile 与える Port の PortProfile
     *
     * @else
     *
     * @brief Set a PortProfile to the Port
     *
     * This operation sets a PortProfile to the Port.
     * Existing PortProfile will be overwritten and deleted.
     * Given PortProfile to the Port should be configured in advance properly.
     *
     * @param profile The PortProfile to be set this Port
     *
     * @endif
     */
    void setProfile(const PortProfile& profile);


    /*!
     * @if jp
     *
     * @brief PortProfileを取得する
     *
     * Portが保持する PortProfile の const 参照を返す。
     *
     * @return この Port の PortProfile
     *
     * @else
     *
     * @brief Get the PortProfile of the Port
     *
     * This operation returns const reference of the PortProfile.
     *
     * @return the PortProfile of the Port
     *
     * @endif
     */
    const PortProfile& getProfile();
    

    /*!
     * @if jp
     *
     * @brief Port の名前を設定する
     *
     * Port の名前を設定する。この名前は Port が保持する PortProfile.name
     * に反映される。
     *
     * @param name Port の名前
     *
     * @else
     *
     * @brief Set the name of this Port
     *
     * This operation sets the name of this Port. The given Port's name is
     * applied to Port's PortProfile.name.
     *
     * @param name The name of this Port.
     *
     * @endif
     */
    void setName(const char* name);


    /*!
     * @if jp
     *
     * @brief Port の名前を取得する
     *
     * Port の名前を取得する。
     * この名前は Port が保持する PortProfile.name である。
     *
     * @return Port の名前
     *
     * @else
     *
     * @brief Get the name of this Port
     *
     * This operation returns the name of this Port.
     * The returned Port's name is same as PortProfile.name.
     *
     * @return The name of this Port.
     *
     * @endif
     */
    const char* getName();


    /*!
     * @if jp
     *
     * @brief Port の PortInterfaceProfileList を設定する
     *
     * PortProfile は Port が所有するインターフェースのプロファイルのリスト
     * PortInterfaceProfileList を保持している。
     * このオペレーションはこの Port の PortInterfaceProfileList を設定する。
     * 設定される PortInterfaceProfileList は事前に適切に設定されていなければ
     * ならない。
     * 既存の PortProfile が所有する PortInterfaceProfileList は破棄される。
     *
     * @param if_profiles Port の PortInterfaceProfileList
     *
     * @else
     *
     * @brief Set the PortInterfaceProfileList of this Port
     *
     * PortProfile has a list of profile information of interfaces that are
     * owned by the Port as PortInterfaceProfileList.
     * This operation sets the PortInterfaceProfileList of this Port.
     * The given PortInterfaceProfileList should be configured in advance properly.
     * The existing PortInterfaceProfileList of the PortProfile will be deleted.
     *
     * @param if_profiles The PortInterfaceProfileList of this Port
     *
     * @endif
     */
    void setInterfaceProfiles(PortInterfaceProfileList& if_profiles);


    /*!
     * @if jp
     *
     * @brief Port の PortInterfaceProfile を追加する
     *
     * このオペレーションはこの Port の PortInterfaceProfile を追加する。
     * 設定される PortInterfaceProfile は事前に適切に設定されていなければならない。
     * 与えられた PortInterfaceProfile は PortProfile の PortInterfaceProfileList の
     * 最後に追加される。
     *
     * @param if_profile Port の PortInterfaceProfile 
     *
     * @else
     *
     * @brief Add the PortInterfaceProfile of this Port
     *
     * This operation sets the PortInterfaceProfile of this Port.
     * The given PortInterfaceProfile should be configured in advance properly.
     * The given PortInterfaceProfile will be added to the end of the
     * IntefaceProfileList that is owned by the PortProfile.
     *
     * @param if_profile The PortInterfaceProfile of this Port
     *
     * @endif
     */
    void addInterfaceProfile(PortInterfaceProfile& if_profile);


    /*!
     * @if jp
     *
     * @brief Port の PortInterfaceProfileList を取得する
     *
     * このオペレーションはこの Port の PortProfile が保持する 
     * PortInterfaceProfile のリスト PortInterfaceProfileList を返す。
     *
     * @return この Port のPortProfile が保持する PortInterfaceProfileList
     *
     * @else
     *
     * @brief get the InterfaceprofileList of this Port
     *
     * This operation return the PortInterfaceProfileList of the PortProfile
     * that is owned by this Port.
     *
     * @return The PortInterfaceProfileList of this Port's PortProfile
     *
     * @endif
     */
    PortInterfaceProfileList getInterfaceProfiles();


    /*!
     * @if jp
     *
     * @brief Port の PortInterfaceProfile を取得する
     *
     * このオペレーションは Port の PortProfile が保持する PortInterfaceProfile
     * の中から、与えられた name を持つ PortInterfaceProfile を返す。
     *
     * @return 名前 name を持つ PortInterfaceProfile
     *
     * @else
     *
     * @brief Get the Interfaceprofile of this Port
     *
     * This operation returns the PortInterfaceProfile that is specified by the
     * given name from PortProfile of this Port.
     *
     * @return The PortInterfaceProfile named "name".
     *
     * @endif
     */
    PortInterfaceProfile getInterfaceProfile(const char* name);


    /*!
     * @if jp
     *
     * @brief Port のオブジェクト参照を設定する
     *
     * このオペレーションは Port の PortProfile にこの Port 自身の
     * オブジェクト参照を設定する。
     *
     * @param この Port のオブジェクト参照
     *
     * @else
     *
     * @brief Set the object reference of this Port
     *
     * This operation sets the object reference itself
     * to the Port's PortProfile.
     *
     * @param The object reference of this Port.
     *
     * @endif
     */
    void setPortRef(Port_ptr port_ref);


    /*!
     * @if jp
     *
     * @brief Port のオブジェクト参照を取得する
     *
     * このオペレーションは Port の PortProfile が保持している
     * この Port 自身のオブジェクト参照を取得する。
     *
     * @return この Port のオブジェクト参照
     *
     * @else
     *
     * @brief Get the object reference of this Port
     *
     * This operation returns the object reference
     * that is stored in the Port's PortProfile.
     *
     * @return The object reference of this Port.
     *
     * @endif
     */
    Port_ptr getPortRef();


    /*!
     * @if jp
     *
     * @brief ConnectorProfile を追加する
     *
     * このオペレーションは Port の PortProfile が保持している
     * ConnectorProfileList に与えられた ConnectorProfile を追加する。
     *
     * @param PortProfile の ConnectorProfileList に追加する ConnectorProfile
     *
     * @else
     *
     * @brief Set the ConnectorProfile to PortProfile
     *
     * This operation sets the ConnectorProfile to the ConnectorProfileList
     * that is owned by the PortProfile.
     *
     * @param The ConnectorProfile to be added to ConnectorProfileList.
     *
     * @endif
     */
    void addConnectorProfile(ConnectorProfile conn_prof);

    /*!
     * @if jp
     *
     * @brief ConnectorProfile を削除する
     *
     * このオペレーションは Port の PortProfile が保持している
     * ConnectorProfileList のうち与えられた id を持つ ConnectorProfile
     * を削除する。
     *
     * @param id 削除する ConnectorProfile の id
     *
     * @else
     *
     * @brief Delete the ConnectorProfile
     *
     * This operation deletes a ConnectorProfile specified by id from
     * ConnectorProfileList owned by PortProfile of this Port.
     *
     * @param id The id of the ConnectorProfile to be deleted.
     *
     * @endif
     */
    void eraseConnectorProfile(const char* id);


    /*!
     * @if jp
     *
     * @brief ConnectorProfileList を取得する
     *
     * このオペレーションは Port の PortProfile が保持している
     * ConnectorProfileList の const 参照を取得する。
     *
     * @return ConnectorProfileList
     *
     * @else
     *
     * @brief Get ConnectorProfileList
     *
     * This operation returns the ConnectorProfileList owned by
     * PortProfile of this Port.
     *
     * @return ConnectorProfileList
     *
     * @endif
     */
    const ConnectorProfileList& getConnectorProfileList();


    /*!
     * @if jp
     *
     * @brief ConnectorProfile を取得する
     *
     * このオペレーションは Port の PortProfile が保持している
     * ConnectorProfile のうち id を持つものを返す。
     *
     * @return ConnectorProfile
     *
     * @else
     *
     * @brief Get ConnectorProfile
     *
     * This operation returns the ConnectorProfile specified by given id
     * from PortProfile of this Port.
     *
     * @return ConnectorProfileList
     *
     * @endif
     */
    const ConnectorProfile& getConnectorProfile(const char* id);


    /*!
     * @if jp
     *
     * @brief Port の owner の RTObject を指定する
     *
     * このオペレーションは Port の PortProfile.owner を設定する。
     *
     * @param owner この Port を所有する RTObject の参照
     *
     * @else
     *
     * @brief Set the owner RTObject of the Port
     *
     * This operation sets the owner RTObject of this Port.
     *
     * @param owner The owner RTObject's reference of this Port
     *
     * @endif
     */
    void setOwner(RTObject_ptr owner);


    /*!
     * @if jp
     *
     * @brief Port の owner の RTObject を取得する
     *
     * このオペレーションは Port の PortProfile.owner を取得する。
     *
     * @return この Port を所有する RTObject の参照
     *
     * @else
     *
     * @brief Get the owner RTObject of the Port
     *
     * This operation gets the owner RTObject of this Port.
     *
     * @return The owner RTObject's reference of this Port
     *
     * @endif
     */
    RTObject_ptr getOwner();


    /*!
     * @if jp
     *
     * @brief PortProfile の property を設定する
     *
     * このオペレーションは Port の PortProfile.properties を設定する。
     *
     * @param properties PortProfile.properties
     *
     * @else
     *
     * @brief Set the properties of the PortProfile
     *
     * This operation sets the properties of the PortProfile.properties.
     *
     * @param The properties to be set to the PortProfile.properties.
     *
     * @endif
     */
    void setProperties(const NVList& properties);


    /*!
     * @if jp
     *
     * @brief PortProfile の property を取得する
     *
     * このオペレーションは Port の PortProfile.properties を返す。
     *
     * @return PortProfile.properties
     *
     * @else
     *
     * @brief Get the properties of the PortProfile
     *
     * This operation returns the properties of the PortProfile.properties.
     *
     * @return The properties of the PortProfile.properties.
     *
     * @endif
     */
    const NVList& getProperties();

    /*!
     * @if jp
     *
     * @brief UUIDを生成する
     *
     * このオペレーションは UUID を生成する。
     *
     * @return uuid
     *
     * @else
     *
     * @brief Get the UUID
     *
     * This operation generates UUID.
     *
     * @return uuid
     *
     * @endif
     */
    const std::string getUUID() const;
    
  protected:
    PortProfile m_profile;
    ACE_Recursive_Thread_Mutex m_profile_mutex;
    typedef ACE_Guard<ACE_Recursive_Thread_Mutex> Guard;

    //============================================================
    // Functor
    //============================================================
    /*!
     * @if jp
     * @brief instance_name を持つ PortInterfaceProfile を探す Functor
     * @else
     * @brief A functor to find a PortInterfaceProfile named instance_name
     * @endif
     */
    struct if_name;


    /*!
     * @if jp
     * @brief id を持つ ConnectorProfile を探す Functor
     * @else
     * @brief A functor to find a ConnectorProfile named id
     * @endif
     */
    struct find_conn_id;


    /*!
     * @if jp
     * @brief Port の接続を行う Functor
     * @else
     * @brief A functor to connect Ports
     * @endif
     */
    struct connect_func;


    /*!
     * @if jp
     * @brief Port の接続解除を行う Functor
     * @else
     * @brief A functor to disconnect Ports
     * @endif
     */
    struct disconnect_func;
 

    /*!
     * @if jp
     * @brief Port の全接続解除を行う Functor
     * @else
     * @brief A functor to disconnect all Ports
     * @endif
     */
    struct disconnect_all_func;

    friend class disconnect_all_func;

  };
};
#endif // PortBase_h
