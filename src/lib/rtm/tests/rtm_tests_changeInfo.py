#!/usr/bin/env python
#
# chmod 775
#

import sys, os, datetime, time
import commands
	
LINE_START_SF = "SF:"
END_OF_RECORD  = "end_of_record"

class ChangeTestsInfo():
    def __init__(self, parent=None):
        print "__init__(self, parent=None):"

    def checkIsDeleteRecord(self, line, use_line_src_lib_rtm):
        rtmlength = len(use_line_src_lib_rtm)
        linelength = len(line)
        if linelength > rtmlength:
            if line[0:rtmlength] == use_line_src_lib_rtm:
                for var in range(rtmlength + 1, linelength):
                    if line[var] == '/':
                        return True
                return False
        return True
        
#        if line[0:7] == DEL_LINE_ROOTUSR:
#            return True
#        coillength = len(DEL_LINE_SRC_LIB_COIL)
#        if line[0:coillength] == DEL_LINE_SRC_LIB_COIL:
#            return True

    def getSrcLibRtmPath(self):
        nowdir = commands.getoutput('pwd')
        nowdirpart = nowdir.split('/')
        usepath = '/'
        for idx in range(1, (len(nowdirpart) - 2)):
            usepath = usepath + nowdirpart[idx] + '/'
#        print usepath
        return usepath

    def openTestsInfoFile(self, infofilename):
        use_line_src_lib_rtm = LINE_START_SF + self.getSrcLibRtmPath()
        print use_line_src_lib_rtm

        infofilenameNew = infofilename + '.new'
        infofilenameOrg = infofilename + '.org'
        if os.path.exists(infofilenameOrg) == False:
            os.rename(infofilename, infofilenameOrg)
        fr = open(infofilenameOrg)
        allDt = fr.read()
        fr.close()

#        fw = open(infofilenameNew, "w")
        fw = open(infofilename, "w")
        writeFlag = True

        allLine = allDt.split('\n')
        for line in allLine:
            if len(line) > 10:
#                if line[0:7] == DEL_LINE_ROOTUSR:
                if line[0:3] == LINE_START_SF:
                    if self.checkIsDeleteRecord(line, use_line_src_lib_rtm) == True:
                        writeFlag = False
                        continue
                if line == END_OF_RECORD:
                    if writeFlag == False:
                        writeFlag = True
                        continue
            if writeFlag == True:
                fw.write(line + '\n')
        fw.close

def main(argvs):
    changetestsinfo = ChangeTestsInfo()
    changetestsinfo.openTestsInfoFile(argvs[1])

if __name__ == '__main__':
    main(sys.argv)
