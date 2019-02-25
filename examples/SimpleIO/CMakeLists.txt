cmake_minimum_required (VERSION 3.0.2)


set(srcs ConsoleIn.cpp ConsoleIn.h)
ComponentBuild(ConsoleIn "${srcs}" ConsoleInComp.cpp "" "")


set(srcs ConsoleOut.cpp ConsoleOut.h)
ComponentBuild(ConsoleOut "${srcs}" ConsoleOutComp.cpp "" "")


install(FILES rtc.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
install(FILES consin.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
install(FILES consout.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
install(FILES component.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
