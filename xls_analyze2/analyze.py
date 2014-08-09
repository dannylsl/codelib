#!/usr/bin/python

import csver
import fpser
import mediafps
import meminfo
import procrank

import xlrd
import xlwt
from xlutils.copy import copy
from ConfigParser import ConfigParser
import sys
import os
from prints import *



support_platform = ['BYT', 'MOOREFLD']

class myConfigParser(ConfigParser) :
    def optionxform(self, optionstr):
        return optionstr

def Usage() :
    global support_platform
    print "Usage: %s [platform] [raw_folder]"%sys.argv[0]
    print "Example - 1: %s MRFLD raw_folder "%sys.argv[0]
    print "Example - 2: python analyze.py BYT raw_folder"
    print "-----" * 10
    print "Platform Supported:",support_platform


if __name__ == "__main__" :

    if len(sys.argv) != 3 :
        Usage()
        sys.exit(0)

    platform = sys.argv[1]
    csv_file_base_dir = '%s/'%sys.argv[2]

    if platform not in support_platform :
        print "Platform[%s] is not supported"%platform
        Usage()
        sys.exit(0)

    config = myConfigParser()
    config.read("analyze.ini")

    xls_template_dir = config.get("directory", 'xls_template_dir')

    if platform == 'BYT' :
        xls_tmp = "BYT_SOCWATCH_ANALYSIS_TEMPLATE.xls"
    elif platform == 'MOOREFLD' :
        xls_tmp  = "MOOREFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE.xls"

    xls_out = xls_tmp.replace('.xls', '_%s.xls'%sys.argv[2])

    data = xlrd.open_workbook('%s/%s'%(xls_template_dir, xls_tmp), formatting_info = True)
    table = data.sheets()[0]

    cases_options = config.options("%s-cases"%platform)
    print cases_options

    case_option_id = 0
    for case_option in cases_options :
        case_option_id =  case_option_id + 1
        print config.get("%s-cases"%platform, case_option)
        case_name = config.get("%s-cases"%platform, case_option)
        case_csv_filename = "%s.csv"%case_name
        case_csv_filepath = "%s%s"%(csv_file_base_dir, case_csv_filename)

        if os.path.exists(case_csv_filepath) == False :
            print_msg('E', '%s not exist'%case_csv_filepath)
            continue

        csvr = csver.csvReader(case_csv_filepath)
        corenum = int(csvr.core_num)
        case_offset = int((case_option_id-1) * corenum + 1)

### case_name
        title_row = int(config.get('title', platform)) -1
        table.put_cell(title_row, case_offset , 1, case_name , 0)

### cstate
        for cs_item in csvr.cstate :
            cs_row = int(config.get('%s-cstate'%platform, cs_item[0])) - 1
            for core_offset in range(0, corenum) :
                table.put_cell(cs_row, case_offset + core_offset, 1, cs_item[1 + core_offset] , 0)


### pstate
        freq_num = len(csvr.pstate)/corenum
        ps_row = int(config.get('pstate-startpos', platform)) -1
        row_offset = 0
        core_offset = 0
        for ps_item in csvr.pstate :
            table.put_cell(ps_row + row_offset, case_offset + core_offset, 1, ps_item[2], 0)
            cell_value = table.cell(ps_row + row_offset, case_offset + core_offset).value
            row_offset = row_offset + 1
            if row_offset%freq_num == 0:
                core_offset = core_offset + 1
                row_offset = 0

### nc-state
        print csvr.ncstate
        ncs_row = int(config.get('ncstate-startpos', platform)) -1
        row_offset = 0
        print "NCSTATEOFFSET"
        print "table.put_cell(ncs_row + row_offset[%s], case_offset[%s] , 1, ncs_item[4], 0)"%((ncs_row+row_offset), case_offset)
        print "NCSTATEOFFSET"
        for ncs_item in csvr.ncstate :
            table.put_cell(ncs_row + row_offset, case_offset , 1, ncs_item[4], 0)
            row_offset = row_offset + 1

### BANDWIDTH
        bw_options = config.options("%s-bw"%platform);
        for bw_option in bw_options :
            case_bw_filename = "%s_%s.csv"%(case_name, bw_option)
            case_bw_filepath = "%s%s"%(csv_file_base_dir, case_bw_filename)
            print_msg('D', case_bw_filepath)

            bw_row = int(config.get("%s-bw"%platform, bw_option)) -1

            if os.path.exists(case_bw_filepath) == True :
                bw_csvr = csver.csvReader(case_bw_filepath)
                bw_data = bw_csvr.get_bw_data(bw_option)

                if bw_option != "dram-srr" :
                    bw_total = bw_data[len(bw_data)-1][1]
                    table.put_cell(bw_row, case_offset, 1, bw_total , 0)
                else :
                    table.put_cell(bw_row    , case_offset, 1, bw_data[0][1] , 0)
                    table.put_cell(bw_row + 1, case_offset, 1, bw_data[1][1] , 0)

                ###  DELETE csvReader Object FOR bandwidth
                del bw_csvr
            else :
                if bw_option != "dram-srr" :
                    table.put_cell(bw_row, case_offset, 1, "NONE" , 0)
                else :
                    table.put_cell(bw_row    , case_offset, 1, "NONE" , 0)
                    table.put_cell(bw_row + 1, case_offset, 1, "NONE" , 0)

### FPS
        print "****************************************"
        print "fps"
        print "****************************************"
        if "record" in case_name :
            fps_prefix = config.get('fpsfile', 'record_prefix')
            fps_suffix = config.get('fpsfile', 'record_suffix')
            fps_filepath = "%s%s%s%s"%(csv_file_base_dir, fps_prefix, case_name, fps_suffix)
            print_msg('D', fps_filepath)
            record_mediainfo = mediafps.mediaFPS(fps_filepath)
            fps_value =  record_mediainfo.frate
        else :
            fps_prefix = config.get('fpsfile', 'video_prefix')
            fps_suffix = config.get('fpsfile', 'video_suffix')
            fps_filepath = "%slog/%s%s%s"%(csv_file_base_dir, fps_prefix, case_name, fps_suffix)
            print_msg('D', fps_filepath)
            video_fps = fpser.FPS(fps_filepath, 'render_FPS=[0-9]*\.[0-9]*')
            fps_value = video_fps.fps

        fps_row = int(config.get('fpsfile', '%s-row'%platform)) -1
        table.put_cell(fps_row, case_offset, 1, fps_value, 0)
        print "table.put_cell(fps_row[%s], case_offset[%s], 1, fps_value[%s], 0)"%(fps_row, case_offset, fps_value)
        print "****************************************"
        print "fps value=",fps_value
        print "****************************************"


### MemoryInfo
##### MEMORY BEFORE
        prefix = config.get("%s-memoryinfo_pre"%platform, 'prefix')
        suffix = config.get("%s-memoryinfo_pre"%platform, 'suffix')
        meminfo_pre = meminfo.MemoryInfo("%s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))
        print_msg('D', "%s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))

        mmtotal_row = int(config.get("%s-memoryinfo_pre"%platform, 'MemTotal')) - 1
        table.put_cell(mmtotal_row, case_offset, 1, meminfo_pre.memTotal, 0)

        mmfree_row  = int(config.get("%s-memoryinfo_pre"%platform, 'MemFree')) - 1
        table.put_cell(mmfree_row, case_offset, 1, meminfo_pre.memFree, 0)

        mmcache_row = int(config.get("%s-memoryinfo_pre"%platform, 'Cached')) -1
        table.put_cell(mmcache_row, case_offset, 1, meminfo_pre.memCached, 0)

##### MEMORY AFTER
        prefix = config.get("%s-memoryinfo_next"%platform, 'prefix')
        suffix = config.get("%s-memoryinfo_next"%platform, 'suffix')
        meminfo_next = meminfo.MemoryInfo("%s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))
        print_msg('D', "%s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))

        mmtotal_row = int(config.get("%s-memoryinfo_next"%platform, 'MemTotal')) - 1
        table.put_cell(mmtotal_row, case_offset, 1, meminfo_next.memTotal, 0)

        mmfree_row  = int(config.get("%s-memoryinfo_next"%platform, 'MemFree')) - 1
        table.put_cell(mmfree_row, case_offset, 1, meminfo_next.memFree, 0)

        mmcache_row = int(config.get("%s-memoryinfo_next"%platform, 'Cached')) - 1
        table.put_cell(mmcache_row, case_offset, 1, meminfo_next.memCached, 0)

### Procrank
##### PROCRANK BEFORE
        prefix      = config.get("%s-procrank_pre"%platform, 'prefix')
        suffix      = config.get("%s-procrank_pre"%platform, 'suffix')
        table_cell  = int(config.get("%s-procrank_pre"%platform, 'table_cell'))
        sf_row      = int(config.get("%s-procrank_pre"%platform, 'surfaceflinger')) - 1
        md_row      = int(config.get("%s-procrank_pre"%platform, 'mediaserver')) - 1
        print_msg('D', "PROCRANK   %s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))

        procinfo_pre = procrank.Procrank("%s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))
        surfaceflinger_data = procinfo_pre.get_data('surfaceflinger')
        cell_offset = 0
        for sf_item in surfaceflinger_data :
            table.put_cell(sf_row, case_offset + cell_offset , 1, surfaceflinger_data[sf_item] , 0)
            cell_offset = cell_offset + table_cell

        mediaserver_data    = procinfo_pre.get_data('mediaserver')
        cell_offset = 0
        for md_item in mediaserver_data :
            table.put_cell(md_row, case_offset + cell_offset , 1, mediaserver_data[md_item] , 0)
            cell_offset = cell_offset + table_cell

##### PROCRANK AFTER
        prefix      = config.get("%s-procrank_next"%platform, 'prefix')
        suffix      = config.get("%s-procrank_next"%platform, 'suffix')
        table_cell  = int(config.get("%s-procrank_next"%platform, 'table_cell'))
        sf_row      = int(config.get("%s-procrank_next"%platform, 'surfaceflinger')) - 1
        md_row      = int(config.get("%s-procrank_next"%platform, 'mediaserver')) - 1
        print_msg('D', "PROCRANK   %s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))

        procinfo_next = procrank.Procrank("%s%s%s%s"%(csv_file_base_dir, prefix, case_name, suffix))
        surfaceflinger_data = procinfo_next.get_data('surfaceflinger')
        cell_offset = 0
        for sf_item in surfaceflinger_data :
            table.put_cell(sf_row, case_offset + cell_offset , 1, surfaceflinger_data[sf_item] , 0)
            cell_offset = cell_offset + table_cell

        mediaserver_data    = procinfo_next.get_data('mediaserver')
        cell_offset = 0
        for md_item in mediaserver_data :
            table.put_cell(md_row, case_offset + cell_offset , 1, mediaserver_data[md_item] , 0)
            cell_offset = cell_offset + table_cell



###  DELETE csvReader Object
        del csvr

### SAVE AS EXCEL
wb = copy(data)
ws = wb.get_sheet(0)
wb.save(xls_out)
print "analysis work finished!"
print "%s saved"%xls_out
