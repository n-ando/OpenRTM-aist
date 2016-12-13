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
#include <iostream>
#include <string>
#include <coil/config_coil.h>

#define COIL_DEFAULT_DYNLIB_MODE LOAD_WITH_ALTERED_SEARCH_PATH

/*!
 * Test for DLL export.
 */
#ifdef TEST_DYNAMIC_LIB
#  define  DynamicLib_EXPORT __declspec(dllexport)
#else
#  define  DynamicLib_EXPORT __declspec(dllimport)
#endif

extern "C"
{
  DynamicLib_EXPORT int ForExternTest(void);
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
    const char* error(void) const;
    static int ForExternTest(void) { 
        std::cout<<"ForExternTest"<<std::endl;
        return 0xdeadbeef; 
    }
  private:
    std::string m_name;
    int m_mode;
    int m_closeflag;
    HINSTANCE m_handle;
    int m_error;
  };  // class DynamicLib

};  // namespace coil

#endif // DynamicLib_h
