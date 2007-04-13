// -*- C++ -*-
/*!
 * @file DefaultConfiguration.h
 * @brief RTC manager default configuration
 * @date $Date: 2007-04-13 18:16:47 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: DefaultConfiguration.h,v 1.4 2007-04-13 18:16:47 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2006/12/02 18:37:06  n-ando
 * Default configuration parameters were changed.
 *
 * Revision 1.2  2006/10/23 08:40:02  n-ando
 * The last entry "" that inidicate the end of entry did not exist. Fixed it.
 *
 * Revision 1.1  2006/10/17 19:30:45  n-ando
 * The first comitment.
 *
 *
 */

#include "rtm/version.h"

static const char* default_config[] =
  {
    "config.version",         openrtm_version,
    "openrtm.version",        openrtm_name,
    "manager.name",           "manager",
    "manager.pid",            "",
    "os.name",                "",
    "os.release",             "",
    "os.version",             "",
    "os.arch",                "",
    "os.hostname",            "",
    "logger.enable",          "YES",
    "logger.file_name",       "./rtc%p.log",
    "logger.date_format",     "%b %d %H:%M:%S",
    "logger.log_level",       "NORMAL",
    "logger.stream_lock",     "NO",
    "logger.master_logger",   "",
    "module.conf_path",       "",
    "module.load_path",       "",
    "name_svc.enable",        "YES",
    "name_svc.type",          "corba",
    "name_svc.update.enable", "YES",
    "name_svc.update.interval","10.0",
    "timer.enable",           "YES",
    "timer.tick",             "0.1",
    "corba.args",             "",
    "corba.endpoint",         "",                   // hostname:port_number
    "corba.id",               corba_name,
    "corba.name_servers",     "",
    "exec_cxt.periodic.type", "PeriodicExecutionContext",
    "exec_cxt.periodic.rate", "1000",
    "exec_cxt.evdriven.type", "EventDrivenExecutionContext",

    ""
  };

