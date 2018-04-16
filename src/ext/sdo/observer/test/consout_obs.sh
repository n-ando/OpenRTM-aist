#!/bin/sh
rm -f *.log
rm -f comp.ior

(sleep 1 ; ln -s ConsoleOut0.rtc comp.ior ; sleep 1 ; echo "Run ./observer.py in another terminal")&
../../../../../examples/SimpleIO/ConsoleInComp -f ./rtc.conf 



