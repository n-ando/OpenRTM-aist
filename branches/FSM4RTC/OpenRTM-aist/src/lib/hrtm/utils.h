#ifndef HRTM_UTILS_H
#define HRTM_UTILS_H
#include <iostream>
using namespace std;

namespace hrtm
{
  ostream& operator<<(ostream& os, const SDOPackage::NameValue& nv) {
  os << "name:" << nv.name << endl;
  const char* tmp(NULL);
  os << "value:";
  if (nv.value >>= tmp) {
    os << tmp << endl;
  } else {
    os << "<<<NO PRINTABLE>>>" << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const SDOPackage::NVList& nvlist) {
  CORBA::ULong len(nvlist.length());
  for (CORBA::ULong i(0); i < len; i++) {
    os << nvlist[i];
  }
  return os;
}

ostream& operator<<(ostream& os, const SDOPackage::ConfigurationSet& cs) {
  os << "---[BEGIN ConfigurationSet]---" << endl;
  os << "id:" << cs.id << endl;
  os << "description:" << cs.description << endl;
  os << "configuration_data:" << endl;
  os << cs.configuration_data << endl;
  os << "---[END   ConfigurationSet]---" << endl;
  return os;
}
};

#endif // HRTM_UTILS_H
