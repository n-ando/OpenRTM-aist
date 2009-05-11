#ifndef MYFACTORY_H
#define MYFACTORY_H
#include <coil/Factory.h>

class Base
{
public:
  virtual ~Base(){}
  virtual std::string name() = 0;
};


// for Windows DLL export
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define DLL_EXPORT __declspec(dllexport)
#   define DLL_IMPORT __declspec(dllimport)
#   ifdef LIBRARY_EXPORTS
#      define EXTERN
#   else
#      define EXTERN extern
#   endif
#else 
#   define DLL_EXPORT
#   define DLL_IMPORT
#   define EXTERN
#endif /* Windows */

#ifdef LIBRARY_EXPORTS
#   define DLL_PLUGIN DLL_EXPORT
#else
#   define DLL_PLUGIN DLL_IMPORT
#endif

typedef coil::GlobalFactory<Base> MyFactory;
EXTERN template class DLL_PLUGIN coil::GlobalFactory<Base>;


#endif // MYFACTORY_H
