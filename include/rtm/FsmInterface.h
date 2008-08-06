// -*- C++ -*-
/*!
 * @file  FsmInterface.h
 * @brief FsmInterface interface class
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

#ifndef FsmInterface_h
#define FsmInterface_h
 
namespace RTC
{
  namespace Interface
  {
    /*!
     * @if jp
     * @class FsmInterface
     * @brief FsmInterface インターフェースクラス
     * @else
     * @class FsmInterface
     * @brief FsmInterface interface class
     * @endif
     */
    class FsmInterface
    {
    public:
      virtual ~FsmInterface() {};
    };
  };   // namespace Interface 
};     // namespace RTC
#endif // FsmInterface_h
  
  
