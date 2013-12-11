import csv
import sys

class csvReader() :
    reader      = None
    csv_list    = list()
    core_num    = 0
    cstate      = list()
    wakeups     = 0.0
    pstate      = list()
    ncstate     = list()


    def __init__(self, filename) :
        print "__init___ called  filename = %s"%filename
        try :
            self.reader = csv.reader(open(filename, 'rb'))
            self.init_csv_list()
            self.get_core_num()
            self.get_cstate()
            self.get_wakeup_sec_core()
            self.get_pstate()
            self.get_ncstate()
            self.csv_list_print()
        except :
            print "Fail to init the csvReader Object"
#       print "__init__ call end"


    def __del__(self) :
        del self.csv_list[:]
        del self.cstate[:]
        del self.pstate[:]
        del self.ncstate[:]
        print  "__del__ called"


    def allprint(self) :
        print self.reader
        print "**" * 10
#        print self.csv_list
#        print "**" * 10
        print self.cstate
        print "**" * 10
        print self.pstate
        print "**" * 10
        print self.ncstate
        print "**" * 10
        sys.exit(0)
        for item in self.reader :
            item = item.strip(' ')
            print ', '.join(item)


    def csv_list_print(self) :
#       for line in self.csv_list :
#           print line
        print "csv_list length=%d"%len(self.csv_list)


    def get_value(self, itemname) :
        row = 0
        col = 0
        for line in self.reader :
#items = line.split(',')
            if itemname in line :
                print "find the result"
#               print line


    def init_csv_list(self) :
        print "init the csv_list"
        #Print "remove needless space from self.reader"
        #And store data in csv_list
        for line in self.reader :
            list_tmp = list()
            for item_in_line in line:
                item_stripped = item_in_line.strip()
                if item_stripped != '' and item_stripped.find('----') == -1 :
                    list_tmp.append(item_stripped)
            if list_tmp != [] :
                self.csv_list.append(list_tmp)
                list_tmp = []
        #print self.csv_list


    def get_core_num(self) :
        cstate_index = self.csv_list.index(['Core C State Residency'])
        if cstate_index == -1:
            cstate_index = self.csv_list.index(['C State Residency'])
        self.core_num = len(self.csv_list[cstate_index + 1])
        print "core num = %d"%self.core_num


    def get_cstate(self) :
        cstate_index = self.csv_list.index(['Core C State Residency'])
        if cstate_index == -1:
            cstate_index = self.csv_list.index(['C State Residency'])
        core_list= self.csv_list[cstate_index + 1]
        offset = 2
        while True :
            if len(self.csv_list[cstate_index + offset]) == (self.core_num + 1) :
                self.cstate.append(self.csv_list[cstate_index + offset])
                offset = offset + 1
            else :
                break
#       print self.cstate
#       print "Detect %d cores on this device"%self.core_num
#       print "get cstate index = %d"%cstate_index


    def get_wakeup_sec_core(self) :
        for item in self.csv_list :
            if len(item) == 1 :
                if item[0].find('Wakeups/sec/core') != -1 :
#           print item
                    self.wakeups = float(item[0].split('=')[1])
                    print "wakeups/sec/core = %s"%self.wakeups
                    break


    def get_pstate(self) :
        pstate_index = self.csv_list.index(['P State Residency'])
        offset = 2
        core_num = self.core_num
        while core_num > 0 :
            if len(self.csv_list[pstate_index + offset]) == 3 :
                self.pstate.append(self.csv_list[pstate_index + offset])
            else :
                core_num = core_num - 1
            offset = offset + 1
#       print self.pstate


    def get_ncstate(self) :
        ncstate_index = self.csv_list.index(['North Complex', 'Residency'])
        offset = 2
        while True :
#if len(self.csv_list[ncstate_index + offset] != 6 :
            if self.csv_list[ncstate_index + offset][0].find('NC-') != -1 :
                self.ncstate.append(self.csv_list[ncstate_index + offset])
                offset = offset + 1
            else :
                break
#       print self.ncstate

# D0state :
#   0 -> D0i0
#   1 -> D0i1
#   2 -> D0i2
#   3 -> D0i3
# feature : MRFLD
#   GFXSLC | GSDKCK | GRSCD | Video Decoder | Video Encoder | Display Island A
#   Display Island B | Display Island C
#   VSP | ISP | MIO | HDMIO | GFXSLCLDO
#
# feature : BYT
#   RENder | Media | Display DPIO | CMNLM | TX0 | TX1 | TX2 | TX3 | RX0 | RX1 |
#   Video Decoder | ISP

    def get_ncstate_value(self, D0state, feature, platform) :

        state = ['D0i0', 'D0i1', 'D0i2', 'D0i3']
        if platform == 'MRFLD' :
            feat  = ['GFXSLC', 'GSDKCK', 'GRSCD', 'Video Decoder', 'Video Encoder', 'Display Island A', 'Display Island B', 'Display Island C', 'VSP', 'ISP', 'MIO', 'HDMIO', 'GFXSLCLDO']
        elif platform == 'BYT' :
            feat = ['RENder', 'Media', 'Display DPIO', 'CMNLM', 'TX0', 'TX1', 'TX2','TX3', 'RX0', 'RX1', 'Video Decoder', 'ISP']

        state_index = state.index(D0state)
        if (D0state in state) and (feature in feat) :
            for items in self.ncstate :
                if feature in items :
#                   print '%s - %s -%s'% (D0state, feature, items[state_index + 1])
                    return items[state_index + 1]
        else:
            print 'NOT FOUND'
            return  'NOT FOUND'


#csvr = csvReader('csv_folder/idle.csv')
#csvr = csvReader('play1.csv')
#csvr.init_csv_list()
#csvr.csv_list_print()
#csvr.get_cstate()
#csvr.get_wakeup_sec_core()
#csvr.get_pstate()
#csvr.get_ncstate()
#csvr.get_ncstate_value('D0i3','Video Decoder')
#csvr.get_value('CC0')
#csvr.allprint()
