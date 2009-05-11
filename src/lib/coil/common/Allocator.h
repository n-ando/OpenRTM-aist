// -*- C++ -*-
/*!
 * @file  Allocator.h
 * @brief Memory allocator class
 * @date  $Date$
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
 * $Id: PublisherPeriodic.h 1225 2009-02-28 02:30:25Z n-ando $
 *
 */

#ifndef COIL_ALLOCATOR_H
#define COIL_ALLOCATOR_H

#include <stddef.h>
#include <coil/Singleton.h>

namespace coil
{
  class Allocator
    : public Singleton<Allocator>
  {
  public:
    virtual ~Allocator(){};
    virtual void* New(size_t t) throw (std::bad_alloc);
    virtual void Delete(void* p) throw ();
    virtual void* NewArray(size_t t) throw (std::bad_alloc);
    virtual void DeleteArray(void* p) throw ();
  };
};
#endif // COIL_ALLOCATOR_H
