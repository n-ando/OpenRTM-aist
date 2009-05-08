#ifndef MYFACTORY_H
#define MYFACTORY_H
#include <coil/Factory.h>

class Base
{
public:
  virtual ~Base(){}
  virtual std::string name() = 0;
};

typedef coil::GlobalFactory<Base> MyFactory;
#endif // MYFACTORY_H
