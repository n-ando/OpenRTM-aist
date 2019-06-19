// -*- C++ -*-
/*!
 * @file  Routing.cpp
 * @brief Network routing information handling functions
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2010
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

#include <stdio.h>
#include <netdb.h>      // gethostbyname
#include <arpa/inet.h>  // inet_ntoa
#include <netinet/in.h> // sockaddr_in
#include <sys/wait.h>

#include <coil/Routing.h>
#include <coil/stringutil.h>
#include <coil/config_coil.h>

#ifndef __RTP__
#include <wrapper/wrapperHostLib.h>
#endif

namespace coil
{
  /*!
   * @if jp
   * @brief 宛先アドレスから利用されるエンドポイントアドレスを得る
   * @else
   * @brief Getting network interface name from destination address
   * @endif
   */
  bool dest_to_endpoint(std::string dest_addr, std::string& endpoint)
  {
    return false;
  }

  /*!
   * @if jp
   * @brief 宛先アドレスから利用されるネットワークインターフェース名を得る
   * @else
   * @brief Getting network interface name from destination address
   * @endif
   */
  bool find_dest_ifname(std::string dest_addr, std::string& dest_if)
  {
    return false;
  }

  /*!
   * @if jp
   * @brief ネットワークインターフェース名からIPアドレスを得る
   * @else
   * @brief Get IP address from a network interface name
   * @endif
   */
  bool ifname_to_ipaddr(std::string ifname, std::string& ipaddr)
  {
    return false;
  }
  
} // namespace coil
