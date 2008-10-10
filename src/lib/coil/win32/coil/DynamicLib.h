// -*- C++ -*-
/*!
 * @file DynamicLib_posix.h
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

#ifndef COIL_DYNAMICLIB_H
#define COIL_DYNAMICLIB_H

#include <windows.h>
#include <string>
#include <coil/config_coil.h>

#define COIL_DEFAULT_DYNLIB_MODE DONT_RESOLVE_DLL_REFERENCES

namespace coil
{
  class DynamicLib
  {
  public:
    DynamicLib(int close_handle_on_destruction = 1);
    DynamicLib(const char* dynlib_name,
               int open_mode = COIL_DEFAULT_DYNLIB_MODE,
               int close_handle_on_destruction = 1);
    virtual ~DynamicLib();
    DynamicLib(const DynamicLib& rhs);
    DynamicLib& operator=(const DynamicLib& rhs);

    virtual int open(const char* dll_name,
                     int open_mode = COIL_DEFAULT_DYNLIB_MODE,
                     int close_handle_on_destruction = 1);
    virtual int close(void);
    void *symbol (const char* symbol_name);
    const char* error(void) const;
  private:
    std::string m_name;
    int m_mode;
    int m_closeflag;
    HINSTANCE m_handle;
    int m_error;
    char m_strbuf[256];
  };

};

#endif // DynamicLib_h
