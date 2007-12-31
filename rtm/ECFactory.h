// -*- C++ -*-
/*!
 * @file ECFactory.h
 * @brief ExecutionContext Factory class
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ECFactory.h,v 1.1.2.1 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/04/13 16:06:22  n-ando
 * ExecutionContext Factory class.
 *
 */

#ifndef ECFactory_h
#define ECFactory_h

#include <rtm/ExecutionContextBase.h>
#include <string>

namespace RTC 
{
  
  typedef ExecutionContextBase* (*ECNewFunc)();
  typedef void (*ECDeleteFunc)(ExecutionContextBase* ec);
  
  /*!
   * @if jp
   *
   * @brief ExecutionContext生成用テンプレート関数
   * 
   * ExecutionContextのインスタンスを生成するためのテンプレート関数。
   *
   * @return 生成したExecutionContextインスタンス
   * 
   * @else
   *
   * @endif
   */
  template <class _New>
  ExecutionContextBase* ECCreate()
  {
    return new _New();
  }
  
  /*!
   * @if jp
   *
   * @brief ExecutionContext破棄用テンプレート関数
   * 
   * ExecutionContextのインスタンスを破棄するためのテンプレート関数。
   *
   * @param ec 破棄対象ExecutionContextのインスタンス
   *
   * @else
   *
   * @endif
   */
  template <class _Delete>
  void ECDelete(ExecutionContextBase* ec)
  {
    delete ec;
  }
  
  /*!
   * @if jp
   * @class ECFactoryBase
   * @brief ECFactoryBase 抽象クラス
   * 
   * ExecutionContext生成用Factoryの抽象クラス。
   * 各ExecutionContextを生成するための具象Factoryクラスは、
   * 以下の純粋仮想関数の実装を提供しなければならない。
   *
   * publicインターフェースとして以下のものを提供する。
   * - name()   : 生成対象ExecutionContext名称の取得
   * - create() : ExecutionContextインスタンスの生成
   * - destroy(): ExecutionContextインスタンスの破棄
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ECFactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * 仮想デストラクタ。
     *
     * @else
     *
     * @endif
     */
    virtual ~ECFactoryBase(){};
    
    /*!
     * @if jp
     *
     * @brief 生成対象ExecutionContext名称取得用純粋仮想関数
     * 
     * 生成対象ExecutionContextの名称を取得するための純粋仮想関数。
     *
     * @return 生成対象ExecutionContext名称
     * 
     * @else
     *
     * @endif
     */
    virtual const char* name() = 0;
    
    /*!
     * @if jp
     *
     * @brief ExecutionContext生成用純粋仮想関数
     * 
     * ExecutionContextのインスタンスを生成するための純粋仮想関数。
     *
     * @return 生成したExecutionContextインスタンス
     * 
     * @else
     *
     * @endif
     */
    virtual ExecutionContextBase* create() = 0;
    
    /*!
     * @if jp
     *
     * @brief ExecutionContext破棄用純粋仮想関数
     * 
     * ExecutionContextのインスタンスを破棄するための純粋仮想関数。
     *
     * @param comp 破棄対象のExecutionContextインスタンス
     * 
     * @else
     *
     * @endif
     */
    virtual void destroy(ExecutionContextBase* comp) = 0;
  protected:
  };
  
  /*!
   * @if jp
   * @class ECFactoryCXX
   * @brief ECFactoryCXX クラス
   * 
   * C++言語用ExecutionContextインスタンスを生成するFactoryクラス。
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  class ECFactoryCXX
    : public ECFactoryBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     * 
     * コンストラクタ
     *
     * @param name 生成対象ExecutionContext名称
     * @param new_func ExecutionContext生成用関数
     * @param delete_func ExecutionContext破棄用関数
     * 
     * @else
     *
     * @endif
     */
    ECFactoryCXX(const char* name,
		 ECNewFunc new_func,
		 ECDeleteFunc delete_func);
    
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * 仮想デストラクタ。
     *
     * @else
     *
     * @endif
     */
    ~ECFactoryCXX();
    
    /*!
     * @if jp
     *
     * @brief 生成対象ExecutionContext名称を取得
     * 
     * 生成対象のExecutionContext名称を取得する。
     *
     * @return 生成対象ExecutionContext名称
     * 
     * @else
     *
     * @endif
     */
    virtual const char* name();
    
    /*!
     * @if jp
     *
     * @brief 生成対象ExecutionContextインスタンスを生成
     * 
     * 生成対象のExecutionContextクラスのインスタンスを生成する。
     *
     * @return 生成したExecutionContextインスタンス
     * 
     * @else
     *
     * @endif
     */
    virtual ExecutionContextBase* create();
    
    /*!
     * @if jp
     *
     * @brief 対象ExecutionContextインスタンスを破棄
     * 
     * 対象ExecutionContextクラスのインスタンスを破棄する。
     *
     * @param comp 破棄対象ExecutionContextインスタンス
     * 
     * @else
     *
     * @endif
     */
    virtual void destroy(ExecutionContextBase* comp);
    
  protected:
    /*!
     * @if jp
     * @brief  生成対象ExecutionContext名称
     * @else
     * @endif
     */
    std::string m_name;
    
    /*!
     * @if jp
     * @brief  対象ExecutionContext生成用関数
     * @else
     * @endif
     */
    ECNewFunc m_New;
    
    /*!
     * @if jp
     * @brief  対象ExecutionContext破棄用関数
     * @else
     * @endif
     */
    ECDeleteFunc m_Delete;
  };
};
#endif // ECFactory_h
