// -*- C++ -*-
/*!
 * @file StringUtil.h
 * @brief String operation utility
 * @date $Date: 2006-11-27 10:00:15 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: StringUtil.h,v 1.7 2006-11-27 10:00:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
 * 指定した文字がエスケープされていればtrue、されていなければfalseを返す。
 *
 * @param str エスケープされているかどうか判断する文字を含む文字列
 * @param pos エスケープされているかどうか判断する文字の位置
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
 * @else
 * @brief Erase the head blank characters of string
 * @endif
 */
void eraseHeadBlank(std::string& str);


/*!
 * @if jp
 * @brief 文字列の末尾の空白文字を削除する
 * @else
 * @brief Erase the tail blank characters of string
 * @endif
 */
void eraseTailBlank(std::string& str);


/*!
 * @if jp
 * @brief 文字列を置き換える
 * @else
 * @brief Replace string
 * @endif
 */
void replaceString(std::string& str, const std::string from,
		   const std::string to);


/*!
 * @if jp
 * @brief 文字列を分割文字で分割する
 * @else
 * @brief Split string by delimiter
 * @endif
 */
std::vector<std::string> split(const std::string& input,
			       const std::string& delimiter);


/*!
 * @if jp
 * @brief 与えられた文字列をbool値に変換する
 * @else
 * @brief Convert given string to bool value
 * @endif
 */
bool toBool(std::string str, std::string yes, std::string no, 
	    bool default_value = true);


/*!
 * @if jp
 * @brief 与えられた文字列が絶対パスかどうかを判断する
 * @else
 * @brief Investigate whether the given string is absolute path or not
 * @endif
 */
bool isAbsolutePath(const std::string& str);


/*!
 * @if jp
 * @brief 与えられた文字列がURLかどうかを判断する
 * @else
 * @brief Investigate whether the given string is URL or not
 * @endif
 */
bool isURL(const std::string& str);


/*!
 * @if jp
 * @brief 与えられたオブジェクトをstd::stringに変換
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

std::vector<std::string> unique_sv(std::vector<std::string> sv);

std::string flatten(std::vector<std::string> sv);

#endif // StringUtil_h
