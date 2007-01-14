#!/bin/sh

nsport='9876'
hostname=`hostname`


../../utils/rtm-naming/rtm-naming $nsport

echo 'corba.nameservers: '$hostname':'$nsport > ./rtc.conf
echo 'naming_formats: %n.rtc' >> ./rtc.conf
echo 'logger.log_level: TRACE' >> ./rtc.conf

kterm -e ./ConsoleInComp -f ./rtc.conf &
kterm -e ./ConsoleOutComp -f ./rtc.conf &

sleep 5
./ConnectorComp -f ./rtc.conf &
sleep 10

nspid=`ps -ax | grep 9876 | awk '{print $1}'`

kill $nspid
echo 'Naming service was stopped.'
