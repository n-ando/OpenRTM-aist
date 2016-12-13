// -*- C++ -*-
/*!
 * @file Task.cpp
 * @brief Task class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_FILE_H
#define COIL_FILE_H

#include <libgen.h>
#include <coil/config_coil.h>
#include <memory>


namespace coil
{

  inline char* dirname(char* path)
  {
    return ::dirname(path);
  }

  inline const char* basename(const char* path)
  {
    const char *cp = strrchr(path,'/');
    if(cp == 0)
    {
       return path;
    }
    else
    {
       return cp + 1 ;
    }
  }
};

#endif // COIL_FILE_H
