#!/usr/bin/env python

from Tkinter import *
from tkFont import *
import tkMessageBox, os.path, string
import tkSimpleDialog
import tkCommonDialog
import time
import re
import thread
import sys

default_searchdir="C:\\Program Files"

property_sheet=os.path.dirname(sys.argv[0]) + "\\OpenRTM-aist.vsprops"

widlist = ["ace_root", "ace_inc", "ace_lib",
           "omni_root", "omni_bin", "omni_inc", "omni_lib"]

jwin_title = "OpenRTM-aist-win32 ビルド環境設定"
win_title  = "OpenRTM-aist-win32 Build Environment Setting"

jexplain = """OpenRTM-aistをビルドするために必要な環境を設定します。下記の項目に必要な情報を入力して、プロパティシート生成ボタンを押してください。"""

explain = """Setting up OpenRTM-aist build environment. Please input information to the following forms, and push Generate button to generate property sheet"""

jsearch_expln = """自動的に検索することもできます。検索するディレクトリを入力して「検索」ボタンを押してください。
検索には数分かかることがあります。"""
search_expln = """Automatic search. Input search directory and push [Search] button. 
It may take a few minutes."""

jsearch_dir = "検索ディレクトリ"
search_dir = "Search Directory"

jsbutton="検索"
sbutton="Search"

jdirname_error="ディレクトリが見つかりません。"
dirname_error="DIrectory not found."


entries = {
    "ace_root" : \
        {"label": "ACE directory",
         "expln": "The ACE_wrapper directory a.k.a ACE_ROOT directory."},
    "ace_inc"  : \
        {"label": "ACE include directory",
         "expln": "The directory in which ace/ACE.h exists."},
    "ace_lib"  : \
        {"label": "ACE lib directory",
         "expln": "The directory in which ACE.LIB exists."},
    "omni_root": \
        {"label": "omniORB directory",
         "expln": "The omniORB directory in which bin, include, lib dirs exist."},
    "omni_bin" : \
        {"label": "omniORB bin directory",
         "expln": "The directory in which omniidl exists."},
    "omni_inc" : \
        {"label": "omniORB include directory",
         "expln": "The directory in which omniORB4/CORBA.h exists"},
    "omni_lib" : \
        {"label": "omniORB lib directory",
         "expln": "The directory in wihch omniORB407_rt.lib exists."}
    }

jentries = {
    "ace_root" : \
        {"label": "ACEディレクトリ",
         "expln": "通常はACE_wrapperディレクトリの位置を指定してください。"},
    "ace_inc"  : \
        {"label": "ACE include ディレクトリ",
         "expln": "ace/ACE.hがあるディレクトリを指定してください。"},
    "ace_lib"  : \
        {"label": "ACE lib ディレクトリ",
         "expln": "ACE.LIBがある場所を指定してください。"},
    "omni_root": \
        {"label": "omniORBディレクトリ",
         "expln": "omniORBのディレクトリ(下にbin, include, libがある)を指定してください。"},
    "omni_bin" : \
        {"label": "omniORB bin ディレクトリ",
         "expln": "omniidlがあるディレクトリを指定してください。"},
    "omni_inc" : \
        {"label": "omniORB include ディレクトリ",
         "expln": "omniORB4/CORBA.hがあるディレクトリを指定してください。"},
    "omni_lib" : \
        {"label": "omniORB lib ディレクトリ",
         "expln": "omniORB407_rt.libなどがあるディレクトリを指定してください。"}
    }


jgbutton="生成"
gbutton="Generate"

jgen_label="プロパティシート:"
gen_label="Property Sheet:"

jgen_expln = """OpenRTM-aistソースディレクトリの下にOpenRTM-aist.vspropsというファイル名でプロパティシートを生成する必要があります。ACEやomniORBの各種パスおよびプロパティシートのディレクトリが正しければ生成ボタンを押してください。"""

gen_expln = """Property sheet named OpenRTM-aist.vsprops should exist under OpenRTM-aist source directory. Please confirm directories of ACE, omniORB and property sheet and push Generate button."""

prop_sheet = """<?xml version="1.0" encoding="shift_jis"?>
<VisualStudioPropertySheet
	ProjectType="Visual C++"
	Version="8.00"
	Name="OpenRTM-aist-0.4"
	>
	<Tool
		Name="VCCLCompilerTool"
		AdditionalIncludeDirectories="&quot;$(SolutionDir)&quot;;&quot;$(SolutionDir)\\rtm\idl&quot;;&quot;$(ace_include)&quot;;&quot;$(omni_include)&quot;;.;..\..;..;..\..\.."
	/>
	<Tool
		Name="VCLinkerTool"
		AdditionalLibraryDirectories="&quot;$(SolutionDir)\\bin&quot;;&quot;$(ace_libdir)&quot;;&quot;$(omni_libdir)&quot;"
	/>
	<UserMacro
		Name="ace_root"
		Value="%s"
	/>
	<UserMacro
		Name="omni_root"
		Value="%s"
	/>
	<UserMacro
		Name="rtm_root"
		Value="$(SolutionDir)"
	/>
	<UserMacro
		Name="ace_include"
		Value="%s"
	/>
	<UserMacro
		Name="ace_libdir"
		Value="%s"
	/>
	<UserMacro
		Name="omni_include"
		Value="%s"
	/>
	<UserMacro
		Name="omni_libdir"
		Value="%s"
	/>
	<UserMacro
		Name="omni_bin"
		Value="%s"
	/>
	<UserMacro
		Name="rtm_includes"
		Value="$(SolutionDir);$(SolutionDir)\\rtm\idl;$(ace_include);$(omni_include);.;..\..\\"
	/>
	<UserMacro
		Name="rtm_libdir"
		Value="$(SolutionDir)\\bin;$(ace_libdir);$(omni_libdir);."
	/>
	<UserMacro
		Name="rtm_path"
		Value="$(SolutionDir)\\bin;$(SolutionDir)\\build;&quot;$(omni_bin)&quot;"
	/>
</VisualStudioPropertySheet>
"""

jisdir_error = "同名のディレクトリが存在します。 "
isdir_error = "The Directory of a same name exists. "

jfile_exists = "ファイルが存在します。上書きしますか？ "
file_exists = "The file already exists. Overwrite? "

jfile_gened = "ファイルを生成しました。"
file_gened = "File generated."


def search(path, fnames, results):
    try:
        flist = os.listdir(path)
    except:
        return

    mp = []
    for fn in fnames:
        mp.append(re.compile(fn))

    for f in flist:
        fullpath = path + "/" + f
        if os.path.isfile(fullpath):
#            for fname in fnames:
#                if f == fname:
#                    results[fname] = fullpath
            i = 0
            for m in mp:
                if m.match(f):
                    results[fnames[i]] = fullpath
                i += 1
        elif os.path.isdir(fullpath):
            res = search(fullpath, fnames, results)
    return


def j(str, encoding="cp932"):
  return unicode(str, encoding).encode("utf8")



class App(Frame):
    def init(self):
        self.setlang()
        self.width=512
        
        self.f8  = Font(weight=NORMAL, family="", size=8) 
        self.f9  = Font(weight=NORMAL, family="", size=9) 
        self.f10 = Font(weight=NORMAL, family="", size=10) 
        self.f11 = Font(weight=NORMAL, family="", size=11) 

        self.master.title(self.win_title)
        
        f = Frame()

        # 説明
        self.expw = Label(f, text=self.explain, font=self.f11, \
                              justify=LEFT, wraplength=self.width)
        self.expw.pack(side=TOP, anchor=W, padx=3, pady=3)

        self.search_frame(f)
        self.entries_frame(f)
        self.gen_frame(f)
        f.pack(side=TOP, anchor=E, pady=5)

    def setlang(self):
        if time.tzname[0].find("東京") or time.tzname[0].find("JST"):
            self.ent = jentries
            self.win_title = j(jwin_title)
            self.explain = j(jexplain)
            self.search_expln = j(jsearch_expln)
            self.search_dir = j(jsearch_dir)
            self.search_button = j(jsbutton)
            self.gen_button = j(jgbutton)
            self.dirname_error=j(jdirname_error)
            self.gen_label = j(jgen_label)
            self.gen_expln = j(jgen_expln)
            self.isdir_error = j(jisdir_error)
            self.file_exists = j(jfile_exists)
            self.file_gened = j(jfile_gened)
        else:
            self.ent = entries
            self.win_title = win_title
            self.explain = explain
            self.search_expln = search_expln
            self.search_dir = search_dir
            self.search_button = sbutton
            self.gen_button = gbutton
            self.dirname_error=dirname_error
            self.gen_label = gen_label
            self.gen_expln = gen_expln
            self.isdir_error = isdir_error
            self.file_exists = file_exists
            self.file_gened = file_gened

    def search_frame(self, f):
        frame = Frame(f, relief=Tkinter.GROOVE, bd=2)
        dummyw = Frame(frame, width=self.width)
        dummyw.pack(side=TOP)
        frame.pack(side=TOP)
        # 自動検索の説明
        self.search_explnw = Label(frame, text=self.search_expln, \
                                       wraplength=self.width, justify=LEFT,\
                                       font=self.f11)
        self.search_explnw.pack(side=TOP, anchor=W, padx=0)

        f1 = Frame(frame, width=self.width)
        f1.pack(side=TOP)

        self.search_labelw = Label(f1, text=self.search_dir, font=self.f11)
        self.search_labelw.pack(side=LEFT, anchor=W)
        self.search_dirw   = Entry(f1, width=40, font=self.f11)
        self.search_dirw.delete(0)
        self.search_dirw.insert(0, default_searchdir)
        self.search_dirw.pack(side=LEFT, anchor=W, padx=5, pady=5)
        self.search_button = Button(f1, text=self.search_button,
                                    command=self.search, font=self.f10)
        self.search_button.pack(side=LEFT, anchor=W, padx=10, pady=5)
        f1.pack(side=TOP, anchor=W)

    def entries_frame(self, f):
        frame = Frame(f, relief=GROOVE, bd=2)
        dummyw = Frame(frame, width=self.width)
        dummyw.pack(side=TOP)
        frame.pack(side=TOP)
        for w in widlist:
            self.ent[w]["wid"] = Label(frame, text=j(self.ent[w]["label"]), \
                                         font=self.f11, wraplength='10c')
            self.ent[w]["wid"].pack(side=TOP, anchor=W, padx=10)
            self.ent[w]["wid"] = Label(frame, text=j(self.ent[w]["expln"]), \
                                         font=self.f9, wraplength='10c')
            self.ent[w]["wid"].pack(side=TOP, anchor=W, padx=10)
            self.ent[w]["wid"] = Entry(frame, width=80, font=self.f9)
            self.ent[w]["wid"].pack(side=TOP, anchor=NW, padx=10, pady=5)

    def gen_frame(self, f):
        frame = Frame(f, relief=Tkinter.GROOVE, bd=2)
        dummyw = Frame(frame, width=self.width)
        dummyw.pack(side=TOP)
        frame.pack(side=TOP)

        self.gen_expw = Label(frame, text=self.gen_expln, \
                                       wraplength=self.width, justify=LEFT,\
                                       font=self.f11)
        self.gen_expw.pack(side=TOP, anchor=W, padx=0)

        f1 = Frame(frame)
        self.gen_labelw = Label(f1, text=self.gen_label, font=self.f11)
        self.gen_labelw.pack(side=LEFT, anchor=W, padx=3, pady=3)
        self.gen_entryw = Entry(f1, width=40, \
                                    text="OpenRTM-aist.vsprops", font=self.f11)
        self.gen_entryw.insert(0, property_sheet)
        self.gen_entryw.pack(side=LEFT, anchor=W, padx=5, pady=5)
        self.gbuttonw = Button(f1, text=self.gen_button, font=self.f10,
                               command=self.generate)
        self.gbuttonw.pack(side=LEFT, anchor=W, padx=3, pady=3)
        f1.pack(side=TOP, anchor=W)


    def quit(self):
        self.master.destroy()

    def generate(self):
        ace_inc = self.ent["ace_inc"]["wid"].get()
        ace_lib = self.ent["ace_lib"]["wid"].get()
        ace_dirs = [ace_inc, ace_lib]

        omni_bin = self.ent["omni_bin"]["wid"].get()
        omni_inc = self.ent["omni_inc"]["wid"].get()
        omni_lib = self.ent["omni_lib"]["wid"].get()
        omni_dirs = [omni_bin, omni_inc, omni_lib]
            
        ace_root, ace_paths   = self.common_path(ace_dirs)
        omni_root, omni_paths = self.common_path(omni_dirs)

        print ace_paths
        print ace_root
        print ace_inc
        if ace_paths[0] == "/" and ace_paths[1] == "/lib/":
            ace_inc = "$(ace_root)"
            ace_lib = "$(ace_root)/lib"

        if omni_paths[0] == "/bin/x86_win32/" and \
           omni_paths[1] == "/include/"       and \
           omni_paths[2] == "/lib/x86_win32/"     :
            omni_bin = "$(omni_root)/bin/x86_win32"
            omni_inc = "$(omni_root)/include"
            omni_lib = "$(omni_root)/lib/x86_win32"

        ace_root  = re.sub("/", "\\\\", ace_root)
        omni_root = re.sub("/", "\\\\", omni_root)
        ace_inc   = re.sub("/", "\\\\", ace_inc)
        ace_lib   = re.sub("/", "\\\\", ace_lib)
        omni_bin  = re.sub("/", "\\\\", omni_bin)
        omni_inc  = re.sub("/", "\\\\", omni_inc)
        omni_lib  = re.sub("/", "\\\\", omni_lib)

        fname = self.gen_entryw.get()

        if os.path.isdir(fname):
            tkMessageBox.showerror(title=self.isdir_error, 
                                   message=self.isdir_error + fname)
            return

        if os.path.isfile(fname):
            if not tkMessageBox.askyesno(title=self.file_exists, 
                                         message=self.file_exists + fname):
                return

        f = open(fname, "w")
        f.write(prop_sheet % \
                    (ace_root, omni_root, \
                         ace_inc, ace_lib, \
                         omni_inc, omni_lib, omni_bin))
        f.close()
        tkMessageBox.showinfo(title=self.file_gened,
                              message=self.file_gened + fname)
        return

    def search(self):
        w = {
            "ACE.h"               : ["ace_inc", "ace/ACE.h"],
            "ACE.lib"             : ["ace_lib", "ACE.lib"],
            "omniidl.exe"         : ["omni_bin", "omniidl.exe"],
            "omniORB.h"           : ["omni_inc", "omniORB4/omniORB.h"],
            "omniORB[0-9]+_rt.lib": ["omni_lib", "omniORB[0-9]+_rt.lib"]
            }
        res = {}
        dirname = self.search_dirw.get()
        if os.path.isdir(dirname):
#            th = thread.start_new_thread(search, (dirname, w.keys(), res))
            search(dirname, w.keys(), res)
        else:
            tkMessageBox.showerror(title=self.dirname_error, 
                                   message=self.dirname_error + dirname)
            return

        # 検索結果をEntryにセット
        for f in w.keys():
            if res.has_key(f):
                l = len(self.ent[w[f][0]]["wid"].get())
                self.ent[w[f][0]]["wid"].delete(0, l)
                t = re.sub(re.compile(w[f][1]), "", res[f])
                self.ent[w[f][0]]["wid"].insert(0, t)

        # 検索結果を取得
        ace_dirs = [
            self.ent["ace_inc"]["wid"].get(),
            self.ent["ace_lib"]["wid"].get()
            ]
        
        omni_dirs = [
            self.ent["omni_bin"]["wid"].get(),
            self.ent["omni_inc"]["wid"].get(),
            self.ent["omni_lib"]["wid"].get()
            ]
            
        # 共通パスを取得
        ace_root = ""
        if ace_dirs[0] != "" or ace_dirs[1] != "":
            ace_root, ace_paths   = self.common_path(ace_dirs)

        omni_root = ""
        if omni_dirs[0] != "" or \
                omni_dirs[1] != "" or \
                omni_dirs[2] != "":
            omni_root, omni_paths = self.common_path(omni_dirs)


        if omni_root != "":
            l = len(self.ent["omni_root"]["wid"].get())
            self.ent["omni_root"]["wid"].delete(0, l)
            self.ent["omni_root"]["wid"].insert(0, omni_root)

        # ACE_ROOT, OMNI_ROOTをEntryにセット
        if ace_root != "":
            l = len(self.ent["ace_root"]["wid"].get())
            self.ent["ace_root"]["wid"].delete(0, l)
            self.ent["ace_root"]["wid"].insert(0, ace_root)

        return


    def common_path_len(self, plist):
        for i in range(len(plist[0])): # ディレクトリ名を比較
            dirname = plist[0][i]
            for j in range(1, len(plist)):
                if dirname != plist[j][i]:
                    return i
        return

    def common_path_split(self, paths):
        plist = []
        for p in paths:
            plist.append(p.split("/"))
        return plist

    def common_path(self, paths):
        plist  = self.common_path_split(paths)
        comlen = self.common_path_len(plist)

        compath=""
        for i in range(comlen):
            compath += plist[0][i]
            if i != comlen - 1:
                compath += "/"

        diff_paths = [""] * len(paths)
        for i in range(len(paths)):
            diff_paths[i] = ""
            for j in range(comlen, len(plist[i])):
                diff_paths[i] += "/" + plist[i][j]

        return compath, diff_paths



    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack();    self.init()


if __name__ == "__main__": app = App();  app.mainloop()
# end.

