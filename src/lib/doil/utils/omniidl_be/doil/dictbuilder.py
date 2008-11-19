#!/usr/bin/env python
# -*- coding: sjis -*-
# -*- python -*-
#
#  @file omniidl_be/doil/dictbuilder
#  @brief Dictionary Builder class for doil backend
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

"""Produce Dictionary from IDL AST"""

import string

# module from omniidl
from omniidl import idlast, idlvisitor, idltype

# module from omniidl_be/cxx
from omniidl_be.cxx import ast, id, types, output

# module from omniidl_be/doil
from omniidl_be.doil import util

import omniidl_be.doil.yat as yat

#import dictbuilder

#self = dictbuilder

def impl_fullname(name):
    bits = name.suffix("Servant").fullName()
    return string.join(bits, "_")

# Main code entrypoint
def run(tree, config):
    # first thing is to build the interface implementations
    bsi = BuildDictionaryFromAST(config)
    tree.accept(bsi)
    return bsi.get_dict()


# Build the interface implementations
#
class BuildDictionaryFromAST(idlvisitor.AstVisitor):
    def get_dict(self):
        return self.dict

    def __init__(self, config):
        self.dict = {}
        self.dict['interfaces'] = []
        self.config = config
        self.typemap = self.config['TypeMapping']
        # now configurations can be accessed by self.config["key"]

        # keep track of all interfaces for later use
        self.__allInterfaces = []
        self.tk_map = {
            idltype.tk_null               : "tk_null",
            idltype.tk_void               : "tk_void",
            idltype.tk_short              : "tk_short",
            idltype.tk_long               : "tk_long",
            idltype.tk_ushort             : "tk_ushort",
            idltype.tk_ulong              : "tk_ulong",
            idltype.tk_float              : "tk_float",
            idltype.tk_double             : "tk_double",
            idltype.tk_boolean            : "tk_boolean",
            idltype.tk_char               : "tk_char",
            idltype.tk_octet              : "tk_octet",
            idltype.tk_any                : "tk_any",
            idltype.tk_TypeCode           : "tk_TypeCode",
            idltype.tk_Principal          : "tk_Principal",
            idltype.tk_objref             : "tk_objref",
            idltype.tk_struct             : "tk_struct",
            idltype.tk_union              : "tk_union",
            idltype.tk_enum               : "tk_enum",
            idltype.tk_string             : "tk_string",
            idltype.tk_sequence           : "tk_sequence",
            idltype.tk_array              : "tk_array",
            idltype.tk_alias              : "tk_alias",
            idltype.tk_except             : "tk_except",
            idltype.tk_longlong           : "tk_longlong",
            idltype.tk_ulonglong          : "tk_ulonglong",
            idltype.tk_longdouble         : "tk_longdouble",
            idltype.tk_wchar              : "tk_wchar",
            idltype.tk_wstring            : "tk_wstring",
            idltype.tk_fixed              : "tk_fixed",
            idltype.tk_value              : "tk_value",
            idltype.tk_value_box          : "tk_value_box",
            idltype.tk_native             : "tk_native",
            idltype.tk_abstract_interface : "tk_abstract_interface",
            idltype.tk_local_interface    : "tk_local_interface"
            }
        self.corba_primitive = {
            "CORBA::Short"                : "short",
            "CORBA::UShort"               : "unsigned short",
            "CORBA::Long"                 : "long",
            "CORBA::ULong"                : "unsigned long",
            "CORBA::Float"                : "float",
            "CORBA::Double"               : "double",
            "CORBA::Char"                 : "char",
            "CORBA::Boolean"              : "bool"
            }
        self.corba_other = {
            "char*"                       : "std::string",
            "CORBA::Any"                  : "std::string"
            }
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

    def visitStruct(self, node):
        dict = {}
        #------------------------------------------------------------
        # struct name
        # - name: struct name
        # - fq_name_d: fully qualified struct name
        # - scoped_name:
        name = node.identifier()
        dict['name'] = id.mapID(name)
        dict['fq_name_d'] = id.Name(node.scopedName()).fullyQualify()
        dict['scoped_name'] = node.scopedName()

        # getting environment
        outer_environment = id.lookup(node)
        environment = outer_environment.enter(dict['name'])
        scope = environment.scope()

        #------------------------------------------------------------
        # members
        members = []
        for m in node.members():
            #------------------------------------------------------------
            # member
            # - type_d: type of a member
            # - decl_d: decralation list
            memberType = types.Type(m.memberType())
            memtype = memberType.member(environment)
            print "TYPE: ", memtype
            for d in m.declarators():
                mdict = {}
                # type_d
                mdict['type_d'] = id.mapID(memtype)
                # decl_d
                ident = d.identifier()
                cxx_id = id.mapID(ident)
                mdict['decl_d'] = cxx_id
                # dims_d
                decl_dims = d.sizes()

                print "decl_dims", decl_dims
                is_array_declarator = decl_dims != []

                # non-arrays of direct sequences are done via a typedef
                if not is_array_declarator and memberType.sequence():
                    pass
                else:
                    mdict['dims_d'] = decl_dims
                members.append(mdict)
        dict['members'] = members
        return


    # interfaces cannot be further nested
    def visitInterface(self, node):
        self.__allInterfaces.append(node)
        # listed scope and interface name
        dict = {}
        dict = self.createIface(node)

        # build methods corresponding to attributes, operations etc.
        # attributes[] and operations[] will contain lists of function
        # signatures eg
        #   [ char *echoString(const char *mesg) ]
        #        attributes = []
        #        operations = []
        #        virtual_operations = []
        # we need to consider all callables, including inherited ones
        # since this implementation class is not inheriting from anywhere
        # other than the IDL skeleton
        allInterfaces = [node] + ast.allInherits(node)
        allCallables = util.fold( map(lambda x:x.callables(), allInterfaces),
                                  [], lambda x, y: x + y )
        # declarations[] contains a list of in-class decl signatures
        # implementations[] contains a list of out of line impl signatures
        # (typically differ by classname::)
        #        declarations = []
        #        implementations = []

        dict['operations'] = []
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
                # operations
                op_dict           = self.createOperation(c)
                op_dict['return'] = self.createReturn(c)
                op_dict['args']   = self.createArgs(c)
                dict['operations'].append(op_dict)
            else:
                util.fatalError("Internal error generating interface member")
                raise "No code for interface member: " + repr(c)

        self.dict['interfaces'].append(dict)
        return

    # ------------------------------------------------------------
    # インターフェース全体に関する辞書を作成する
    #
    # servant_name: サーバントのクラス名
    # corba_fq_name: CORBAサーバントの完全修飾名
    # corba_poa_name: CORBAサーバントのPOAの完全修飾名
    # corba_skel_h: CORBAサーバントのヘッダ
    # servant_ns: サーバントのnamespaceのリスト
    # servant_h: サーバントのヘッダファイル名
    # servant_h_path: サーバントのヘッダのフルパス
    # servant_cpp: サーバントの実装ファイル名
    # servant_include_guard: インクルードガード
    # iface_name: インターフェース名
    # iface_ns: インターフェースのnamespaceのリスト
    # iface_h: インターフェースヘッダ名
    # iface_h_path: インターフェースのヘッダのフルパス
    # iface_cpp: インターフェースの実装ファイル名
    # iface_include_guard: インターフェースヘッダのインクルードガード
    #
    def createIface(self, node):
        dict = {}
        ifname_list = node.scopedName()

        #------------------------------------------------------------
        # corba header include
        dict['include_h'] = self.config["IncludeHeaders"]

        #------------------------------------------------------------
        # servant class name
        # - corna_iface
        # - servant_name
        sname = ifname_list[-1]
        dict['corba_iface'] = sname
        dict['servant_name'] = \
            self.config["ServantPrefix"] + sname + self.config["ServantSuffix"]

        # servant namespace
        # - servant_ns = []
        servant_ns_flat = ""
        dict['servant_ns'] = self.config['ServantNs']

        # servant cpp/header
        # - servant_h
        # - servant_cpp
        # - servant_h_path
        # - servant_include_guard
        dict['servant_h'] = dict['servant_name'] + ".h"
        dict['servant_cpp'] = dict['servant_name'] + ".cpp"
        if self.config['ServantDir'] == '':
            dict['servant_h_path'] = dict['servant_h']
        else:
            dict['servant_h_path'] = \
                self.config['ServantDir'] + '/' + dict['servant_h']
        servant_ns_flat = string.join(map(lambda x: x + '_',
                                          dict['servant_ns']), '')
        dict['servant_include_guard'] = \
            servant_ns_flat.upper() + dict['servant_name'].upper() + "_H"

        # servant fullyquarified name
        # - corba_fq_name
        # - corba_poa_name
        scopedName = id.Name(node.scopedName())
        dict['corba_fq_name'] = scopedName.fullyQualify()
        dict['corba_poa_name'] = 'POA_' + dict['corba_fq_name']

        #------------------------------------------------------------
        # adapter class name
        # - adapter_name
        dict['adapter_name'] = \
            self.config["AdapterPrefix"] + sname + self.config["AdapterSuffix"]

        # adapter namespace
        # - adapter_ns = []
        adapter_ns_flat = ""
        dict['adapter_ns'] = self.config['AdapterNs']

        # adapter cpp/header
        # - adapter_h
        # - adapter_cpp
        # - adapter_h_path
        # - adapter_include_guard
        dict['adapter_h'] = dict['adapter_name'] + ".h"
        dict['adapter_cpp'] = dict['adapter_name'] + ".cpp"
        if self.config['AdapterDir'] == '':
            dict['adapter_h_path'] = dict['adapter_h']
        else:
            dict['adapter_h_path'] = \
                self.config['AdapterDir'] + '/' + dict['adapter_h']
        adapter_ns_flat = string.join(map(lambda x: x + '_',
                                          dict['adapter_ns']), '')
        dict['adapter_include_guard'] = \
            adapter_ns_flat.upper() + dict['adapter_name'].upper() + "_H"

        #------------------------------------------------------------
        # interface class name
        # - iface_name
        dict['iface_name'] = \
            self.config["IfacePrefix"] + sname + self.config["IfaceSuffix"]

        # interface namespace
        # - iface_ns
        dict['iface_ns'] = self.config['IfaceNs']

        # interface header
        # - iface_h
        # - iface_cpp
        # - iface_h_path
        # - iface_include_guard
        dict['iface_h'] = dict['iface_name'] + ".h"
        dict['iface_cpp'] = dict['iface_name'] + ".cpp"
        if self.config['IfaceDir'] == '':
            dict['iface_h_path'] = dict['iface_h']
        else:
            dict['iface_h_path'] = \
                self.config['IfaceDir'] + '/' + dict['iface_h']
        iface_ns_flat = string.join(map(lambda x: x + '_',
                                        dict['iface_ns']), '')
        dict['iface_include_guard'] = \
            iface_ns_flat.upper() + dict['iface_name'].upper() + "_H"
        
        return dict

    # ------------------------------------------------------------
    # オペレーションに関する辞書を作成する
    #
    # name: オペレーションの名称
    #
    def createOperation(self, operation):
        dict = {}
        dict['name'] = id.mapID(operation.identifier())
        return dict

    # ------------------------------------------------------------
    # オペレーションの戻り値に関する辞書を作成する
    #
    # type_r: remote戻り値の型名
    # type_l: local戻り値の型名
    # var_r: remote戻り値の変数名
    # var_l: local戻り値の変数名
    # to_doil: to_remote変換関数
    # to_local: to_local変換関数
    #
    def createReturn(self, operation):
        cdict = {}
        ldict = {}

        retType = types.Type(operation.returnType())
        cdict['base_type'] = types.Type(operation.returnType()).base()
        cdict['ret_type'] = types.Type(operation.returnType()).op(types.RET)
        cdict['tk'] = self.tk_map[retType.kind()]
        ldict['tk'] = cdict['tk']
        local_ns   = string.join(self.config['IfaceNs'], '::')

        corba_type = cdict['base_type']
        if retType.typedef():
            retType = retType.deref()

        # primitive type
        if retType.is_basic_data_types():
            if self.typemap.has_key(corba_type):
                local_type = self.typemap[corba_type]
            elif self.corba_primitive.has_key(corba_type):
                local_type = self.corba_primitive[corba_type]
            else:
                local_type = local_ns + '::' + corba_type.split('::')[-1]
            ldict['base_type'] = local_type
            ldict['ret_type']  = local_type
            ldict['decl_type'] = local_type
        # Enum type
        elif retType.enum():
            if self.typemap.has_key(corba_type):
                local_type = self.typemap[corba_type]
            else:
                local_type = local_ns + '::' + corba_type.split('::')[-1]
            ldict['base_type'] = local_type
            ldict['ret_type']  = local_type
            ldict['decl_type'] = local_type
        # Struct type
        # Sequence type
        # Union type
        elif retType.struct() or retType.sequence() or retType.union():
            if self.typemap.has_key(corba_type):
                local_type = self.typemap[corba_type]
            else:
                local_type = local_ns + '::' + corba_type.split('::')[-1]
            ldict['base_type'] = local_type
            ldict['ret_type']  = local_type
            ldict['decl_type'] = local_type
        # Object type
        elif retType.objref():
            corba_type = corba_type.rstrip('_ptr')
            if self.typemap.has_key(corba_type):
                local_type = 'I' + self.typemap[corba_type]
            else:
                local_type = local_ns + '::I' + corba_type.split('::')[-1]
            ldict['base_type'] = local_type
            ldict['ret_type']  = local_type + '*'
            ldict['decl_type'] = local_type + '*'
        # String type
        # Any type
        elif retType.any() or retType.string():
            local_type = "std::string"
            ldict['base_type'] = local_type
            ldict['ret_type']  = local_type
            ldict['decl_type'] = local_type
        # void type
        elif retType.void():
            local_type = "void"
            ldict['base_type'] = local_type
            ldict['ret_type']  = local_type
            ldict['decl_type'] = local_type
        else:
            print "UNKNOWN TYPE"
            print retType.typedef()
            print retType.deref().sequence()
        return {'corba': cdict, 'local': ldict}
        

    # ------------------------------------------------------------
    # オペレーションの引数に関する辞書を作成する
    #
    # type_r: remoteの引数の型
    # type_l: localの引数の型
    # var_r: remoteの変数名
    # var_l: localの変数名
    # to_doil: to_remote変換関数
    # to_local: to_local変換関数
    #
    def createArgs(self, operation):
        args = []
        direction = ['in', 'out', 'inout','return']
        for arg in operation.parameters():
            # corba args information
            cdict = {}
            paramType = types.Type(arg.paramType())
            cdict['base_type'] = paramType.base()
            cdict['arg_type']  = paramType.op(types.direction(arg), use_out = 0)
            cdict['arg_name']  = id.mapID(arg.identifier())
            cdict['var_name']  = '_' + cdict['arg_name']
            cdict['direction'] = direction[arg.direction()]
            cdict['tk']        = self.tk_map[paramType.kind()]
            
            # local args information
            ldict = {}
            ldict['arg_name'] = cdict['arg_name']
            ldict['var_name'] = cdict['var_name']
            ldict['direction'] = cdict['direction']
            ldict['tk']        = cdict['tk']
            corba_type = cdict['base_type']
            direc = cdict['direction']
            tk = cdict['tk']
            local_ns = string.join(self.config['IfaceNs'], '::')

            if paramType.typedef():
                paramType = paramType.deref()
            # primitive type
            if paramType.is_basic_data_types():
                if self.typemap.has_key(corba_type):
                    local_type = self.typemap[corba_type]
                elif self.corba_primitive.has_key(corba_type):
                    local_type = self.corba_primitive[corba_type]
                else:
                    local_type = local_ns + '::' + corba_type.split('::')[-1]
                ldict['base_type'] = local_type
                if direc == 'in':
                    ldict['arg_type'] = local_type
                elif direc == 'out' or direc == 'inout':
                    ldict['arg_type'] = local_type + '&'
                ldict['decl_type'] = local_type
                cdict['decl_type'] = corba_type
            # Enum type
            elif paramType.enum():
                if self.typemap.has_key(corba_type):
                    local_type = self.typemap[corba_type]
                else:
                    local_type = local_ns + '::' + corba_type.split('::')[-1]
                ldict['base_type'] = local_type
                if direc == 'in':
                    ldict['arg_type'] = local_type
                elif direc == 'out' or direc == 'inout':
                    ldict['arg_type'] = local_type + '&'
                ldict['decl_type'] = local_type
                cdict['decl_type'] = corba_type
            # Struct type
            # Sequence type
            # Union type           
            elif paramType.struct() or paramType.sequence() \
                    or paramType.union():
                if self.typemap.has_key(corba_type):
                    local_type = self.typemap[corba_type]
                else:
                    local_type = local_ns + '::' + corba_type.split('::')[-1]

                ldict['base_type'] = local_type
                if direc == 'in':
                    ldict['arg_type'] = 'const ' + local_type + '*'
                elif direc == 'out' or direc == 'inout':
                    ldict['arg_type'] = local_type + '*'
                ldict['decl_type'] = local_type
                cdict['decl_type'] = corba_type + '*'
            # Object type
            elif paramType.objref():
                corba_type = corba_type.rstrip('_ptr')
                if self.typemap.has_key(corba_type):
                    local_type = 'I' + self.typemap[corba_type]
                else:
                    local_type = local_ns + '::I' + corba_type.split('::')[-1]
                ldict['base_type'] = local_type
                if direc == 'in':
                    ldict['arg_type'] = 'const ' + local_type + '*'
                elif direc == 'out' or direc == 'inout':
                    ldict['arg_type'] = local_type + '*'
                ldict['decl_type'] = local_type + '*'
                cdict['decl_type'] = corba_type
            # String type
            # Any type
            elif paramType.any() or paramType.string():
                local_type = "std::string"
                ldict['base_type'] = local_type
                if direc == 'in':
                    ldict['arg_type'] = 'const ' + local_type + '&'
                elif direc == 'out' or direc == 'inout':
                    ldict['arg_type'] = local_type + '&'
                ldict['decl_type'] = local_type
                cdict['decl_type'] = corba_type
            else:
                print "UNKNOWN TYPE"
                print paramType.typedef()
                print paramType.deref().sequence()
            args.append({'corba': cdict, 'local': ldict})
        return args

