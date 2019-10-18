cmake_minimum_required (VERSION 3.5.1)


set(srcs ConsoleIn.cpp ConsoleIn.h)
examples_build(ConsoleIn SRCS "${srcs}" MAIN ConsoleInComp.cpp)


set(srcs ConsoleOut.cpp ConsoleOut.h)
examples_build(ConsoleOut SRCS "${srcs}" MAIN ConsoleOutComp.cpp)


install(FILES rtc.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
install(FILES consin.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
install(FILES consout.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
install(FILES component.conf DESTINATION ${INSTALL_RTM_EXAMPLE_DIR} COMPONENT examples)
