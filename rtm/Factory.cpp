// -*- C++ -*-
/*!
 * @file Factory.h
 * @brief RT component manager class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Factory.cpp,v 1.5.2.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.5  2007/04/13 16:09:10  n-ando
 * Error handling was added.
 *
 * Revision 1.4  2006/11/06 01:28:31  n-ando
 * Now the "instance_name" is set to the component at creation time.
 *
 * Revision 1.3  2006/10/25 17:35:52  n-ando
 * Classes were renamed, and class reference manual was described.
 *
 * Revision 1.2  2006/10/24 14:25:26  n-ando
 * Renamed RtcFactory.cpp to Factory.cpp
 *
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#include <rtm/Factory.h>

namespace RTC 
{
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   *
   * @endif
   */
  FactoryBase::FactoryBase(const Properties& profile)
    : m_Profile(profile), m_Number(-1)
  {
  }
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   *
   * @endif
   */
  FactoryBase::~FactoryBase()
  {
  }
  
  /*!
   * @if jp
   * @brief コンポーネントプロファイルの取得
   * @else
   *
   * @endif
   */
  Properties& FactoryBase::profile()
  {
    return m_Profile;
  }
  
  /*!
   * @if jp
   * @brief 現在のインスタンス数の取得
   * @else
   *
   * @endif
   */
  int FactoryBase::number()
  {
    return m_Number;
  }
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   *
   * @endif
   */
  FactoryCXX::FactoryCXX(const Properties& profile,
			 RtcNewFunc new_func,
			 RtcDeleteFunc delete_func,
			 NumberingPolicy* policy)
    : FactoryBase(profile),
      m_New(new_func),
      m_Delete(delete_func),
      m_policy(policy)
  {
  }
  
  /*!
   * @if jp
   * @brief コンポーネントの生成
   * @else
   *
   * @endif
   */
  RtcBase* FactoryCXX::create(Manager* mgr)
  {
    try
      {
	RtcBase* rtobj(m_New(mgr));
	if (rtobj == 0) return NULL;
	
	++m_Number;
	rtobj->setProperties(this->profile());
	
	// create instance_name
	std::string instance_name(rtobj->getTypeName());
	instance_name.append(m_policy->onCreate(rtobj));
	rtobj->setInstanceName(instance_name.c_str());
	
	return rtobj;
      }
    catch (...)
      {
	return NULL;
      }
  }
  
  /*!
   * @if jp
   * @brief コンポーネントの破棄
   * @else
   *
   * @endif
   */
  void FactoryCXX::destroy(RtcBase* comp)
  {
    --m_Number;
    m_policy->onDelete(comp);
    m_Delete(comp);
  }
};
