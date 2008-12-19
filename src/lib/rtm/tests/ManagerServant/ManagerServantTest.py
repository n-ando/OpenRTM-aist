#!/usr/bin/env python

import sys
import omniORB.CORBA as CORBA
import CosNaming
import RTM
import RTC
import omniORB.any

import NSHelper


# NameServer
ns = NSHelper.NSHelper()
ns.Connect("192.168.100.1")
dict = ns.GetNSDict()


def flatten(nsdict, flatdict, curr_name):
    for k in nsdict.keys():
        name = curr_name + '/' + \
            nsdict[k][0]['id'] + '.' + \
            nsdict[k][0]['kind']
        if nsdict[k][1] == None:
            objref  = nsdict[k][0]['objref']
            flatdict[name] = objref
        else:
            tmptuple = nsdict[k][1:]
            for t in tmptuple:
                for k in t.keys():
                    d = t[k][0]
                    flatten(t, flatdict, name)
    
flatdict = {}
flatten(dict, flatdict, "")

#import yaml
#print yaml.dump(flatdict, default_flow_style=False)

# Manager
mgr = flatdict['/manager.mgr']

prop = mgr.get_profile().properties
print "# Manager Profile"
for p in prop:
    print p.name, ': ', omniORB.any.from_any(p.value)

loadedmod = mgr.get_loaded_modules()
print "# Loaded modules:"
for mp in loadedmod:
    for nv in mp.properties:
        print nv.name, ": ", omniORB.any.from_any(nv.value)

loadablemod = mgr.get_loadable_modules()
print "# Loadable modules:", loadablemod

conf = mgr.get_configuration()
print "# Manager's configuration"
for c in conf:
    print c.name, ': ', omniORB.any.from_any(c.value)

print "setting configuration"
mgr.set_configuration("naming.formats", "modified_naming_format.dummy_cxt/%n.rtc")
conf = mgr.get_configuration()
print "# Manager's configuration"
for c in conf:
    print c.name, ': ', omniORB.any.from_any(c.value)

print "# Components"
comps = mgr.get_components()
for c in comps:
    print "------------------------------"
    print "instance_name: ", c.get_component_profile().instance_name
    print "category:      ", c.get_component_profile().category

print "create component"
comp = mgr.create_component("ConsoleOut?naming.formats=context_given_from_outside.cxt/%n.rtc&instance_name=HOGEHOGEComponent")

print "# Created component"
print "instance_name: ", comp.get_component_profile().instance_name
print "category:      ", comp.get_component_profile().category

print "# Components"
comps = mgr.get_components()
for c in comps:
    print "------------------------------"
    print "instance_name: ", c.get_component_profile().instance_name
    print "category:      ", c.get_component_profile().category

prop = mgr.get_factory_profiles()
print "# Factory profiles"
for p in prop:
    for nv in p.properties:
        print nv.name, ': ', omniORB.any.from_any(nv.value)


#import time
#time.sleep(5)
print "# Delete component"
mgr.delete_component("ConsoleOut1")
    
print "# shutdown manager in 5 sec"
import time
time.sleep(5)
mgr.shutdown()

print "# Done"
