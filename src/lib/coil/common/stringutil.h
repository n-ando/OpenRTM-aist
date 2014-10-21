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
 * $Id: StringUtil.h 826 2008-08-26 08:13:39Z n-ando $
 *
 */

#ifndef COIL_STRINGUTIL_H
#define COIL_STRINGUTIL_H

#include <string>
#include <vector>
#include <sstream>

#if defined (_MSC_VER) && (_MSC_VER <=1500) // VC2008(VC9.0) or before
#else
#include <stdint.h>
#endif
// Cygwin's gcc does not provide wstring type
#if defined(Cygwin) && ( __GNUC__ < 4 )
namespace std
{
  typedef basic_string<wchar_t> wstring;
}
#endif

namespace coil
{
  typedef std::vector<std::string> vstring;

  /*!
   * @if jp
   * @brief string ¤«¤Ewstring ¤Ø¤ÎÊÑ´¹
   *
   * Í¿¤¨¤é¤E¿ string Ê¸»úÎó¤Ewstring Ê¸»úÎó¤ËÊÑ´¹
   *
   * @param str std::string ·¿¤ÎÆşÎÏÊ¸»úÎE   * @return std::wstring ·¿¤Î½ĞÎÏÊ¸»úÎE   *
   * @else
   * @brief string to wstring conversion
   *
   * This function convert from a string to a wstring.
   * 
   * @param str The input std::string type string
   * @return Converted std::wstring type string
   *
   * @endif
   */
  std::wstring string2wstring(std::string str);

  /*!
   * @if jp
   * @brief wstring ¤«¤Estring ¤Ø¤ÎÊÑ´¹
   *
   * Í¿¤¨¤é¤E¿ wstring Ê¸»úÎó¤Estring Ê¸»úÎó¤ËÊÑ´¹
   *
   * @param str std::wstring ·¿¤ÎÆşÎÏÊ¸»úÎE   * @return std::string ·¿¤Î½ĞÎÏÊ¸»úÎE   *
   * @else
   * @brief wstring to string conversion
   *
   * This function convert from a wstring to a string.
   * 
   * @param str The input std::wstring type string
   * @return Converted std::string type string
   *
   * @endif
   */
  std::string wstring2string(std::wstring wstr);

  /*!
   * @if jp
   * @brief ÂçÊ¸»ú¤Ø¤ÎÊÑ´¹
   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤òÂçÊ¸»ú¤ËÊÑ´¹
   *
   * @param str ÆşÎÏÊ¸»úÎE   *
   * @else
   * @brief Uppercase String Transformation
   *
   * This function transforms a given string to uppercase letters
   * 
   * @param str The input string
   *
   * @endif
   */
  void toUpper(std::string& str);

  /*!
   * @if jp
   * @brief ¾®Ê¸»ú¤Ø¤ÎÊÑ´¹
   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤ò¾®Ê¸»ú¤ËÊÑ´¹
   *
   * @param str ÆşÎÏÊ¸»úÎE   *
   * @else
   * @brief Lowercase String Transformation
   *
   * This function transforms a given string to lowercase letters
   * 
   * @param str The input string
   *
   * @endif
   */
  void toLower(std::string& str);

  /*!
   * @if jp
   * @brief ÆşÎÏ¥¹¥È¥ê¡¼¥à¤«¤E¹ÔÆÉ¤ß¹ş¤E   *
   * ÆşÎÏ¥¹¥È¥ê¡¼¥à¤«¤E¹ÔÆÉ¤ß¹ş¤à¡£
   * ÆşÎÏ¥¹¥È¥ê¡¼¥à¤Ï¤Î²ş¹Ô¥³¡¼¥É¤ÏUNIX, Windows¤Î²ş¹Ô¥³¡¼¥É¤Î¤¤¤º¤E«¡¢
   * ¤â¤·¤¯¤Ïº®ºß¤·¤Æ¤¤¤Æ¤â¤è¤¤¡£
   *
   * @param istr ÆşÎÏ¥¹¥È¥ê¡¼¥E   * @param line ÆÉ¤ß¹ş¤ó¤ÀÊ¸»úÎó¤ò³ÊÇ¼¤¹¤EÑ¿E   *
   * @return ²ş¹ÔÊ¸»ú¤ò½E¯ÆÉ¤ß¹ş¤ó¤ÀÊ¸»úÎó¤ÎÄ¹¤µ
   *
   * @else
   * @brief Read a line from input stream
   *
   * This function reads a line from input stream.
   * UNIX, Windows or mixed line feed code is acceptable.
   *
   * @param istr The input stream.
   * @param line The output variable to store string to be read.
   *
   * @return The length of read string except line feed character.
   *
   * @endif
   */
  int getlinePortable(std::istream& istr, std::string& line);
  
  /*!
   * @if jp
   * @brief Ê¸»úÎó¤¬¥¨¥¹¥±¡¼¥×¤µ¤EÆ¤¤¤E«È½ÃÇ¤¹¤E   *
   * »ØÄê¤µ¤E¿Ê¸»ú¤¬¥¨¥¹¥±¡¼¥×¤µ¤EÆ¤¤¤E«¤É¤¦¤«¤òÈ½ÃÇ¤¹¤E£
   *
   * @param str ¥¨¥¹¥±¡¼¥×¤µ¤EÆ¤¤¤E«¤É¤¦¤«È½ÃÇ¤¹¤E¸»ú¤ò´Ş¤àÊ¸»úÎE   * @param pos ¥¨¥¹¥±¡¼¥×¤µ¤EÆ¤¤¤E«¤É¤¦¤«È½ÃÇ¤¹¤E¸»ú¤Î°ÌÃÖ
   *
   * @return »ØÄê¤·¤¿Ê¸»ú¤¬¥¨¥¹¥±¡¼¥×¤µ¤EÆ¤¤¤EĞ true, ¤½¤EÊ³°¤Ï false
   *
   * @else
   * @brief Check whether the character is escaped or not
   *
   * Check whether the specified character is escaped or not
   *
   * @param str The string that includes the character to be investigated.
   * @param pos The position of the character to be investigated.
   *
   * @return True if the specified character is escaped, else False.
   *
   * @endif
   */
  bool isEscaped(const std::string& str, std::string::size_type pos);
  
  /*!
   * @if jp
   * @brief Ê¸»úÎó¤ò¥¨¥¹¥±¡¼¥×¤¹¤E   *
   * ¼¡¤ÎÊ¸»ú¤ò¥¨¥¹¥±¡¼¥×¥·¡¼¥±¥ó¥¹¤ËÊÑ´¹¤¹¤E£<br>
   * HT -> "\t" <br>
   * LF -> "\n" <br>
   * CR -> "\r" <br>
   * FF -> "\f" <br>
   * ¥·¥ó¥°¥E¯¥ª¡¼¥È¡¢¥À¥Ö¥E¯¥ª¡¼¥È¤Ë¤Ä¤¤¤Æ¤Ï¤È¤¯¤Ë½èÍı¤Ï¤·¤Ê¤¤¡£
   *
   * @param str ¥¨¥¹¥±¡¼¥×½èÍıÂĞ¾İÊ¸»úÎE   *
   * @return ¥¨¥¹¥±¡¼¥×½èÍı·EÌÊ¸»úÎE   *
   * @else
   *
   * @brief Escape string
   *
   * The following characters are converted. <br>
   * HT -> "\t" <br>
   * LF -> "\n" <br>
   * CR -> "\r" <br>
   * FF -> "\f" <br>
   * Single quote and double quote are not processed.
   *
   * @param str The target string for the escape
   *
   * @return Result string of the escape
   *
   * @endif
   */
  std::string escape(const std::string str);
  
  /*!
   * @if jp
   * @brief Ê¸»úÎó¤Î¥¨¥¹¥±¡¼¥×¤òÌá¤¹
   *
   * ¼¡¤Î¥¨¥¹¥±¡¼¥×¥·¡¼¥±¥ó¥¹¤òÊ¸»ú¤ËÊÑ´¹¤¹¤E£<br>
   * "\t" -> HT <br>
   * "\n" -> LF <br>
   * "\r" -> CR <br>
   * "\f" -> FF <br>
   * "\"" -> "  <br>
   * "\'" -> '  <br>
   * ¢¨¥¨¥¹¥±¡¼¥×½èÍı¤Î´°Á´¤ÊµÕÊÑ´¹¤Ë¤Ï¤Ê¤Ã¤Æ¤¤¤Ê¤¤¤¿¤á¡¢ÃúÌÕ¤¬É¬Í×¡£
   *
   * @param str ¥¢¥ó¥¨¥¹¥±¡¼¥×½èÍıÂĞ¾İÊ¸»úÎE   *
   * @return ¥¢¥ó¥¨¥¹¥±¡¼¥×½èÍı·EÌÊ¸»úÎE   *
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
   * Note: This is not complete inversion of the escape processing.
   *
   * @param str The target string for the unescape
   *
   * @return Result string of the unescape
   *
   * @endif
   */
  std::string unescape(const std::string str);

  /*!
   * @if jp
   * @brief Ê¸»úÎó¤Î¶õÇòÊ¸»ú¤òºEE¹¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤Î¶õÇòÊ¸»ú¤òºEE¹¤E£
   * ¶õÇòÊ¸»ú¤È¤·¤Æ°·¤¦¤Î¤Ï' '(¥¹¥Ú¡¼¥¹)¤È'\\t'(¥¿¥Ö)¡£
   *
   * @param str ¶õÇòÊ¸»úºEEèÍıÊ¸»úÎE   *
   * @else
   * @brief Erase blank characters of string
   *
   * Erase blank characters that exist at the head of the given string.
   * Space ' 'and tab '\\t' are supported as the blank character.
   *
   * @param str The target blank characters of string for the erase
   *
   * @endif
   */
  void eraseBlank(std::string& str);

  /*!
   * @if jp
   * @brief Ê¸»úÎó¤ÎÀèÆ¬¤Î¶õÇòÊ¸»ú¤òºEE¹¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤ÎÀèÆ¬¤ËÂ¸ºß¤¹¤EõÇòÊ¸»ú¤òºEE¹¤E£
   * ¶õÇòÊ¸»ú¤È¤·¤Æ°·¤¦¤Î¤Ï' '(¥¹¥Ú¡¼¥¹)¤È'\\t'(¥¿¥Ö)¡£
   *
   * @param str ÀèÆ¬¶õÇòÊ¸»úºEEèÍıÊ¸»úÎE   *
   * @else
   * @brief Erase the head blank characters of string
   *
   * Erase the blank characters that exist at the head of the given string.
   * Space ' 'and tab '\\t' are supported as the blank character.
   *
   * @param str The target head blank characters of string for the erase
   *
   * @endif
   */
  void eraseHeadBlank(std::string& str);
  
  /*!
   * @if jp
   * @brief Ê¸»úÎó¤ÎËöÈø¤Î¶õÇòÊ¸»ú¤òºEE¹¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤ÎËöÈø¤ËÂ¸ºß¤¹¤EõÇòÊ¸»ú¤òºEE¹¤E£
   * ¶õÇòÊ¸»ú¤È¤·¤Æ°·¤¦¤Î¤Ï' '(¥¹¥Ú¡¼¥¹)¤È'\\t'(¥¿¥Ö)¡£
   *
   * @param str ËöÈø¶õÇòÊ¸»úºEEèÍıÊ¸»úÎE   *
   * @else
   * @brief Erase the tail blank characters of string
   *
   * Erase the blank characters that exist at the tail of the given
   * string.  Space ' 'and tab '\\t' are supported as the blank
   * character.
   *
   * @param str The target tail blank characters of string for the erase
   *
   * @endif
   */
  void eraseTailBlank(std::string& str);

  /*!
   * @if jp
   * @brief Ê¸»úÎó¤ÎÀèÆ¬¡¦ËöÈø¤Î¶õÇòÊ¸»ú¤òºEE¹¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤ÎÀèÆ¬¤ª¤è¤ÓËöÈø¤ËÂ¸ºß¤¹¤EõÇòÊ¸»ú¤òºEE¹¤E£
   * ¶õÇòÊ¸»ú¤È¤·¤Æ°·¤¦¤Î¤Ï' '(¥¹¥Ú¡¼¥¹)¤È'\\t'(¥¿¥Ö)¡£
   *
   * @param str ÀèÆ¬ËöÈø¶õÇòÊ¸»úºEEèÍıÊ¸»úÎE   *
   * @else
   * @brief Erase the head blank and the tail blank characters of string
   *
   * Erase the head blank characters and the blank characters that
   * exist at the tail of the given string.  Space ' 'and tab '\\t'
   * are supported as the blank character.
   *
   * @param str The target tail blank characters of string for the erase
   *
   * @endif
   */
  void eraseBothEndsBlank(std::string& str);

  /*!
   * @if jp
   * @brief Ê¸»úÎó¤òÀµµ¬²½¤¹¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤ÎÀèÆ¬¤ª¤è¤ÓËöÈø¤ËÂ¸ºß¤¹¤EõÇòÊ¸»ú¤òºEE·¡¢
   * ±Ñ»ú¤ò¤¹¤Ù¤Æ¾®Ê¸»ú¤ËÊÑ´¹¤¹¤E£
   *
   * @param str ½èÍıÂĞ¾İÊ¸»úÎE   *
   * @else
   * @brief Erase the head/tail blank and replace upper case to lower case
   *
   * Erase the head blank characters and the blank characters that
   * exist at the tail of the given string.  Space ' 'and tab '\\t'
   * are supported as the blank character.
   * And all upper case cahracters are converted into lower case.
   *
   * @param str The target string for the erase
   *
   * @endif
   */
  std::string normalize(std::string& str);
  
  /*!
   * @if jp
   * @brief Ê¸»úÎó¤òÃÖ¤­´¹¤¨¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤ËÂĞ¤·¤Æ¡¢»ØÄê¤·¤¿Ê¸»ú¤ÎÃÖ¤­´¹¤¨¤ò¹Ô¤¦¡£
   *
   * @param str ÃÖ¤­´¹¤¨½èÍıÂĞ¾İÊ¸»úÎE   * @param from ÃÖ´¹¸µÊ¸»E   * @param to ÃÖ´¹ÀèÊ¸»E   *
   * @else
   * @brief Replace string
   *
   * Replace the given string with the specified characters.
   *
   * @param str The target characters of string for replacement processing
   * @param from Characters of replacement source
   * @param to Characters of replacement destination
   *
   * @endif
   */
  unsigned int replaceString(std::string& str, const std::string from,
                             const std::string to);
  
  /*!
   * @if jp
   * @brief Ê¸»úÎó¤òÊ¬³äÊ¸»ú¤ÇÊ¬³ä¤¹¤E   * 
   * ÀßÄê¤µ¤E¿Ê¸»úÎó¤òÍ¿¤¨¤é¤E¿¥Ç¥Eß¥¿¤ÇÊ¬³ä¤¹¤E£
   *
   * @param input Ê¬³äÂĞ¾İÊ¸»úÎE   * @param delimiter Ê¬³äÊ¸»úÎE¥Ç¥Eß¥¿)
   *
   * @return Ê¸»úÎóÊ¬³ä·EÌ¥E¹¥È
   *
   * @else
   * @brief Split string by delimiter
   * 
   * Split the set string by the given delimiter
   *
   * @param input The target characters of string for split
   * @param delimiter Split string (delimiter)
   *
   * @return Split string result list
   *
   * @endif
   */
  vstring split(const std::string& input,
                const std::string& delimiter,
                bool ignore_empty = false);
  
  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿Ê¸»úÎó¤òboolÃÍ¤ËÊÑ´¹¤¹¤E   * 
   * »ØÄê¤µ¤E¿Ê¸»úÎó¤ò¡¢trueÉ½¸½Ê¸»úÎó¡¢falseÉ½¸½Ê¸»úÎó¤ÈÈæ³Ó¤·¡¢¤½¤Î·EÌ¤E   * boolÃÍ¤È¤·¤ÆÊÖ¤¹¡£
   * Èæ³Ó¤Î·EÌ¡¢trueÉ½¸½Ê¸»úÎó¡¢falseÉ½¸½Ê¸»úÎó¤Î¤É¤Á¤é¤È¤â°E×¤·¤Ê¤¤¾Eç¤Ï¡¢
   * Í¿¤¨¤é¤E¿¥Ç¥Õ¥©¥EÈÃÍ¤òÊÖ¤¹¡£
   *
   * @param str È½ÃÇÂĞ¾İÊ¸»úÎE   * @param yes trueÉ½¸½Ê¸»úÎE   * @param no falseÉ½¸½Ê¸»úÎE   * @param default_value ¥Ç¥Õ¥©¥EÈÃÍ(¥Ç¥Õ¥©¥EÈÃÍ:true)
   * @else
   * @brief Convert given string into bool value
   * 
   * Compare the specified string with the true representation string and
   * the false representation string, and return the result as bool value.
   * If it matches neither the true representation string nor the false
   * representation string as a result of the comparison, the given default
   * value will be return.
   *
   * @param str The target string for investigation
   * @param yes The true representation string
   * @param no The false representation string
   * @param default_value The default value (The default value:true)
   * @endif
   */
  bool toBool(std::string str, std::string yes, std::string no, 
              bool default_value = true);
  /*!
   * @if jp
   * @brief Ê¸»úÎó¥E¹¥ÈÃæ¤Ë¤¢¤E¸»úÎó¤¬´Ş¤Ş¤EE«¤É¤¦¤«¤òÈ½ÃÇ¤¹¤E   * 
   * ÂE°ú¿ô¤Ë¥«¥ó¥Ş¶èÀÚ¤ê¤Î¥E¹¥È¤ò¡¢ÂE°ú¿ô¤ËÃµº÷ÂĞ¾İÊ¸»úÎó¤ò»ØÄê¤·¡¢
   * ¤½¤ÎÊ¸»úÎó¤¬ÂE°ú¿ô¤ÎÃæ¤Ë´Ş¤Ş¤EE«¤òÈ½ÃÇ¤¹¤E£
   *
   * @param list ÂĞ¾İ¥E¹¥È
   * @param value Ãµº÷Ê¸»úÎE   * @return true: ´Ş¤Ş¤EE¢false: ´Ş¤Ş¤EÊ¤¤
   *
   * @else
   * @brief Include if a string is included in string list
   * 
   * if the second argument is included in the comma separated string
   * list of the first argument, This operation returns "true value".
   *
   * @param list The target comma separated string
   * @param value The searched string
   * @return true: included, false: not included
   *
   * @endif
   */
  bool includes(const vstring& list, std::string value,
                bool ignore_case = true);

  /*!
   * @if jp
   * @brief Ê¸»úÎó¥E¹¥ÈÃæ¤Ë¤¢¤E¸»úÎó¤¬´Ş¤Ş¤EE«¤É¤¦¤«¤òÈ½ÃÇ¤¹¤E   * 
   * ÂE°ú¿ô¤Ë¥«¥ó¥Ş¶èÀÚ¤ê¤Î¥E¹¥È¤ò¡¢ÂE°ú¿ô¤ËÃµº÷ÂĞ¾İÊ¸»úÎó¤ò»ØÄê¤·¡¢
   * ¤½¤ÎÊ¸»úÎó¤¬ÂE°ú¿ô¤ÎÃæ¤Ë´Ş¤Ş¤EE«¤òÈ½ÃÇ¤¹¤E£
   *
   * @param list ÂĞ¾İÊ¸»úÎE   * @param value Ãµº÷Ê¸»úÎE   * @return true: ´Ş¤Ş¤EE¢false: ´Ş¤Ş¤EÊ¤¤
   *
   * @else
   * @brief Include if a string is included in string list
   * 
   * if the second argument is included in the comma separated string
   * list of the first argument, This operation returns "true value".
   *
   * @param list The target comma separated string
   * @param value The searched string
   * @return true: included, false: not included
   *
   * @endif
   */
  bool includes(const std::string& list, std::string value,
                bool ignore_case = true);
  
  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿Ê¸»úÎó¤¬ÀäÂĞ¥Ñ¥¹¤«¤É¤¦¤«¤òÈ½ÃÇ¤¹¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤¬ÀäÂĞ¥Ñ¥¹É½¸½¤Ç¤¢¤E«¤É¤¦¤«¤òÈ½ÃÇ¤¹¤E£
   * Ê¸»úÎó¤¬°Ê²¼¤Î¾Eç¤Ë¤ÏÀäÂĞ¥Ñ¥¹¤È¤·¤ÆÈ½ÃÇ¤¹¤E£
   *  - ÀèÆ¬Ê¸»ú¤¬'/' (UNIX¤Î¾EE
   *  - ÀèÆ¬£³Ê¸»ú¤¬¥¢¥EÕ¥¡¥Ù¥Ã¥È¡Ü'/'¡Ü'\\' (Windows¤Î¾EE
   *  - ÀèÆ¬£²Ê¸»ú¤¬'\\\\' (Windows¥Í¥Ã¥È¥E¼¥¯¥Ñ¥¹¤Î¾EE
   *
   * @param str È½ÄEĞ¾İÊ¸»úÎE   *
   * @return ÀäÂĞ¥Ñ¥¹È½ÄEEÌ
   *
   * @else
   * @brief Investigate whether the given string is absolute path or not
   *
   * Investigate whether the given string is absolute path or not.
   * Investigate it as an absolute path, if the string is as follows:
   *  - The first character '/' (UNIX)
   *  - The first 3 characters are alphabet ¡Ü'/'¡Ü'\\' (Windows)
   *  - The first 2 characters are '\\\\' (Windows network path)
   *
   * @param str The target string for the investigation
   *
   * @return Investigation result of absolute path
   *
   * @endif
   */
  bool isAbsolutePath(const std::string& str);
  
  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿Ê¸»úÎó¤¬URL¤«¤É¤¦¤«¤òÈ½ÃÇ¤¹¤E   *
   * Í¿¤¨¤é¤E¿Ê¸»úÎó¤¬URLÉ½¸½¤«¤É¤¦¤«¤òÈ½ÃÇ¤¹¤E£
   * Í¿¤¨¤é¤E¿Ê¸»úÎóÃæ¤Ë¡¢'://'¤È¤¤¤¦Ê¸»úÎó¤¬´Ş¤Ş¤EÆ¤¤¤EEç¤Ë¤Ï
   * URLÉ½¸½¤È¤·¤ÆÈ½ÃÇ¤¹¤E£
   *
   * @param str È½ÄEĞ¾İÊ¸»úÎE   *
   * @return URLÈ½ÄEEÌ
   *
   * @else
   * @brief Investigate whether the given string is URL or not
   *
   * Investigate whether the given string is URL or not.
   * When the string '://' is included in the given character string,
   * make it of URL representation.
   *
   * @param str The target string for investigation
   *
   * @return URL investigation result
   *
   * @endif
   */
  bool isURL(const std::string& str);
  
  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿¥ª¥Ö¥¸¥§¥¯¥È¤òstd::string¤ËÊÑ´¹
   *
   * °ú¿ô¤Ç»ØÄê¤µ¤E¿¥ª¥Ö¥¸¥§¥¯¥È¤òÊ¸»úÎó¤ËÊÑ´¹¤¹¤E£
   *
   * @param n ÊÑ´¹ÂĞ¾İ¥ª¥Ö¥¸¥§¥¯¥È
   *
   * @return Ê¸»úÎóÊÑ´¹·EÌ
   *
   * @else
   * @brief Convert the given object to std::string
   *
   * Convert the object specified by the argument to string.
   *
   * @param n The target object for conversion
   *
   * @return String conversion result
   *
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
   * @brief Í¿¤¨¤é¤E¿std::string¤ò¥ª¥Ö¥¸¥§¥¯¥È¤ËÊÑ´¹
   *
   * °ú¿ô¤ÇÍ¿¤¨¤é¤E¿Ê¸»úÎó¤ò»ØÄê¤µ¤E¿¥ª¥Ö¥¸¥§¥¯¥È¤ËÊÑ´¹¤¹¤E£
   *
   * @param val ÊÑ´¹Àè¥ª¥Ö¥¸¥§¥¯¥È
   * @param str ÊÑ´¹¸µÊ¸»úÎE   *
   * @return true: À®¸E false: ¼ºÇÔ
   *
   * @else
   * @brief Convert the given std::string to object.
   *
   * Convert string given by the argument to specified object.
   *
   * @param val The object of conversion destination
   * @param str String of conversion source
   *
   * @return true: successful, false: failed
   *
   * @endif
   */
  template <typename To>
  bool stringTo(To& val, const char* str)
  {
    if (str == 0) { return false; }

    std::stringstream s;
    if ((s << str).fail()) { return false; }
    if ((s >> val).fail()) { return false; }
    return true;
  }
  
  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿Ê¸»úÎó¤òstd::string¤ËÊÑ´¹
   *
   * °ú¿ô¤ÇÍ¿¤¨¤é¤E¿Ê¸»úÎó¤òstd::string¤ËÊÑ´¹¤¹¤E£
   *
   * @param val ÊÑ´¹ÀèÊ¸»úÎE   * @param str ÊÑ´¹¸µÊ¸»úÎE   *
   * @return true: À®¸E false: ¼ºÇÔ
   *
   * @else
   * @brief Convert the given string to std::string.
   *
   * Convert string given by the argument to std::string.
   *
   * @param val String of conversion destination
   * @param str String of conversion source
   *
   * @return true: successful, false: failed
   *
   * @endif
   */
  template<>
  bool stringTo<std::string>(std::string& val, const char* str);

  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿Ê¸»úÎó¥E¹¥È¤«¤é½ÅÊ£¤òºEE   *
   * °ú¿ô¤ÇÍ¿¤¨¤é¤E¿Ê¸»úÎó¥E¹¥È¤«¤é½ÅÊ£¤òºEE·¤¿¥E¹¥È¤òºûÜ®¤¹¤E£
   *
   * @param sv ³ÎÇ§¸µÊ¸»úÎó¥E¹¥È
   *
   * @return ½ÅÊ£ºEEèÍı·EÌ¥E¹¥È
   *
   * @else
   * @brief Eliminate duplication from the given string list
   *
   * Create a list of eliminating duplication from the string list
   * given by the argument.
   *
   * @param sv The string list for confirmation source
   *
   * @return Eliminating duplication result list
   *
   * @endif
   */
  vstring unique_sv(vstring sv);
  
  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿Ê¸»úÎó¥E¹¥È¤«¤éCSV¤òÀ¸À®
   *
   * °ú¿ô¤ÇÍ¿¤¨¤é¤E¿Ê¸»úÎó¥E¹¥È¤Î³ÆÍ×ÁÇ¤òÊÂ¤Ù¤¿CSV¤òÀ¸À®¤¹¤E£
   * Ê¸»úÎó¥E¹¥È¤¬¶õ¤Î¾Eç¤Ë¤Ï¶õÇòÊ¸»ú¤òÊÖ¤¹¡£
   *
   * @param sv CSVÊÑ´¹ÂĞ¾İÊ¸»úÎó¥E¹¥È
   *
   * @return CSVÊÑ´¹·EÌÊ¸»úÎE   *
   * @else
   * @brief Create CSV file from the given string list
   *
   * Create CSV that arranged each element of the character string
   * list given by the argument.
   * If the string list is empty, the null will be returned.
   *
   * @param sv The target string list for creating CSV
   *
   * @return String of CSV creating result
   *
   * @endif
   */
  std::string flatten(vstring sv);
  
  /*!
   * @if jp
   * @brief Í¿¤¨¤é¤E¿Ê¸»úÎó¥E¹¥È¤ò°ú¿ô¥E¹¥È¤ËÊÑ´¹
   *
   * °ú¿ô¤ÇÍ¿¤¨¤é¤E¿Ê¸»úÎó¥E¹¥È¤Î³ÆÍ×ÁÇËöÈø¤Ë'\\0'¤ò²Ã¤¨¡¢°ú¿ô¥E¹¥È
   * ¤ËÊÑ´¹¤¹¤E£
   *
   * @param args ÊÑ´¹ÂĞ¾İÊ¸»úÎó¥E¹¥È
   *
   * @return °ú¿ôÊÑ´¹·EÌÊ¸»úÎE   *
   * @else
   * @brief Convert the given string list into the argument list
   *
   * Convert the string list into the argument list by adding '\\0' to
   * each element at the end of the string list given by the argument
   *
   * @param args The target string list for conversion
   *
   * @return String of argument conversion result
   *
   * @endif
   */
  char** toArgv(const vstring& args); 


  /*!
   * @if jp
   * @brief »ØÄê¤µ¤E¿½ñ¼°¤ËÊÑ´¹
   *
   * °ú¿ô¤ÇÍ¿¤¨¤é¤E¿½ñ¼°¤ËÊÑ´¹¤·¤ÆÊÖ¤¹¡£
   *
   * @param fmt ½ñ¼°
   *
   * @return ÊÑ´¹·EÌÊ¸»úÎE   *
   * @else
   * @brief Convert it into a format given with an argumen
   *
   * Convert it into a format given with an argument and return it.
   *
   * @param fmt Format
   *
   * @return String of conversion result
   *
   * @endif
   */
