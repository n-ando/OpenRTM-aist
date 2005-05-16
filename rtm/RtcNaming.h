// -*- C++ -*-
/*!
 * @file RtcNaming.h
 * @brief naming Service helper class
 * @date $Date: 2005-05-16 06:29:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNaming.h,v 1.2 2005-05-16 06:29:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */


#ifndef RtcNaming_h
#define RtcNaming_h

// CORBA header include
#include "rtm/idl/RTMBaseStub.h"
#include "rtm/idl/RTMBaseSkel.h"
#include "rtm/RtcBase.h"

// STL includes
#include <map>
#include <string>
#include <vector>

#define HOST_CTXT_LEVEL 1
#define MANAGER_CTXT_LEVEL 2
#define MANAGER_LEVEL 3
#define CATEGORY_CTXT_LEVEL 3
#define MODULE_CTXT_LEVEL 4
#define COMPONENT_LEVEL 5

namespace RTM
{
  using namespace std;
  
  typedef std::vector<CosNaming::NamingContextExt_var> ContextList;
  typedef std::vector<CORBA::Object_ptr> ObjectList;


  /*!
   * @if jp
   *
   * @class RtcNaming
   *
   * @brief CORBA Naming Service アクセスヘルパークラス
   *
   * @else
   *
   * @class RtcNaming
   *
   * @brief CORBA Naming Service access helper class
   *
   * @endif
   */
  class EXPORTS RtcNaming
  {
  public:
	/*!
	 * @if jp
	 * @brief RtcNaming クラスコンストラクタ
	 *
	 * @else
	 *
	 * @brief A constructor of RtcNaming class.
	 *
	 * @endif
	 */
    RtcNaming() : m_bindListNum(100) {};
	
	/*!
	 * @if jp
	 * @brief RtcNaming クラスコンストラクタ
	 *
	 * @else
	 *
	 * @brief A constructor of RtcNaming class.
	 *
	 * @endif
	 */
    RtcNaming(CORBA::ORB_ptr orb) : m_bindListNum(100) {initNaming(orb);};
	
	/*!
	 * @if jp
	 * @brief RtcNaming クラスデストラクタ
	 *
	 * @else
	 *
	 * @brief A destructor of RtcNaming class.
	 *
	 * @endif
	 */
	~RtcNaming();
	
	
	/*!
	 * @if jp
	 * @brief RtcNaming クラスデストラクタ
	 *
	 * @param orb ORB へのポインタ
	 *
	 * @else
	 *
	 * @brief Initialize RtcNaming object
	 *
	 * @param orb pointer tod ORB
	 *
	 * @endif
	 */
    bool initNaming(const CORBA::ORB_ptr orb);
	
	
    //============================================================
    // << Create and Bind Methods >>
    //============================================================
	
	
	/*!
	 * @if jp
	 * @brief ネーミングコンテキストの生成
	 *
	 * 与えられたネーミングコンテキスト上に id,kind のコンテキストを生成
	 * 
     * @param context コンテキストを生成する親ネーミングコンテキスト
     * @param id コンテキスト ID
     * @param kind コンテキスト KIND
	 *
	 * @else
	 *
	 * @brief Create naming context
	 *
     * Create a naming context using Context_var, id and kind
	 *
     * @param context Naming context to be created new context
     * @param id context ID
     * @param kind context KIND
	 *
	 * @endif
	 */
    CosNaming::NamingContextExt_var
    createContext(CosNaming::NamingContextExt_var context,
				  const std::string& id, const std::string& kind);
	
	
	/*!
	 * @if jp
	 * @brief ホストコンテキストの生成
	 *
	 * ホストコンテキストレベルにホスト名のコンテキストを生成する
	 * 
     * @param id コンテキスト名として与えるホスト名
	 *
	 * @else
	 *
	 * @brief Create host context
	 *
     * Create host context on the default naming service.
	 *
     * @param id host name as a context id 
	 *
	 * @endif
	 */
    bool createHostContext(const std::string& id);
	
	
	/*!
	 * @if jp
	 * @brief マネージャコンテキストの生成
	 *
	 * マネージャコンテキストレベルにマネージャ名のコンテキストを生成する
	 * 
     * @param id コンテキスト名として与えるマネージャ名
	 *
	 * @else
	 *
	 * @brief Create manager context
	 *
     * Create manager context on the default naming service.
	 *
     * @param id manager name as a context id 
	 *
	 * @endif
	 */
    bool createManagerContext(const std::string& id);
	
	
	/*!
	 * @if jp
	 * @brief カテゴリコンテキストの生成
	 *
	 * カテゴリコンテキストレベルにマネージャ名のコンテキストを生成する
	 * 
     * @param id コンテキスト名として与えるカテゴリ名
	 *
	 * @else
	 *
	 * @brief Create category context
	 *
     * Create category context on the default naming service.
	 *
     * @param id category name as a context id 
	 *
	 * @endif
	 */
    bool createCategoryContext(const std::string& category);
	
	
	/*!
	 * @if jp
	 * @brief モジュールコンテキストの生成
	 *
	 * モジュールコンテキストレベルにマネージャ名のコンテキストを生成する
	 * 
     * @param module コンテキスト名として与えるモジュール名
     * @param category モジュールコンテキストを作成するカテゴリ名
	 *
	 * @else
	 *
	 * @brief Create module context
	 *
     * Create module context on the default naming service.
	 *
     * @param module module name as a context id 
     * @param category category name on which module context is created
	 *
	 * @endif
	 */
    bool createModuleContext(const std::string& module,
							 const std::string& category);
	
	
	/*!
	 * @if jp
	 * @brief オブジェクトのバインド
	 *
	 * オブジェクトを指定したコンテキスト下にバインド
	 * 
     * @param context オブジェクトをバインドするコンテキスト
     * @param id オブジェクト ID
     * @param kind オブジェクト KIND
     * @param obj バインドするオブジェクトのオブジェクトリファレンス
	 *
	 * @else
	 *
	 * @brief Bind object to a context
	 *
     * Bind object to specified naming context
	 *
     * @param context A context to be bound the object
     * @param id object ID
     * @param kind object KIND
     * @param obj Object pointer to be bound
	 *
	 * @endif
	 */
    bool bindObject(CosNaming::NamingContextExt_var context,
					const std::string& id, const std::string& kind,
					CORBA::Object_ptr obj);

	/*!
	 * @if jp
	 * @brief オブジェクトをフルパス指定でバインド
	 *
	 * オブジェクトを指定フルパスに従ってバインドする。
	 * 
     * @param path オブジェクトをバインドするネーミングツリーのフルパス
     * @param obj バインドするオブジェクトのオブジェクトリファレンス
	 *
	 * @else
	 *
	 * @brief Bind object to a context specified full path string
	 *
     * Bind object to specified full path string.
	 *
     * @param path A full path string to be bound a object.
     * @param obj Object reference to be bound
	 *
	 * @endif
	 */
	bool bindObjectByFullPath(const std::string& path,
							  CORBA::Object_ptr obj);
	
	/*!
	 * @if jp
	 * @brief コンポーネントのバインド
	 *
	 * オブジェクトを指定したコンテキスト下にバインド
	 * 
     * @param id コンポーネントの ID
     * @param category コンポーネントのカテゴリ
     * @param obj コンポーネントのオブジェクトリファレンス
	 *
	 * @else
	 *
	 * @brief Bind component to a context
	 *
     * Bind object to specified naming context
	 *
     * @param id object ID
     * @param category A category bind to the obobject
     * @param obj Component object pointer to be bound
	 *
	 * @endif
	 */
    bool bindComponent(const std::string& component, const std::string& module,
					   const std::string& category, CORBA::Object_ptr obj);
	
	/*!
	 * @if jp
	 * @brief マネージャのバインド
	 *
	 * マネージャを指定したコンテキスト下にバインド
	 * 
     * @param id マネージャ名
     * @param obj マネージャのオブジェクトリファレンス
	 *
	 * @else
	 *
	 * @brief Bind manager to a context
	 *
     * Bind manager object to specified naming context
	 *
     * @param id Manager's name as a object id
     * @param obj Manager's object pointer
	 *
	 * @endif
	 */
    bool bindManager(const std::string& id, CORBA::Object_ptr obj);
	
	
    //============================================================
    // << Destroy and Unbind methods >>
    //============================================================
	
	
	/*!
	 * @if jp
	 * @brief 自分のホストコンテキストの削除
	 *
	 * @else
	 * @brief Destroy host context
	 *
	 * @endif
	 */
    bool destroyHostContext();
	
	/*!
	 * @if jp
	 * @brief 自分のマネージャコンテキストの削除
	 *
	 * @else
	 * @brief Destroy manager context
	 *
	 * @endif
	 */
    bool destroyManagerContext();
	
	/*!
	 * @if jp
	 * @brief カテゴリコンテキストの削除
	 *
	 * @param id カテゴリ名
	 *
	 * @else
	 * @brief Destroy manager context
	 *
	 * @param id Category name
	 *
	 * @endif
	 */
    bool destroyCategoryContext(const std::string& id);
	
	
	/*!
	 * @if jp
	 * @brief モジュールコンテキストの削除
	 *
	 * @param module モジュール名
	 * @param category カテゴリ名
	 *
	 * @else
	 * @brief Destroy manager context
	 *
	 * @param module Module name
	 * @param category Category name
	 *
	 * @endif
	 */
    bool destroyModuleContext(const std::string& module,
							  const std::string& category);
	
	
	/*!
	 * @if jp
	 * @brief オブジェクトのアンバインド
	 *
	 * 指定したコンテキスト下のオブジェクトをアンバインド
	 * 
     * @param context オブジェクトをバインドするコンテキスト
     * @param id オブジェクト ID
     * @param kind オブジェクト KIND
	 *
	 * @else
	 *
	 * @brief Unbind object to a context
	 *
     * Unbind object to specified naming context
	 *
     * @param context A context to be unbound the object
     * @param id object ID
     * @param kind object KIND
	 *
	 * @endif
	 */
    bool unbindObject(CosNaming::NamingContextExt_var context,
					  const std::string& id, const std::string& kind);



	/*!
	 * @if jp
	 * @brief オブジェクトをフルパス指定でアンバインド
	 *
	 * オブジェクトを指定フルパスに従ってアンバインドする。
	 * 
     * @param path アンバインドするオブジェクトのフルパス
	 *
	 * @else
	 *
	 * @brief Unbind object to a context specified full path string
	 *
     * Unbind object to specified full path string.
	 *
     * @param path A full path string to be bound a object.
	 *
	 * @endif
	 */
	bool unbindObjectByFullPath(const std::string& path);


	/*!
	 * @if jp
	 * @brief コンポーネントオブジェクトをアンバインド
	 *
	 * 当該RtcNamingクラスでバインドされたロングネームのオブジェクトを
	 * アンバインドする。
	 * 
     * @param category アンバインドするオブジェクトのカテゴリ名
     * @param module アンバインドするオブジェクトのモジュール名
     * @param instance アンバインドするオブジェクトのインスタンス名
	 *
	 * @else
	 *
	 * @brief Unbind component object
	 *
     * Unbind object which was bound this RtcNaming object.
	 *
     * @param category Category name of the object to be unbound.
     * @param module Module name of the object to be unbound.
     * @param instance Instance name of the object to be unbound.
	 *
	 * @endif
	 */
	bool unbindLocalComponent(const std::string category,
							  const std::string module,
							  const std::string instance);
	


    //============================================================
    // << Find methods >>
    //============================================================
	
	/*!
	 * @if jp
	 * @brief ホストコンテキストの検索
	 *
	 * @param id_seq 検索するID列
	 * @param context コンテキスト列 (戻り値)
	 *
	 * @else
	 * @brief Find host context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findHostContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief カテゴリコンテキストの検索
	 *
	 * @param id_seq 検索するID列
	 * @param context コンテキスト列 (戻り値)
	 *
	 * @else
	 * @brief Find category context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findCategoryContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief モジュールコンテキストの検索
	 *
	 * @param id_seq 検索するID列
	 * @param context コンテキスト列 (戻り値)
	 *
	 * @else
	 * @brief Find module context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findModuleContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief マネージャコンテキストの検索
	 *
	 * @param id_seq 検索するID列
	 * @param context コンテキスト列 (戻り値)
	 *
	 * @else
	 * @brief Find manager context
	 *
	 * @param id_seq ID sequence to be find
	 * @param context context sequence (return value)	
	 *
	 * @endif
	 */
    bool findManagerContext(const std::string& id_seq, ContextList& context);
	
	
	/*!
	 * @if jp
	 * @brief マネージャオブジェクトリファレンスの検索・取得
	 *
	 * @param id_seq 検索するID列
	 * @param object オブジェクトリファレンス列 (戻り値)
	 *
	 * @else
	 * @brief Find and get manager object reference
	 *
	 * @param id_seq ID sequence to be find
	 * @param object objecte reference list (return value)	
	 *
	 * @endif
	 */
    bool findManager(std::string& id, ObjectList& objects);
	
	
	/*!
	 * @if jp
	 * @brief コンポーネントオブジェクトリファレンスの検索・取得
	 *
	 * @param id_seq 検索するID列
	 * @param object オブジェクトリファレンス列 (戻り値)
	 *
	 * @else
	 * @brief Find and get component object reference
	 *
	 * @param id_seq ID sequence to be find
	 * @param object objecte reference list (return value)	
	 *
	 * @endif
	 */
    bool findComponents(const std::string& id_seq, ObjectList& objects);
	
	
  protected:
	/*!
	 * @if jp
	 * @brief ネーミングコンテキストの再帰的削除
	 *
	 * @param context 削除を開始するコンテキスト
	 *
	 * @else
	 * @brief Destroy naming context recursive
	 *
	 * @param context Starting point naming context to be deleted.
	 *
	 * @endif
	 */
    bool destroyRecursive(CosNaming::NamingContextExt_var context);
	
	
	/*!
	 * @if jp
	 * @brief オブジェクトリファレンスを再帰的に取得
	 *
	 * @param context 検索を開始するコンテキスト
	 * @param path 検索パス
	 * @param obj オブジェクトリファレンス列 (戻り値)
	 *
	 * @else
	 * @brief Find object reference recursive
	 *
	 * @param context Starting point naming context 
	 * @param path Search path name
	 * @param obj Object reference list (return value)
	 *
	 * @endif
	 */
    void findObjectsRecursive(CosNaming::NamingContextExt_ptr context,
							  const std::string& path, ObjectList& obj);
	
	/*!
	 * @if jp
	 * @brief ネーミングコンテキストを再帰的に取得
	 *
	 * @param context 検索を開始するコンテキスト
	 * @param path 検索パス
	 * @param context_list コンテキスト列 (戻り値)
	 *
	 * @else
	 * @brief Find naming context recursive
	 *
	 * @param context Starting point naming context 
	 * @param path Search path name
	 * @param context_list Naming context list (return value)
	 *
	 * @endif
	 */
    void findContextRecursive(CosNaming::NamingContextExt_var context,
							  const std::string& path, ContextList& context_list);
	
	
	/*!
	 * @if jp
	 * @brief コンテキスト・オブジェクトを再帰的にバインド
	 *
	 * @param context バインドを開始するコンテキスト
	 * @param path 検索パス
	 * @param obj オブジェクトリファレンス
	 *
	 * @else
	 * @brief Bind context/object recursive
	 *
	 * @param context Starting point naming context 
	 * @param path Binding path name
	 * @param obj Object reference to be bound
	 *
	 * @endif
	 */
	void bindObjectRecursive(CosNaming::NamingContextExt_var context,
							 const std::string& path,
							 CORBA::Object_ptr obj);
	
	
  private:
	/*!
	 * @if jp
	 * @brief 文字列の分割
	 * @else
	 * @brief Strig split function
	 * @endif
	 */
    int split(const std::string& input, const std::string& delimiter,
			  std::vector<std::string>& results);
	
	/*!
	 * @if jp
	 * @brief 与えられた文字列をフルパスにする
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * If given path is "hoge/munya" and level is 5, it is converted to 
	 * "*./*./*./hoge/munya".
	 *
	 * @param path path which have to converted to full path
	 * @param level compensation level
	 *
	 * @endif
	 */
    std::string makeFullPath(std::string path, int level);
	
	/*!
	 * @if jp
	 * @brief 現在のノードを切り出す
	 *
	 * @param path パス
	 * @param node 切り出されたノード名 (戻り値)
	 * @param remain 残りのパス (戻り値)
	 *
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * @param path Given path
	 * @param node Picked up path node name (return value)
	 * @param remain Remain path string (return value)
	 *
	 * @endif
	 */
    bool pickupNode(const std::string& path, std::string& node, std::string& remain);
	
	/*!
	 * @if jp
	 * @brief 与えられた文字列を ID と KIND に分割する
	 * Kind が空の場合 ".*" が代入される。
	 *
	 * @param node ノード名
	 * @param id ID (戻り値)
	 * @param kind KIND (戻り値)
	 *
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * @param node Node name
	 * @param id ID (return value)
	 * @param kind KIND (return value)
	 *
	 * @endif
	 */
    void nodeToIdKindAny(const std::string& node,
					  std::string& id, std::string& kind);

	/*!
	 * @if jp
	 * @brief 与えられた文字列を ID と KIND に分割する
	 *
	 * @param node ノード名
	 * @param id ID (戻り値)
	 * @param kind KIND (戻り値)
	 *
	 * @else
	 * @brief Convert given string to full path string
	 *
	 * @param node Node name
	 * @param id ID (return value)
	 * @param kind KIND (return value)
	 *
	 * @endif
	 */
    void nodeToIdKind(const std::string& node,
					  std::string& id, std::string& kind);
	
  private:
	
	/*!
	 * @if jp
	 * @brief ネーミングサービスのオブジェクトレファレンス
	 * @else
	 * @brief Object reference of Naming Service
	 * @endif
	 */
    CORBA::Object_var m_nameRef;
	
	/*!
	 * @if jp
	 * @brief ルートコンテキスト
	 * @else
	 * @brief Root naming context
	 * @endif
	 */
    CosNaming::NamingContextExt_var m_rootContext;
	
	/*!
	 * @if jp
	 * @brief ホストコンテキスト
	 * @else
	 * @brief Host naming context
	 * @endif
	 */
    CosNaming::NamingContextExt_var m_hostContext;
	std::string m_hostName;

	/*!
	 * @if jp
	 * @brief マネージャコンテキスト
	 * @else
	 * @brief Manager naming context
	 * @endif
	 */
    CosNaming::NamingContextExt_var m_mngrContext;
	std::string m_mngrName;

	/*!
	 * @if jp
	 * @brief カテゴリコンテキストマップ
	 * @else
	 * @brief Category naming context map
	 * @endif
	 */
    std::map<std::string, CosNaming::NamingContextExt_var> m_cateContext;
	
	/*!
	 * @if jp
	 * @brief コンポーネントコンテキストマップ
	 * @else
	 * @brief Category naming context map
	 * @endif
	 */
    std::map<std::string, std::map<std::string, CosNaming::NamingContextExt_var> > m_compContext;
	
	/*!
	 * @if jp
	 * @brief 取得するネーミングコンテキストの最大数
	 * @else
	 * @brief maximum number of naming context to get at once
	 * @endif
	 */
    int m_bindListNum;
	
	/*!
	 * @if jp
	 * @brief オブジェクトリスト
	 * @else
	 * @brief Object reference list
	 * @endif
	 */
    std::vector<CORBA::Object_ptr> m_vObjects;
	
  };
  
}; // end of namespace RTM

#endif // end of __RtcNaming_h__
