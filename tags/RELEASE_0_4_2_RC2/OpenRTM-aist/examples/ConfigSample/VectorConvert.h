// -*- C++ -*-

#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <rtm/StringUtil.h>

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v)
{
  std::string s;
  std::vector<std::string> sv;
  is >> s;
  sv = split(s ,",");
  v.resize(sv.size());
  for (int i(0), len(sv.size()); i < len; ++i)
    {
      T tv;
      if (stringTo(tv, sv[i].c_str()))
	{
	  v[i] = tv;
	}
    }
  return is;
}
