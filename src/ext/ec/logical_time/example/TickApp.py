#!/usr/bin/env python

import Tkinter as Tk

class SendTick:
    def __init__(self):
        pass

def hoge():
    print "hoge"
    
class Frame(Tk.Frame):
    def __init__(self, master = None):
        self.lttsample = LTTSample()
        self.time = 0.0
#        self.protocol("WM_DELETE_WINDOW", self.closeEvent)
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
        import os
        os.system("killall LTTSampleComp")
        os.system("killall lt-LTTSampleComp")

import CORBA

class LTTSample:
    def __init__(self):
        self.orb = CORBA.ORB_init()
        try:
            self.ior = open("LTTSample0.rtc").read()
        except:
            print "LTTSample0.rtc not found"
            import os
            import time
            print "Launching LTTSampleComp..."
            os.system("./LTTSampleComp&")
            time.sleep(1.0)
            self.ior = open("LTTSample0.rtc").read()
        obj = self.orb.string_to_object(self.ior)
        if CORBA.is_nil(obj):
            print "Object in LTTSample0.rtc is nil. Restarting LTTSampleComp..."
            os.system("./LTTSampleComp&")
            self.ior = open("LTTSample0.rtc").read()
            obj = self.orb.string_to_object(self.ior)
            if CORBA.is_nil(obj):
                print "Object reference is nil"
                sys.exit(1)

        import omniORB
        import sys

        self.sdo_idl = omniORB.importIDL("idl/SDOPackage.idl")
        self.rtc_idl = omniORB.importIDL("idl/RTC.idl", ["-Iidl"])
        self.ltt_idl = omniORB.importIDL("idl/LogicalTimeTriggeredEC.idl", ["-Iidl"])

        RTC = sys.modules["RTC"]
        OpenRTM = sys.modules["OpenRTM"]
        try:
            self.rtobj = obj._narrow(RTC.RTObject)
        except:
            print "Narrowing failed. Restarting LTTSampleComp..."
            import os
            import time
            print "Launching LTTSampleComp..."
            os.system("./LTTSampleComp&")
            time.sleep(1.0)
            obj = self.orb.string_to_object(open("LTTSample0.rtc").read())
            self.rtobj = obj._narrow(RTC.RTObject)

        cxts = self.rtobj.get_owned_contexts()
        self.lttcxt = cxts[0]._narrow(OpenRTM.LogicalTimeTriggeredEC)
        profile = self.lttcxt.get_profile()
        print profile

    def tick(self, ticktime):
        sec = int(ticktime)
        usec = int((ticktime - sec) * 1000000)
        self.lttcxt.tick(sec, usec)

    def gettime(self):
        return self.lttcxt.gettime()

    def shutdown(self):
        self.rtobj.exit()


if __name__ == '__main__':
#    root = Tk.Tk()
#    root.protocol("WM_DELETE_WINDOW", on_close(root))
    f = Frame()
    f.pack()
    f.mainloop()
    f.onClose()


