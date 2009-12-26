// -*- C++ -*-
/*!
 * @file DynamicLib.cpp
 * @brief DynamicLib class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008 Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/DynamicLib.h>

namespace coil
{
  DynamicLib::DynamicLib(int close_handle_on_destruction)
    : m_closeflag(close_handle_on_destruction)
  {
  }

  DynamicLib::DynamicLib(const char* dynlib_name,
                         int open_mode,
                         int close_handle_on_destruction)
    : m_name(dynlib_name), m_mode(open_mode),
      m_closeflag(close_handle_on_destruction)
  {
    if (open(m_name.c_str(), m_mode, m_closeflag) != 0)
      {
        throw std::bad_alloc();
      }
  }

  DynamicLib::~DynamicLib()
  {
    close();
  }

  DynamicLib::DynamicLib(const DynamicLib& rhs)
    : m_name(""), m_mode(0), m_closeflag(0), m_handle(0)
  {
    if (!rhs.m_name.empty() &&
        open(rhs.m_name.c_str(), rhs.m_mode, rhs.m_closeflag) == 0)
      return;
//    throw std::bad_alloc();
  }

  DynamicLib& DynamicLib::operator=(const DynamicLib& rhs)
  {
    DynamicLib tmp(rhs);
    std::swap(this->m_name, tmp.m_name);
    std::swap(this->m_mode, tmp.m_mode);
    std::swap(this->m_closeflag, tmp.m_closeflag);
    std::swap(this->m_handle, tmp.m_handle);
    return *this;
  }

  int DynamicLib::open(const char* dll_name,
                   int open_mode,
                   int close_handle_on_destruction)
  {
    void* handle = ::dlopen(dll_name, open_mode);
    if (handle == NULL)
      {
        return -1;
      }
    m_handle = handle;
    m_name = dll_name;
    return 0;
  }

  int DynamicLib::close(void)
  {
    if (m_handle == NULL)
      return -1;
    if (m_name.empty())
      {
        return -1;
      }
    ::dlclose(m_handle);
    m_handle = NULL;
    m_name = "";
    return 0;
  }

  void* DynamicLib::symbol(const char* symbol_name)
  {
    if (m_handle == NULL) return NULL;
    return ::dlsym(m_handle, symbol_name);
  }

  const char* DynamicLib::error(void) const
  {
    return ::dlerror();
  }
};

/*!
 * for unit test.
 */
extern "C"
{
  int ForExternTest(void) { return coil::DynamicLib::ForExternTest(); }
}
