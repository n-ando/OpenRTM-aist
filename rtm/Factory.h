// -*- C++ -*-
/*!
 * @file RtcFactory.h
 * @brief RTComponent factory class
 * @date $Date: 2006-10-24 14:23:45 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Factory.h,v 1.3 2006-10-24 14:23:45 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2005/05/16 06:06:30  n-ando
 * - RtcFactoryBase, RtcFactoryCXX classes were DLL exported for Windows port.
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcFactory_h
#define RtcFactory_h

#include "rtm/RtcModuleProfile.h"


namespace RTM 
{
  class RtcBase;
  class RtcManager;
  /*!
   * @if jp
   *
   * @class RtcFactoryBase
   *
   * @brief RtcFactoryBase 基底クラス
   * 
   * コンポーネントファクトリの基底クラス。
   *
   * @else
   *
   * @class RtcFactoryBase
   *
   * @brief RtcFactoryBase base class
   *
   * RTComponent factory base class.
   *
   * @endif
   */
  class EXPORTS RtcFactoryBase
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief RtcFactoryBase クラスコンストラクタ
	 *
	 * RtcFactoryBase クラスのコンストラクタ。
	 *
	 * @param profile コンポーネントのプロファイル
	 *
	 * @else
	 *
	 * @brief RtcFactoryBase class constructor.
	 *
	 * RtcFactoryBase class constructor.
	 *
	 * @param profile component profile
	 *
	 * @endif
	 */
    RtcFactoryBase(RtcModuleProfile profile)
      : m_Profile(profile), m_Number(-1) {};
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントの生成
	 *
	 * Python で実装された RTComponent のインスタンスを生成する。
	 * 純粋仮想関数。
	 *
	 * @param mgr RtcManager へのポインタ
	 *
	 * @else
	 *
	 * @brief Create component
	 *
	 * Create component implemented in Python.
	 * Pure virtual method.
	 *
	 * @param mgr pointer to RtcManager
	 *
	 * @endif
	 */
    virtual RtcBase* create(RtcManager* mgr) = 0;
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントの破棄
	 *
	 * RTComponent のインスタンスを破棄する。
	 * 純粋仮想関数。
	 *
	 * @param comp RtcBase へのポインタ
	 *
	 * @else
	 *
	 * @brief Destroy component
	 *
	 * Destroy component instance
	 * Pure virtual method.
	 *
	 * @param comp pointer to RtcBase
	 *
	 * @endif
	 */
    virtual void destroy(RtcBase* comp) = 0;
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントプロファイルの取得
	 *
	 * コンポーネントのプロファイルを取得する
	 *
	 * @else
	 *
	 * @brief Get component profile
	 *
	 * Get component profile.
	 *
	 * @endif
	 */
    virtual RtcModuleProfile& profile() {return m_Profile;};
	
	/*!
	 * @if jp
	 *
	 * @brief 現在のインスタンス数
	 *
	 * コンポーネントの現在のインスタンス数を取得する。
	 *
	 * @else
	 *
	 * @brief Get number of component instances
	 *
	 * Get number of current component instances.
	 *
	 * @endif
	 */
    virtual int& number() {return m_Number;};
	
  protected:
	/*!
	 * @if jp
	 * @brief コンポーネントのプロファイル
	 * @else
	 * @brief Component profile
	 * @endif
	 */
    RtcModuleProfile m_Profile;
	/*!
	 * @if jp
	 * @brief 現在のインスタンス数
	 * @else
	 * @brief Number of current component instances.
	 * @endif
	 */
	int m_Number;
  };
  
  
  
  /*!
   * @if jp
   *
   * @class RtcFactoryCXX
   *
   * @brief RtcFactoryCXX クラス
   * 
   * C++用コンポーネントファクトリクラス。
   *
   * @else
   *
   * @class RtcFactoryCXX
   *
   * @brief RtcFactoryCXX class
   *
   * RTComponent factory class for C++.
   *
   * @endif
   */
  class EXPORTS RtcFactoryCXX
    : public RtcFactoryBase
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief RtcFactoryCXX クラスコンストラクタ
	 *
	 * RtcFactoryCXX クラスのコンストラクタ。
	 * プロファイル、生成関数へのポインタ、破棄関数へのポインタを引数に取り、
	 * C++ で実装されたコンポーネントのファクトリクラスを生成する。
	 *
	 * @param profile コンポーネントのプロファイル
	 * @param new_func コンポーネントの生成関数へのポインタ
	 * @param delete_func コンポーネントの破棄関数へのポインタ
	 *
	 * @else
	 *
	 * @brief RtcFactoryCXX class constructor.
	 *
	 * RtcFactoryCXX class constructor.
	 * Create component factory class with three arguments:
	 * component profile, function pointer to object create function and
	 * object delete function.
	 *
	 * @param profile Component profile
	 * @param new_func Pointer to component create function
	 * @param delete_func Pointer to component delete function
	 *
	 * @endif
	 */
    RtcFactoryCXX(RtcModuleProfile profile,
				  RtcNewFunc new_func,
				  RtcDeleteFunc delete_func);
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントの生成
	 *
	 * Python で実装された RTComponent のインスタンスを生成する。
	 *
	 * @param mgr RtcManager へのポインタ
	 *
	 * @else
	 *
	 * @brief Create component
	 *
	 * Create component implemented in Python.
	 *
	 * @param mgr pointer to RtcManager
	 *
	 * @endif
	 */
    virtual RtcBase* create(RtcManager* mgr);
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントの破棄
	 *
	 * RTComponent のインスタンスを破棄する。
	 *
	 * @param comp RtcBase へのポインタ
	 *
	 * @else
	 *
	 * @brief Destroy component
	 *
	 * Destroy component instance
	 *
	 * @param comp pointer to RtcBase
	 *
	 * @endif
	 */
    virtual void destroy(RtcBase* comp);
	
  protected:
	/*!
	 * @if jp
	 * @brief コンポーネントオブジェクト生成関数へのポインタ
	 * @else
	 * @brief The pointer to component object create function
	 * @endif
	 */
    RtcNewFunc m_New;
	
	/*!
	 * @if jp
	 * @brief コンポーネントオブジェクト破棄関数へのポインタ
	 * @else
	 * @brief The pointer to component object delete function
	 * @endif
	 */
    RtcDeleteFunc m_Delete;
  };
};


#endif // RtcFactory_h
