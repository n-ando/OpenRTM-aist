// -*- C++ -*-
/*!
 * @file rtcd.cpp
 * @brief RT component server daemon
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
 * $Id: rtcd.cpp,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include <iostream>
#include <rtm/RtcManager.h>

using namespace std;

int main (int argc, char** argv)
{
  RTM::RtcManager manager(argc, argv);

  manager.initManager();
  cout << "init Manager done" << endl;

  manager.activateManager();
  cout << "activate Manager done" << endl;

  manager.runManager();
  cout << "run Manager done" << endl;

  return 0;
}
