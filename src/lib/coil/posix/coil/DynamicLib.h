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

#include <dlfcn.h>
#include <string>
#include <coil/config_coil.h>

#define COIL_DEFAULT_DYNLIB_MODE RTLD_LAZY

extern "C"
{
  int ForExternTest(void);
}

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
    static int ForExternTest(void) { return 0xdeadbeef; }
    const char* error(void) const;
  private:
    std::string m_name;
    int m_mode;
    int m_closeflag;
    void* m_handle;
    int m_error;
  };

};

#endif // DynamicLib_h
