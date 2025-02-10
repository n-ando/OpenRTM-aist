#!/usr/bin/env python3
# -*- Python -*-
# -*- coding: utf-8 -*-

#import sys
#sys.path = sys.path

from idl import *
import idl
import idl.ComponentObserver_idl
import SDOPackage
import OpenRTM__POA
from omniORB import CORBA, PortableServer, any
import omniORB
import sys
import uuid

def dict_to_nvlist(dict):
    '''Convert a dictionary into a CORBA namevalue list.'''
    result = []
    for item in list(dict.keys()):
        result.append(SDOPackage.NameValue(item, omniORB.any.to_any(dict[item])))
    return result

class RTCObserver(OpenRTM__POA.ComponentObserver):
    def __init__(self):
        pass
        
    def update_status(self, kind, hint):
        kind = str(kind)
        print "kind: " + kind + " hint: " + hint


orb = CORBA.ORB_init(sys.argv, CORBA.ORB_ID)
poa = orb.resolve_initial_references("RootPOA")
poa._get_the_POAManager().activate()

fd = open("comp.ior", "r")
ior = fd.readline()
fd.close()

print ior

obj = orb.string_to_object(ior)
sdo = obj._narrow(SDOPackage.SDO)
conf = sdo.get_configuration()

obs = RTCObserver()
uuid_val = uuid.uuid4().get_bytes()
intf_type = obs._this()._NP_RepositoryId
props = dict_to_nvlist({'heartbeat.enable': 'YES',
                        'heartbeat.interval': '1.0',
                        'port_profile.send_event.min_interval': '1.0',
                        'port_profile.receive_event.min_interval': '1.0',
                        'observed_status': 'ALL'})

sprof = SDOPackage.ServiceProfile(id=uuid_val,
                                  interface_type=intf_type,
                                  service=obs._this(),
                                  properties=props)
res = conf.add_service_profile(sprof)
try:
    orb.run()
except KeyboardInterrupt:
    conf.remove_service_profile(uuid_val)
print res
