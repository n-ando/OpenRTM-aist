// -*- C++ -*-
/*!
 * @file ECFactory.h
 * @brief ExecutionContext Factory class
 * @date $Date: 2007-04-13 16:06:22 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ECFactory.h,v 1.1 2007-04-13 16:06:22 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef ECFactory_h
#define ECFactory_h

#include <rtm/ExecutionContextBase.h>
#include <string>

namespace RTC 
{

  typedef ExecutionContextBase* (*ECNewFunc)();
  typedef void (*ECDeleteFunc)(ExecutionContextBase* ec);

  template <class _New>
  ExecutionContextBase* ECCreate()
  {
    return new _New();
  }

  template <class _Delete>
  void ECDelete(ExecutionContextBase* ec)
  {
    delete ec;
  }


  class ECFactoryBase
  {
  public:
    virtual ~ECFactoryBase(){};
    virtual const char* name() = 0;
    virtual ExecutionContextBase* create() = 0;
    virtual void destroy(ExecutionContextBase* comp) = 0;
  protected:
  };
  
  class ECFactoryCXX
    : public ECFactoryBase
  {
  public:
    ECFactoryCXX(const char* name,
		 ECNewFunc new_func,
		 ECDeleteFunc delete_func);
    ~ECFactoryCXX();
    virtual const char* name();
    virtual ExecutionContextBase* create();
    virtual void destroy(ExecutionContextBase* comp);
    
  protected:
    std::string m_name;
    ECNewFunc m_New;
    ECDeleteFunc m_Delete;
  };
};


#endif // RtcFactory_h
