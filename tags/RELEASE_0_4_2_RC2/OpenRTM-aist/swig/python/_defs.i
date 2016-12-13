// -*- C++ -*-
/*!
 * @file _defs.i
 * @brief swig interface file for type definition
 * @date $Date: 2005-05-12 09:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

namespace RTM {
  typedef short int RtmRes;
};

//%{
  //#include "pyhelper.h"
//%}

//%exception
//{
//  PyThreadState* __tstate = rtmPyBeginAllowThreads();
//  $function
//  rtmPyEndAllowThreads(__tstate);
//  if (PyErr_Occurred()) return NULL;
//}
