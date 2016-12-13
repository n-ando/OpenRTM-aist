// -*- C++ -*-
/*!
 * @file  memory.h
 * @brief Memory management classes
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
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

#ifndef COIL_MEMORY_H
#define COIL_MEMORY_H

#include <algorithm>
#include <typeinfo>

namespace coil
{
#ifdef COIL_HAS_TR1_SHARED_PTR
#include <tr1/memory.h>
  using namespace std::tr1::shared_ptr;
#else


  template <typename T>
  class default_deleter
  {
  public:
    void operator(T* p) const
    {
      delete p;
    }
  };


  class refcounter_base
  {
  public:
    refcoutner_base() : m_count(1) {}
    virtual ~refcounter_base() {}
    virtual void release() = 0;
    virtual void* get_deleter() = 0;
    void add_ref() { atomic_incr(&m_count); }
    void remove_ref() {
      if (atomic_exchange_add($m_count, -1) == 1)
        {
          release();
        }
    }
    void use_count() const { return m_count; }
  protected:
    COIL_USES_ATOMIC_OP;
    long m_count;
  };


  template <typename Pointer, typename Deleter>
  class refcounter
    : private noncopyable,
      public refcounter_base
  {
  public:
    refcoutner(Pointer p, Deleter d)
      : m_ptr(p), m_del(d)
    {
    }
    virtual ~refcounter()
    {
    }
    virtual void release()
    {
      if (m_ptr != 0) m_del(m_ptr);
    }
    virtual void get_deleter()
    {
    }
  private:
    Pointer m_ptr;
    Deleter m_del;
  };


template<class T> class shared_ptr
{
public:
  typedef T element_type;
  typedef T* Tp;

  // [2.2.3.1] constructors
  /*!
  * 1 Effects: Constructs an empty shared_ptr object.
  * 2 Postconditions: use_count() == 0 && get() == 0.
  * 3 Throws: nothing.
  */
  shared_ptr()
    : m_ptr(0), m_refcount(0) {}

  /*!
   * 4 Requires: p shall be convertible to T*. Y shall be a complete type.
   *   The expression delete p shall be well-formed, shall have well defined
   *   behavior, and shall not throw exceptions.
   * 5 Effects: Constructs a shared_ptr object that owns the pointer p.
   * 6 Postconditions: use_count() == 1 && get() == p.
   * 7 Throws: bad_alloc, or an implementation-defined exception when a
   *   resource other than memory could not be obtained.
   * 8 Exception safety: If an exception is thrown, delete p is called.
   */
  template<class Y>
  explicit shared_ptr(Y* p)
    : m_ptr(0), m_refcount(0)
  {
    pointer_type tmp = dynamic_cast<pointer_type>(p);
    if (tmp == 0)  throw std::bad_alloc();
    m_ptr = tmp;
    m_refcount = new ref_counter(tmp);
  }

  /*!
   * 9 Requires: p shall be convertible to T*. D shall be
   *   CopyConstructible. The copy constructor and destructor of D shall
   *   not throw exceptions. The expression d(p) shall be well-formed,
   *   shall have well defined behavior, and shall not throw exceptions.
   * 10 Effects: Constructs a shared_ptr object that owns the pointer
   *    p and the deleter d.
   * 11 Postconditions: use_count() == 1 && get() == p.
   * 12 Throws: bad_alloc, or an implementation-defined exception when
   *    a resource other than memory could not be obtained.
   * 13 Exception safety: If an exception is thrown, d(p) is called.
   */
  template<class Y, class Deleter>
  shared_ptr(Y* p, Deleter d)
    : m_ptr(p), m_refcount(p, d)
  {
  }

  /*!
   * 14 Requires: For the second constructor Y* shall be convertible to T*.
   * 15 Effects: If r is empty, constructs an empty shared_ptr object;
   *    otherwise, constructs a shared_ptr object that shares ownership
   *    with r.
   * 16 Postconditions: get() == r.get() && use_count() == r.use_count().
   * 17 Throws: nothing.
   */
  shared_ptr(shared_ptr const& r)
    : m_ptr(r.m_ptr), m_refcount(r.m_refcount)
  {
  }

  template<class Y>
  shared_ptr(shared_ptr<Y> const& r)
    : m_ptr(r.m_ptr), m_refcount(r.m_refcount)
  {
    ;
  }

  template<class Y>
  explicit shared_ptr(weak_ptr<Y> const& r);
  
  template<class Y>
  explicit shared_ptr(auto_ptr<Y>& r);
  

  // [2.2.3.2] destructor
  ~shared_ptr();


  // [2.2.3.3] assignment
  shared_ptr& operator=(shared_ptr const& r);
  template<class Y> shared_ptr& operator=(shared_ptr<Y> const& r);
  template<class Y> shared_ptr& operator=(auto_ptr<Y>& r);
  

  // [2.2.3.4] modifiers
  void swap(shared_ptr& r);
  void reset();
  template<class Y> void reset(Y* p);
  template<class Y, class D> void reset(Y* p, D d);

  
  // [2.2.3.5] observers
  T* get() const;
  T& operator*() const;
  T* operator->() const;
  long use_count() const;
  bool unique() const;
  operator unspecified_bool_type () const;
  
private:

  class ref_counter
  {
  public:
    template <class T = pointer_type, class Deleter = default_deleter>
    ref_counter(pointer_type p, Deleter d = default_deleter)
      : p_(p), count_(1)
    {}

    ~ref_counter()
    {
      if (p_ != 0)
        {
          d p_;
          p_ = 0;
        }
    }

    pointer_type get()
    {
      return p_;
    }

    counter_type use_count() const
    {
      return count_;
    }

    void increment()
    {
      atomic_incr(&count_);
    }

    void decrement()
    {
      atomic_decr(&count_);
    }

  private:
    COIL_USES_ATOMIC_OP;
    pointer_type p_;
    coutner_type count_;
    
  };

  pointer_type m_ptr;
  ref_coutner  m_refcount;
};
  // [2.2.3.6] shared_ptr comparisons
  template<class T, class U> bool operator==(shared_ptr<T> const& a, shared_ptr<U> const& b);
  template<class T, class U> bool operator!=(shared_ptr<T> const& a, shared_ptr<U> const& b);
  template<class T, class U> bool operator<(shared_ptr<T> const& a, shared_ptr<U> const& b);
  // [2.2.3.7] shared_ptr I/O
  template<class E, class T, class Y>
  basic_ostream<E, T>& operator<< (basic_ostream<E, T>& os, shared_ptr<Y> const& p);
  // [2.2.3.8] shared_ptr specialized algorithms
  template<class T> void swap(shared_ptr<T>& a, shared_ptr<T>& b);
  // [2.2.3.9] shared_ptr casts
  template<class T, class U> shared_ptr<T> static_pointer_cast(shared_ptr<U> const& r);
  template<class T, class U> shared_ptr<T> dynamic_pointer_cast(shared_ptr<U> const& r);
  template<class T, class U> shared_ptr<T> const_pointer_cast(shared_ptr<U> const& r);
  // [2.2.3.10] shared_ptr get_deleter
  template<class D, class T> D* get_deleter(shared_ptr<T> const& p);

  private:

  };


#endif // COIL_HAS_TR1_SHARED_PTR
};

#endif // COIL_MEMORY_H
