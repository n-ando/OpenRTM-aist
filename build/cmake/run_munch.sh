#!/bin/bash

NM=$1
TARGET_NAME=$2
#TCLSH=$3
MUNCH=$3
#NM_FLAG=$5
#TAGS=$6
OUTPUT=$4

#export WIND_BASE=/home/openrtm/vxworks-6.6-linux/vxworks-6.6
#export WIND_HOST_TYPE=x86-linux2
#/home/openrtm/vxworks-6.6-linux/gnu/4.1.2-vxworks-6.6/x86-linux2/bin/nmppc ConsoleIn_partialImage.o | /home/openrtm/vxworks-6.6-linux/vxworks-6.6/host/x86-linux2/bin/munch > ctdt.c

#echo "$NM $TARGET_NAME | $TCLSH $MUNCH -c $NM_FLAG -tags $TAGS > $OUTPUT"
#$NM $TARGET_NAME | tclsh $MUNCH > $OUTPUT
$NM $TARGET_NAME | $MUNCH > $OUTPUT
