// -*- C++ -*-
/*!
 * @file RtcFactory.h
 * @brief RT component manager class
 * @date $Date: 2006-10-24 14:25:26 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Factory.cpp,v 1.2 2006-10-24 14:25:26 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include "rtm/RtcBase.h"
#include "rtm/RtcModuleProfile.h"
#include "rtm/RtcManager.h"
#include "rtm/RtcFactory.h"

namespace RTM 
{


  RtcFactoryCXX::RtcFactoryCXX(RtcModuleProfile profile,
			       RtcNewFunc new_func,
			       RtcDeleteFunc delete_func)
    : RtcFactoryBase(profile), m_New(new_func), m_Delete(delete_func)
  {
  }


  RtcBase* RtcFactoryCXX::create(RtcManager* mgr)
  {
    ++m_Number;
    return m_New(mgr);
  }

  void RtcFactoryCXX::destroy(RtcBase* comp)
  {
    m_Delete(comp);
  }

};

