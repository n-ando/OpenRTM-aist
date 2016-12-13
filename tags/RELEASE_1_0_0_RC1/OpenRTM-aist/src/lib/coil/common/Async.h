// -*- C++ -*-
/*!
 * @file Async.h
 * @brief Asynchronous function invocation helper class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_ASYNC_H
#define COIL_ASYNC_H

#include <coil/Task.h>
#include <coil/Guard.h>
#include <iostream>

namespace coil
{
  class Async
    : public coil::Task
  {
  public:
    Async() {}
    virtual ~Async(){}
    virtual void invoke() = 0;
    virtual bool finished() = 0;
  };
  
  template <typename Object, typename Func>
  class Async_t
    : public Async
  {
  public:
    Async_t(Object* obj, Func func, bool auto_delete = false)
      : m_obj(obj), m_func(func), m_finished(false), m_autodelete(auto_delete)
    {
    }
    virtual ~Async_t()
    {
    }
    
    virtual int svc()
    {
      m_func(m_obj);
      {
        Guard<Mutex> guard(m_mutex);
        m_finished = true;
      }
      
      return 0;
    }
    virtual void finalize()
    {
      Task::finalize();
      if (m_autodelete) delete this;
    }
    virtual void invoke()
    {
      activate();
    }
    virtual bool finished()
    {
      Guard<Mutex> guard(m_mutex);
      return m_finished;
    }
  private:
    Object* m_obj;
    Func m_func;
    bool m_finished;
    const bool m_autodelete;
    Mutex m_mutex;
  };
  
  template <typename Object, typename Func>
  class Async_ref_t
    : public Async
  {
  public:
    Async_ref_t(Object* obj, Func& func, bool auto_delete = false)
      : m_obj(obj), m_func(func), m_finished(false), m_autodelete(auto_delete)
    {
    }
    virtual ~Async_ref_t()
    {
    }
    
    virtual int svc()
    {
      m_func(m_obj);
      m_finished = true;
      return 0;
    }
    virtual void invoke()
    {
      activate();
    }
    virtual bool finished()
    {
      return m_finished;
    }
    virtual void finalize()
    {
      Task::finalize();
      if (m_autodelete) delete this;
    }
  private:
    Object* m_obj;
    Func& m_func;
    bool m_finished;
    bool m_autodelete;
    
  };
  
  /*!
   * @if jp
   * @brief 非同期メンバー関数呼び出しヘルパー関数
   *
   * メンバー関数を非同期に呼ぶためのヘルパー関数
   * 例
   *
   *  class A
   *  {
   *  public:
   *    // 時間のかかる関数
   *    void hoge() {
   *      for (int i(0); i < 5; ++i) {
   *        std::cout << "hoge" << std::endl;
   *        sleep(1);
   *      }
   *    }
   *    // 時間のかかる関数
   *    void munya(const char* msg) {
   *      for (int i(0); i < 10; ++i) {
   *        std::cout << "message is: " << msg << std::endl;
   *        sleep(1);
   *      }
   *    }
   *    int add_one(int val) {
   *      return val + 1;
   *    }
   *  };
   * この様なクラスのオブジェクトに対して、
   *
   *  A a;
   *  Async* invoker0(AsyncInvoker(&a,
   *                               std::mem_fun(&A::hoge)));
   *  Async* invoker1(AsyncInvoker(&a,
   *                               std::bind2nd(std::mem_fun(&A::munya),
   *                                            "ほげ")));
   *  invoker0->invoke(); // すぐに戻る
   *  invoker1->invoke(); // すぐに戻る
   *
   *  delete invoker0; // 必ず削除すること
   *  delete invoker1; // 必ず削除すること
   *
   * のように非同期の呼び出しができる。
   * 呼び出しの戻り値を取得したい場合は、自前の関数オブジェクトを用意する。
   *
   *  class add_one_functor
   *  {
   *    int m_val, m_ret;
   *  public:
   *    add_one_functor(int val) : m_val(val), m_ret(0) {}
   *    void operaotr(A* obj) {
   *      m_ret = obj->add_one(m_val);
   *    }
   *    int get_ret() {
   *      return m_ret;
   *    }
   *  };
   *
   * 上記の関数オブジェクトのインスタンスを作成し、そのポインタを渡す。
   *
   *  add_one_functor aof(100);
   *  Async* invoker2(AsyncInvoker(&a, &aof));
   *  invoker2->invoke();
   *  invoker2->wait();
   *  std::cout << "result: " << aof.get_ret() << std::endl;
   *  delete invoker2;
   *
   * 通常、AsyncInvoker が返すオブジェクトは明示的に削除しなければ
   * ならないが、第三引数に true を渡すことで、非同期実行が終了すると同時に
   * 自動的にインスタンスが削除される。
   *
   * // invoker3 は削除 (delete invoker3) してはいけない
   * Async* invoker3(AsyncInvoker(&a, std::mem_fun(&A::hoge), true));
   *
   * // インスタンス生成と同時に実行することもできる。
   * AsyncInvoker(&a, std::mem_fun(&A::hoge))->invoke();
   *
   * @else
   *
   * @endif
   */
  template <typename Object, typename Func>
  inline Async_t<Object, Func>*
  AsyncInvoker(Object* obj, Func func, bool auto_delete = false)
  {
    return new Async_t<Object, Func>(obj, func, auto_delete);
  }

  template <typename Object, typename Func>
  inline Async_ref_t<Object, Func>*
  AsyncInvoker(Object* obj, Func* func, bool auto_delete = false)
  {
    return new Async_ref_t<Object, Func>(obj, *func, auto_delete);
  }


};

#endif // COIL_ASYNC_H
