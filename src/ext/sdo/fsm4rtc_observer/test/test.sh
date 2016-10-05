#!/bin/sh
rm *.log
../../../../../examples/SimpleIO/ConsoleInComp -o "logger.log_level:DEBUG" -o "manager.local_service.modules:../.libs/ComponentObserverConsumer.so(ComponentObserverConsumerInit)"

