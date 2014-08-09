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

    io_bw_list      = list()
    ddr_bw_list     = list()
    dram_srr_list   = list()
    cpu_ddr_bw_list = list()
    gfx_ddr_bw_list = list()
    isp_ddr_bw_list = list()
    disp_ddr_bw_list= list()

    #FOR SOCWATCH 1.4.1
    keywords = {
        "cstate"  : ["Core CState Residency"],
        "wakeups" : ["Wakeups/sec/core"],
        "pstate"  : ["P State Residency"],
        "ncstate" : ['North Complex', 'Residency During S0i0'],
    }

    def __init__(self, filename) :
        print "__init___ called  filename = %s"%filename
        try :
            self.filename = filename
            self.reader = csv.reader(open(filename, 'rb'))
            self.init_csv_list()
            self.get_core_num()
            self.get_cstate()
            self.get_wakeup_sec_core()
            self.get_pstate()
            self.get_ncstate()
#            self.csv_list_print()
        except Exception as err :
            print "Fail to init the csvReader Object"
            print "Error:",err
#       print "__init__ call end"


    def __del__(self) :
        print "file [%s] delete"%self.filename
        del self.csv_list[:]
        del self.cstate[:]
        del self.pstate[:]
        del self.ncstate[:]
        del self.cpu_ddr_bw_list[:]
        del self.ddr_bw_list[:]
        del self.dram_srr_list[:]
        del self.disp_ddr_bw_list[:]
        del self.gfx_ddr_bw_list[:]
        del self.io_bw_list[:]
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
        for line in self.csv_list :
            print line
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
        cstate_index = self.csv_list.index(self.keywords['cstate'])
        self.core_num = len(self.csv_list[cstate_index + 1])
        print "core num = %d"%self.core_num


    def get_cstate(self) :
        cstate_index = self.csv_list.index(self.keywords['cstate'])
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
                if item[0].find(self.keywords['wakeups'][0]) != -1 :
                    self.wakeups = float(item[0].split('=')[1])
                    print "wakeups/sec/core = %s"%self.wakeups
                    break


    def get_pstate(self) :
        pstate_index = self.csv_list.index(self.keywords['pstate'])
        print "pstate_index=", pstate_index
        offset = 1
        core_num = self.core_num
        while core_num >= 0 :
            if len(self.csv_list[pstate_index + offset]) == 3 :
                pstate_item = self.csv_list[pstate_index + offset] + pstate_core
                self.pstate.append(pstate_item)
            elif len(self.csv_list[pstate_index + offset]) == 1 :
            #Core 1 | Core 2 | ...
                core_num = core_num - 1
                pstate_core = self.csv_list[pstate_index + offset]
                pstate_core[0] = pstate_core[0].lower()
            else :
                break
            offset = offset + 1
#        print self.pstate


    def get_ncstate(self) :
        print "GET NCSTATE"
        ncstate_index = self.csv_list.index(self.keywords['ncstate'])
        offset = 2
        while True :
            if self.csv_list[ncstate_index + offset][0].find('NC-') != -1 :
#                print self.csv_list[ncstate_index + offset]
                self.ncstate.append(self.csv_list[ncstate_index + offset])
                offset = offset + 1
            else :
                break
#        print self.ncstate


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
        elif platform == 'MOOREFLD' :
            feat  = ['GFXSLC', 'GSDKCK', 'GRSCD', 'Video Decoder', 'Video Encoder', 'Display Island A', 'Display Island B', 'Display Island C', 'VSP', 'ISP', 'MIO', 'HDMIO', 'GFXSLCLDO']

        state_index = state.index(D0state)
        if (D0state in state) and (feature in feat) :
            for items in self.ncstate :
                if feature in items :
#                   print '%s - %s -%s'% (D0state, feature, items[state_index + 1])
                    return items[state_index + 1]
        else:
            print 'NOT FOUND'
            return  'NOT FOUND'

# Retrieve cpu-ddr-bw
    def get_cpu_ddr_bw(self) :
        print "CPU DDR BW"
        cpu_ddr_bw_index = self.csv_list.index(['cpu-ddr-bw'])
        print self.csv_list[cpu_ddr_bw_index]
        offset = 2
        while True :
            if len(self.csv_list) > (cpu_ddr_bw_index + offset) :
                if len(self.csv_list[cpu_ddr_bw_index + offset]) == 2 :
                    self.cpu_ddr_bw_list.append(self.csv_list[cpu_ddr_bw_index+offset])
                    offset = offset + 1
                else :
                    break
            else :
                break
#        print self.cpu_ddr_bw_list

# Retrieve ddr-bw
    def get_ddr_bw(self) :
        print "DDR BW"
        ddr_bw_index = self.csv_list.index(['ddr-bw'])
        offset = 2
        while True :
#           print "ddr_bw_index [%s] offset [%s]  Total [%s]"%(ddr_bw_index, offset, ddr_bw_index + offset)
#           print "csv_list len=",len(self.csv_list)
            if len(self.csv_list) > (ddr_bw_index + offset) :
                if len(self.csv_list[ddr_bw_index+offset]) == 2 :
                    self.ddr_bw_list.append(self.csv_list[ddr_bw_index + offset])
                    offset = offset + 1
                else :
                    break
            else :
                break
#        print self.ddr_bw_list

# Retrieve dram-srr
    def get_dram_srr(self) :
        print "DRAM SELF REFRESE DRAM-SRR"
        dram_srr_index = self.csv_list.index(['dram-srr'])
        offset = 2
        while True:
            if len(self.csv_list) > (dram_srr_index + offset) :
                if len(self.csv_list[dram_srr_index+offset]) == 2 :
                    self.dram_srr_list.append(self.csv_list[dram_srr_index + offset])
                    offset = offset + 1
                else :
                    break
            else :
                break
#        print self.dram_srr_list

# Retrieve disp-ddr-bw
    def get_disp_ddr_bw(self) :
        print "DISP DDR BW"
        disp_ddr_bw_index = self.csv_list.index(['disp-ddr-bw'])
        offset = 2
        while True :
            if len(self.csv_list) > (disp_ddr_bw_index + offset) :
                if len(self.csv_list[disp_ddr_bw_index + offset]) == 2:
                    self.disp_ddr_bw_list.append(self.csv_list[disp_ddr_bw_index + offset])
                    offset = offset + 1
                else :
                    break
            else :
                break
#        print self.disp_ddr_bw_list

# Retrieve io-bw
    def get_io_bw(self) :
        print "IO BW"
        io_bw_index = self.csv_list.index(['io-bw'])
        offset = 2
        while True :
            if len(self.csv_list) > (io_bw_index + offset) :
                if len(self.csv_list[io_bw_index + offset]) == 2 :
                    self.io_bw_list.append(self.csv_list[io_bw_index + offset])
                    offset = offset + 1
                else :
                    break
            else :
                break
#       print self.io_bw_list

# Retrieve gfx-ddr-bw
    def get_gfx_ddr_bw(self) :
        print "GFX DDR BW"
        gfx_ddr_bw_index = self.csv_list.index(['gfx-ddr-bw'])
        offset = 2
        while True :
            if len(self.csv_list) > (gfx_ddr_bw_index + offset) :
                if len(self.csv_list[gfx_ddr_bw_index + offset]) == 2 :
                    self.gfx_ddr_bw_list.append(self.csv_list[gfx_ddr_bw_index + offset])
                    offset = offset + 1
                else :
                    break
            else :
                break

# Retrieve isp-ddr-bw
    def get_isp_ddr_bw(self) :
        print "ISP DDR BW"
        isp_ddr_bw_index = self.csv_list.index(['isp-ddr-bw'])
        offset = 2
        while True :
            if len(self.csv_list) > (isp_ddr_bw_index + offset) :
                if len(self.csv_list[isp_ddr_bw_index + offset]) == 2 :
                    self.isp_ddr_bw_list.append(self.csv_list[isp_ddr_bw_index + offset])
                    offset = offset + 1
                else :
                    break
            else :
                break


# GET BW DATA
    def get_bw_data(self, bw_type) :
        if bw_type == 'ddr-bw' :
            self.get_ddr_bw()
            bw_list = self.ddr_bw_list
        elif bw_type == 'dram-srr' :
            self.get_dram_srr()
            bw_list = self.dram_srr_list
        elif bw_type == 'disp-ddr-bw' :
            self.get_disp_ddr_bw()
            bw_list = self.disp_ddr_bw_list
        elif bw_type == 'isp-ddr-bw' :
            self.get_isp_ddr_bw()
            bw_list = self.isp_ddr_bw_list
        elif bw_type == 'io-bw' :
            self.get_io_bw()
            bw_list = self.io_bw_list
        elif bw_type == 'cpu-ddr-bw' :
            self.get_cpu_ddr_bw()
            bw_list = self.cpu_ddr_bw_list
        elif bw_type == 'gfx-ddr-bw' :
            self.get_gfx_ddr_bw()
            bw_list = self.gfx_ddr_bw_list
        else :
            bw_list = "TYPE %s UNDEFINED"%bw_type
        return bw_list


if __name__ == "__main__" :
#csvr = csvReader('MOORE_WW22/stream_chrome.csv')
    csvr = csvReader('Socwatch_Baytrail_WW29/stream_chrome_ddr-bw.csv')  #4test/video_playback_720p_30fps_VP9_power.csv')
#    csvr.csv_list_print()
    print "==="*10
    csvr.get_ddr_bw()
    print "==="*10
#   csvr.init_csv_list()
#    csvr.get_cstate()
#    csvr.get_wakeup_sec_core()
#    csvr.get_pstate()
#    csvr.get_ncstate()
#csvr.get_ncstate_value('D0i3','Video Decoder')
#csvr.get_value('CC0')
#csvr.allprint()

#csvr = csvReader('MOORE_WW08/idle.csv')
#csvr = csvReader('bw/big_buck_bunny_1080p_audio_30fps.mp4_cpu-ddr-bw.csv')
#csvr.get_cpu_ddr_bw()

#csvr = csvReader('bw/big_buck_bunny_1080p_audio_30fps.mp4_ddr-bw.csv')
#csvr.csv_list_print()
#print "==="*10
#csvr.get_ddr_bw()
#print "==="*10


#csvr = csvReader('bw/big_buck_bunny_1080p_audio_30fps.mp4_dram-srr.csv')
#csvr.csv_list_print()
#print "==="*10
#csvr.get_dram_srr()
#print csvr.get_bw_data('dram-srr')
#print csvr.dram_srr_list
#print "==="*10


#csvr = csvReader('bw/big_buck_bunny_1080p_audio_30fps.mp4_disp-ddr-bw.csv')
#csvr.csv_list_print()
#print "==="*10
#csvr.get_disp_ddr_bw()
#print "==="*10

#csvr = csvReader('bw/big_buck_bunny_1080p_audio_30fps.mp4_io-bw.csv')
#csvr.csv_list_print()
#print "==="*10
#csvr.get_io_bw()
#print "==="*10

