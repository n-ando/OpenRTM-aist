// -*- C++ -*-
/*!
 * @file RTM.i
 * @brief swig interface file for RTM
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

/*
 * $Log: not supported by cvs2svn $
 *
 */

%module(directors="1") RTM

%init %{
  PyEval_InitThreads();
%}

%include "_defs.i"
%include "typemaps_py.i"
%include "RtcDataType.i"
%include "RtcInPort.i"
%include "RtcOutPort.i"
%include "RtcModuleProfile.i"
%include "RtcManager.i"
%include "RtcBase.i"
%include "RTCInPort.i"
%include "RTCOutPort.i"
%include "RTComponent.i"
%include "RTCBase.i"
%include "RTCManager.i"


 

