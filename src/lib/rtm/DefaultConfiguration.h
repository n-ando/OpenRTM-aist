// -*- C++ -*-
/*!
 * @file DefaultConfiguration.h
 * @brief RTC manager default configuration
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#include "rtm/version.h"

/*!
 * @if jp
 * @brief Manager 用 デフォルト・コンフィギュレーション
 *
 * Managerクラス用デフォルトコンフィギュレーション。
 *
 * @since 0.4.0
 *
 * @else
 * @brief Default configuration for Manager
 *
 * Default configuration for Manager class
 *
 * @since 0.4.0
 *
 * @endif
 */
static const char* default_config[] =
  {
    "config.version",                     openrtm_version,
    "openrtm.version",                    openrtm_name,
    "manager.instance_name",              "manager",
    "manager.name",                       "manager",
    "manager.naming_formats",             "%h.host_cxt/%n.mgr",
    "manager.pid",                        "",
    "manager.refstring_path",             "/var/log/rtcmanager.ref",
    "os.name",                            "",
    "os.release",                         "",
    "os.version",                         "",
    "os.arch",                            "",
    "os.hostname",                        "",
    "logger.enable",                      "YES",
    "logger.file_name",                   "./rtc%p.log",
    "logger.date_format",                 "%b %d %H:%M:%S",
    "logger.log_level",                   "INFO",
    "logger.stream_lock",                 "NO",
    "logger.master_logger",               "",
    "module.conf_path",                   "",
    "module.load_path",                   "",
    "naming.enable",                      "YES",
    "naming.type",                        "corba",
    "naming.formats",                     "%h.host_cxt/%n.rtc",
    "naming.update.enable",               "YES",
    "naming.update.interval",             "10.0",
    "timer.enable",                       "YES",
    "timer.tick",                         "0.1",
    "corba.args",                         "",
    "corba.endpoint",                     "",  // hostname:port_number
    "corba.id",                           corba_name,
    "corba.name_servers",                 "",
    "corba.master_manager",               "localhost:2810",
    "corba.nameservice.replace_endpoint", "NO",
    "exec_cxt.periodic.type",             "PeriodicExecutionContext",
    "exec_cxt.periodic.rate",             "1000",
    "exec_cxt.evdriven.type",             "EventDrivenExecutionContext",
    "manager.modules.load_path",          "./",
    "manager.modules.abs_path_allowed",   "YES",
    "manager.is_master",                  "NO",
    "manager.corba_servant",              "YES",
    "manager.shutdown_nortcs",            "YES",
    "manager.shutdown_auto",              "YES",
    "manager.name",                       "manager",
    "manager.command",                    "rtcd",

    ""
  };

