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

#include <coil/Routing.h>
#include <coil/stringutil.h>
#include <coil/config_coil.h>

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
    std::string dest_if;
    if (!find_dest_ifname(dest_addr, dest_if))
      {
        return false;
      }
    return ifname_to_ipaddr(dest_if, endpoint);
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
    //  struct hostent ipaddr;
    //  ipaddr = gethostbyname(dest_addr.c_str());
    
#if defined(COIL_OS_FREEBSD) || defined(COIL_OS_DARWIN)
    std::string cmd("route get ");
    const char* match_str = "interface";
    const char* delimiter = ":";
    int ifname_pos(1);
    cmd += dest_addr;
#endif // COIL_OS_IS_FREEBSD || COIL_OS_DARWIN
#ifdef COIL_OS_LINUX
    std::string cmd("ip route get ");
    const char* match_str = "dev ";
    const char* delimiter = " ";
    int ifname_pos(2);
    cmd += dest_addr;
#endif // COIL_OS_IS_LINUX    
    
    FILE* fp;
    if ((fp = popen(cmd.c_str(), "r")) == NULL)
      {
        return false;
      }
    
    do
      {
        char str[512];
        fgets(str, 512, fp);
        std::string line(str);
        
        if (std::string::npos == line.find(match_str)) { continue; }
        
        line.erase(line.end() - 1);
        coil::vstring vs(coil::split(line, delimiter));
        if (vs.size() == 2)
          {
            dest_if = vs[ifname_pos];
            pclose(fp);
            return true;
          }
      } while (!feof(fp));
    pclose(fp);
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
    std::string cmd("ifconfig ");
    cmd += ifname;
    
    FILE* fp;
    if ((fp = popen(cmd.c_str(), "r")) == NULL)
      {
        return false;
      }
    
    do
      {
        char str[512];
        fgets(str, 512, fp);
        std::string line(str);
        
        if (std::string::npos == line.find("inet ")) { continue; }
        
        line.erase(line.end() - 1);
        coil::eraseHeadBlank(line);
        coil::vstring vs(coil::split(line, " "));
        if (vs.size() == 6)
          {
            ipaddr = vs[1];
            pclose(fp);
            return true;
          }
      } while (!feof(fp));
    pclose(fp);
    return false;
  }
  
}; // namespace coil
