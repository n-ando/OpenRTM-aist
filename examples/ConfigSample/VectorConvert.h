// -*- C++ -*-

#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <coil/stringutil.h>

namespace std
{
  template<typename T>
  std::istream& operator>>(std::istream& is, std::vector<T>& v)
  {
    std::string s;
    std::vector<std::string> sv;
    is >> s;
    sv = coil::split(s ,",");
    v.resize(sv.size());
    for (size_t i(0), len(sv.size()); i < len; ++i)
      {
	T tv;
	if (coil::stringTo(tv, sv[i].c_str()))
	  {
	    v[i] = tv;
	  }
      }
    return is;
  }
} // namespace std

