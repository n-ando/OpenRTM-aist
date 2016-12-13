// -*- C++ -*-
/*!
 * @file ECFactory.cpp
 * @brief ExecutionContext fuctory class
 * @date $Date: 2007-04-13 16:06:16 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ECFactory.cpp,v 1.1 2007-04-13 16:06:16 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/ECFactory.h>

namespace RTC 
{

  ECFactoryCXX::ECFactoryCXX(const char* name,
			     ECNewFunc new_func,
			     ECDeleteFunc delete_func)
    : m_name(name),
      m_New(new_func),
      m_Delete(delete_func)
  {
  }

  ECFactoryCXX::~ECFactoryCXX()
  {
  }

  const char* ECFactoryCXX::name()
  {
    return m_name.c_str();
  }

  ExecutionContextBase* ECFactoryCXX::create()
  {
    return m_New();
  }

  void ECFactoryCXX::destroy(ExecutionContextBase* ec)
  {
    m_Delete(ec);
  }

};

