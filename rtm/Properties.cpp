// -*- C++ -*-
/*!
 * @file Properties.cpp
 * @brief Property list class (derived from Java Properties)
 * @date $Date: 2006-10-17 10:10:13 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Properties.cpp,v 1.3 2006-10-17 10:10:13 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/13 03:49:52  n-ando
 * The bug that white space delimiter did not work properly was fixed.
 *
 * Revision 1.1  2006/09/11 18:09:42  n-ando
 * Java compatible properties class.
 *
 *
 */

#include <iostream>
#include "rtm/Properties.h"
#include "rtm/StringUtil.h"

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  Properties::Properties(const std::map<std::string, std::string>& defaults)
  {
    m_defaults = defaults;
    
    Itr it    (m_defaults.begin());
    Itr it_end(m_defaults.end());
    
    while (it != it_end)
      {
	(*this)[std::string(it->first)];
	++it;
      }
    
  }
  
  
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  Properties::Properties(const char* defaults[], long num)
  {
    for (long i = 0; i < num && defaults[i][0] != '\0' ; i += 2)
      {
	std::string key(defaults[i]);
	std::string value(defaults[i + 1]);
	
	//	key = unescape(key);
	eraseHeadBlank(key);
	eraseTailBlank(key);
	
	//	value = unescape(value);
	eraseHeadBlank(value);
	eraseTailBlank(value);
	
	m_defaults[key] = value;
	(*this)[key];
      }
  }
  
  
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  Properties::~Properties()
  {
  };
  
  
  /*!
   * @if jp
   * @brief 指定されたキーを持つプロパティを、プロパティリストから探す
   * @else
   * @brief Searches for the property with the specified key in this property
   * @endif
   */
  std::string Properties::getProperty(const std::string& key)
  {
    return getProperty(key, "");
  }
  
  
  /*!
   * @if jp
   * @brief 指定されたキーを持つプロパティを、プロパティリストから探す
   * @else
   * @brief Searches for the property with the specified key in this property
   * @endif
   */
  std::string Properties::getProperty(const std::string& key,
				      const std::string& defaultValue)
  {
    std::string s((*this)[key]);
    if (s == "")
      {
	std::string defaults;
	defaults = m_defaults[key];
	if (defaults == "")
	  return defaultValue;
	else
	  return defaults;
      }
    else
      {
	return s;
      }
  }
  
  
  /*!
   * @if jp
   * @brief 指定された出力ストリームに、プロパティリストを出力する
   * @else
   * @brief Prints this property list out to the specified output stream
   * @endif
   */
  void Properties::list(std::ostream& out)
  {
    Itr it    (this->begin());
    Itr it_end(this->end());
    
    while (it != it_end)
      {
	std::string key(it->first);
	std::string value;
	std::string line;
	value = getProperty(it->first);
	key = escape(key);
	value = escape(value);
	line = key + std::string(" = ") + value;
	out << line.c_str() << std::endl;
	++it;
      }
  }
  
  
  /*!
   * @if jp
   * @brief 入力ストリームからキーと要素が対になったプロパティリストを読み込む
   * @else
   * @brief Loads property list consists of key:value from input stream
   * @endif
   */
  void Properties::load(std::istream& inStream)
  {
    std::string pline;
    
    while(!inStream.eof())
      {
	std::string tmp;
	getline(inStream, tmp);
	eraseHeadBlank(tmp);
	
	// Skip comments or empty lines
	if (tmp[0] == '#' || tmp[0] == '!' || tmp == "") continue;
	
	// line-end '\' continues entry
	if (tmp[tmp.size() - 1] == '\\' && !isEscaped(tmp, tmp.size() - 1))
	  {
	    tmp.erase(tmp.size() - 1);
	    pline += tmp;
	    continue;
	  }
	pline += tmp;
	
	// Skip empty line (made of only ' ' or '\t')
	if (pline == "") continue;
	
	std::string key, value;
	splitKeyValue(pline, key, value);
	key = unescape(key);
	eraseHeadBlank(key);
	eraseTailBlank(key);
	
	value = unescape(value);
	eraseHeadBlank(value);
	eraseTailBlank(value);
	
	(*this)[key] = value;
	pline.clear();
      }
  }
  
  
  /*!
   * @if jp
   * @brief プロパティのキーのリストを vector で返す
   * @else
   * @brief Returns an vector of all the keys in this property
   * @endif
   */
  std::vector<std::string> Properties::propertyNames()
  {
    std::vector<std::string> names;
    Itr it    (this->begin());
    Itr it_end(this->end());
    
    while (it != it_end)
      {
	names.push_back(it->first);
	++it;
      }
    return names;
  }
  
  
  /*!
   * @if jp
   * @brief プロパティリストを指定されたストリームに保存する
   * @else
   * @brief Save the properties list to the stream
   * @endif
   */
  void Properties::save(std::ostream& out, const std::string& header)
  {
    store(out, header);
    return;
  }
  
  
  /*!
   * @if jp
   * @brief Properties に value を key について登録する
   * @else
   * @brief Sets a value associated with key in the property list
   * @endif
   */
  std::string Properties::setProperty(const std::string& key,
				      const std::string& value)
  {
    std::string old_value(getProperty(key));
    (*this)[key] = value;
    return old_value;
  }
  
  
  /*!
   * @if jp
   * @brief プロパティリストを出力ストリームへ保存する
   * @else
   * @brief Stores property list to the output stream
   * @endif
   */
  void Properties::store(std::ostream& out, const std::string& header)
  {
    Itr it    (this->begin());
    Itr it_end(this->end());
    
    out << "# " << header << std::endl;
    while (it != it_end)
      {
	std::string key(it->first);
	std::string value;
	
	value = getProperty(it->first);
	key = escape(key);
	value = escape(value);
	out << key << " = " << value << std::endl;
	++it;
      }
  }
  
 
  void Properties::splitKeyValue(const std::string& str, std::string& key,
				 std::string& value)
  {
    std::string::size_type i(0);
    std::string::size_type len(str.size());
    
    while (i < len)
      {
	if ((str[i] == ':' || str[i] == '=') && !isEscaped(str, i))
	  {
	    key   = str.substr(0, i); // substr(0, i) returns 0...(i-1) chars.
	    value = str.substr(i + 1);
	    return;
	  }
	++i;
      }
    
    // If no ':' or '=' exist, ' ' would be delimiter.
    i = 0;
    while (i < len)
      {
	if ((str[i] == ' ') && !isEscaped(str, i))
	  {
	    key   = str.substr(0, i); // substr(0, i) returns 0...(i-1) chars.
	    value = str.substr(i + 1);
	    return;
	  }
	++i;
      }
    
    key = str;
    value = "";
    return;
  }
  
}; // namespace RTC
