// -*- C++ -*-
/*!
 * @file properties.h
 * @brief hrtm::Peoperties wrapper class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2016
 *     Noriaki Ando
 *     National Institute of
 *     Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef HRTM_PROPERTIES_H
#define HRTM_PROPERTIES_H

#include <coil/Properties.h>

namespace hrtm
{
namespace utils
{
  class Properties
    : public coil::Properties
  {
  public:
    explicit Properties();
    explicit Properties(const char* defaults[], long num = LONG_MAX);
    virtual ~Properties();
  };
}; // namespace utils
}; // namespace hrtm
#endif // HRTM_PROPERTIES_H

