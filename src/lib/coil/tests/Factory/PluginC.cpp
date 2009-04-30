#include "MyFactory.h"


// for Windows DLL export 
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
BOOL WINAPI DllMain (HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved);
#else 
#   define DLL_EXPORT 
#   define WINAPI
#endif /* Windows */


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
  DLL_EXPORT void PluginCInit();
  void PluginCInit()
  {
    g_factory::instance().addFactory("C",
                                     coil::Creator<Base, C>,
                                     coil::Destructor<Base, C>);
  }


};
