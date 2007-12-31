// -*- C++ -*-
/*!
 * @file NamingManager.h
 * @brief naming Service helper class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NamingManager.h,v 1.3.2.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:37:48  n-ando
 * getObjects() function was added.
 *
 * Revision 1.2  2007/04/13 18:08:42  n-ando
 * Some changes for NameServers rebinding and objects rebinding.
 *
 * Revision 1.1  2006/11/04 21:11:44  n-ando
 * NamingManager was introduced to support multiple name server.
 *
 */
#ifndef NamingManager_h
#define NamingManager_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  class Manager;
  /*!
   * @if jp
   *
   * @brief NamingService 管理用抽象クラス
   *
   * NamingServer 管理用抽象インターフェースクラス。
   * 具象管理クラスは、以下の純粋仮想関数の実装を提供しなければならない。
   * - bindObject() : 指定したオブジェクトのNamingServiceへのバインド
   * - unbindObject() : 指定したオブジェクトのNamingServiceからのアンバインド
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class NamingBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * @else
     *
     * @endif
     */
    NamingBase() {};
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~NamingBase() {};
    
    /*!
     * @if jp
     *
     * @brief 指定したオブジェクトをNamingServiceへバインドする純粋仮想関数
     *
     * @param name バインド時の名称
     * @param rtobj バインド対象オブジェクト
     *
     * @else
     *
     * @endif
     */
    virtual void bindObject(const char* name, const RTObject_impl* rtobj) = 0;
    
    /*!
     * @if jp
     *
     * @brief 指定したオブジェクトをNamingServiceからアンバインドするための
     *        純粋仮想関数
     *
     * @param name アンバインド対象オブジェクト
     *
     * @else
     *
     * @endif
     */
    virtual void unbindObject(const char* name) = 0;
  };
  
  /*!
   * @if jp
   *
   * @brief CORBA 用 NamingServer 管理クラス
   *
   * CORBA 用 NamingServer 管理用クラス。
   * CORBA コンポーネントのNamingServiceへの登録、解除などを管理する。
   *
   * @since 0.4.0
   *
   * @else
   *
   * @biref ModuleManager class
   *
   * @endif
   */
  class NamingOnCorba
    : public virtual NamingBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param orb ORB
     * @param names NamingServer 名称
     *
     * @else
     *
     * @endif
     */
    NamingOnCorba(CORBA::ORB_ptr orb, const char* names)
      : m_cosnaming(orb, names)
    {};
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~NamingOnCorba(){};
    
    /*!
     * @if jp
     *
     * @brief 指定した CORBA オブジェクトのNamingServiceへバインド
     * 
     * 指定した CORBA オブジェクトを指定した名称で CORBA NamingService へ
     * バインドする。
     * 
     * @param name バインド時の名称
     * @param rtobj バインド対象オブジェクト
     *
     * @else
     *
     * @endif
     */
    virtual void bindObject(const char* name, const RTObject_impl* rtobj);
    
    /*!
     * @if jp
     *
     * @brief 指定した CORBA オブジェクトをNamingServiceからアンバインド
     * 
     * 指定した CORBA オブジェクトを CORBA NamingService からアンバインドする。
     * 
     * @param name アンバインド対象オブジェクト
     *
     * @else
     *
     * @endif
     */
    virtual void unbindObject(const char* name);
    
  private:
    CorbaNaming m_cosnaming;
    std::map<std::string, RTObject_impl*> m_names;
  };
  
  /*!
   * @if jp
   *
   * @brief NamingServer 管理クラス
   *
   * NamingServer 管理用クラス。
   * コンポーネントのNamingServiceへの登録、解除などを管理する。
   *
   * @since 0.4.0
   *
   * @else
   *
   * @biref ModuleManager class
   *
   * @endif
   */
  class NamingManager
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param manager マネージャオブジェクト
     *
     * @else
     *
     * @endif
     */
    NamingManager(Manager* manager);
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~NamingManager();
    
    /*!
     * @if jp
     *
     * @brief NameServer の登録
     *
     * 指定した形式の NameServer を登録する。
     * 現在指定可能な形式は CORBA のみ。
     *
     * @param method NamingService の形式
     * @param name_server 登録する NameServer の名称
     *
     * @else
     *
     * @endif
     */
    void registerNameServer(const char* method, const char* name_server);
    
    /*!
     * @if jp
     *
     * @brief 指定したオブジェクトのNamingServiceへバインド
     * 
     * 指定したオブジェクトを指定した名称で CORBA NamingService へバインドする。
     * 
     * @param name バインド時の名称
     * @param rtobj バインド対象オブジェクト
     *
     * @else
     *
     * @endif
     */
    void bindObject(const char* name, const RTObject_impl* rtobj);
    
    /*!
     * @if jp
     *
     * @brief NamingServer の情報の更新
     * 
     * 設定されている NameServer 内に登録されているオブジェクトの情報を
     * 更新する。
     * 
     * @else
     *
     * @endif
     */
    void update();
    
    /*!
     * @if jp
     *
     * @brief 指定したオブジェクトをNamingServiceからアンバインド
     * 
     * 指定したオブジェクトを NamingService からアンバインドする。
     * 
     * @param name アンバインド対象オブジェクト
     *
     * @else
     *
     * @endif
     */
    void unbindObject(const char* name);
    
    /*!
     * @if jp
     *
     * @brief 全てのオブジェクトをNamingServiceからアンバインド
     * 
     * 全てのオブジェクトを CORBA NamingService からアンバインドする。
     * 
     * @else
     *
     * @endif
     */
    void unbindAll();
    
    /*!
     * @if jp
     *
     * @brief バインドされている全てのオブジェクトを取得
     * 
     * バインドされている全てのオブジェクトを 取得する。
     *
     * @return バインド済みオブジェクト リスト
     * 
     * @else
     *
     * @endif
     */
    std::vector<RTObject_impl*> getObjects();
    
  protected:
    /*!
     * @if jp
     *
     * @brief NameServer 管理用オブジェクトの生成
     * 
     * 指定した型のNameServer 管理用オブジェクトを生成する。
     *
     * @param method NamingService 形式
     * @param name_server NameServer 名称
     * 
     * @return 生成した NameServer オブジェクト
     * 
     * @else
     *
     * @endif
     */
    NamingBase* createNamingObj(const char* method, const char* name_server);
    
    /*!
     * @if jp
     *
     * @brief 設定済みコンポーネントを NameServer に登録
     * 
     * 設定済みコンポーネントを指定した NameServer に登録する。
     *
     * @param ns 登録対象 NameServer
     * 
     * @else
     *
     * @endif
     */
    void bindCompsTo(NamingBase* ns);
    
    /*!
     * @if jp
     *
     * @brief NameServer に登録するコンポーネントの設定
     * 
     * NameServer に登録するコンポーネントを設定する。
     *
     * @param name コンポーネントの登録時名称
     * @param rtobj 登録対象オブジェクト
     * 
     * @else
     *
     * @endif
     */
    void registerCompName(const char* name, const RTObject_impl* rtobj);
    
    /*!
     * @if jp
     *
     * @brief NameServer に登録するコンポーネントの設定解除
     * 
     * NameServer に登録するコンポーネントの設定を解除する。
     *
     * @param name 設定解除対象コンポーネントの名称
     * 
     * @else
     *
     * @endif
     */
    void unregisterCompName(const char* name);
    
  protected:
    // Name Servers' method/name and object
    /*!
     * @if jp
     * @brief NameServer 管理用構造体
     * @else
     *
     * @endif
     */
    struct Names
    {
      Names(const char* meth, const char* name, NamingBase* naming)
	: method(meth), nsname(name), ns(naming)
      {
      }
      std::string method;
      std::string nsname;
      NamingBase* ns;
    };
    /*!
     * @if jp
     * @brief NameServer リスト
     * @else
     *
     * @endif
     */
    std::vector<Names*> m_names;
    ACE_Thread_Mutex m_namesMutex;
    
    // Components' name and object
    /*!
     * @if jp
     * @brief コンポーネント管理用構造体
     * @else
     *
     * @endif
     */
    struct Comps
    {
      Comps(const char* n, const RTObject_impl* obj)
	: name(n), rtobj(obj)
      {}
      std::string name;
      const RTObject_impl* rtobj;
    };
    /*!
     * @if jp
     * @brief コンポーネントリスト
     * @else
     *
     * @endif
     */
    std::vector<Comps*> m_compNames;
    ACE_Thread_Mutex m_compNamesMutex;
    
    /*!
     * @if jp
     * @brief マネージャオブジェクト
     * @else
     *
     * @endif
     */
    Manager* m_manager;
    
    /*!
     * @if jp
     * @brief ロガー仲介バッファ
     * @else
     * @brief Logger mediation buffer
     * @endif
     */
    MedLogbuf m_MedLogbuf;
    
    /*!
     * @if jp
     * @brief ロガーストリーム
     * @else
     * @brief Logger stream
     * @endif
     */
    LogStream rtcout;
  }; // class NamingManager
}; // namespace RTC

#endif // NamingManager_h
