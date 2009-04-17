#include "MyFactory.h"

class C
  : public Base
{
public:
  C()
  {
  }
  virtual std::string name()
  {
    return "C";
  }
};

extern "C"
{
  void PluginCInit()
  {
    g_factory::instance().addFactory("C",
                                     coil::Creator<Base, C>,
                                     coil::Destructor<Base, C>);
  }


};
