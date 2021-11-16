// -*- C++ -*-
/*!
 * @file Async.cpp
 * @brief Asynchronous function invocation helper class
 * @date $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2021
 *     Industrial Cyber-Physical Systems Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/Async.h>

namespace coil
{
  DeleteAsyncThread* DeleteAsyncThread::delasync = nullptr;
  std::mutex DeleteAsyncThread::mutex;
}

