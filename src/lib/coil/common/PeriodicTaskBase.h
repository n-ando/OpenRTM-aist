// -*- C++ -*-
/*!
 * @file PeriodicTaskBase.h
 * @brief 
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

#ifndef COIL_PERIODICTASKBASE_H
#define COIL_PERIODICTASKBASE_H

#include <coil/TimeValue.h>
#include <coil/TimeMeasure.h>
#include <coil/Task.h>

namespace coil
{
  class TaskFuncBase
  {
  public:
    virtual ~TaskFuncBase() {}
    virtual int operator()() = 0;
  };
  
  template <typename T, typename F = int (*)()>
  class TaskFunc
    : public TaskFuncBase
  {
  public:
    TaskFunc(T* obj, F func)
      : m_obj(obj), m_func(func)
    {
    }
    virtual ~TaskFunc() {}
    virtual int operator()()
    {
      return (m_obj->*m_func)();
    }
    T* m_obj;
    F m_func;
  };

  class PeriodicTaskBase
    : public coil::Task
  {
  public:
    virtual ~PeriodicTaskBase(){};

    virtual void activate() = 0;
    virtual void finalize() = 0;
    virtual int suspend(void) = 0;
    virtual int resume(void) = 0;
    virtual void signal() = 0;
    virtual bool setTask(TaskFuncBase* func, bool delete_in_dtor = true) = 0;

    template <class O, class F>
    bool setTask(O* obj, F fun)
    {
      return this->setTask(new TaskFunc<O, F>(obj, fun));
    }
    virtual void setPeriod(double period) = 0;
    virtual void setPeriod(coil::TimeValue& period) = 0;
    virtual void executionMeasure(bool value) = 0;
    virtual void executionMeasureCount(int n) = 0;
    virtual void periodicMeasure(bool value) = 0;
    virtual void periodicMeasureCount(int n) = 0;
    virtual coil::TimeMeasure::Statistics getExecStat() = 0;
    virtual coil::TimeMeasure::Statistics getPeriodStat() = 0;
  };
}; // namespace coil

#endif // COIL_PERIODICTASKBASE_H
