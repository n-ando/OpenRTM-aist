#!/usr/bin/env python
#
# @brief WiX wxs file generator for omniORB
# @date $Date$
# @author Norkai Ando <n-ando@aist.go.jp>
#
# Copyright (C) 2010
#     Noriaki Ando
#     Intelligent Systems Research Institute,
#     National Institute of
#         Advanced Industrial Science and Technology (AIST), Japan
#     All rights reserved.
#
# $Id$
#

OpenCV_files = "README OpenCVConfig.cmake"

data = [
    ("",                OpenCV_files),
    ("bin",             "*.dll"),
    ("gpu/x86/bin",     "*.dll"),
    ("gpu/x86/lib",     "*.lib"),
    ("include/opencv",  "*.h *.hpp"),
    ("include/opencv2", "*.h *.hpp"),
    ("include/opencv2/calib3d", "*.h *.hpp"),
    ("include/opencv2/contrib", "*.h *.hpp"),
    ("include/opencv2/core", "*.h *.hpp"),
    ("include/opencv2/features2d", "*.h *.hpp"),
    ("include/opencv2/flann", "*.h *.hpp"),
    ("include/opencv2/gpu", "*.h *.hpp"),
    ("include/opencv2/highgui", "*.h *.hpp"),
    ("include/opencv2/imgproc", "*.h *.hpp"),
    ("include/opencv2/legacy", "*.h *.hpp"),
    ("include/opencv2/ml", "*.h *.hpp"),
    ("include/opencv2/objdetect", "*.h *.hpp"),
    ("include/opencv2/ts", "*.h *.hpp"),
    ("include/opencv2/video", "*.h *.hpp"),
    ("lib",             "*.lib"),
    ("staticlib",             "*.lib"),
    ("doc",             "license.txt *.pdf")
]

import os
base_dir = os.getenv("OPENCV_ROOT")
base_dir = base_dir.replace("\"", "")

if base_dir == None:
    base_dir="C:\\distribution\\OpenCV2.3"
else:
    base_dir += "\\"

def path_to_dir_id(path, prefix):
    # path = "bin/x86_win32" prefix = "omni"
    # output = "omni_bin_x86_win32"
    # "." -> "_"
    output = prefix + "_" + "_".join(path.split("/"))
    return output.replace(".", "_")


def path_to_comp_id(path, prefix):
    # path = "bin/x86_win32" prefix = "omni"
    # output = "OmniBinX86_win32"
    # "." -> "_"
    output = prefix
    for c in path.split("/"):
        output += c.capitalize()
    return output.replace(".", "_")

import makewxs

for (path, files) in data:
    # wxs component name
    comp_name = path_to_comp_id(path, "OpenCV")
    # wxs directory name
    dir_name = path_to_dir_id(path, "OpenCV")

    path = path.replace("/", "\\")

    # full path to target directory
    full_path = base_dir + "\\\\" + path

    import glob
    flist = []
    for f in files.split(" "):
        flist += glob.glob(full_path + "\\" + f)

    cmd = ["flist",
           "-c", comp_name,
           "-o", dir_name + ".yaml",
           "-p",  base_dir + path]
    cmd += flist

    makewxs.main(cmd)

import re
if None != re.search('2\.3',base_dir):
    cmd = ["wxs",
           "-o", "OpenCV_inc.wxs",
           "-i", "OpenCV23_inc.wxs.in"]
else:
    cmd = ["wxs",
           "-o", "OpenCV_inc.wxs",
           "-i", "OpenCV23_inc.wxs.in"]

cmd += glob.glob("*.yaml")
makewxs.main(cmd)
