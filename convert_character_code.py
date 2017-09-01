#!/usr/bin/env python
# -*- coding: euc-jp -*-

import sys
import chardet
import glob
import os.path
import codecs



if __name__ == '__main__':
  args = sys.argv
  dirpath = args[1]
  target = args[2]
  code = args[3]
  ext_list = ["*.cpp",
              "*.h"]
  
  path_list = ["src/lib/rtm",
               "src/lib/coil",
               "src/lib/coil/common",
               os.path.join("src/lib/coil", target, "coil"),
               "examples/*",
               "utils/*"]
  
  #path_list = [os.path.join("src/lib/coil", target, "coil")]
  for p in path_list:
    for e in ext_list:
      #print os.path.join(p, e)
      #print glob.glob(os.path.join(dirpath, p, e))
      filelist = glob.glob(os.path.join(dirpath, p, e))
      for n in filelist:
        with open(n, mode='rb') as f:
          encoding = chardet.detect(f.read())["encoding"]
        str_list = []
        with codecs.open(n, "r", encoding) as f:
          for row in f:
            str_list.append(row)
        with codecs.open(n, "w", code) as f:
          for row in str_list:
            f.write(row)
        
        
          
          
  
  
  
  