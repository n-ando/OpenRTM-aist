// -*- C++ -*-
/*!
 * @file SdoConfiguration.h
 * @brief RT component base class
 * @date $Date: 2007-04-23 04:58:21 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.h,v 1.7 2007-04-23 04:58:21 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  2007/01/24 16:03:58  n-ando
 * The ctor. was changed.
 *
 * Revision 1.5  2007/01/21 13:05:13  n-ando
 * A trivial fix.
 *
 * Revision 1.4  2006/11/08 20:00:21  n-ando
 * ConfigurationSet related interfaces are fixed.
 *
 * Revision 1.3  2006/10/30 08:05:45  n-ando
 * CORBA sequence operations were replaced by CORBA_SeqUtil functions.
 *
 * Revision 1.2  2006/10/17 10:13:15  n-ando
 * Small fixes.
 *
 * Revision 1.1  2006/09/11 18:14:01  n-ando
 * The first commit.
 *
 *
 */

#ifndef SdoConfiguration_h
#define SdoConfiguration_h

#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>

// CORBA header include
#include <rtm/RTC.h>

// local includes
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/ConfigAdmin.h>
#include <string>

// SdoConfiguration with SeqEx 159120
// SdoConfiguration with SeqUtil 114504 114224

namespace SDOPackage
{
  /*!
   * @if jp
   *
   * @class Configuration_impl
   * @brief SDO Configuration 実装クラス
   *
   * Configuration interface は Resource Data Model で定義されたデータの
   * 追加、削除等の操作を行うためのインターフェースである。
   * DeviceProfile, ServiceProfile, ConfigurationProfile および Organization
   * の変更を行うためのオペレーションを備えている。SDO の仕様ではアクセス制御
   * およびセキュリティに関する詳細については規定していない。
   * 
   * 複数の設定 (Configuration) を保持することにより、容易かつ素早くある設定
   * を反映させることができる。事前に定義された複数の設定を ConfigurationSets
   * および configuration profile として保持することができる。ひとつの
   * ConfigurationSet は特定の設定に関連付けられた全プロパティ値のリストを、
   * ユニークID、詳細とともに持っている。これにより、各設定項目の詳細を記述し
   * 区別することができる。Configuration interface のオペレーションはこれら
   * ConfiguratioinSets の管理を支援する。
   *
   *
   * - ConfigurationSet: id, description, NVList から構成される1セットの設定
   * - ConfigurationSetList: ConfigurationSet のリスト
   * - Parameter: name, type, allowed_values から構成されるパラメータ定義。
   * - ActiveConfigurationSet: 現在有効なコンフィギュレーションの1セット。
   *
   * 以下、SDO仕様に明記されていないもしくは解釈がわからないため独自解釈
   *
   * 以下の関数は ParameterList に対して処理を行う。
   * - get_configuration_parameters()
   *
   * 以下の関数はアクティブなConfigurationSetに対する処理を行う
   * - get_configuration_parameter_values()
   * - get_configuration_parameter_value()
   * - set_configuration_parameter()
   *
   * 以下の関数はConfigurationSetListに対して処理を行う
   * - get_configuration_sets()
   * - get_configuration_set()
   * - set_configuration_set_values()
   * - get_active_configuration_set()
   * - add_configuration_set()
   * - remove_configuration_set()
   * - activate_configuration_set()
   *
   * @else
   *
   * @class Configuration_impl
   * @brief Configuration implementation class
   *
   * Configuration interface provides operations to add or remove data
   * specified in resource data model. These operations provide functions to
   * change DeviceProfile, ServiceProfile, ConfigurationProfile, and
   * Organization. This specification does not address access control or
   * security aspects. Access to operations that modifies or removes profiles
   * should be controlled depending upon the application.
   *
   * Different configurations can be stored for simple and quick activation.
   * Different predefined configurations are stored as different
   * ConfigurationSets or configuration profile. A ConfigurationSet stores the
   * value of all properties assigned for the particular configuration along
   * with its unique id and description to identify and describe the
   * configuration respectively. Operations in the configuration interface
   * help manage these ConfigurationSets.
   *
   * @endif
   */
  class Configuration_impl
    : public virtual POA_SDOPackage::Configuration,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    Configuration_impl(RTC::ConfigAdmin& configAdmin);
    virtual ~Configuration_impl();

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO の DeviceProfile をセットする
     *
     * このオペレーションは SDO の DeviceProfile をセットする。SDO が
     * DeviceProfile を保持している場合は新たな DeviceProfile を生成し、
     * DeviceProfile をすでに保持している場合は既存のものと置き換える。
     *
     * @param dProfile SDO に関連付けられる DeviceProfile。
     * @return オペレーションが成功したかどうかを返す。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InvalidParameter 引数 "dProfile" が null である。
     * @exception InternalError 内部的エラーが発生した。
     * 
     * @else
     *
     * @brief [CORBA interface] Set DeviceProfile of SDO
     *
     * This operation sets the DeviceProfile of an SDO. If the SDO does not
     * have DeviceProfile, the operation will create a new DeviceProfile,
     * otherwise it will replace the existing DeviceProfile.
     *
     * @param dProfile The device profile that is to be assigned to this SDO.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "dProfile" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_device_profile(const DeviceProfile& dProfile)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] SDO の ServiceProfile のセット
     *
     * このオペレーションはこの Configuration interface を所有する対象 SDO の
     * ServiceProfile を設定する。もし引数の ServiceProfile の id が空であれば
     * 新しい ID が生成されその ServiceProfile を格納する。もし id が空で
     * なければ、SDO は同じ id を持つ ServiceProfile を検索する。
     * 同じ id が存在しなければこの ServiceProfile を追加し、id が存在すれば
     * 上書きをする。
     *
     * @param sProfile 追加する ServiceProfile
     * @return オペレーションが成功したかどうかを返す。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception InvalidParameter 引数 "sProfile" が nullである。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Set SDO's ServiceProfile
     *
     * This operation adds ServiceProfile to the target SDO that navigates this
     * Configuration interface. If the id in argument ServiceProfile is null,
     * new id is created and the ServiceProfile is stored. If the id is not
     * null, the target SDO searches for ServiceProfile in it with the same id.
     * It adds the ServiceProfile if not exist, or overwrites if exist.
     *
     * @param sProfile ServiceProfile to be added.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument "sProfile" is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_service_profile(const ServiceProfile& sProfile)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization の追加
     *
     * このオペレーションは Organization object のリファレンスを追加する。
     *
     * @param org 追加する Organization
     * @return オペレーションが成功したかどうかを返す。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InvalidParameter 引数 "organization" が null である。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Add Organization
     *
     * This operation adds reference of an Organization object.
     *
     * @param org Organization to be added.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InvalidParameter The argument “organization” is null.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean add_organization(Organization_ptr org)
      throw (InvalidParameter, NotAvailable, InternalError);
    
    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ServiceProfile の削除
     *
     * このオペレーションはこの Configuration interface を持つ SDO の
     * Service の ServiceProfile を削除する。削除する ServiceProfile
     * は引数により指定される。
     *
     * @param id 削除する ServcieProfile の serviceID。
     * @return オペレーションが成功したかどうかを返す。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception InvalidParameter 引数 "id" が null である。もしくは "id" に
     *                             関連付けられた ServiceProfile が存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Remove ServiceProfile
     *
     * This operation removes ServiceProfile object to the SDO that has this
     * Configuration interface. The ServiceProfile object to be removed is
     * specified by argument.
     *
     * @param id serviceID of a ServiceProfile to be removed.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter The argument "sProfile" is null, or if the
     *          object that is specified by argument "sProfile" does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_service_profile(const char* id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organization の参照の削除
     *
     * このオペレーションは Organization の参照を削除する。
     *
     * @param organization_id 削除する Organization の一意な id。
     * @return オペレーションが成功したかどうかを返す。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception InvalidParameter 
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Remove the reference of Organization 
     *
     * This operation removes the reference of an Organization object.
     *
     * @param organization_id Unique id of the organization to be removed.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter The argument "organizationID" is null,
     *            or the object which is specified by argument "organizationID"
     *            does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_organization(const char* organization_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] 設定パラメータのリストの取得
     *
     * このオペレーションは configuration parameter のリストを返す。
     * SDO が設定可能なパラメータを持たなければ空のリストを返す。
     *
     * @return 設定を特徴付けるパラメータ定義のリスト。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Getting a list of configuration parameter
     *
     * This operation returns a list of Parameters. An empty list is returned
     * if the SDO does not have any configurable parameter.
     *
     * @return The list with definitions of parameters characterizing the
     *          configuration.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ParameterList* get_configuration_parameters()
      throw (NotAvailable, InternalError);

     /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration parameter の値のリストの取得
     *
     * このオペレーションは configuration パラメータおよび値を返す。
     *
     * @return 全ての configuration パラメータと値のリスト。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Getting value list of configuration parameter
     *
     * This operation returns all configuration parameters and their values.
     *
     * @return List of all configuration parameters and their values.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual NVList* get_configuration_parameter_values()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration parameter の値の取得
     *
     * このオペレーションは引数 "name" で指定されたパラメータ値を返す。
     *
     * @param name 値を要求するパラメータの名前。
     * @return 指定されたパラメータの値。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Getting value of configuration parameter
     *
     * This operation returns a value of parameter that is specified by
     * argument "name."
     *
     * @param Name of the parameter whose value is requested.
     * @return The value of the specified parameter.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Any* get_configuration_parameter_value(const char* name)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Configuration パラメータの変更
     *
     * このオペレーションは "name" で指定したパラメータの値を "value" に
     * 変更する。
     *
     * @param name 変更したいパラメータの名前。
     * @param value 変更したいパラメータの値。
     * @return オペレーションが成功したかどうかを返す。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Modify the parameter value
     *
     * This operation sets a parameter to a value that is specified by argument
     * "value." The parameter to be modified is specified by argument " name."
     *
     * @param name The name of parameter to be modified.
     * @param value New value of the specified parameter.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter if arguments ("name" and/or "value") is
     *            null, or if the parameter that is specified by the argument
     *            "name" does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean set_configuration_parameter(const char* name,
						       const CORBA::Any& value)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet リストの取得 
     *
     * このオペレーションは ConfigurationProfile が持つ ConfigurationSet の
     * リストを返す。 SDO が ConfigurationSet を持たなければ空のリストを返す。
     *
     * @return 保持している ConfigurationSet のリストの現在値。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Getting list of ConfigurationSet
     *
     * This operation returns a list of ConfigurationSets that the
     * ConfigurationProfile has. An empty list is returned if the SDO does not
     * have any ConfigurationSets.
     * This operation returns a list of all ConfigurationSets of the SDO.
     * If no predefined ConfigurationSets exist, then empty list is returned.
     *
     * @return The list of stored configuration with their current values.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ConfigurationSetList* get_configuration_sets()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet の取得
     *
     * このオペレーションは引数で指定された ConfigurationSet の ID に関連
     * 付けられた ConfigurationSet を返す。
     *
     * @param config_id ConfigurationSet の識別子。
     * @return 引数により指定された ConfigurationSet。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception InvalidParameter "config_id" が null か、指定された
     *            ConfigurationSet が存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Getting a ConfigurationSet
     *
     * This operation returns the ConfigurationSet specified by the parameter
     * configurationSetID.
     *
     * @param config_id Identifier of ConfigurationSet requested.
     * @return The configuration set specified by the parameter config_id.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ConfigurationSet* get_configuration_set(const char* config_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet をセットする
     *
     * このオペレーションは指定された id の ConfigurationSet を更新する。
     *
     * @param configu_id 変更する ConfigurationSet の ID。
     * @param configuration_set 変更する ConfigurationSet そのもの。
     * @return ConfigurationSet が正常に更新できた場合は true。
     *         そうでなければ false を返す。
     * @exception InvalidParameter config_id が null か ConfigurationSet
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Set ConfigurationSet
     *
     * This operation modifies the specified ConfigurationSet of an SDO.
     *
     * ※ パラメータの数が spec と IDL で異なる！！！
     * @param configu_id The ID of ConfigurationSet to be modified.
     * @param configuration_set ConfigurationSet to be replaced.
     * @return A flag indicating if the ConfigurationSet was modified 
     *         successfully. "true" - The ConfigurationSet was modified
     *         successfully. "false" - The ConfigurationSet could not be
     *         modified successfully.
     * @exception InvalidParameter if the parameter 'configurationSetID' is
     *            null or if there is no ConfigurationSet stored with such id.
     *            This exception is also raised if one of the attributes
     *            defining ConfigurationSet is not valid.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    set_configuration_set_values(const char* config_id,
				 const ConfigurationSet& configuration_set)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] アクティブな ConfigurationSet を取得する
     *
     * このオペレーションは当該SDOの現在アクティブな ConfigurationSet を返す。
     * (もしSDOの現在の設定が予め定義された ConfigurationSet により設定されて
     * いるならば。)
     * ConfigurationSet は以下の場合にはアクティブではないものとみなされる。
     *
     * - 現在の設定が予め定義された ConfigurationSet によりセットされていない、
     * - SDO の設定がアクティブになった後に変更された、
     * - SDO を設定する ConfigurationSet が変更された、
     * 
     * これらの場合には、空の ConfigurationSet が返される。
     *
     * @return 現在アクティブな ConfigurationSet。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Get active ConfigurationSet
     *
     * This operation returns the current active ConfigurationSet of an
     * SDO (i.e., if the current configuration of the SDO was set using
     * predefined configuration set).
     * ConfigurationSet cannot be considered active if the:
     *
     * - current configuration of the SDO was not set using any predefined
     *   ConfigurationSet, or
     * - configuration of the SDO was changed after it has been active, or
     * - ConfigurationSet that was used to configure the SDO was modified.
     *
     * Empty ConfigurationSet is returned in these cases.
     *
     * @return The active ConfigurationSet.
     * @exception SDONotExists The target SDO does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual ConfigurationSet* get_active_configuration_set()
      throw (NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet を追加する
     *
     * ConfigurationProfile に ConfigurationSet を追加するオペレーション。
     *
     * @param configuration_set 追加される ConfigurationSet。
     * @return オペレーションが成功したかどうか。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Add ConfigurationSet
     *
     * This operation adds a ConfigurationSet to the ConfigurationProfile.
     *
     * @param configuration_set The ConfigurationSet that is added.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter If the argument "configurationSet" is null,
     *            or if one of the attributes defining "configurationSet" is
     *            invalid, or if the specified identifier of the configuration
     *            set already exists.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean
    add_configuration_set(const ConfigurationSet& configuration_set)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet を削除する
     *
     * ConfigurationProfile から ConfigurationSet を削除する。
     *
     * @param configu_id 削除する ConfigurationSet の id。
     * @return オペレーションが成功したかどうか。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception InvalidParameter 引数 "configurationSetID" が null である、
     *            もしくは、引数で指定された ConfigurationSet が存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Remove ConfigurationSet
     *
     * This operation removes a ConfigurationSet from the ConfigurationProfile.
     *
     * @param config_id The id of ConfigurationSet which is removed.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter The arguments "configurationSetID" is null,
     *            or if the object specified by the argument
     *            "configurationSetID" does not exist.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean remove_configuration_set(const char* config_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] ConfigurationSet のアクティブ化
     *
     * ConfigurationProfile に格納された ConfigurationSet のうち一つを
     * アクティブにする。
     * このオペレーションは特定の ConfigurationSet をアクティブにする。
     * すなわち、SDO のコンフィギュレーション・プロパティがその格納されている
     * ConfigurationSet により設定されるプロパティの値に変更される。
     * 指定された ConfigurationSet の値がアクティブ・コンフィギュレーション
     * にコピーされるということを意味する。
     *
     * @param config_id アクティブ化する ConfigurationSet の id。
     * @return オペレーションが成功したかどうか。
     * @exception SDONotExists ターゲットのSDOが存在しない。
     * @exception InvalidParameter 引数 "config_id" が null である、もしくは
     *            引数で指定された ConfigurationSet が存在しない。
     * @exception NotAvailable SDOは存在するが応答がない。
     * @exception InternalError 内部的エラーが発生した。
     * @else
     *
     * @brief [CORBA interface] Activate ConfigurationSet
     *
     * This operation activates one of the stored ConfigurationSets in the
     * ConfigurationProfile.
     * This operation activates the specified stored ConfigurationSets.
     * This means that the configuration properties of the SDO are changed as
     * the values of these properties specified in the stored ConfigurationSet.
     * In other words, values of the specified ConfigurationSet are now copied
     * to the active configuration.
     *
     * @param Identifier of ConfigurationSet to be activated.
     * @return If the operation was successfully completed.
     * @exception SDONotExists The target SDO does not exist.
     * @exception InvalidParameter if the argument ("configID") is null or
     *            there is no configuration set with identifier specified by
     *            the argument.
     * @exception NotAvailable The target SDO is reachable but cannot respond.
     * @exception InternalError The target SDO cannot execute the operation
     *                          completely due to some internal error.
     * @endif
     */
    virtual CORBA::Boolean activate_configuration_set(const char* config_id)
      throw (InvalidParameter, NotAvailable, InternalError);

    // end of CORBA interface definition
    //============================================================

    Configuration_ptr getObjRef();

    const DeviceProfile getDeviceProfile();

    const ServiceProfileList getServiceProfiles();

    const ServiceProfile getServiceProfile(const char* id);
    
    const OrganizationList getOrganizations();

  protected:
    const std::string getUUID() const;

    Configuration_var m_objref;

    typedef ACE_Guard<ACE_Thread_Mutex> Guard;
    /*!
     * @if jp
     * @brief Lock 付き SDO DeviceProfile
     * @else
     * @brief SDO DeviceProfile with mutex lock
     * @endif
     */
    DeviceProfile m_deviceProfile;
    ACE_Thread_Mutex m_dprofile_mutex;

    /*!
     * @if jp
     * @brief SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList
     * @endif
     */
    ServiceProfileList m_serviceProfiles;
    ACE_Thread_Mutex m_sprofile_mutex;

    /*!
     * @if jp
     * @brief SDO ParameterList
     * @else
     * @brief SDO ParameterList
     * @endif
     */
    /*
    struct Parameter
    {
      string         name;
      TypeCode  type;
      AllowedValues allowed_values;
    };
    */
    ParameterList m_parameters;
    ACE_Thread_Mutex m_params_mutex;

    /*!
     * @if jp
     * @brief SDO ConfigurationSetList
     * @else
     * @brief SDO ConfigurationSetList
     * @endif
     */
    /*
      struct ConfigurationSet
      {
      string id;
      string description;
      NVList configuration_data;
      };
    */
    RTC::ConfigAdmin& m_configsets;
    ACE_Thread_Mutex m_config_mutex;

    /*!
     * @if jp
     * @brief SDO OrganizationList
     * @else
     * @brief SDO OrganizationList
     * @endif
     */
    OrganizationList m_organizations;
    ACE_Thread_Mutex m_org_mutex;

    /*!
     * @if jp
     * @brief アクティブな ConfigurationSet
     * @else
     * @brief Active ConfigurationSet id
     * @endif
     */

    struct nv_name
    {
      nv_name(const char* name) : m_name(name) {};
      bool operator()(const NameValue& nv)
      {
	return m_name == std::string(nv.name);
      }
      std::string m_name;
    };


    // functor for ServiceProfile
    struct service_id
    {
      service_id(const char* id) : m_id(id) {};
      bool operator()(const ServiceProfile& s)
      {
	std::string id(s.id);
	return m_id == id;
      }
      const std::string m_id;
    };

    // functor for Organization
    struct org_id
    {
      org_id(const char* id) : m_id(id) {};
      bool operator()(const Organization_ptr& o)
      {
	std::string id(o->get_organization_id());
	return m_id == id;
      }
      const std::string m_id;
    };
    
    // functor for ConfigurationSet
    struct config_id
    {
      config_id(const char* id) :  m_id(id) {};
      bool operator()(const ConfigurationSet& c)
      {
	std::string id(c.id);
	return m_id == id;
      }
      const std::string m_id;
    };

  };

}; // namespace SDOPackage

#endif // SdoConfiguration_h
