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
 * $Id: ConfigAdmin.h,v 1.3.2.1 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/24 01:27:22  n-ando
 * Bug fix.
 *
 * Revision 1.2  2007/04/23 07:28:08  n-ando
 * Some functions were added.
 *
 * Revision 1.1  2007/04/23 04:51:21  n-ando
 * COnfiguration Admin class.
 *
 */

#ifndef ConfigAdmin_h
#define ConfigAdmin_h

#include <rtm/Properties.h>
#include <rtm/StringUtil.h>
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
     * @endif
     */
    virtual bool update(const char* val) = 0;
    
    /*!
     * @if jp
     * @brief  コンフィギュレーション名
     * @else
     * @endif
     */
    const char* name;
    
    /*!
     * @if jp
     * @brief  文字列形式のデフォルト値
     * @else
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
     * @endif
     */
    Config(const char* name, VarType& var, const char* def_val,
	   TransFunc trans = stringTo)
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
     * @endif
     */
    VarType& m_var;
    
    /*!
     * @if jp
     * @brief  コンフィギュレーションパラメータ型文字列変換関数
     * @else
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
     * @endif
     */
    ConfigAdmin(RTC::Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * 仮想デストラクタ。
     *
     * @else
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
     * @endif
     */
    template <typename VarType>
    bool bindParameter(const char* param_name, VarType& var,
		       const char* def_val,
		       bool (*trans)(VarType&, const char*) = ::stringTo)
    {
      if (isExist(param_name)) return false;
      if (!::stringTo(var, def_val)) return false;
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
     * @param config_set コンフィギュレーション名称。｢.｣区切りで最後の要素を
     *                   除いた名前
     * @param config_param コンフィギュレーションセットの最後の要素名
     * 
     * @else
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
     * @endif
     */
    const std::vector<Properties*>& getConfigurationSets();
    
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
     * @endif
     */
    const Properties& getConfigurationSet(const char* config_id);
    
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
     * @endif
     */
    bool setConfigurationSetValues(const char* config_id,
				   const RTC::Properties& configuration_set);
    
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
     * @endif
     */
    const Properties& getActiveConfigurationSet();
    
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
     * @endif
     */
    bool addConfigurationSet(const Properties& configuration_set);
    
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

    RTC::Properties& m_configsets;
    RTC::Properties  m_emptyconf;
    std::vector<ConfigBase*> m_params;
    std::string m_activeId;
    bool m_active;
    bool m_changed;
    std::vector<std::string> m_newConfig;
  };
}; // namespace RTC
#endif // ConfigAdmin_h
