#include <coil/Factory.h>

class Base
{
public:
  virtual ~Base(){}
  virtual std::string name() = 0;
};

typedef coil::GlobalFactory<Base> g_factory;
