#!/usr/bin/env python
# -*- python -*-
#
#  @file omniidl_be/doil/servant/main.py
#  @brief CORBA servant generator for doil backend
#  @date $Date$
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2008
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id$
# 

"""Produce CORBA servant classes"""

import string

# module from omniidl
from omniidl import idlast, idlvisitor

# module from omniidl_be/cxx
from omniidl_be.cxx import ast, id, types, output

# module from omniidl_be/doil
from omniidl_be.doil import util
from omniidl_be.doil.servant import template

import main

self = main

def __init__(config):
    self.config = config

def impl_fullname(name):
    bits = name.suffix("Servant").fullName()
    return string.join(bits, "_")

# Main code entrypoint
def run(tree):
    # first thing is to build the interface implementations
    bsi = BuildServantImplementations(self.config)
    tree.accept(bsi)


# Build the interface implementations
#
class BuildServantImplementations(idlvisitor.AstVisitor):

    def __init__(self, config):
        self.config = config
        # now configurations can be accessed by self.config["key"]

        # keep track of all interfaces for later use
        self.__allInterfaces = []

    # Returns the list of all present interfaces (each one will be
    # implemented)
    #    def allInterfaces(self):
    #        print "YYYYYYYYYYYYYYYYYYYY", self.__allInterfaces[:]
    #        return self.__allInterfaces[:]

    # Tree walking code
    def visitAST(self, node):
        for n in node.declarations():
            if ast.shouldGenerateCodeForDecl(n):
                n.accept(self)

    # modules can contain interfaces
    def visitModule(self, node):
        for n in node.definitions():
            n.accept(self)

    # interfaces cannot be further nested
    def visitInterface(self, node):
        self.__allInterfaces.append(node)
        # listed scope and interface name
        ifname_list = node.scopedName()

        dict = {}

        # servant class name
        # - servant_name
        idlif_name = ifname_list[-1]
        dict['servant_name'] = \
            self.config["ServantPrefix"] + \
            idlif_name + \
            self.config["ServantSuffix"]

        # servant namespace
        # - servant_ns
        # - servant_ns_end
        servant_ns_flat = ""
        dict['servant_ns'] = ""
        dict['servant_ns_end'] = ""
        for ns in self.config['ServantNs']:
            servant_ns_flat += ns + "_"
            dict['servant_ns'] += "\nnamespace " + ns + "\n{"
            dict['servant_ns_end'] += "}; // end of " + ns + "\n"

        # servant cpp/header
        # - servant_h
        # - servant_h_path
        # - servant_cpp
        # - include_guard
        dict['servant_h'] = dict['servant_name'] + ".h"
        dict['servant_h_path'] = \
            self.config['ServantDir'] + '/' + \
            dict['servant_h']
        dict['servant_cpp'] = dict['servant_name'] + ".cpp"
        dict['include_guard'] = \
            servant_ns_flat.upper() + \
            dict['servant_name'].upper() + "_H"

        # servant fullyquarified name
        # - corba_fq_name
        # - corba_poa_name
        scopedName = id.Name(node.scopedName())
        dict['corba_fq_name'] = scopedName.fullyQualify()
        dict['corba_poa_name'] = 'POA_' + dict['corba_fq_name']

        # interface class name
        # - iface_name
        dict['iface_name'] = \
            self.config["IfacePrefix"] + \
            idlif_name + \
            self.config["IfaceSuffix"]

        # interface namespace
        # - iface_ns
        # - iface_ns_end
        iface_ns_flat = ""
        dict['iface_ns'] = ""
        dict['iface_ns_end'] = ""
        for ns in self.config['IfaceNs']:
            iface_ns_flat += ns + "_"
            dict['iface_ns'] += "\nnamespace " + ns + "\n{"
            dict['iface_ns_end'] += "};\n"

        # interface header
        # - iface_h
        # - iface_h_path
        dict['iface_h'] = dict['iface_name'] + ".h"
        dict['iface_h_path'] = \
            self.config['IfaceDir'] + '/' + \
            dict['iface_h']

        # build methods corresponding to attributes, operations etc.
        # attributes[] and operations[] will contain lists of function
        # signatures eg
        #   [ char *echoString(const char *mesg) ]
        attributes = []
        operations = []
        virtual_operations = []

        # we need to consider all callables, including inherited ones
        # since this implementation class is not inheriting from anywhere
        # other than the IDL skeleton
        allInterfaces = [node] + ast.allInherits(node)
        allCallables = util.fold( map(lambda x:x.callables(), allInterfaces),
                                  [], lambda x, y: x + y )


        # declarations[] contains a list of in-class decl signatures
        # implementations[] contains a list of out of line impl signatures
        # (typically differ by classname::)
        declarations = []
        implementations = []

        for c in allCallables:
            if isinstance(c, idlast.Attribute):
                attrType = types.Type(c.attrType())
                d_attrType = attrType.deref()

                for i in c.identifiers():
                    attribname = id.mapID(i)
                    returnType = attrType.op(types.RET)
                    inType = attrType.op(types.IN)
                    attributes.append(returnType + " " + attribname + "()")
                    # need a set method if not a readonly attribute
                    if not c.readonly():
                        args = attribname + "(" + inType + ")"
                        declarations.append("void " + args)
                        implementations.append("void " + \
                                                   dict['servant_name'] + \
                                                   "::" + args)
                    declarations.append(returnType + " " + attribname + "()")
                    implementations.append(returnType + \
                                               " " + \
                                               dict['servant_name'] + \
                                               "::" + attribname + "()")
            elif isinstance(c, idlast.Operation):
                params = []
                for p in c.parameters():
                    paramType = types.Type(p.paramType())
                    cxx_type = paramType.op(types.direction(p), use_out = 0)
                    
                    argname = id.mapID(p.identifier())
                    params.append(cxx_type + " " + argname)

                # deal with possible "context"
                if c.contexts() != []:
                    params.append("CORBA::Context_ptr _ctxt")

                return_type = types.Type(c.returnType()).op(types.RET)

                opname = id.mapID(c.identifier())
                arguments = string.join(params, ", ")
                args = opname + "(" + arguments + ")"
                declarations.append(return_type + " " + args)
                implementations.append("  " + return_type + \
                                           "\n  " + \
                                           dict['servant_name'] +\
                                           "::" + args)
            else:
                util.fatalError("Internal error generating interface member")
                raise "No code for interface member: " + repr(c)

        # the class definition has no actual code...
        defs = string.join(map(lambda x:x + ";\n", declarations), "")
        # Output the _i class definition definition
        stream = output.Stream(output.createFile(dict['servant_h']), 2)
        dict['operations'] = defs
        stream.out(template.servant_def, dict)
        stream.close()
        # Output the implementations of the class methods
        impls = string.join(map(lambda x: x + """
  {

  }

""",
                                implementations), "")
               
        stream = output.Stream(output.createFile(dict['servant_cpp']), 2)
        dict['operations'] = impls
        stream.out(template.servant_code, dict)
