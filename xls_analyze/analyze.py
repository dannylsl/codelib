#!/usr/bin/python

import csver
import fpser
import xlrd
import xlwt
from xlutils.copy import copy
from ConfigParser import ConfigParser
import sys
import os


class myConfigParser(ConfigParser) :
    def optionxform(self, optionstr):
        return optionstr

def Usage() :
    print "Usage: %s [platform = MRFLD | BYT] [raw_folder]"%sys.argv[0]
    print "Example - 1: %s MRFLD raw_folder "%sys.argv[0]
    print "Example - 2: python analyze.py BYT raw_folder"

platform = sys.argv[1]

if (platform != 'MRFLD' and platform != 'BYT') :
    print "Error : Please set the platform"
    Usage()
    sys.exit(0)

if len(sys.argv) != 3 :
    Usage()
    sys.exit(0)

### MYSQL-DB
conn = MySQLdb.connect(host='vpnp-workstation1', user='root', passwd='123456', db='socwatch',charset='utf8', port=3306)
cur = conn.cursor()

platform = sys.argv[1]
csv_file_base_dir = '%s/'%sys.argv[2]

config = myConfigParser()
config.read("analyze.conf")

xls_template_dir = config.get("directory", 'xls_template_dir')

#platform = "MRFLD"
#xls_tmp  = "MRFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE.xls"
#xls_out  = "MRFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE_OUT.xls"

if platform == 'MRFLD':
    xls_tmp  = "MRFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE.xls"
elif platform == 'BYT' :
    xls_tmp = "BYT_SOCWATCH_ANALYSIS_TEMPLATE.xls"

xls_out = xls_tmp.replace('.xls', '_%s.xls'%sys.argv[2])

data = xlrd.open_workbook('%s/%s'%(xls_template_dir, xls_tmp), formatting_info = True)
table = data.sheets()[0]

#sections = config.sections()
#print sections
cases_order = config.get("cases_order", platform)
#print cases_order
cases =  cases_order.split('-')
print "cases : %s" %cases


########################
# GET csv-file
########################
csvfilelist = config.options('%s-csvfile'%platform)
file_list = list()
for csvfilename in csvfilelist :
    csvfile = config.get('%s-csvfile'%platform, csvfilename)
    file_list.append(csvfile)
print "file_list : %s"%file_list
# GET csv-file done

for csv_filename in file_list :
#csv_filename = "stream_chrome"
    csv_file = "%s%s.csv"%(csv_file_base_dir, csv_filename)
    print csv_file
    is_file_exist = os.path.exists(csv_file)
    if is_file_exist == False :
        print "file not exist"
        continue
    csvr = csver.csvReader(csv_file)

    corenum = int(csvr.core_num)
    case_offset = int(cases.index(csv_filename) * corenum + 1)

### cstate
#   print csvr.cstate
    for cs_item in csvr.cstate :
        cs_row = int(config.get('%s-cstate'%platform, cs_item[0])) - 1
#       print cs_row
#       cell_value = table.cell(cs_row, case_offset).value
#       print "row = %s col= %s => %s"%(cs_row + 1, case_offset, cell_value)
        for core_offset in range(0, corenum) :
#           print "core_offset = %d value= %s"%(core_offset, cs_item[1 + core_offset])
            table.put_cell(cs_row, case_offset + core_offset, 1, cs_item[1 + core_offset] , 0)


### pstate
    freq_num = len(csvr.pstate)/corenum
#   print 'freq_num = %s'%freq_num
    ps_row = int(config.get('pstate', platform)) -1
    row_offset = 0
    core_offset = 0
    for ps_item in csvr.pstate :
#   cell_value = table.cell(ps_row + row_offset, case_offset + core_offset).value
#   print "row = %s col= %s => %s"%(row_offset, case_offset + core_offset, cell_value)
#       print "row_offset = %s col= %s => %s"%(row_offset, case_offset + core_offset, ps_item[2])
        table.put_cell(ps_row + row_offset, case_offset + core_offset, 1, ps_item[2], 0)
        cell_value = table.cell(ps_row + row_offset, case_offset + core_offset).value
#       print "row = %s col= %s => %s"%(ps_row + row_offset, case_offset + core_offset, cell_value)
        row_offset = row_offset + 1
#   print "prow = %s pcol= %s"%(ps_row + row_offset, case_offset + core_offset)
        if row_offset%freq_num == 0:
            core_offset = core_offset + 1
            row_offset = 0

### wakeup/sec/core
    wakeup_row = int(config.get('WU/sec/core', platform)) -1
    table.put_cell(wakeup_row, case_offset, 1, str(csvr.wakeups), 0)

### nc-state
    ncs_list = config.options('%s-ncstate'%platform) 
#   print ncs_list
    for ncs_item in ncs_list :
        row = int(config.get('%s-ncstate'%platform, ncs_item))-1
        if ncs_item == 'Encode' :
            ncs_item = "Video Encoder"
        if ncs_item == 'Decode':
            ncs_item = "Video Decoder"
        value = csvr.get_ncstate_value('D0i3', ncs_item, platform)
#       print 'ncs_item=%s value=%s row=%s' %(ncs_item, value, row)
        table.put_cell(row, case_offset, 1, str(value), 0)

    del csvr


########################
# GET fps file
########################
fps_prefix = config.get("fpsfile","prefix")
fps_suffix = config.get("fpsfile","suffix")
print ">>>>>>>>>>>>>>>>>  FPS RETRIEVE <<<<<<<<<<<<<<<<"
for case in cases :
    fps_filename = "%s/%s%s%s"%(csv_file_base_dir, fps_prefix, case, fps_suffix)
    if os.path.exists(fps_filename) == False:
        pass
    else :
        fps = fpser.FPS(fps_filename, 'render_FPS=[0-9]*\.[0-9]*')
        fps_row = int(config.get('fps', platform)) - 1
        case_offset = int(cases.index(case) * corenum + 1)
        print fps.fps
        table.put_cell(fps_row, case_offset, 1, str(fps.fps) , 0)

#sys.exit(0)

### SAVE AS EXCEL
wb = copy(data)
ws = wb.get_sheet(0)
wb.save(xls_out)
print "analysis work finished!"
print "%s saved"%xls_out
