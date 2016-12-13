// -*- C++ -*-
/*!
 * @file RtcNameComponent.h
 * @brief Name component helper class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcNameComponent.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcNameComponent_h
#define RtcNameComponent_h

// CORBA header include
#include "rtm/idl/RTMBaseStub.h"
#include "rtm/idl/RTMBaseSkel.h"

// STL includes
#include <string>
#include <vector>

namespace RTM
{

  /*!
   * @if jp
   *
   * @class RtcNameComponent
   *
   * @brief CORBA Naming Service で用いる Name Component ヘルパークラス
   *
   * @else
   *
   * @class RtcNameComponent
   *
   * @brief Name component handling class for CORBA Naming Service.
   *
   * @endif
   */
  class RtcNameComponent
  {
  public:
	/*!
	 * @if jp
	 * @brief RtcNaming クラスコンストラクタ
	 *
	 * @else
	 *
	 * @brief A constructor of RtcNaming class.
	 *
	 * @endif
	 */
	RtcNameComponent();

	/*!
	 * @if jp
	 * @brief Name Component の生成
	 *
	 * 与えられた文字列から Name Component を作成する。
	 * 
     * @param path Name Component 化するパス文字列
	 *
	 * @else
	 *
	 * @brief Create name component
	 *
     * Create a name component from given string.
	 *
     * @param path path string to be name component.
	 *
	 * @endif
	 */
	RtcNameComponent(const std::string path);
	
	/*!
	 * @if jp
	 * @brief Name Component の生成
	 *
	 * 与えられた文字列から Name Component を作成する。
	 * 
     * @param path Name Component 化するパス文字列
	 *
	 * @else
	 *
	 * @brief Create name component
	 *
     * Create a naming component from given string.
	 *
     * @param path path string to be name component.
	 *
	 * @endif
	 */
	RtcNameComponent(const char* path);

	/*!
	 * @if jp
	 * @brief Name Component の取得
	 *
	 * 現在保持されている Name Component を取得する。
	 * 
	 * @else
	 *
	 * @brief Get current name component
	 *
     * Create a name component from given string.
	 *
     * @param path path string to be name component.
	 *
	 * @endif
	 */
	CosNaming::Name get();

	/*!
	 * @if jp
	 * @brief Name Component のpop
	 *
	 * 現在保持されている Name Component の最末尾をpopする。
	 * 
	 * @else
	 *
	 * @brief Pop the last name component.
	 *
     * Pop and return the last name component from current name components.
	 *
	 * @endif
	 */
	CosNaming::Name pop();

	/*!
	 * @if jp
	 * @brief Name Component の push
	 *
	 * 現在保持されている Name Component の最末尾に push する。
	 * 
	 * @else
	 *
	 * @brief Push the given string.
	 *
     * Push the given string to the last of name components.
	 *
	 * @endif
	 */
	CosNaming::Name push(const std::string& path);

	/*!
	 * @if jp
	 * @brief Name Component の消去
	 *
	 * 現在保持されている Name Component を消去する。
	 * 
	 * @else
	 *
	 * @brief Erase the current name components.
	 *
     * Erase the curent name component which this object is holding.
	 *
	 * @endif
	 */
	void erase();

	inline int length() {return m_Length;}

	/*!
	 * @if jp
	 * @brief Name Component の作成
	 *
	 * 与えられた文字列から Name Component を作成する静的メンバメソッド。
	 * 
	 * @else
	 *
	 * @brief Create name component.
	 *
     * Static member method which creates name component from given path string.
	 *
	 * @endif
	 */
	static CosNaming::Name stringToNameComponent(const std::string& path);

  private:
	/*!
	 * @if jp
	 * @brief 文字列の分割
	 *
	 * 与えられた文字列から Name Component を作成する静的メンバメソッド。
	 * 
     * @param input 入力文字列。 std::string 型。
     * @param delimiter デリミタ。 std::string 型。
     * @param results 結果。 std::vector<std::string> 型。
	 *
	 * @else
	 *
	 * @brief Split string.
	 *
     * Static member method which creates name component from given path string.
	 *
     * @param input Input string to be split. std::string tyoe.
     * @param delimiter Delimter. std::string type.
     * @param results Results. std::vector<std::string> type.
	 *
	 * @endif
	 */
	static int split(const std::string& input, const std::string& delimiter,
					 std::vector<std::string>& results);

	static void nodeToIdKind(const std::string& node, std::string& id,
							 std::string& kind);

	/*!
	 * @if jp
	 * @brief Name Component
	 *
	 * オブジェクト内部に保持される name component。
	 * 
	 * @else
	 *
	 * @brief name Component
	 *
     * A name component to be hold by this object.
	 *
	 * @endif
	 */
	CosNaming::Name m_Name;
	/*!
	 * @if jp
	 * @brief Name Component の長さ
	 *
	 * オブジェクト内部に保持される name component の長さ。
	 * 
	 * @else
	 *
	 * @brief Length of the name component
	 *
     * The length of the name component.
	 *
	 * @endif
	 */
	int m_Length;
  };
};

#endif // RtcNameComponent_h
