// -*- C++ -*-
/*!
 * @file Singleton.h
 * @brief Singleton template class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_SINGLETON_H
#define COIL_SINGLETON_H

#include <mutex>

namespace coil
{
  /*!
   * @if jp
   *
   * @class Singleton
   * @brief Singleton テンプレートクラス
   *
   * このテンプレートは、任意のクラスを Singleton にするテンプレートである。
   * 以下のようにして使用する。
   *
   * class A { // };
   * using A_ = coil::Singleton<A>;
   *
   * 任意の場所で
   *
   * A& a(A_:instance()); // a は A の唯一のインスタンスが入る
   *
   * ただし、A自体のコンストラクタは使用できるので、同一のソースで、
   *
   * A* a = new A();
   *
   * のようにすることもできるため、注意が必要である。
   * 対象とするクラスを new することを禁止するためには、以下のように、
   * 対象クラスで Singelton を継承 (CRTP) し friend 宣言する必要がある。
   *
   * class A
   *  : public coil::Singleton<A>
   * {
   * public:
   * private:
   *   A(){}
   *
   *   friend class coil::Singelton<A>;
   * };
   *
   * こうすることで、
   *
   * A* a = new A(); // は禁止される
   * A& a(A::instance()); // が唯一のインスタンスを得る唯一の方法
   *
   * @else
   *
   * @class Singleton
   * @brief Singleton template class
   *
   * This class template makes any classed into Singleton classes.
   * Usage is as follows.
   *
   * class A { // };
   * using A_ = coil::Singleton<A>;
   *
   * In the any places,
   * A& a(A_:instance()); // a has singular instance of A
   *
   * Since the constructor of A is still public, however, user can
   * create other instance of A as follows.
   *
   * A* a = new A();
   *
   * If you want to prohibit user from creating new instance, please
   * inherit Singleton class (CRTP) and declare it as a friend class
   * in the target class.
   *
   * class A
   *  : public coil::Singleton<A>
   * {
   * public:
   * private:
   *   A(){}
   *
   *   friend class coil::Singelton<A>;
   * };
   *
   * A* a = new A(); // compile error
   * A& a(A::instance()); // This is the only method to get unique instance
   *
   * @endif
   */
  template <class SingletonClass>
  class Singleton
  {
  public:
    // A helper class to call SingletonClass-destructor.
    struct Container
    {
      SingletonClass* x;
      ~Container(){ delete x; }
    };

    /*!
     * @if jp
     *
     * @brief インスタンス生成
     *
     * インスタンスを生成する。
     *
     * @return インスタンス
     *
     * @else
     *
     * @brief Create instance
     *
     * Create instance.
     *
     * @return Instances
     *
     * @endif
     */
    static SingletonClass& instance()
    {
      std::call_once(m_once, []{
        m_instance.x = new SingletonClass();
      });
      return *m_instance.x;
    }

  protected:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    Singleton() = default;

    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~Singleton() = default;

  private:
    Singleton(const Singleton& x) = delete;
    Singleton& operator=(const Singleton& x) = delete;

    /*!
     * @if jp
     * @brief 排他制御オブジェクト
     * @else
     * @brief Mutual exclusion object
     * @endif
     */
    static std::once_flag m_once;

    /*!
     * @if jp
     * @brief SingletonClass オブジェクト
     * @else
     * @brief SingletonClass object
     * @endif
     */
    static Container m_instance;
  };

  template <class SingletonClass>
  typename Singleton<SingletonClass>::Container
  Singleton<SingletonClass>::m_instance;

  template <class SingletonClass>
  std::once_flag Singleton<SingletonClass>::m_once;
} // namespace coil

#endif  // COIL_SINGLETON_H
