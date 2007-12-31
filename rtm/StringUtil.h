// -*- C++ -*-
/*!
 * @file StringUtil.h
 * @brief String operation utility
 * @date $Date: 2007-12-31 03:08:07 $
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
 * $Id: StringUtil.h,v 1.9.2.1 2007-12-31 03:08:07 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.9  2007/04/23 04:58:53  n-ando
 * FUnction "stringTo()" was added.
 *
 * Revision 1.8  2007/04/13 15:57:13  n-ando
 * toArgv() was added to create command line arguments.
 * Some bug fixes.
 *
 * Revision 1.7  2006/11/27 10:00:15  n-ando
 * otos() function that converts object to string was added.
 * flatten() function that flattens string vector was added.
 *
 * Revision 1.6  2006/10/24 06:24:45  n-ando
 * Now StringUtil was devided into definition and implementation.
 *
 * Revision 1.5  2006/10/23 07:41:20  n-ando
 * Kanji-code was changed from JIS to EUC.
 *
 * Revision 1.4  2006/10/23 07:37:42  n-ando
 * Bug fix for split(). The problems that split() does not return empty
 * string as list of results string.
 * Reference manuals for functions were described.
 *
 * Revision 1.3  2006/10/17 10:11:09  n-ando
 * Some escape/unescape related bugs are fixed.
 * The following some functions were added.
 * - eraseHeadBlank(), eraseTailBlank(), replaceString()
 *
 * Revision 1.2  2006/10/13 03:51:37  n-ando
 * The "escape" and "unescape" functions were added.
 *
 * Revision 1.1  2006/09/20 08:49:08  n-ando
 * The first commit.
 *
 *
 */

#ifndef StringUtil_h
#define StringUtil_h

#include <string>
#include <vector>
#include <sstream>

/*!
 * @if jp
 * @brief 文字列がエスケープされているか判断する
 *
 * 指定された文字がエスケープされているかどうかを判断する。
 *
 * @param str エスケープされているかどうか判断する文字を含む文字列
 * @param pos エスケープされているかどうか判断する文字の位置
 *
 * @return 指定した文字がエスケープされていれば true, それ以外は false
 *
 * @else
 * @brief Whether the character is escaped or not
 *
 * This operation returns true if the specified character is escaped, and
 * if the specified character is not escaped, it returns false
 *
 * @param str The string thath includes the character to be investigated.
 * @param pos The position of the character to be investigated.
 *
 * @return true: the character is escaped, false: the character is not escaped.
 *
 * @endif
 */
bool isEscaped(const std::string& str, std::string::size_type pos);

/*!
 * @if jp
 * @brief 文字列をエスケープする
 *
 * 次の文字をエスケープシーケンスに変換する。<br>
 * HT -> "\t" <br>
 * LF -> "\n" <br>
 * CR -> "\r" <br>
 * FF -> "\f" <br>
 * シングルクオート、ダブルクオートについてはとくに処理はしない。
 *
 * @param str エスケープ処理対象文字列
 *
 * @return エスケープ処理結果文字列
 *
 * @else
 *
 * @brief Escape string
 *
 * The following characters are converted. <br>
 * HT -> "\t" <br>
 * LF -> "\n" <br>
 * CR -> "\r" <br>
 * FF -> "\f" <br>
 * Single quote and dobule quote are not processed.
 *
 * @endif
 */
std::string escape(const std::string str);


/*!
 * @if jp
 * @brief 文字列のエスケープを戻す
 *
 * 次のエスケープシーケンスを文字に変換する。<br>
 * "\t" -> HT <br>
 * "\n" -> LF <br>
 * "\r" -> CR <br>
 * "\f" -> FF <br>
 * "\"" -> "  <br>
 * "\'" -> '  <br>
 * ※エスケープ処理の完全な逆変換にはなっていないため、注意が必要。
 *
 * @param str アンエスケープ処理対象文字列
 *
 * @return アンエスケープ処理結果文字列
 *
 * @else
 *
 * @brief Unescape string
 *
 * The following characters are converted. <br>
 * "\t" -> HT <br>
 * "\n" -> LF <br>
 * "\r" -> CR <br>
 * "\f" -> FF <br>
 * "\"" -> "  <br>
 * "\'" -> '  <br>
 *
 * @endif
 */
std::string unescape(const std::string str);

/*!
 * @if jp
 * @brief 文字列の先頭の空白文字を削除する
 *
 * 与えられた文字列の先頭に存在する空白文字を削除する。
 * 空白文字として扱うのは' '(スペース)と'\t'(タブ)。
 *
 * @param str 先頭空白文字削除処理文字列
 *
 * @else
 * @brief Erase the head blank characters of string
 * @endif
 */
void eraseHeadBlank(std::string& str);

/*!
 * @if jp
 * @brief 文字列の末尾の空白文字を削除する
 *
 * 与えられた文字列の末尾に存在する空白文字を削除する。
 * 空白文字として扱うのは' '(スペース)と'\t'(タブ)。
 *
 * @param str 末尾空白文字削除処理文字列
 *
 * @else
 * @brief Erase the tail blank characters of string
 * @endif
 */
void eraseTailBlank(std::string& str);

/*!
 * @if jp
 * @brief 文字列を置き換える
 *
 * 与えられた文字列に対して、指定した文字の置き換えを行う。
 *
 * @param str 置き換え処理対象文字列
 * @param from 置換元文字
 * @param to 置換先文字
 *
 * @else
 * @brief Replace string
 * @endif
 */
void replaceString(std::string& str, const std::string from,
		   const std::string to);

/*!
 * @if jp
 * @brief 文字列を分割文字で分割する
 * 
 * 設定された文字列を与えられたデリミタで分割する。
 *
 * @param input 分割対象文字列
 * @param delimiter 分割文字列(デリミタ)
 *
 * @return 文字列分割結果リスト
 *
 * @else
 * @brief Split string by delimiter
 * @endif
 */
std::vector<std::string> split(const std::string& input,
			       const std::string& delimiter);

/*!
 * @if jp
 * @brief 与えられた文字列をbool値に変換する
 * 
 * 指定された文字列を、true表現文字列、false表現文字列と比較し、その結果を
 * bool値として返す。
 * 比較の結果、true表現文字列、false表現文字列のどちらとも一致しない場合は、
 * 与えられたデフォルト値を返す。
 *
 * @param str 判断対象文字列
 * @param yes true表現文字列
 * @param no false表現文字列
 * @param default_value デフォルト値(デフォルト値:true)
 * @else
 * @brief Convert given string to bool value
 * @endif
 */
bool toBool(std::string str, std::string yes, std::string no, 
	    bool default_value = true);

/*!
 * @if jp
 * @brief 与えられた文字列が絶対パスかどうかを判断する
 *
 * 与えられた文字列が絶対パス表現であるかどうかを判断する。
 * 文字列が以下の場合には絶対パスとして判断する。
 *  - 先頭文字が'/' (UNIXの場合)
 *  - 先頭３文字がアルファベット＋'/'＋'\\' (Windowsの場合)
 *  - 先頭２文字が'\\\\' (Windowsネットワークパスの場合)
 *
 * @param str 判定対象文字列
 *
 * @return 絶対パス判定結果
 *
 * @else
 * @brief Investigate whether the given string is absolute path or not
 * @endif
 */
bool isAbsolutePath(const std::string& str);

/*!
 * @if jp
 * @brief 与えられた文字列がURLかどうかを判断する
 *
 * 与えられた文字列がURL表現かどうかを判断する。
 * 与えられた文字列中に、'://'という文字列が含まれている場合には
 * URL表現として判断する。
 *
 * @param str 判定対象文字列
 *
 * @return URL判定結果
 *
 * @else
 * @brief Investigate whether the given string is URL or not
 * @endif
 */
bool isURL(const std::string& str);

/*!
 * @if jp
 * @brief 与えられたオブジェクトをstd::stringに変換
 *
 * 引数で指定されたオブジェクトを文字列に変換する。
 *
 * @param n 変換対象オブジェクト
 *
 * @return 文字列変換結果
 *
 * @else
 * @brief Convert the given object to st::string.
 * @endif
 */
template <class Printable>
std::string otos(Printable n)
{
  std::stringstream str_stream;
  str_stream << n;
  return str_stream.str();
};

/*!
 * @if jp
 * @brief 与えられたstd::stringをオブジェクトに変換
 *
 * 引数で与えられた文字列を指定されたオブジェクトに変換する。
 *
 * @param val 変換先オブジェクト
 * @param str 変換元文字列
 *
 * @return 変換処理実行結果
 *
 * @else
 * @brief Convert the given object to st::string.
 * @endif
 */
template <typename To>
bool stringTo(To& val, const char* str)
{
  std::stringstream s;
  return (s << str && s >> val);
}

/*!
 * @if jp
 * @brief 与えられた文字列リストから重複を削除
 *
 * 引数で与えられた文字列リストから重複を削除したリストを作成する。
 *
 * @param sv 確認元文字列リスト
 *
 * @return 重複削除処理結果リスト
 *
 * @else
 *
 * @endif
 */
std::vector<std::string> unique_sv(std::vector<std::string> sv);

/*!
 * @if jp
 * @brief 与えられた文字列リストからCSVを生成
 *
 * 引数で与えられた文字列リストの各要素を並べたCSVを生成する。
 * 文字列リストが空の場合には空白文字を返す。
 *
 * @param sv CSV変換対象文字列リスト
 *
 * @return CSV変換結果文字列
 *
 * @else
 *
 * @endif
 */
std::string flatten(std::vector<std::string> sv);

/*!
 * @if jp
 * @brief 与えられた文字列リストを引数リストに変換
 *
 * 引数で与えられた文字列リストの各要素末尾に'\0'を加え、引数リストに変換する。
 *
 * @param args V変換対象文字列リスト
 *
 * @return 引数変換結果文字列
 *
 * @else
 *
 * @endif
 */
char** toArgv(const std::vector<std::string>& args); 

#endif // StringUtil_h
