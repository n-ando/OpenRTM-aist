// -*- C++ -*-
/*!
 * @file ConfigAdmin.h
 * @brief Configuration Administration classes
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef ConfigAdmin_h
#define ConfigAdmin_h

#include <coil/Properties.h>
#include <coil/stringutil.h>
#include <string>
#include <vector>
#include <iostream>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント
 *
 * @else
 *
 * @namespace RTC
 *
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  //============================================================
  // ConfigBase class
  //============================================================
  /*!
   * @if jp
   * @class ConfigBase
   * @brief ConfigBase 抽象クラス
   * 
   * 各種コンフィギュレーション情報を保持するための抽象クラス。
   * 具象コンフィギュレーションクラスは、以下の純粋仮想関数の実装を提供しなけれ
   * ばならない。
   *
   * publicインターフェースとして以下のものを提供する。
   * - update(): コンフィギュレーションパラメータ値の更新
   *
   * @since 0.4.0
   *
   * @else
   * @class ConfigBase
   * @brief ConfigBase abstract class
   *
   * This is the abstract interface class to hold various configuration 
   * information.
   * Concrete configuration classes must implement the following pure virtual
   * functions.
   *
   * This class provides public interface as follows.
   * - update(): update configuration parameter value
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ConfigBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     * 
     * コンストラクタ
     *
     * @param name_ コンフィギュレーション名
     * @param def_val 文字列形式のデフォルト値
     * 
     * @else
     *
     * @brief Constructer
     *
     * Constructer
     *
     * @param name_ Configuration name
     * @param def_val Default value in string format
     *
     * @endif
     */
    ConfigBase(const char* name_, const char* def_val)
      : name(name_), default_value(def_val) {}
    
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * 仮想デストラクタ。
     *
     * @else
     *
     * @brief Virtual Destructor
     *
     * Virtual Destructor
     *
     * @endif
     */
    virtual ~ConfigBase(){};
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションパラメータ値更新用純粋仮想関数
     * 
     * コンフィギュレーション設定値でコンフィギュレーションパラメータを更新する
     * ための純粋仮想関数。
     *
     * @param val パラメータ値の文字列表現
     *
     * @return 設定結果
     * 
     * @else
     *
     * @brief Pure virtual function to update configuration parameter values
     * 
     * Pure virtual function to update configuration parameter 
     * by the configuration value.
     *
     * @param val The parameter values converted into character string format
     *
     * @return Result of the setup
     *
     * @endif
     */
    virtual bool update(const char* val) = 0;
    
    /*!
     * @if jp
     * @brief  コンフィギュレーション名
     * @else
     * @brief  Configuration name
     * @endif
     */
    const char* name;
    
    /*!
     * @if jp
     * @brief  文字列形式のデフォルト値
     * @else
     * @brief  Default value in string format
     * @endif
     */
    const char* default_value;
  };
  
  //============================================================
  // Config template class
  //============================================================
  /*!
   * @if jp
   * @class Config
   * @brief Config クラス
   * 
   * コンフィギュレーションパラメータの情報を保持するクラス。
   * \<VarType\>としてコンフィギュレーションのデータ型を指定する。
   * \<TransFunc\>として設定されたデータ型を文字列に変換する変換関数を指定する。
   *
   * @param VarType コンフィギュレーションパラメータ格納用変数
   * @param TransFunc 格納したデータ型を文字列に変換する変換関数
   *
   * @since 0.4.0
   *
   * @else
   * @class Config
   * @brief Config class
   * 
   * Class to hold the configuration parameter information.
   * Specify the data type of the configuration as \<VarType\>
   * Specify transformation function to convert data type set as \<TransFunc\>
   * into string format.
   *
   * @param VarType Cariable to hold configuration parameter
   * @param TransFunc Transformation function to transform the stored data 
   * type into string format.
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <typename VarType,
	    typename TransFunc = bool (*)(VarType&, const char*)>
  class Config
    : public ConfigBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     * 
     * コンストラクタ
     *
     * @param name コンフィギュレーションパラメータ名
     * @param var コンフィギュレーションパラメータ格納用変数
     * @param def_val 文字列形式のデフォルト値
     * @param trans 文字列形式変換関数
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     *
     * @param name Configuration parameter name
     * @param var Configuration parameter variable
     * @param def_val Default value in string format
     * @param trans Function to transform into string format
     *
     * @endif
     */
    Config(const char* name, VarType& var, const char* def_val,
	   TransFunc trans = coil::stringTo)
      : ConfigBase(name, def_val), m_var(var), m_trans(trans)
    {
    }
    
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * 仮想デストラクタ。
     *
     * @else
     *
     * @brief Virtual Destructor
     * 
     * Virtual Destructor.
     *
     * @endif
     */
    virtual ~Config(){}
    
    /*!
     * @if jp
     *
     * @brief バインドパラメータ値を更新
     * 
     * コンフィギュレーション設定値でコンフィギュレーションパラメータを更新する
     *
     * @param val パラメータ値の文字列表現
     *
     * @return 更新処理結果(更新成功:true，更新失敗:false)
     * 
     * @else
     *
     * @brief Update a bind parameter value
     * 
     * Update configuration paramater by the configuration value.
     *
     * @param val The parameter values converted into character string format
     *
     * @return Update result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool update(const char* val)
    {
      if ((*m_trans)(m_var, val)) return true;
      (*m_trans)(m_var, default_value);
      return false;
    }
    
  protected:
    /*!
     * @if jp
     * @brief  コンフィギュレーションパラメータ格納用変数
     * @else
     * @brief  Configuration parameter variable
     * @endif
     */
    VarType& m_var;
    
    /*!
     * @if jp
     * @brief  コンフィギュレーションパラメータ型文字列変換関数
     * @else
     * @brief  Transformation function to convert configuration parameter type 
     *         into string format.
     * @endif
     */
    TransFunc m_trans;
  };
  
  //============================================================
  // ConfigAdmin class
  //============================================================
  /*!
   * @if jp
   * @class ConfigAdmin
   * @brief ConfigAdmin クラス
   * 
   * 各種コンフィギュレーション情報を管理するクラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class ConfigAdmin
   * @brief ConfigAdmin class
   * 
   * Class to manage various configuration information.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class ConfigAdmin
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     * 
     * コンストラクタ
     *
     * @param prop 設定対象プロパティ名
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     *
     * @param prop The target property name for setup
     *
     * @endif
     */
    ConfigAdmin(coil::Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * 仮想デストラクタ。
     *
     * @else
     *
     * @brief Virtual Destructor
     * 
     * Virtual Destructor
     *
     * @endif
     */
    ~ConfigAdmin();
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションパラメータの設定
     * 
     * コンフィギュレーションパラメータと変数をバインドする
     * 指定した名称のコンフィギュレーションパラメータが既に存在する場合は
     * falseを返す。
     * \<VarType\>としてコンフィギュレーションパラメータのデータ型を指定する。
     *
     * @param param_name コンフィギュレーションパラメータ名
     * @param var コンフィギュレーションパラメータ格納用変数
     * @param def_val コンフィギュレーションパラメータデフォルト値
     * @param trans コンフィギュレーションパラメータ文字列変換用関数
     *
     * @return 設定結果(設定成功:true，設定失敗:false)
     * 
     * @else
     *
     * @brief Setup for configuration parameters
     * 
     * Bind configuration parameter to its variable.
     * Return false, if configuration parameter of specified name has already 
     * existed.
     * Specify the data type of the configuration as \<VarType\>.
     *
     * @param param_name Configuration parameter name
     * @param var Configuration parameter variable
     * @param def_val Default value of configuration parameter
     * @param trans Function to transform configuration parameter type into 
     *        string format
     *
     * @return Setup result (Successful:true, Failed:false)
     *
     * @endif
     */
    template <typename VarType>
    bool bindParameter(const char* param_name, VarType& var,
		       const char* def_val,
		       bool (*trans)(VarType&, const char*) = coil::stringTo)
    {
      if (isExist(param_name)) return false;
      if (!coil::stringTo(var, def_val)) return false;
      m_params.push_back(new Config<VarType>(param_name, var, def_val, trans));
      return true;
    }
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションパラメータの更新(ID指定)
     * 
     * 指定したIDのコンフィギュレーションセットに設定した値で、
     * コンフィギュレーションパラメータの値を更新する
     * 指定したIDのコンフィギュレーションセットが存在しない場合は、
     * 何もせずに終了する。
     *
     * @param config_set 設定対象のコンフィギュレーションセットID
     * 
     * @else
     *
     * @brief Update configuration parameter (By ID)
     * 
     * Update comfiguration parameter value by the value that 
     * set to a configuration set of specified ID.
     * Exit without doing anthing if a configuration set of specified ID 
     * does not exist.
     *
     * @param config_set The target configuration set's ID to setup
     *
     * @endif
     */
    void update(const char* config_set);
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションパラメータの更新(名称指定)
     * 
     * 指定したパスのコンフィギュレーションに設定した値で、
     * コンフィギュレーションパラメータの値を更新する
     *
     * @param config_set コンフィギュレーション名称。「.」区切りで最後の要素を
     *                   除いた名前
     * @param config_param コンフィギュレーションセットの最後の要素名
     * 
     * @else
     *
     * @brief Update the values of configuration parameters (By name)
     * 
     * Update the configuration value by the value that set to a configuration
     * set value of specified name.
     *
     * @param config_set configuration name. Name that each separates 
     *        by each comma(.) and excludes the last element.
     * @param config_param Last element name of configuration set
     *
     * @endif
     */
    void update(const char* config_set, const char* config_param);
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションパラメータの更新
     *        (アクティブコンフィギュレーションセット)
     * 
     * コンフィギュレーションセットが更新されている場合に、
     * 現在アクティブになっているコンフィギュレーションに設定した値で、
     * コンフィギュレーションパラメータの値を更新する。
     * この処理での更新は、アクティブとなっているコンフィギュレーションセットが
     * 存在している場合、前回の更新からコンフィギュレーションセットの内容が
     * 更新されている場合のみ実行される。
     *
     * @else
     *
     * @brief Update the values of configuration parameters
     *        (Active configuration set)
     * 
     * When configuration set is updated, update the configuration parameter 
     * value to the value that is set to the current active configuration.
     * This update will be executed, only when an active configuration set 
     * exists and the content of the configuration set has been updated from 
     * the last update.
     *
     * @endif
     */
    void update();
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションパラメータの存在確認
     * 
     * 指定した名称を持つコンフィギュレーションパラメータが存在するか確認する。
     *
     * @param name コンフィギュレーションパラメータ名称。
     *
     * @return 存在確認結果(パラメータあり:true，パラメータなし:false)
     *
     * @else
     *
     * @brief Check the existence of configuration parameters
     * 
     * Check the existence of configuration parameters of specified name.
     *
     * @param name Configuration parameter name
     *
     * @return Result of existance confirmation 
     *         (Parameters exist:true, else:false)
     *
     * @endif
     */
    bool isExist(const char* name);
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションパラメータの変更確認
     * 
     * コンフィギュレーションパラメータが変更されたか確認する。
     *
     * @return 変更確認結果(変更あり:true、変更なし:false)
     *
     * @else
     *
     * @brief Confirm to change configuration parameters
     * 
     * Confirm that configuration parameters have changed.
     *
     * @return Result of change confirmation
     *         (There is a change:true、No change:false)
     *
     * @endif
     */
    bool isChanged() {return m_changed;}
    
    /*!
     * @if jp
     *
     * @brief アクティブ・コンフィギュレーションセットIDの取得
     * 
     * 現在アクティブなコンフィギュレーションセットのIDを取得する。
     *
     * @return アクティブ・コンフィギュレーションセットID
     *
     * @else
     *
     * @brief Get ID of active configuration set
     * 
     * Get ID of the current active configuration set.
     *
     * @return The active configuration set ID
     *
     * @endif
     */
    const char* getActiveId() {return m_activeId.c_str();}
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションセットの存在確認
     * 
     * 指定したコンフィギュレーションセットが存在するか確認する。
     *
     * @param config_id 確認対象コンフィギュレーションセットID
     *
     * @return 存在確認結果(指定したConfigSetあり:true、なし:false)
     *
     * @else
     *
     * @brief Check the existence of configuration set
     * 
     * Check the existence of specified configuration set.
     *
     * @param config_id ID of target configuration set for confirmation
     *
     * @return Result of existence confirmation 
     *         (Specified ConfigSet exists:true, else:false)
     *
     * @endif
     */
    bool haveConfig(const char* config_id)
    {
      return (m_configsets.hasKey(config_id) == NULL) ? false : true;
    }
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションセットのアクティブ化確認
     * 
     * コンフィギュレーションセットがアクティブ化されているか確認する。
     *
     * @return 状態確認結果(アクティブ状態:true、非アクティブ状態:false)
     *
     * @else
     *
     * @brief Confirm to activate configuration set
     * 
     * Confirm that configuration set has been activated.
     *
     * @return Result of state confirmation
     *         (Active state:true, Inactive state:false)
     *
     * @endif
     */
    bool isActive()
    {
      return m_active;
    }
    //    const std::vector<Properties*>* getConfigurationParameterValues();
    //    const Properties* getConfigurationParameterValue(const char* name);
    //    bool setConfigurationParameter(const char* name, const char* value);
    
    /*!
     * @if jp
     *
     * @brief 全コンフィギュレーションセットの取得
     * 
     * 設定されている全コンフィギュレーションセットを取得する。
     *
     * @return 全コンフィギュレーションセット
     *
     * @else
     *
     * @brief Get all configuration sets
     * 
     * Get all specified configuration sets
     *
     * @return All configuration sets
     *
     * @endif
     */
    const std::vector<coil::Properties*>& getConfigurationSets();
    
    /*!
     * @if jp
     *
     * @brief 指定したIDのコンフィギュレーションセットの取得
     * 
     * IDで指定したコンフィギュレーションセットを取得する。
     * 指定したコンフィギュレーションセットが存在しない場合は、
     * 空のコンフィギュレーションセットを返す。
     *
     * @param config_id 取得対象コンフィギュレーションセットのID
     *
     * @return コンフィギュレーションセット
     *
     * @else
     *
     * @brief Get a configuration set by specified ID
     * 
     * Get a configuration set that was specified by ID
     * Return empty configuration set, if a configuration set of
     * specified ID doesn't exist.
     *
     * @param config_id ID of the target configuration set for getting
     *
     * @return The configuration set
     *
     * @endif
     */
    const coil::Properties& getConfigurationSet(const char* config_id);
    
    /*!
     * @if jp
     *
     * @brief 指定したプロパティのコンフィギュレーションセットへの追加
     * 
     * 指定したプロパティをIDで指定したコンフィギュレーションセットへ追加する。
     * 指定したIDと一致するコンフィギュレーションセットが存在しない場合は、
     * false を返す。
     *
     * @param config_id 追加対象コンフィギュレーションセットのID
     * @param configuration_set 追加するプロパティ
     *
     * @return 追加処理実行結果(追加成功:true、追加失敗:false)
     *
     * @else
     *
     * @brief Add to configuration set from specified property
     * 
     * Add specified property to configuration set that was specified by ID.
     * Return false if configuration set, that matches specified ID, 
     * doesn't exist.
     *
     * @param config_id ID of the target configuration set for add
     * @param configuration_set Property to add
     *
     * @return Add result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool setConfigurationSetValues(const char* config_id,
				   const coil::Properties& configuration_set);
    
    /*!
     * @if jp
     *
     * @brief アクティブ・コンフィギュレーションセットを取得
     * 
     * 現在アクティブとなっているコンフィギュレーションセットを取得する。
     * アクティブとなっているコンフィギュレーションセットが存在しない場合は、
     * 空のコンフィギュレーションセット を返す。
     *
     * @return アクティブ・コンフィギュレーションセット
     *
     * @else
     *
     * @brief Get the active configuration set
     * 
     * Get the current active configuration set.
     * Return empty configuration set, if an active configuration set 
     * doesn't exist.
     *
     * @return The active configuration set
     *
     * @endif
     */
    const coil::Properties& getActiveConfigurationSet();
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションセットに設定値を追加
     * 
     * コンフィギュレーションセットに設定値を追加する。
     *
     * @param configuration_set 追加するプロパティ
     *
     * @return 追加処理結果(追加成功:true、追加失敗:false)
     *
     * @else
     *
     * @brief Add the configuration value to configuration set
     * 
     * Add the configuration value to configuration set
     *
     * @param configuration_set Property to add
     *
     * @return Add Result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool addConfigurationSet(const coil::Properties& configuration_set);
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションセットの削除
     * 
     * 指定したIDのコンフィギュレーションセットを削除する。
     * 指定したIDのコンフィギュレーションセットが存在しない場合は、
     * falseを返す。
     *
     * @param config_id 削除対象コンフィギュレーションセットのID
     *
     * @return 削除処理結果(削除成功:true、削除失敗:false)
     *
     * @else
     *
     * @brief Remove the configuration set
     * 
     * Remove the configuration set of specified ID
     * Return empty configuration set, if a configuration set of
     * specified ID doesn't exist.
     *
     * @param config_id ID of the target configuration set for remove
     *
     * @return Remove result (Successful:true, Failed:false)
     *
     * @endif
     */
    bool removeConfigurationSet(const char* config_id);
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションセットのアクティブ化
     * 
     * 指定したIDのコンフィギュレーションセットをアクティブ化する。
     * 指定したIDのコンフィギュレーションセットが存在しない場合は、
     * falseを返す。
     *
     * @param config_id 削除対象コンフィギュレーションセットのID
     *
     * @return アクティブ処理結果(成功:true、失敗:false)
     *
     * @else
     *
     * @brief Activate the configuration set
     * 
     * Activate the configuration set of specified ID
     * Return empty configuration set, if a configuration set of
     * specified ID doesn't exist.
     *
     * @param config_id ID of the target configuration set for remove
     *
     * @return Activate result (Remove success:true、Remove failure:false)
     *
     * @endif
     */
    bool activateConfigurationSet(const char* config_id);
    
  private:
    ConfigAdmin(const ConfigAdmin& ca) : m_configsets(ca.m_configsets) {};
    ConfigAdmin& operator=(const ConfigAdmin& ca){return *this;};
    
    struct find_conf
    {
      std::string m_name;
      find_conf(const char* name) : m_name(name) {};
      bool operator()(ConfigBase* conf)
      {
	return m_name == conf->name;
      }
    };
    
    coil::Properties& m_configsets;
    coil::Properties  m_emptyconf;
    std::vector<ConfigBase*> m_params;
    std::string m_activeId;
    bool m_active;
    bool m_changed;
    std::vector<std::string> m_newConfig;
  };
}; // namespace RTC
#endif // ConfigAdmin_h
