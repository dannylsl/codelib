#s!/bin/python

import MySQLdb
import csver
import fpser
from ConfigParser import ConfigParser
import sys
import os
import datetime


class myConfigParser(ConfigParser) :
    def optionxform(self, optionstr):
        return optionstr


device_list = ['FFRD','FFRD8','VVBOARD']

def Usage() :
    print "Usage: %s [platform = MRFLD | BYT] [DEVICE] [WEEK ID] [raw_folder]"%sys.argv[0]
    print "Example - 1: %s MRFLD FFRD ww49 raw_folder "%sys.argv[0]
    print "Example - 2: python raw2db.py BYT FFRD8 ww49 raw_folder"
    print "device value", device_list


def isDescriptInTable(cursor, decription, table) :
    sql = "select * from %s where `description`='%s'"%(table, description)
    count = cursor.execute(sql)
    if count == 0 :
        return False
    else :
        return True


platform = sys.argv[1]

device = sys.argv[2]

if len(sys.argv) != 5 :
    print "Error : ERROR parameters number"
    Usage()
    sys.exit(0)

if (platform != 'MRFLD' and platform != 'BYT') :
    print "Error : Please set the platform"
    Usage()
    sys.exit(0)

if (device not in device_list) :
    print "Error : ERROR DEVICE"
    Usage()
    sys.exit(0)


### MYSQL-DB CONNECTION
try :
    conn = MySQLdb.connect(host='vpnp-workstation1', user='root', passwd='123456', db='socwatch',charset='utf8', port=3306)
    cur = conn.cursor()

except Exception,e:
    print "CONNECTION FAILED! ERROR:%s"%e
    sys.exit(0)

table = "soc_data"

raw_file_base_dir = '%s/'%sys.argv[4]
week = sys.argv[3]
week = week.upper()

config = myConfigParser()
config.read("analyze.conf")


########################
# GET csv-file
########################
csvfilelist = config.options('%s-csvfile'%platform)
file_list = list()
for csvfilename in csvfilelist :
    csvfile = config.get('%s-csvfile'%platform, csvfilename)
    file_list.append(csvfile)
print "file_list : %s"%file_list

for csv_filename in file_list :
    csv_file = "%s%s.csv"%(raw_file_base_dir, csv_filename)
    case_name = csv_filename
    print csv_file
    is_file_exist = os.path.exists(csv_file)
    if is_file_exist == False :
        print "file not exist"
        continue
    csvr = csver.csvReader(csv_file)


#####################
### cstate
#####################
#   print csvr.cstate
    category = 'cstate'
    for cs_item in csvr.cstate :
        item_name = cs_item[0]
        core_id = 0
        for cs_value in cs_item[1:]:
            core_num = "core %s"%core_id
            core_id = core_id + 1
            description = "%s#%s#%s#%s#%s#%s"%(week, platform, category, item_name, case_name, core_num)
            value = cs_value
            print description
            if isDescriptInTable(cur, description, table) :
            ### record exist already, need update
                updatetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

                sql="UPDATE %s SET `value`='%s',`updatetime`='%s' WHERE `description`='%s'"%(table, value, updatetime, description)
                print "update:%s"%sql
                cur.execute(sql)

#sql="UPDATE %s SET `platform`='%s', `category`='%s', `item_name`='%s', `case_name`='%s', `core_num`='%s', `value`='%s', `week`='%s' WHERE `description`='%s'"%(platform, category, item_name, case_name, core_num, value, week, updatetime, description)
            else :
            ### record not exist, insert
                init_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                updatetime = init_time
                sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, device, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
                print "insert:%s"%sql
                cur.execute(sql)


###################
### pstate
###################
    category = "pstate"
    freq_num = len(csvr.pstate)/csvr.core_num
    core_id = 0
    item_count = 0
    for ps_item in csvr.pstate :
        item_name = ps_item[1]
        core_num = "core %s"%core_id
        value = ps_item[2]
        description = "%s#%s#%s#%s#%s#%s"%(week, platform, category, item_name, case_name, core_num)

        if isDescriptInTable(cur, description, table) :
        ### record exist already, need update
            updatetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            sql="UPDATE %s SET `value`='%s',`updatetime`='%s' WHERE `description`='%s'"%(table, value, updatetime, description)
            print "update:%s"%sql
            cur.execute(sql)
        else :
        ### record not exist, insert
            init_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            updatetime = init_time
#            sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
            sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, device, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
            print "insert:%s"%sql
            cur.execute(sql)

        item_count = item_count + 1

        if item_count%freq_num == 0 :
            core_id = core_id + 1


#########################
### wakeup/sec/core
#########################
    category = "wakeups"
    item_name ='WU/sec/core'
    core_num = "core ALL"
    description = "%s#%s#%s#%s#%s#%s"%(week, platform, category, item_name, case_name, core_num)
    value = csvr.wakeups

    if isDescriptInTable(cur, description, table) :
    ### record exist already, need update
        updatetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        sql="UPDATE %s SET `value`='%s',`updatetime`='%s' WHERE `description`='%s'"%(table, value, updatetime, description)
        print "update:%s"%sql
        cur.execute(sql)
    else :
    ### record not exist, insert
        init_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        updatetime = init_time
#        sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
        sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, device, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
        print "insert:%s"%sql
        cur.execute(sql)

################
### nc-state
################
    category = "ncstate"
    ncs_list = config.options('%s-ncstate'%platform) 
#    print ncs_list
    for ncs_item in ncs_list :
        row = int(config.get('%s-ncstate'%platform, ncs_item))-1
        if ncs_item == 'Encode' :
            ncs_item = "Video Encoder"
        if ncs_item == 'Decode':
            ncs_item = "Video Decoder"
        value = csvr.get_ncstate_value('D0i3', ncs_item, platform)
        item_name = ncs_item
        core_num = "core ALL"
        description = "%s#%s#%s#%s#%s#%s"%(week, platform, category, item_name, case_name, core_num)

        if isDescriptInTable(cur, description, table) :
        ### record exist already, need update
            updatetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            sql="UPDATE %s SET `value`='%s',`updatetime`='%s' WHERE `description`='%s'"%(table, value, updatetime, description)
            print "update:%s"%sql
            cur.execute(sql)
        else :
        ### record not exist, insert
            init_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            updatetime = init_time
#            sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
            sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, device, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
            print "insert:%s"%sql
            cur.execute(sql)


########################
# GET fps file
########################

    category = "fps"
    item_name ='fps'
    core_num = "core ALL"
    description = "%s#%s#%s#%s#%s#%s"%(week, platform, category, item_name, case_name, core_num)

    fps_prefix = config.get("fpsfile","prefix")
    fps_suffix = config.get("fpsfile","suffix")

    fps_filename = "%s/%s%s%s"%(raw_file_base_dir, fps_prefix, case_name, fps_suffix)
    if os.path.exists(fps_filename) == False:
        value='NONE'
        #pass
    else :
        fps = fpser.FPS(fps_filename, 'render_FPS=[0-9]*\.[0-9]*')
        value = fps.fps

    if isDescriptInTable(cur, description, table) :
    ### record exist already, need update
        updatetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        sql="UPDATE %s SET `value`='%s',`updatetime`='%s' WHERE `description`='%s'"%(table, value, updatetime, description)
        print "update:%s"%sql
        cur.execute(sql)
    else :
    ### record not exist, insert
        init_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        updatetime = init_time
#        sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
        sql="INSERT INTO %s VALUES(null, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"%(table, platform, device, category, item_name, case_name, core_num, value, week, init_time, updatetime, description)
        print "insert:%s"%sql
        cur.execute(sql)

    conn.commit() ### COMMIT OPERATION  [MUST]
    del csvr

cur.close()
conn.close()
print "MYSQL DB CLOSED. JOBS DONE"
