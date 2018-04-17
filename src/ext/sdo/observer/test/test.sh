#!/bin/sh
rm -f *.log
rm -f comp.ior

../../../../../examples/SimpleIO/ConsoleInComp -f ./rtc.conf
#comp=`ls *ConsoleOut0.rtc`
#ln -s $comp comp.ior
#../../../../../examples/SimpleIO/ConsoleInComp -f ./rtc.conf



