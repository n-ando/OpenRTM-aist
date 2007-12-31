// -*- C++ -*-
/*!
 * @file NumberingPolicy.h
 * @brief Object numbering policy class
 * @date $Date: 2007-12-31 03:08:04 $
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
 * $Id: NumberingPolicy.h,v 1.2.4.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/21 09:52:28  n-ando
 * A trivial bug fix about dtor.
 *
 * Revision 1.1  2006/11/04 21:07:40  n-ando
 * Component numbering rule was derived into policy class.
 *
 */

#ifndef NumberingPolicy_h
#define NumberingPolicy_h

#include <string>
#include <vector>

/*!
 * @if jp
 *
 * @brief オブジェクト生成時ネーミング・ポリシー(命名規則)管理用抽象クラス
 *
 * オブジェクトを生成する際のネーミング・ポリシー(命名規則)を管理するための
 * 抽象インターフェースクラス。
 * 具象クラスは、以下の純粋仮想関数の実装を提供しなければならない。
 * - onCreate() : オブジェクト生成時の名称作成
 * - onDelete() : オブジェクト削除時の名称解放
 *
 * @since 0.4.0
 *
 * @else
 *
 * @endif
 */
class NumberingPolicy
{
public:
  /*!
   * @if jp
   * @brief オブジェクト未発見例外処理用構造体
   * @else
   *
   * @endif
   */
  struct ObjectNotFound {};
  
  /*!
   * @if jp
   *
   * @brief 仮想デストラクタ
   * 
   * @else
   *
   * @brief virtual destractor
   *
   * @endif
   */
  virtual ~NumberingPolicy(){};
  
  /*!
   * @if jp
   *
   * @brief オブジェクト生成時の名称作成
   *
   * オブジェクト生成時の名称を生成するための純粋仮想関数
   * 
   * @param obj 名称生成対象オブジェクト
   *
   * @return 生成したオブジェクト名称
   *
   * @else
   *
   * @endif
   */
  virtual std::string onCreate(void* obj) = 0;
  
  /*!
   * @if jp
   *
   * @brief オブジェクト削除時の名称解放
   *
   * オブジェクト削除時に名称を解放するための純粋仮想関数
   * 
   * @param obj 名称解放対象オブジェクト
   *
   * @else
   *
   * @endif
   */
  virtual void onDelete(void* obj) = 0;
};

/*!
 * @if jp
 *
 * @brief オブジェクト生成時ネーミング・ポリシー(命名規則)管理用クラス
 *
 * オブジェクトを生成する際のネーミング・ポリシー(命名規則)を管理するための
 * クラス。
 *
 * @since 0.4.0
 *
 * @else
 *
 * @endif
 */
class DefaultNumberingPolicy
  : public NumberingPolicy 
{
public:
  /*!
   * @if jp
   *
   * @brief コンストラクタ
   * 
   * コンストラクタ
   * 
   * @else
   *
   * @brief virtual destractor
   *
   * @endif
   */
  DefaultNumberingPolicy() : m_num(0) {};
  
  /*!
   * @if jp
   *
   * @brief デストラクタ
   * 
   * @else
   *
   * @brief destractor
   *
   * @endif
   */
  virtual ~DefaultNumberingPolicy(){};
  
  /*!
   * @if jp
   *
   * @brief オブジェクト生成時の名称作成
   *
   * オブジェクト生成時の名称を生成する。
   * 生成済みインスタンスの数に応じた名称を生成する。
   * 
   * @param obj 名称生成対象オブジェクト
   *
   * @return 生成したオブジェクト名称
   *
   * @else
   *
   * @endif
   */
  virtual std::string onCreate(void* obj);
  
  /*!
   * @if jp
   *
   * @brief オブジェクト削除時の名称解放
   *
   * オブジェクト削除時に名称を解放する。
   * オブジェクト削除時に生成済みインスタンス数を減算する。
   * 
   * @param obj 名称解放対象オブジェクト
   *
   * @else
   *
   * @endif
   */
  virtual void onDelete(void* obj);
  
protected:
  /*!
   * @if jp
   *
   * @brief オブジェクトの検索
   *
   * オブジェクトリストから指定されたオブジェクトを検索し、
   * 該当するオブジェクトが格納されている場合にはインデックスを返す。
   * 
   * @param obj 検索対象オブジェクト
   *
   * @return オブジェクト格納インデックス
   *
   * @else
   *
   * @endif
   */
  long int find(void* obj);
  
private:
  int m_num;
  std::vector<void*> m_objects;
};
#endif // NumberingPolicy_h
