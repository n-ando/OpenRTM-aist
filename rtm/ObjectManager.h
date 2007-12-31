// -*- C++ -*-
/*!
 * @file ObjectManager.h
 * @brief Object management class
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ObjectManager.h,v 1.6.2.2 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6.2.1  2007/09/20 11:42:25  n-ando
 * for_each const function was added.
 *
 * Revision 1.6  2007/04/27 03:27:25  n-ando
 * A trivial fix.
 *
 * Revision 1.5  2007/04/26 15:30:32  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.4  2007/04/13 18:11:26  n-ando
 * Now return values are used for error propagation instead of exception.
 *
 * Revision 1.3  2006/11/06 01:42:22  n-ando
 * ObjectManager's for_each has been modified to return Predicate object.
 *
 * Revision 1.2  2006/10/25 17:31:03  n-ando
 * for_each()'s arguments are changed from value to reference.
 *
 * Revision 1.1  2006/10/17 10:21:50  n-ando
 * The first commitment.
 *
 *
 */

#ifndef ObjectManager_h
#define ObjectManager_h

#include <rtm/RTC.h>

#include <vector>
#include <string>
#include <algorithm>

#include <ace/Thread.h>
#include <ace/Synch.h>

/*!
 * @if jp
 *
 * @brief オブジェクト管理用クラス
 *
 * 各種オブジェクトを管理するためのクラス。
 *
 * @since 0.4.0
 *
 * @else
 *
 * @endif
 */
template <typename Identifier, typename Object, typename Predicate>
class ObjectManager
{
public:
  typedef std::vector<Object*>                  ObjectVector;
  typedef typename ObjectVector::iterator       ObjectVectorItr;
  typedef typename ObjectVector::const_iterator ObjectVectorConstItr;
  
  /*!
   * @if jp
   *
   * @brief コンストラクタ
   * 
   * コンストラクタ
   * 
   * @else
   *
   * @endif
   */
  ObjectManager(){};
  
  /*!
   * @if jp
   *
   * @brief デストラクタ
   * 
   * デストラクタ
   * 
   * @else
   *
   * @endif
   */
  ~ObjectManager(){};
  
  /*!
   * @if jp
   *
   * @brief 指定したオブジェクトを登録する
   * 
   * 指定したオブジェクトを登録する。
   * 同一オブジェクトが登録済みの場合は、何も行わない。
   *
   * @param obj 登録対象オブジェクト
   *
   * @return 登録処理結果(オブジェクトを登録した場合にtrue)
   * 
   * @else
   *
   * @endif
   */
  bool registerObject(Object* obj)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    
    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(obj));
    if (it == m_objects._obj.end())
      {
	m_objects._obj.push_back(obj);
	return true;
      }
    return false;
  }
  
  /*!
   * @if jp
   *
   * @brief 指定したオブジェクトを登録解除する
   * 
   * 指定したオブジェクトの登録を解除し、取得する。
   * 指定したオブジェクトが登録されていない場合にはNULLを返す。
   *
   * @param id 登録解除対象オブジェクトのID
   *
   * @return 登録解除されたオブジェクト
   * 
   * @else
   *
   * @endif
   */
  Object* unregisterObject(const Identifier& id)
  {
    ObjectVectorItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    
    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it != m_objects._obj.end())
      {
	Object* obj(*it);
	m_objects._obj.erase(it);
	return obj;
      }
    return NULL;;
  }
  
  /*!
   * @if jp
   *
   * @brief オブジェクトを検索する
   * 
   * 登録されているオブジェクトの中から指定した条件に合致するオブジェクトを検索
   * して取得する。
   * 指定した条件に合致するオブジェクトが登録されていない場合にはNULLを返す。
   *
   * @param id 検索対象オブジェクトのID
   *
   * @return オブジェクトの検索結果
   * 
   * @else
   *
   * @endif
   */
  Object* find(const Identifier& id) const
  {
    ObjectVectorConstItr it;
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    it = std::find_if(m_objects._obj.begin(), m_objects._obj.end(),
		      Predicate(id));
    if (it != m_objects._obj.end())
      {
	return *it;
      }
    return NULL;
  }
  
  /*!
   * @if jp
   *
   * @brief 登録されているオブジェクトのリストを取得する
   * 
   * 登録されているオブジェクトのリストを取得する。
   *
   * @return 登録されているオブジェクト・リスト
   * 
   * @else
   *
   * @endif
   */
  std::vector<Object*> getObjects() const
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    return m_objects._obj;
  }
  
  /*!
   * @if jp
   * @brief オブジェクト検索用ファンクタ
   * @else
   *
   * @endif
   */
  template <class Pred>
  Pred for_each(Pred p)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    return std::for_each(m_objects._obj.begin(), m_objects._obj.end(), p);
  }
  
  /*!
   * @if jp
   * @brief オブジェクト検索用ファンクタ
   * @else
   *
   * @endif
   */
  template <class Pred>
  Pred for_each(Pred p) const
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_objects._mutex);
    return std::for_each(m_objects._obj.begin(), m_objects._obj.end(), p);
  }
  
protected:
  /*!
   * @if jp
   * @brief オブジェクト管理用構造体
   * @else
   *
   * @endif
   */
  struct Objects
  {
    mutable ACE_Thread_Mutex _mutex;
    ObjectVector _obj;
  };
  /*!
   * @if jp
   * @brief 登録済みオブジェクト・リスト
   * @else
   *
   * @endif
   */
  Objects m_objects;
};
#endif // ObjectManager_h
