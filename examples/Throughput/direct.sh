#!/bin/bash

DATATYPES="octet short long float double"

#------------------------------------------------------------
# direct mode
#------------------------------------------------------------
for d in $DATATYPES ; do
    cat <<EOF > tmp.conf
logger.enable: NO
corba.args: -ORBgiopMaxMsgSize 209715200
manager.components.preconnect: Throughput0.out:Throughput0.in(dataflow_type=push&interface_type=direct
manager.components.preactivation: Throughput0
example.Throughput.conf.default.maxsize: 100000000
example.Throughput.conf.default.datatype: ${d}
EOF
    ./ThroughputComp -f tmp.conf
done
rm -f tmp.conf
