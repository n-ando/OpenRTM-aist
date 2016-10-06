#!/bin/sh
rm -f *.log
../../../../../examples/SimpleIO/ConsoleInComp -o "logger.log_level:DEBUG" -o "manager.local_service.modules:../.libs/ExtendedFsmServiceProvider.so(ExtendedFsmServiceProviderInit)"

