// -*- C++ -*-
/*!
 * @file Properties.cpp
 * @brief Property list class (derived from Java Properties)
 * @date $Date: 2007-09-19 03:00:08 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Properties.cpp,v 1.7.2.1 2007-09-19 03:00:08 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.7  2007/04/23 04:56:39  n-ando
 * Some fixes about const.
 *
 * Revision 1.6  2007/04/13 18:14:02  n-ando
 * Now Properties class is implemented as hierarchical data structure
 * instead of std::map based data structure.
 *
 * Revision 1.5  2007/01/06 17:59:18  n-ando
 * getProperty() is now const function.
 *
 * Revision 1.4  2006/11/06 01:24:56  n-ando
 * Bug fix.
 * - Constructor's argument was not stored to the property values.
 *
 * Revision 1.3  2006/10/17 10:10:13  n-ando
 * Some escape/unescape related bugs are fixed.
 * The following some functions were moved to StringUtil.h
 * - eraseHeadBlank(), eraseTailBlank(), replaceString()
 *
 * Revision 1.2  2006/10/13 03:49:52  n-ando
 * The bug that white space delimiter did not work properly was fixed.
 *
 * Revision 1.1  2006/09/11 18:09:42  n-ando
 * Java compatible properties class.
 *
 *
 */


#include <rtm/Properties.h>
#include <rtm/StringUtil.h>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @brief コンストラクタ(rootノードのみ作成)
   * @else
   * @brief Constructor
   * @endif
   */
  Properties::Properties(const char* key, const char* value)
    : name(key), value(value), default_value(""), root(NULL), m_empty("")
  {
    leaf.clear();
  }


  /*!
   * @if jp
   * @brief コンストラクタ(mapでデフォルト値を与える)
   * @else
   * @brief Constructor
   * @endif
   */
  Properties::Properties(std::map<std::string, std::string>& defaults)
    : name(""), value(""), default_value(""), root(NULL), m_empty("")
  {
    leaf.clear();
    std::map<std::string, std::string>::iterator it(defaults.begin());
    std::map<std::string, std::string>::iterator it_end(defaults.end());
    
    while (it != it_end)
      {
        setDefault(it->first.c_str(), it->second.c_str());
        ++it;
      }
  }
  
  
  /*!
   * @if jp
   * @brief コンストラクタ(char*[] でデフォルト値を与える)
   * @else
   * @brief Constructor
   * @endif
   */
  Properties::Properties(const char* defaults[], long num)
    : name(""), value(""), default_value(""), root(NULL), m_empty("")
  {
    leaf.clear();
    setDefaults(defaults, num);
  }
  

  /*!
   * @if jp
   * @brief コピーコンストラクタ
   * @else
   * @brief Copy Constructor
   * @endif
   */
  Properties::Properties(const Properties& prop)
    : name(prop.name), value(prop.value),
      default_value(prop.default_value), root(NULL), m_empty("")
  {
    std::vector<std::string> keys;
    keys = prop.propertyNames();
    for (int i(0), len(keys.size()); i < len; ++i)
      {
	Properties* node(NULL);
	if ((node = prop.getNode(keys[i])) != NULL)
	  {
	    setDefault(keys[i],  node->default_value);
	    setProperty(keys[i], node->value);
	  }
      }
  }


  /*!
   * @if jp
   * @brief 代入演算子
   * @else
   * @brief Assignment operator
   * @endif
   */
  Properties& Properties::operator=(const Properties& prop)
  {
    clear();
    name = prop.name;
    value = prop.value;
    default_value = prop.default_value;

    std::vector<std::string> keys;
    keys = prop.propertyNames();
    for (int i(0), len(keys.size()); i < len; ++i)
      {
	Properties* node(NULL);
	if ((node = prop.getNode(keys[i])) != NULL)
	  {
	    setDefault(keys[i],  node->default_value);
	    setProperty(keys[i], node->value);
	  }
      }

    return *this;
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
    // Delete children
    clear();

    // delete myself from parent
    if (root != NULL)
      {
	root->removeNode(name.c_str());
      }
  };
  

  //============================================================
  // public fnctions
  //============================================================
  /*!
   * @if jp
   * @brief 指定されたキーを持つプロパティを、プロパティリストから探す
   * @else
   * @brief Searches for the property with the specified key in this property
   * @endif
   */
  const std::string& Properties::getProperty(const std::string& key) const
  {
    std::vector<std::string> keys;
    split(key, '.', keys);
    Properties* node(NULL);
    if ((node = _getNode(keys, 0, this)) != NULL)
      {
	return (!node->value.empty()) ? node->value : node->default_value;
      }
    return m_empty;
  }
  

  /*!
   * @if jp
   * @brief 指定されたキーを持つプロパティを、プロパティリストから探す
   * @else
   * @brief Searches for the property with the specified key in this property
   * @endif
   */
  const std::string& Properties::getProperty(const std::string& key,
					     const std::string& def) const
  {
    const std::string& value((*this)[key]);
    
    return value.empty() ? def : value;
  }


  /*!
   * @if jp
   * @brief 指定されたキーを持つプロパティを、プロパティリストから探す
   * @else
   * @brief Searches for the property with the specified key in this property
   * @endif
   */
  const std::string& Properties::operator[](const std::string& key) const
  {
    return getProperty(key);
  }
  
  
  /*!
   * @if jp
   * @brief 指定されたキーを持つプロパティを、プロパティリストから探す
   * @else
   * @brief Searches for the property with the specified key in this property
   * @endif
   */
  std::string& Properties::operator[](const std::string& key)
  {
    setProperty(key, getProperty(key));
    Properties* prop = getNode(key);
    
    return prop->value;
  }


  /*!
   * @if jp
   * @brief 指定されたキーに対してデフォルト値を設定する
   * @else
   * @brief Set value as the default value to specified key's property
   * @endif
   */
  const std::string& Properties::getDefault(const std::string& key) const
  {
    std::vector<std::string> keys;
    split(key, '.', keys);
    Properties* node(NULL);
    if ((node = _getNode(keys, 0, this)) != NULL)
      {
	return node->default_value;
      }
    return m_empty;
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
    std::vector<std::string> keys;
    split(key, '.', keys);
    
    Properties* curr(this);
    for (int i(0), len(keys.size()); i < len; ++i)
      {
	Properties* next(curr->hasKey(keys[i].c_str()));
	if (next == NULL)
	  {
	    next = new Properties(keys[i].c_str());
	    next->root = curr;
	    curr->leaf.push_back(next);
	  }
	curr = next;
      }
    std::string retval(curr->value);
    curr->value = value;
    return retval;
  }


  /*!
   * @if jp
   * @brief Properties にデフォルト value を key について登録する
   * @else
   * @brief Sets a default value associated with key in the property list
   * @endif
   */
  std::string Properties::setDefault(const std::string& key,
				     const std::string& value)
  {
    std::vector<std::string> keys;
    split(key, '.', keys);

    Properties* curr(this);
    for (int i(0), len(keys.size()); i < len; ++i)
      {
	Properties* next(curr->hasKey(keys[i].c_str()));
	if (next == NULL)
	  {
	    next = new Properties(keys[i].c_str());
	    next->root = curr;
	    curr->leaf.push_back(next);
	  }
	curr = next;
      }
    curr->default_value = value;
    return value;
  }
  

  /*!
   * @if jp
   * @brief Properties にデフォルト値をまとめて登録する
   * @else
   * @brief Sets a default value associated with key in the property list
   * @endif
   */
  void Properties::setDefaults(const char* defaults[], long num)
  {
    for (long i = 0; i < num && defaults[i][0] != '\0' ; i += 2)
      {
	std::string key(defaults[i]);
	std::string value(defaults[i + 1]);
	
	eraseHeadBlank(key);
	eraseTailBlank(key);
	
	eraseHeadBlank(value);
	eraseTailBlank(value);
	
	setDefault(key.c_str(), value.c_str());
      }
  }


  //============================================================
  // load and save functions
  //============================================================
  /*!
   * @if jp
   * @brief 指定された出力ストリームに、プロパティリストを出力する
   * @else
   * @brief Prints this property list out to the specified output stream
   * @endif
   */
  void Properties::list(std::ostream& out)
  {
    _store(out, "", this);
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
	
	setProperty(key.c_str(), value.c_str());
	pline.clear();
      }
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
   * @brief プロパティリストを出力ストリームへ保存する
   * @else
   * @brief Stores property list to the output stream
   * @endif
   */
  void Properties::store(std::ostream& out, const std::string& header)
  {
    out << "# " << header << std::endl;
    _store(out, "", this);
  }


  //============================================================
  // other util functions
  //============================================================
  /*!
   * @if jp
   * @brief プロパティのキーのリストを vector で返す
   * @else
   * @brief Returns an vector of all the keys in this property
   * @endif
   */
  std::vector<std::string> Properties::propertyNames() const
  {
    std::vector<std::string> names;
    for (int i(0), len(leaf.size()); i < len; ++i)
      {
	_propertiyNames(names, leaf[i]->name, leaf[i]);
      }
    return names;
  }
  
  
  /*!
   * @if jp
   * @brief プロパティの数を取得する
   * @else
   * @brief Get number of Properties
   * @endif
   */
  int Properties::size() const
  {
    return propertyNames().size();
  }


  /*!
   * @if jp
   * @brief ノードを取得する
   * @else
   * @brief Get node of Properties
   * @endif
   */
  Properties* Properties::getNode(const std::string& key) const
  {
    std::vector<std::string> keys;
    std::string value;
    split(key, '.', keys);
    return _getNode(keys, 0, this);
  }
  

  /*!
   * @if jp
   * @brief ノードを切断する
   * @else
   * @brief Get node of Properties
   * @endif
   */
  Properties* Properties::removeNode(const char* leaf_name)
  {
    std::vector<Properties*>::iterator it(leaf.begin()), it_end(leaf.end());
    Properties* prop;
    while (it != it_end)
      {
	if ((*it)->name == leaf_name)
	  {
	    prop = *it;
	    leaf.erase(it);
	    return prop;
	  }
	++it;
      }
    return NULL;
  }
 
  
  /*!
   * @if jp
   * @brief 子ノードにkeyがあるかどうか
   * @else
   * @brief If key exists in the children
   * @endif
   */
  Properties* Properties::hasKey(const char* key) const
  {
    for (int i(0), len(leaf.size()); i < len; ++i)
      {
	if (leaf[i]->name == key)
	  return leaf[i];
      }
    return NULL;
  }


  /*!
   * @if jp
   * @brief 子ノードを全て削除する
   * @else
   * @brief If key exists in the children
   * @endif
   */
  void Properties::clear()
  {
    while (!leaf.empty())
      {
	if (leaf.back() != NULL) // recursive delete
	  delete leaf.back();    // back() returns always new
      }
  }


  /*!
   * @if jp
   * @brief Propertyをマージする
   * @else
   * @brief Merge properties
   * @endif
   */
  Properties& Properties::operator<<(const Properties& prop)
  {
    std::vector<std::string> keys;
    keys = prop.propertyNames();
    for (int i(0), len(prop.size()); i < len; ++i)
      {
	(*this)[keys[i]] = prop[keys[i]];
      }
    return (*this);
  }



  //------------------------------------------------------------
  // Protected functions
  //------------------------------------------------------------
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


  bool Properties::split(const std::string& str, const char delim,
				std::vector<std::string>& value)
  {
    if (str.empty()) return false;
    
    std::string::size_type begin_it(0), end_it(0);
    std::string::size_type len(str.size());
    
    while (end_it < len)
      {
	if ((str[end_it] == delim) && !isEscaped(str, end_it))
	  {
	    // substr(0, i) returns 0...(i-1) chars.
	    value.push_back(str.substr(begin_it, end_it - begin_it));
	    begin_it = end_it + 1;
	  }
	++end_it;
      }
    value.push_back(str.substr(begin_it, end_it));
    return true;
  }
  

  std::string indent(int index)
  {
    std::string space;
    for (int i(0); i < index - 1; ++i)
      {
	space += "  ";
      }
    return space;
  }


  Properties*
  Properties::_getNode(std::vector<std::string>& keys,
		       std::vector<Properties*>::size_type index,
		       const Properties* curr)
  {
    Properties* next(curr->hasKey(keys[index].c_str()));

    if (next == NULL)
      {
	return NULL;
      }

    if (index < keys.size() - 1) // node
      {
	return next->_getNode(keys, ++index, next);
      }
    else
      {
	return next;
      }
    return NULL;
  }

  void
  Properties::_propertiyNames(std::vector<std::string>& names,
			      std::string curr_name,
			      const Properties* curr)
  {
    if (!curr->leaf.empty())
      {
	for (int i(0), len(curr->leaf.size()); i < len; ++i)
	  {
	    std::string next_name;
	    //	    if (curr_name == "") next_name = curr->leaf[i]->name;
	    next_name = curr_name + "." + curr->leaf[i]->name;
	    _propertiyNames(names, next_name, curr->leaf[i]);
	  }
      }
    else
      {
	names.push_back(curr_name);
      }
    return;
  }

  void
  Properties::_store(std::ostream& out, std::string curr_name,
		     Properties* curr)
  {
    if (!curr->leaf.empty())
      {
	
	for (int i(0), len(curr->leaf.size()); i < len; ++i)
	  {
	    std::string next_name;
	    if (curr_name == "") next_name = curr->leaf[i]->name;
	    else next_name = curr_name + "." + curr->leaf[i]->name;
	    _store(out, next_name, curr->leaf[i]);
	  }
      }
    else
      {
	out << curr_name << ": " << curr->value << std::endl;
      }
    return;
  }


  std::ostream&
  Properties::_dump(std::ostream& out, const Properties& curr, int index)
  {
    if (index != 0) out << indent(index) << "- " << curr.name;
    if (curr.leaf.empty())
      {
	if (curr.value.empty())
	  {
	    out << ": " << curr.default_value << std::endl;
	  }
	else
	  {
	    out << ": " << curr.value << std::endl;
	  }
	return out;
      }
    if (index != 0) out << std::endl;
    for (int i(0), len(curr.leaf.size()); i < len ;++i)
      {
	_dump(out, *(curr.leaf[i]), index + 1);
      }
    return out;
  }


  std::string Properties::indent(int index)
  {
    std::string space;
    for (int i(0); i < index - 1; ++i)
      {
	space += "  ";
      }
    return space;
  }


  std::ostream& operator<<(std::ostream& lhs, const Properties& rhs)
  {
    return rhs._dump(lhs, rhs, 0);
  }


}; // namespace RTC
