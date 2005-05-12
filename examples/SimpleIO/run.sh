#!/bin/sh

nsport='9876'
hostname=`hostname`


../../utils/rtm-naming/rtm-naming $nsport

echo 'NameServer '$hostname':'$nsport > ./rtc.conf

kterm -e ./ConsoleInComp -f ./rtc.conf &
kterm -e ./ConsoleOutComp -f ./rtc.conf &

sleep 5
kterm -e ./ConnectorComp -f ./rtc.conf &
sleep 10

nspid=`ps -ax | grep 9876 | awk '{print $1}'`

kill $nspid
echo 'Naming service is stopped.'
