// -*- C++ -*-
/*!
 * @file CorbaConsumer.h
 * @brief CORBA Consumer class
 * @date $Date: 2006-11-21 08:32:26 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: CorbaConsumer.h,v 1.1 2006-11-21 08:32:26 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef Consumer_h
#define Consumer_h

#ifdef ORB_IS_MICO
#include <CORBA.h>
#endif
#ifdef ORB_IS_OMNIORB
#include <omniORB4/CORBA.h>
#endif
#ifdef ORB_IS_ORBACUS
#include <OB/CORBA.h>
#endif
#ifdef ORB_IS_ORBIT2
#include <orbitcpp/orb-cpp/orbitcpp.h>
#endif
#ifdef ORB_IS_ORBIX
#include <CORBA.h>
#endif
#ifdef ORB_IS_TAO
#include <tao/corba.h>
#endif

namespace RTC
{
  /*!
   * @if jp
   * @class ConsumerBase
   * @brief オブジェクトリファレンスを保持するプレースホルダ基底クラス
   * @else
   * @class ConsumerBase
   * @brief Placeholder base class to hold remote object reference.
   * @endif
   */
  class ConsumerBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Consructor
     * @endif
     */
    ConsumerBase(){};

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ConsumerBase(){};

    /*!
     * @if jp
     *
     * @brief CORBAオブジェクトをセットする
     *
     * 与えられたオブジェクトリファレンスは、ConsumerBase オブジェクト内に
     * CORBA::Object_var 型として保持される。 
     *
     * @param obj CORBA オブジェクトのリファレンス
     * @return obj が nil リファレンスの場合 false を返す。
     *
     * @else
     *
     * @brief Set CORBA Object
     *
     * The given CORBA Object is held as CORBA::Object_var type
     *
     * @param obj Object reference of CORBA object
     * @return If obj is nil reference, it returns false.
     *
     * @endif
     */
    virtual bool setObject(CORBA::Object_ptr obj)
    {
      if (CORBA::is_nil(obj))
	{
	  return false;
	}
      m_objref = obj;
      return true;
    }

    /*!
     * @if jp
     *
     * @brief CORBAオブジェクトを取得する
     *
     * 与えられたオブジェクトリファレンスは、ConsumerBase オブジェクト内に
     * CORBA::Object_var 型として保持される。 
     *
     * @param obj CORBA オブジェクトのリファレンス
     *
     * @else
     *
     * @brief Set CORBA Object
     *
     * The given CORBA Object is held as CORBA::Object_var type
     *
     * @param obj Object reference of CORBA object
     *
     * @endif
     */
    virtual CORBA::Object_ptr getObject()
    {
      return m_objref;
    }

  protected:
    CORBA::Object_var m_objref;
  };



  /*!
   * @if jp
   *
   * @class Consumer
   * @brief オブジェクトリファレンスを保持するプレースホルダテンプレートクラス
   * 
   * テンプレート引数で与えられた型のオブジェクトを保持する。
   * オブジェクトがセットされたときに、与えられた型で narrow されるので、
   * _ptr() で取得するリファレンスは、narrow 済みのリファレンスである。
   * 内部的な使用のために、_ptr 型, _var型も同時にテンプレート引数として
   * 与える必要がある。(下記注意事項参照)
   * <br>  
   * 注意: ObjectTypePtr = ObjectType::_ptr_type としているか、
   *       _ptr_type は標準では規定されていない。
   *       ただし、omniORB, TAO, MICO では、プロキシクラス内部で、
   *       Type_ptr 型を _ptr_type に typedef しているので、
   *       テンプレートの第2引数を指定しなくてもコンパイルは通る。
   *
   * @param ObjectType このホルダが保持するオブジェクトの型
   * @param ObjectTypePtr このホルダが保持する _ptr 型
   * @param ObjectTypeVar このホルダが保持する _var 型
   *
   * @else
   *
   * @class Consumer
   * @brief Placeholder template class to hold remote object reference.
   *
   * This class holds a type of object that given by template parameter.
   * For internal use, _ptr type and _var type should be given as template
   * parameter. (Please refere the following notation.)
   *
   * Note: ObjectTypePtr's default value is defined as ObjectType::_ptr_type,
   *       although _ptr_type is not defined as normative type.
   *       However, omniORB, TAO, MICO, ORBit, ORBacus define _ptr_type and
   *       _var_type as _ptr type and _var type in stub code.
   *       Usually, you don't need to specify 2nd and 3rd template arguments.
   *       
   * @endif
   */
  template <class ObjectType,
	    class ObjectTypePtr = class ObjectType::_ptr_type,
	    class ObjectTypeVar = class ObjectType::_var_type>
  class Consumer
    : public ConsumerBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Consructor
     * @endif
     */
    Consumer(){};
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~Consumer(){};

    /*!
     * @if jp
     * @brief オブジェクトをセットする
     *
     * ConsumerBase のオーバーライド。CORBA::Object_var にオブジェクトをセット
     * するとともに、templateパラメータの型で narrow したオブジェクトを
     * メンバ変数に保持する。
     *
     * @param obj CORBA Objecct
     * 
     * @else
     * @brief Set Object
     *
     * Override function of ConsumerBase. This operation set an Object to 
     * CORBA:Object_var in the class, and this object is narrowed to
     * given template parameter and stored in the member variable.
     *
     * @endif
     */
    virtual bool setObject(CORBA::Object_ptr obj)
    {
      if (ConsumerBase::setObject(obj))
	{
	  m_var = ObjectType::_narrow(m_objref);
	  if (!CORBA::is_nil(m_var))
	    return true;
	}
      return false; // object is nil
    }

    inline ObjectTypePtr _ptr()
    {
      return m_var;
    }
  protected:
    ObjectTypeVar m_var;

  };
}; // namespace RTC
#endif // Consumer_h
