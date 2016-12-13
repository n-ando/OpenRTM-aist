#!/bin/sh

nsport='9876'
hostname=`hostname`


../../utils/rtcNaming/rtcNaming $nsport

echo 'NameServer '$hostname':'$nsport > ./rtc.conf

kterm -e ./TkMotor.py &
kterm -e ./SliderComp.py &

sleep 10
kterm -e ./ConnectorComp.py &
sleep 10

nspid=`ps -ax | grep Name | grep 9876 | awk '{print $1}'`

kill $nspid
echo 'Naming service is stopped.'