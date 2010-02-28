// -*- C++ -*-
/*!
 * @file crc.h
 * @brief CRC calculation functions
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2010
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_CRC_H
#define COIL_CRC_H

#include <sys/types.h>

namespace coil
{
  /*
   * @brief crc16 calculation functionSh
   *
   * CRC type: CRC-CCITT
   * CRC generator polynomial:  x^16 + x^12 + x^5 + 1 (0x1021)
   * Initial value:: 0xFFFF
   * Output XOR: 0x0000
   * Input bit inversion: None
   * Output bit inversion: None
   * Bit shift: left
   */
  unsigned short crc16(const char* str, size_t len);
  
  /*!
   * @brief crc32 calculation function
   * 
   * CRC type: RFC2083 Appendix 15
   *          http://www.faqs.org/rfcs/rfc2083.html
   *          http://www.efg2.com/Lab/Mathematics/CRC.htm
   * CRC polynomial:  0xedb88320L
   * Initial value:: 0xFFFFFFFF
   * Output XOR: 0xFFFFFFFF
   * Input bit inversion: None
   * Output bit inversion: None
   * Bit shift: right
   * 
   */
  unsigned long crc32(const char* str, size_t len);
}; //namespace coil

#endif // COIL_CRC_H
