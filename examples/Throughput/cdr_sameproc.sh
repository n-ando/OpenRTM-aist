#!/bin/bash

DATATYPES="octet short long float double"

#------------------------------------------------------------
# corba_cdr with two component with same proc
#------------------------------------------------------------
for d in $DATATYPES ; do
    cat <<EOF > tmp.conf
logger.enable: NO
corba.args: -ORBgiopMaxMsgSize 209715200
manager.components.precreate: Throughput
manager.components.preconnect: Throughput0.out:Throughput1.in(dataflow_type=push&interface_type=corba_cdr
manager.components.preactivation: Throughput0, Throughput1
example.Throughput.conf.default.maxsize: 100000000
example.Throughput.conf.default.datatype: ${d}
example.Throughput.conf.default.filesuffix: -sameproc

EOF
    ./ThroughputComp -f tmp.conf
done
rm -f tmp.conf

