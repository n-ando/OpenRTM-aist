// -*- C++ -*-
/*!
 * @file StringUtil.h
 * @brief String operation utility
 * @date $Date: 2006-10-17 10:11:09 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: StringUtil.h,v 1.3 2006-10-17 10:11:09 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
#include <algorithm>
#include <vector>


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
bool isEscaped(const std::string& str, std::string::size_type pos)
{
  --pos;
  unsigned int i;
  for (i = 0; (pos >= 0) && str[pos] == '\\'; --pos, ++i) ;
  // If the number of \ is odd, delimiter is escaped.
  return (i % 2) == 1;
}


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
struct escape_functor
{
  escape_functor() {};
  void operator()(const char c)
  {
    if      (c == '\t')  str += "\\t";
    else if (c == '\n')  str += "\\n";
    else if (c == '\f')  str += "\\f";
    else if (c == '\r')  str += "\\r";
    //    else if (c == '\"')  str += "\\\"";
    //    else if (c == '\'')  str += "\\\'";
    else str.push_back(c);
  }
  std::string str;
};


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
std::string escape(const std::string str)
{
  return for_each(str.begin(), str.end(), escape_functor()).str;
}


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
struct unescape_functor
{
  unescape_functor() : count(0) {};
  void operator()(char c)
  {
    if (c == '\\')
      {
	++count;
	if (!(count % 2))
	  {
	    str.push_back(c);
	  }
      }
    else
      {
	if (count > 0 && (count % 2))
	  {
	    count = 0;
	    if      (c == 't')  str.push_back('\t');
	    else if (c == 'n')  str.push_back('\n');
	    else if (c == 'f')  str.push_back('\f');
	    else if (c == 'r')  str.push_back('\r');
	    else if (c == '\"') str.push_back('\"');
	    else if (c == '\'') str.push_back('\'');
	    else str.push_back(c);
	  }
	else
	  {
	    count = 0;
	    str.push_back(c);
	  }
      }
  } 
  std::string str;
  int count;
};


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
std::string unescape(const std::string str)
{
  return for_each(str.begin(), str.end(), unescape_functor()).str;

}


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
void eraseHeadBlank(std::string& str)
{
  while (str[0] == ' ' || str[0] == '\t') str.erase(0, 1);
}


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
void eraseTailBlank(std::string& str)
{
  while ((str[str.size() - 1] == ' ' || str[str.size() - 1] == '\t') &&
	 !isEscaped(str, str.size() - 1))
    str.erase(str.size() - 1, 1);
}


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
std::vector<std::string> split(const std::string& input,
			       const std::string& delimiter)
{
  typedef std::string::size_type size;
  std::vector<std::string> results;
  size delim_size = delimiter.size();
  size found_pos(0), begin_pos(0), pre_pos(0), substr_size(0);
  
  if (input.substr(0, delim_size) == delimiter)
    begin_pos = pre_pos = delim_size;
  
  while (1)
    {
    REFIND:
      found_pos = input.find(delimiter, begin_pos);
      if (found_pos == std::string::npos) 
	{
	  results.push_back(input.substr(pre_pos));
	  break;
	}
      if ('\\' == input.at(found_pos - 1))
	{
	  begin_pos = found_pos + delim_size;
	  goto REFIND;
	}
      
      substr_size = found_pos - pre_pos;
      
      if (substr_size > 0)
	{
	  std::string substr(input.substr(pre_pos, substr_size));
	  eraseHeadBlank(substr);
	  results.push_back(substr);
	}
      begin_pos = found_pos + delim_size;
      pre_pos   = found_pos + delim_size;
    }
  return results;
}


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
struct Toupper
{
  void operator()(char &c)
  {
    c = toupper(c);
  }
};


bool toBool(std::string str, std::string yes, std::string no, 
	    bool default_value = true)
{

  
  std::for_each(str.begin(), str.end(), Toupper());
  std::for_each(yes.begin(), yes.end(), Toupper());
  std::for_each(no.begin(),  no.end(),  Toupper());

  if (str.find(yes) != std::string::npos)
    return true;
  else if (!str.find(no) != std::string::npos)
    return false;
  else
    return default_value;
}



/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
bool isAbsolutePath(const std::string& str)
{
  // UNIX absolute path is begun from '/'
  if (str[0] == '/') return true;
  // Windows absolute path is begun from '[a-zA-Z]:\'
  if (isalpha(str[0]) && (str[1] == ':') && str[2] == '\\') return true;
  // Windows network file path is begun from '\\'
  if (str[0] == '\\' && str[1] == '\\') return true;

  return false;
}


/*!
 * @if jp
 * @brief
 * @else
 * @brief
 * @endif
 */
bool isURL(const std::string& str)
{
  typedef std::string::size_type size;
  size pos;
  pos = str.find(":");
  if ((pos != std::string::npos) &&
      (str[pos + 1] == '/') &&
      (str[pos + 2] == '/'))
    return true;
  return false;
}


#endif // StringUtil_h
