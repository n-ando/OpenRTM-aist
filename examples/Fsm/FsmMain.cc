/*
  Copyright 2011 Honda R&D Co.,Ltd.
*/
#if defined(_MSC_VER) && defined(HRTM_DLL)
#define USE_stub_in_nt_dll
#endif

#if defined(__vxworks)
#define INCLUDE_CORBA_CORBALOC 1
#include "hrtm/vw/rdate.h"
#include <envLib.h>
#include <stdio.h>
const char INIT_REF_OPT[] = "-ORBInitRef";
#endif

#include <hrtm/component_manager.h>
#include <iostream>  // NOLINT
#if !defined(USE_SHAREDLIB)
#include "Fsm.h"  // NOLINT
#endif

using hrtm::ComponentManager;
using hrtm::utils::Logger;

#if defined(USE_SHAREDLIB)
#if defined(_MSC_VER)
#define strdup _strdup
#endif
namespace {
void addArgs(int& argc, char**& argv) {
  std::string conf("-frtc_shared.conf");
  char** args = new char*[argc + 2];
  for (int i = 0; i != argc; ++i) {
      args[i] = argv[i];
  }
  args[argc] = strdup(conf.c_str());
  ++argc;
  args[argc] = 0;
  argv = args;
}
}
#endif

int comp_main(int argc, char** argv) {
#if defined(USE_SHAREDLIB)
  int i(1);
  for (; i < argc; i++) {
    if (strstr(argv[i], "-f") == argv[i]) {
      break;
    }
  }
  if (argc <= i) {
    addArgs(argc, argv);
  }
#endif
  ComponentManager& manager(ComponentManager::instance(argc, argv));
#if defined(USE_SHAREDLIB)
  free(argv[argc - 1]);
  delete[] argv;
#else
  manager.set_init_proc(ModuleInit);
#endif
  manager.activate();
  manager.run();
  HRTM_TRACE("Fsm", "exit...");
  return 0;
}

#if !defined(__vxworks)
int main(int argc, char** argv) {
  int ret(comp_main(argc, argv));
  return ret;
}
#else
const char NAME_SERVICE_IP[] = "NAME_SERVICE_IP";

char*
GetInitRef()
{
    static char init_ref[255];
    const char* init_ref_head = "NameService=corbaloc::iiop:1.0@";
    const char* ip = getenv(NAME_SERVICE_IP);
    const char* init_ref_tail = "/NameService";
    sprintf(init_ref, "%s%s%s", init_ref_head, ip, init_ref_tail);

    return (char*)init_ref;
}

void fsm_main(char* arg1, char* arg2, char* arg3,
              char* arg4, char* arg5, char* arg6,
              char* arg7, char* arg8, char* arg9) {
  int   argc     = 0;
  char* argv[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  argv[argc++] = taskName(taskIdSelf());

  if (arg1 != 0 && *arg1 != 0) argv[argc++] = arg1; else goto End_Args;
  if (arg2 != 0 && *arg2 != 0) argv[argc++] = arg2; else goto End_Args;
  if (arg3 != 0 && *arg3 != 0) argv[argc++] = arg3; else goto End_Args;
  if (arg4 != 0 && *arg4 != 0) argv[argc++] = arg4; else goto End_Args;
  if (arg5 != 0 && *arg5 != 0) argv[argc++] = arg5; else goto End_Args;
  if (arg6 != 0 && *arg6 != 0) argv[argc++] = arg6; else goto End_Args;
  if (arg7 != 0 && *arg7 != 0) argv[argc++] = arg7; else goto End_Args;
  if (arg8 != 0 && *arg8 != 0) argv[argc++] = arg8; else goto End_Args;
  if (arg9 != 0 && *arg9 != 0) argv[argc++] = arg9; else goto End_Args;

End_Args:

  if (argc < 9) {
      argv[argc++] = (char*)INIT_REF_OPT;
      argv[argc++] = GetInitRef();
  }

  for (int i = 0; i != argc; i++) {
      std::cout << "arg[" << i << "]: " << argv[i] << std::endl;
  }

  rdate(sysBootParams.hostName);

  comp_main(argc, argv);
}
#endif // !defined(__vxworks)
