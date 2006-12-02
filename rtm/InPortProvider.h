// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2006-12-02 18:41:51 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortProvider.h,v 1.2 2006-12-02 18:41:51 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 09:44:40  n-ando
 * The first commitment.
 *
 */

#ifndef InPortProvider_h
#define InPortProvider_h


namespace RTC
{
  /*!
   * @if jp
   * @class InPortProvider
   * @brief InPortProvider クラス
   * @else
   * @class InPortProvider
   * @brief InPortProvider class
   * @endif
   */
  class InPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    InPortProvider();

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortProvider(){};

  protected:
  
  private:

  };
 
};     // namespace RTC
#endif // InPortProvider_h

