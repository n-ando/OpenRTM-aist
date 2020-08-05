#!/usr/bin/env python3
# -*- coding: utf-8 -*- 
##
# @file TickApp.py
# @brief Example application for LogicalTimeTriggeredEC
# @date$
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# Copyright (C) 2012
#     Noriaki Ando
#     Intelligent Systems Research Institute,
#     National Institute of
#         Advanced Industrial Science and Technology (AIST), Japan
#     All rights reserved.
#
# Usage:
# $ python TickApp.py
#
# This python script
# - Launches LTTSampleComp component,
# - Gets its object reference from LTTSample.rtc file in the current directory,
# - Obtains EC from RTC
# - When tick button is pushed, tick() operation of the EC is called
# - And then call gettime() operation of the EC is called
# - print current time
# - When X button is pushed, tryp to terminate LTTSampleComp
# - And kill all the process LTTSampleComp (and lt-LTTSampleComp)
#
# Requirement:
# - LogicalTimeTriggeredEC.so as EC
# - FileNameservice.so as local service
# - SDOPackage.idl, RTC.idl and LogicalTimeTriggeredEC.idl in idl dir
#
# See details in rtc.conf
#

import os
import Tkinter as Tk

class Frame(Tk.Frame):
    def __init__(self, master = None):
        self.lttsample = LTTSample()
        self.time = 0.0
        Tk.Frame.__init__(self, master)
        self.master.title('Tick Application')

        #------------------------------
        self.frame0 = Tk.LabelFrame(self, width = 18)
        self.text_lavel00 = Tk.Label(self.frame0,
                                     text = "Tick time: ",
                                     width = 12)
        self.text_lavel00.pack(side = Tk.LEFT,  fill=Tk.X, pady = 5)
        self.text_sec = Tk.Entry(self.frame0, width = 12,
                                 justify = Tk.RIGHT)
        self.text_sec.delete(0, Tk.END)
        self.text_sec.insert(0, "0.000")
        self.text_sec.pack(side = Tk.LEFT, fill=Tk.X)
        self.text_lavel01 = Tk.Label(self.frame0, text = "[s]",
                                     width = 5)
        self.text_lavel01.pack(side = Tk.RIGHT, fill=Tk.X, anchor=Tk.E)

        #------------------------------
        self.checkvar = Tk.IntVar()
        self.checkbox = Tk.Checkbutton(self,
                                       text = "auto increment",
                                       variable = self.checkvar,
                                       command = self.toggleAutoinc)
        self.checkvar.set(1)

        #------------------------------
        self.frame1 = Tk.LabelFrame(self, width = 18,
                                    labelwidget = self.checkbox)
        self.text_lavel1 = Tk.Label(self.frame1,
                                    text = "Step: ",
                                    width = 12)
        self.text_lavel1.pack(side = Tk.LEFT,  fill=Tk.X, pady = 5)
        self.stepspin = Tk.Spinbox(self.frame1,
                                   from_ = 0, to = 999, increment = 0.001,
                                   width = 11, justify = Tk.RIGHT,
                                   format = "%03.3f")
        self.stepspin.delete(0, Tk.END)
        self.stepspin.insert(0, "1.000")
        self.stepspin.pack(side = Tk.LEFT, fill=Tk.X, anchor=Tk.E)
        self.text_lavel11 = Tk.Label(self.frame1, text = "[s]",
                                     width = 5)
        self.text_lavel11.pack(side = Tk.LEFT, fill=Tk.X, anchor=Tk.E)

        #------------------------------
        self.frame2 = Tk.Frame(self, width = 18)
        self.button = Tk.Button(self.frame2, text = "tick",
                                width = 8, command = self.tick)
        self.button.pack(side = Tk.LEFT, pady = 5)

        self.frame0.pack(side = Tk.TOP, fill=Tk.X,
                         padx = 5, pady = 5,
                         ipadx = 5, ipady = 5)
        self.frame1.pack(side = Tk.TOP, fill=Tk.X,
                         padx = 5, pady = 5,
                         ipadx = 5, ipady = 5)
        self.frame2.pack(side = Tk.TOP,
                         padx = 5, pady = 5,
                         ipadx = 5, ipady = 5)

    def toggleAutoinc(self):
        if self.checkvar.get() == 1:
            self.stepspin.configure(state = 'normal')
        else:
            self.stepspin.configure(state = 'disabled')

    def tick(self):
        if self.checkvar.get() == 1:
            self.time = self.time + float(self.stepspin.get())
            self.text_sec.delete(0, Tk.END)
            text = "%03.3f" % self.time
            self.text_sec.insert(0, text)
        self.lttsample.tick(float(self.text_sec.get()))

    def onClose(self):
        self.lttsample.shutdown()
        import time
        time.sleep(1.0)
        if os.sep == '\\':
            os.popen("TaskKill /im LTTSampleComp.exe")
        else:
            os.popen("killall -q LTTSampleComp")
            os.popen("killall -q lt-LTTSampleComp")

import CORBA

class LTTSample:
    def __init__(self):
        self.orb = CORBA.ORB_init()
        try:
            self.ior = open("LTTSample0.rtc").read()
        except:
            print "LTTSample0.rtc not found"
            import time, sys
            write = sys.stdout.write
            write("Launching LTTSampleComp...")
            sys.stdout.flush()
            if os.sep == '\\':
                os.system("start LTTSampleComp.exe")
            else:
                os.system("./LTTSampleComp&")
            while True:
                try:
                    self.ior = open("LTTSample0.rtc").read()
                    break;
                except:
                    write(".")
                    sys.stdout.flush()
                    time.sleep(0.01)
                    pass
            print "done"
        obj = self.orb.string_to_object(self.ior)
        if CORBA.is_nil(obj):
            print "Object in LTTSample0.rtc is nil. Restarting LTTSampleComp..."
            if os.sep == '\\':
                os.system("start LTTSampleComp.exe")
            else:
                os.system("./LTTSampleComp&")
            self.ior = open("LTTSample0.rtc").read()
            obj = self.orb.string_to_object(self.ior)
            if CORBA.is_nil(obj):
                print "Object reference is nil"
                sys.exit(1)

        import omniORB
        import sys

        if os.sep == '\\':
            os.system("omniidl -I. -bpython SDOPackage.idl RTC.idl LogicalTimeTriggeredEC.idl")
            import RTC
            import OpenRTM
        else:
            self.sdo_idl = omniORB.importIDL("idl/SDOPackage.idl")
            self.rtc_idl = omniORB.importIDL("idl/RTC.idl", ["-Iidl"])
            self.ltt_idl = omniORB.importIDL("idl/LogicalTimeTriggeredEC.idl",
                                         ["-Iidl"])
            RTC = sys.modules["RTC"]
            OpenRTM = sys.modules["OpenRTM"]
        try:
            self.rtobj = obj._narrow(RTC.RTObject)
        except:
            print "Narrowing failed. Restarting LTTSampleComp..."
            import time
            print "Launching LTTSampleComp..."
            if os.sep == '\\':
                os.system("start LTTSampleComp.exe")
            else:
                os.system("./LTTSampleComp&")
            time.sleep(1.0)
            obj = self.orb.string_to_object(open("LTTSample0.rtc").read())
            self.rtobj = obj._narrow(RTC.RTObject)

        cxts = self.rtobj.get_owned_contexts()
        self.lttcxt = cxts[0]._narrow(OpenRTM.LogicalTimeTriggeredEC)
        profile = self.lttcxt.get_profile()
        p = {}
        p["kind"] = profile.kind
        p["rate"] = profile.rate
        p["owner"] = profile.owner
        from omniORB import any
        for prop in profile.properties:
            p[prop.name] = any.from_any(prop.value)
        print "ExecutionContext:"
        print "      type:", p.pop("type")
        print "      name:", p.pop("name")
        print "      kind:", p.pop("kind")
        print "      rate:", p.pop("rate")
        print "     owner:", p.pop("owner")
        print "properties:", p

    def tick(self, ticktime):
        sec = int(ticktime)
        usec = int((ticktime - sec) * 1000000)
        self.lttcxt.tick(sec, usec)

    def gettime(self):
        return self.lttcxt.gettime()

    def shutdown(self):
        self.rtobj.exit()
        import time, sys
        write = sys.stdout.write
        write("Waiting RTC termination.")
        try:
            while True:
                self.rtobj._non_existent()
                write(".")
                sys.stdout.flush()
                time.sleep(0.01)
        except:
            pass
        print "done"

if __name__ == '__main__':
    f = Frame()
    f.pack()
    f.mainloop()
    f.onClose()


