// -*- C++ -*-
/*!
 * @file RtcNaming.h
 * @brief naming Service helper class
 * @date $Date: 2006-10-17 10:14:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNaming.h,v 1.4 2006-10-17 10:14:52 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/09/11 18:26:20  n-ando
 * RtcNaming class was completely rewritten.
 * - Now RtcCorbaNaming is a wrapper of CosNaming::NamingContext
 *   and CosNaming::NamingContextExt with fixed root context.
 * - find() method is separated from this class.
 * - This class constructor connects to the NameServer without using
 *   resolve_initial_reference().
 *
 * Revision 1.2  2005/05/16 06:29:05  n-ando
 * - RtcNaming class was DLL exported for Windows port.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */


#ifndef RtcNaming_h
#define RtcNaming_h

// CORBA header include
//#include "rtm/idl/RTMBaseStub.h"
//#include "rtm/idl/RTMBaseSkel.h"
//#include "rtm/RtcBase.h"
#include "rtm/RTC.h"
#ifdef ORB_IS_OMNIORB
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#include "omniORB4/CORBA.h"
//#include "omniORB4/Naming.h"
#endif

// STL includes
#include <map>
#include <string>
#include <vector>

namespace RTM
{

  class RtcCorbaNaming
  {
  public:
    RtcCorbaNaming(CORBA::ORB_ptr orb, const char* name_server);
    virtual ~RtcCorbaNaming(){};

    typedef CosNaming::NamingContext::NotFound      NotFound;
    typedef CosNaming::NamingContext::CannotProceed CannotProceed;
    typedef CosNaming::NamingContext::InvalidName   InvalidName;
    typedef CosNaming::NamingContext::AlreadyBound  AlreadyBound;
    typedef CosNaming::NamingContext::NotEmpty      NotEmpty;
    typedef CosNaming::NamingContextExt::InvalidAddress InvalidAddress;
    typedef std::vector<CORBA::Object_ptr> ObjectList;

    /*!
     * @if jp
     *
     * @brief Object を bind する
     *
     * CosNaming::bind() とほぼ同等の働きをするが、常に与えられたネームサーバの
     * ルートコンテキストに対してbind()が呼び出される点が異なる。
     *
     * Name <name> と Object <obj> を当該 NamingContext 上にバインドする。
     * c_n が n 番目の NameComponent をあらわすとすると、
     * name が n 個の NameComponent から成るとき、以下のように扱われる。
     *
     * cxt->bind(<c_1, c_2, ... c_n>, obj) は以下の操作と同等である。
     * cxt->resolve(<c_1, ... c_(n-1)>)->bind(<c_n>, obj)
     *
     * すなわち、1番目からn-1番目のコンテキストを解決し、n-1番目のコンテキスト
     * 上に name <n> として　obj を bind する。
     * 名前解決に参加する <c_1, ... c_(n-1)> の NemingContext は、
     * bindContext() や rebindContext() で既にバインド済みでなければならない。
     * もし <c_1, ... c_(n-1)> の NamingContext が存在しない場合には、
     * NotFound 例外が発生する。
     *
     * ただし、強制バインドフラグ force が true の時は、<c_1, ... c_(n-1)>
     * が存在しない場合にも、再帰的にコンテキストをバインドしながら、
     * 最終的に obj を名前 name <c_n> にバインドする。
     *
     * いずれの場合でも、n-1番目のコンテキスト上に name<n> のオブジェクト
     * (Object あるいは コンテキスト) がバインドされていれば
     * AlreadyBound 例外が発生する。
     *
     * @param name オブジェクトに付ける名前の NameComponent
     * @param obj 関連付けられる Object
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @exception NotFound 途中の <c_1, c_2, ..., c_(n-1)> が存在しない。
     * @exception CannotProceed 何らかの理由で処理を継続できない。
     * @exception InvalidName 引数 name の名前が不正。
     * @exception AlreadyBound name <c_n> の Object がすでにバインドされている。
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bind(const CosNaming::Name& name, CORBA::Object_ptr obj,
	      const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);


    /*!
     * @if jp
     *
     * @brief Object を bind する
     *
     * Object を bind する際に与える名前が文字列表現であること以外は、bind()
     * と同じである。bind(toName(string_name), obj) と等価。
     *
     * @param string_name オブジェクトに付ける名前の文字列表現
     * @param obj 関連付けられるオブジェクト
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @exception NotFound 途中の <c_1, c_2, ..., c_(n-1)> が存在しない。
     * @exception CannotProceed 何らかの理由で処理を継続できない。
     * @exception InvalidName 引数 name の名前が不正。
     * @exception AlreadyBound name <n> の Object がすでにバインドされている。
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindByString(const char* string_name, CORBA::Object_ptr obj,
		      const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief 途中のコンテキストを bind しながら Object を bind する
     *
     * context で与えられた NamingContext に対して、name で指定された
     * ネームコンポーネント <c_1, ... c_(n-1)> を NamingContext として
     * 解決しながら、名前 <c_n> に対して obj を bind する。
     * もし、<c_1, ... c_(n-1)> に対応する NamingContext がない場合には
     * 新たな NamingContext をバインドする。
     *
     * 最終的に <c_1, c_2, ..., c_(n-1)> に対応する NamingContext が生成
     * または解決された上で、CosNaming::bind(<c_n>, object) が呼び出される。
     * このとき、すでにバインディングが存在すれば AlreadyBound例外が発生する。
     *
     * 途中のコンテキストを解決する過程で、解決しようとするコンテキストと
     * 同じ名前の NamingContext ではない Binding が存在する場合、
     * CannotProceed 例外が発生し処理を中止する。
     *
     * @param context bind を開始する　NamingContext
     * @param name オブジェクトに付ける名前のネームコンポーネント
     * @param obj 関連付けられるオブジェクト
     *
     * @exception CannotProceed <c_1, ..., c_(n-1)> に対応する NamingContext 
     *            のうちひとつが、すでに NamingContext 以外の object にバインド
     *            されており、処理を継続できない。
     * @exception InvalidName 名前 name が不正
     * @exception AlreadyBound name <c_n> にすでに何らかの object がバインド
     *            されている。
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindRecursive(CosNaming::NamingContext_ptr context,
		       const CosNaming::Name& name,
		       CORBA::Object_ptr obj)
      throw(CannotProceed, InvalidName, AlreadyBound);



    /*!
     * @if jp
     *
     * @brief Object を rebind する
     *
     * name で指定された Binding がすでに存在する場合を除いて bind() と同じ
     * である。バインディングがすでに存在する場合には、新しいバインディングに
     * 置き換えられる。
     *
     * @param name オブジェクトに付ける名前の NameComponent
     * @param obj 関連付けられるオブジェクト
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebind(const CosNaming::Name& name, CORBA::Object_ptr obj,
		const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);


    /*!
     * @if jp
     *
     * @brief Object を rebind する
     *
     * Object を rebind する際に与える名前が文字列表現であること以外は rebind()
     * と同じである。rebind(toName(string_name), obj) と等価。
     *
     * @param string_name オブジェクトに付ける名前の文字列表現
     * @param obj 関連付けられるオブジェクト
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @exception NotFound 途中の <c_1, c_2, ..., c_(n-1)> が存在しない。
     * @exception CannotProceed 何らかの理由で処理を継続できない。
     * @exception InvalidName 引数 name の名前が不正。
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindByString(const char* string_name, CORBA::Object_ptr obj,
			const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);

    
    /*!
     * @if jp
     *
     * @brief 途中のコンテキストを bind しながら Object を rebind する
     *
     * name <c_n> で指定された NamingContext もしくは Object がすでに存在する
     * 場合を除いて bindRecursive() と同じである。
     *
     * name <c_n> で指定されたバインディングがすでに存在する場合には、
     * 新しいバインディングに置き換えられる。
     *
     * @param name オブジェクトに付ける名前の文字列表現
     * @param obj 関連付けられるオブジェクト
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @exception CannotProceed 途中のコンテキストが解決できない。
     * @exception InvalidName 与えられた name が不正。
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindRecursive(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CORBA::Object_ptr obj)
      throw(CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief NamingContext を bind する
     *
     * bind されるオブジェクトが NamingContext であることを除いて bind() 
     * と同じである。
     *
     * @param name オブジェクトに付ける名前のネームコンポーネント
     * @param name_cxt 関連付けられる NamingContext
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContext(const CosNaming::Name& name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext を bind する
     *
     * bind されるオブジェクトが NamingContext であることを除いて bind() 
     * と同じである。
     *
     * @param name オブジェクトに付ける名前の文字列表現
     * @param name_cxt 関連付けられる NamingContext
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContext(const char* string_name,
		     CosNaming::NamingContext_ptr name_cxt,
		     const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext を bind する
     *
     * bind されるオブジェクトが NamingContext であることを除いて
     * bindRecursive() と同じである。
     *
     * @param context bind を開始する　NamingContext
     * @param name オブジェクトに付ける名前のネームコンポーネント
     * @param name_cxt 関連付けられる NamingContext
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void bindContextRecursive(CosNaming::NamingContext_ptr context,
			      const CosNaming::Name& name,
			      CosNaming::NamingContext_ptr name_cxt);
    /*!
     * @if jp
     *
     * @brief NamingContext を rebind する
     *
     * name で指定されたコンテキストがすでに存在する場合を除いて bindContext() 
     * と同じである。
     * バインディングがすでに存在する場合には、新しいバインディングに
     * 置き換えられる。
     *
     * @param name オブジェクトに付ける名前のネームコンポーネント
     * @param name_cxt 関連付けられる NamingContext
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindContext(const CosNaming::Name& name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief NamingContext を rebind する
     *
     * name で指定されたコンテキストがすでに存在する場合を除いて bindContext() 
     * と同じである。
     * バインディングがすでに存在する場合には、新しいバインディングに
     * 置き換えられる。
     *
     * @param name オブジェクトに付ける名前の文字列表現
     * @param name_cxt 関連付けられる NamingContext
     * @param force trueの場合、途中のコンテキストを強制的にバインドする
     *
     * @else
     *
     * @brief
     *
     * @endif
     */
    void rebindContext(const char* string_name,
		       CosNaming::NamingContext_ptr name_cxt,
		       const bool force = 1)
      throw(NotFound, CannotProceed, InvalidName);


    void rebindContextRecursive(CosNaming::NamingContext_ptr context,
				const CosNaming::Name& name,
				CosNaming::NamingContext_ptr name_cxt);

    /*!
     * @if jp
     *
     * @brief Object を name から解決する
     *
     * name に bind されているオブジェクト参照を返す。
     * ネームコンポーネント <c_1, c_2, ... c_n> は再帰的に解決される。
     * 
     * CosNaming::resolve() とほぼ同等の働きをするが、常に与えられた
     * ネームサーバのルートコンテキストに対して resolve() が呼び出される点が
     * 異なる。
     *
     * @param name 解決すべきオブジェクトの名前のネームコンポーネント
     * @return 解決されたオブジェクト参照
     *
     * @else
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const CosNaming::Name& name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief Object を name から解決する
     *
     * name に bind されているオブジェクト参照を返す。
     * ネームコンポーネント <c_1, c_2, ... c_n> は再帰的に解決される。
     * 
     * CosNaming::resolve() とほぼ同等の働きをするが、常に与えられた
     * ネームサーバのルートコンテキストに対して resolve() が呼び出される点が
     * 異なる。
     *
     * @param name 解決すべきオブジェクトの名前の文字列表現
     * @return 解決されたオブジェクト参照
     *
     * @else
     *
     * @endif
     */
    CORBA::Object_ptr resolve(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief 指定された名前のオブジェクトの bind を解除する
     *
     * name に bind されているオブジェクト参照を返す。
     * ネームコンポーネント <c_1, c_2, ... c_n> は再帰的に解決される。
     * 
     * CosNaming::unbind() とほぼ同等の働きをするが、常に与えられた
     * ネームサーバのルートコンテキストに対して unbind() が呼び出される点が
     * 異なる。
     *
     * @param name 解決すべきオブジェクトの名前のネームコンポーネント
     * @return 解決されたオブジェクト参照
     *
     * @else
     *
     * @endif
     */
    void unbind(const CosNaming::Name& name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief 指定された名前のオブジェクトの bind を解除する
     *
     * name に bind されているオブジェクト参照を返す。
     * ネームコンポーネント <c_1, c_2, ... c_n> は再帰的に解決される。
     * 
     * CosNaming::unbind() とほぼ同等の働きをするが、常に与えられた
     * ネームサーバのルートコンテキストに対して unbind() が呼び出される点が
     * 異なる。
     *
     * @param name 解決すべきオブジェクトの名前の文字列表現
     * @return 解決されたオブジェクト参照
     *
     * @else
     *
     * @endif
     */
    void unbind(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName);

    /*!
     * @if jp
     *
     * @brief 新しいコンテキストを生成する
     *
     * 与えられたネームサーバ上で生成された NamingContext を返す。
     * 返された NamingContext は bind されていない。
     * 
     * @return 生成された新しい NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr newContext();

    /*!
     * @if jp
     *
     * @brief 新しいコンテキストを bind する
     *
     * 与えられた name に対して新しいコンテキストをバインドする。
     * 生成された　NamingContext はネームサーバ上で生成されたものである。
     * 
     * @param name NamingContextに付ける名前のネームコンポーネント
     * @return 生成された新しい NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const CosNaming::Name& name, bool force = true)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief 新しいコンテキストを bind する
     *
     * 与えられた name に対して新しいコンテキストをバインドする。
     * 生成された　NamingContext はネームサーバ上で生成されたものである。
     * 
     * @param name NamingContextに付ける名前の文字列表現
     * @return 生成された新しい NamingContext
     *
     * @else
     *
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindNewContext(const char* string_name, bool force = true)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);

    /*!
     * @if jp
     *
     * @brief NamingContext を非アクティブ化する
     *
     * context で指定された NamingContext を非アクティブ化する。
     * context に他のコンテキストがバインドされている場合は NotEmpty 例外が
     * 発生する。
     * 
     * @param context 非アクティブ化する NamingContext
     *
     * @else
     *
     * @brief Destroy the naming context
     *
     * Delete the specified naming context.
     * any bindings should be <unbind> in which the given context is bound to
     * some names before invoking <destroy> operation on it. 
     *
     * @param context NamingContext which is destroied.
     *     
     * @endif
     */
    void destroy(CosNaming::NamingContext_ptr context)
      throw(NotEmpty);


    /*!
     * @if jp
     * @brief NamingContext を再帰的に下って非アクティブ化する
     * @else
     * @brief Destroy the naming context recursively
     * @endif
     */
    void destroyRecursive(CosNaming::NamingContext_ptr context)
      throw(NotEmpty, NotFound, CannotProceed, InvalidName);


    /*!
     * @if jp
     * @brief すべての Binding を削除する
     * @else
     * @brief Destroy all binding
     * @endif
     */
    void clearAll();


    /*!
     * @if jp
     * @brief 与えられた NamingContext の Binding を取得する
     * @else
     * @brief Get Binding on the NamingContextDestroy all binding
     * @endif
     */
    void list(CosNaming::NamingContext_ptr name_cxt,
	      unsigned long how_many,
	      CosNaming::BindingList_var& bl,
	      CosNaming::BindingIterator_var& bi);


    //============================================================
    // interface of NamingContextExt
    //============================================================
    /*!
     * @if jp
     * @brief 与えられた NameComponent の文字列表現を返す
     * @else
     * @brief Get string representation of given NameComponent
     * @endif
     */
    char* toString(const CosNaming::Name& name)
      throw(InvalidName);
    

    /*!
     * @if jp
     * @brief 与えられた文字列表現を NameComponent に分解する
     * @else
     * @brief Get NameComponent from gien string name representation
     * @endif
     */
    CosNaming::Name toName(const char* string_name)
      throw(InvalidName);


    /*!
     * @if jp
     * @brief 与えられた addre と string_name から URL表現を取得する
     * @else
     * @brief Get URL representation from given addr and string_name
     * @endif
     */
    char* toUrl(char* addr, char* string_name)
      throw(InvalidAddress, InvalidName);


    /*!
     * @if jp
     * @brief 与えられた文字列表現を resolve しオブジェクトを返す
     * @else
     * @brief Resolve from name of string representation and get object 
     * @endif
     */
    CORBA::Object_ptr resolveStr(const char* string_name)
      throw(NotFound, CannotProceed, InvalidName, AlreadyBound);


    //============================================================
    // Find functions
    //============================================================

    //    ObjectList find(const char* name, const char* kind);
    //    ObjectList findById(const char* name, const char* kind);
    //    ObjectList findByKind(const char* name, const char* kind);


    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    const char* getNameServer();
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr getRootContext();

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(const CosNaming::Name& name);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    bool isNamingContext(const char* string_name);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::Name subName(const CosNaming::Name& name,
			    long begin,
			    long end = -1);

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CORBA::Object_ptr bindOrResolve(CosNaming::NamingContext_ptr context,
				    const CosNaming::Name& name,
				    CORBA::Object_ptr obj);
    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name,
			 CosNaming::NamingContext_ptr new_context);

    
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CosNaming::NamingContext_ptr
    bindOrResolveContext(CosNaming::NamingContext_ptr context,
			 const CosNaming::Name& name);


  protected:
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    CORBA::ULong getNameLength(const CosNaming::Name& name);

    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    void nameToString(const CosNaming::Name& name, char* string_name,
		      unsigned long slen);
    /*!
     * @if jp
     * @brief 
     * @else
     * @brief 
     * @endif
     */
    unsigned int split(const std::string& input,
		       const std::string& delimiter,
		       std::vector<std::string>& results);
    
    CORBA::ORB_var m_varORB;
    std::string m_nameServer;
    CosNaming::NamingContextExt_var m_rootContext;

  private:
    CORBA::ULong m_blLength;
    
  };

}; // end of namespace RTM

#endif // end of __RtcNaming_h__
