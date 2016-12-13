/* -*- C++ -*-
 *
 * @file RtcInPortBase.cpp
 * @brief Input channel base class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcInPortBase.cpp,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/RtcInPortBase.h"

namespace RTM
{

  //============================================================
  // CORBA interface
  //============================================================
  PortProfile* InPortBase::profile()
	throw (CORBA::SystemException)
  {
	PortProfile_var profile = new PortProfile(m_Profile);

	return profile._retn();
  }

};

