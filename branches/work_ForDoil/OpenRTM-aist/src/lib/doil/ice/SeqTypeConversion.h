// -*- C++ -*-
/*!
 * @file  SeqTypeConversion.h
 * @brief SeqTypeConversion
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef DOIL_ICE_SEQTYPECONVERSION_H
#define DOIL_ICE_SEQTYPECONVERSION_H

#include <coil/stringutil.h>
#include <doil/ice/Ice.h>
#include <string>
#include <vector>

//-------------------------------------------------------------
// local -> ice
template <typename LocalSeq, typename LocalElement,
          typename IceSeq, typename IceElement>
bool local_to_ice_seq(const LocalSeq& _from, IceSeq& _to)
{
  long int len(_from.size());
  _to.length((::Ice::Long)len);
  for (long int i(0); i < len; ++i)
    {
      if (!local_to_ice(_from[i], _to[i])) return false;
    }
  return true;
}


template <typename IceSeq, typename IceType,
          typename LocalSeq, typename LocalType>
bool ice_to_local_seq(const IceSeq& _from, LocalSeq& _to)
{
  ::Ice::Long len(_from.length());
  _to.resize((long)len);
  for (::Ice::Long i(0); i < len; ++i)
    {
      if (!ice_to_local(_from[i], _to[i]))
        return false;
    }
  return true;
}

#endif // DOIL_ICE_SEQTYPECONVERSION_H
