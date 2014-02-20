import socket
import time
import datetime
import os
import sys
import ConfigParser
import signal
import fcntl, struct
import readline
import traceback
import thread
from multiprocessing import Pool

import dev_heartbeat
import dev_camera_hb


def check_net_send(data, recvdata) :
    return True

    if recvdata != data:
        print "recvdata = %s"%recvdata
        return False
    else:
        return True


def net_send(data) :
    client_socket.send(data)
    #recvdata = client_socket.recv(len(data))
    recvdata = client_socket.recv(1024)
    if( check_net_send(data, recvdata) == False) :
        print "%s net_send ERROR"%data
        sys.exit(0)
    else :
        return recvdata


def init_info(info) :
    fill = '$'
    infolen = len(info)
    INFOMAX = 64

    if infolen < INFOMAX :
        info += fill*(INFOMAX - infolen)
    return info


def net_send_with_(data) :
    INFOMAX = 64
    datalen = len(data)
    dataInfo = init_info(str(datalen))
    client_socket.send(dataInfo)
    print "dataInfo = %s"%dataInfo
    client_socket.send(data)
    print "SEND DATA:%s"%data
    recvdataInfo = client_socket.recv(INFOMAX)
    recvdatalen = int(recvdataInfo.strip('$'))
    print "RECV DATA LENGTH = %d"%recvdatalen
    recvdata = client_socket.recv(recvdatalen)
    print "RECV DATA:%s"%recvdata
    return recvdata


def net_recv() :
    recvdata = client_socket.recv()
    print "%s "%recvdata
    return recvdata


def pmpower_reset() :
    print "reset power"

    devshutdown()

    print "power on"
    data = "PMON_ON#"
    svr_ret = net_send(data)


def pmon_reset() :
    print "reset pm"

    devshutdown()

    off_time = 5
    print "wait %d seconds" %off_time
    time.sleep(off_time)

    print "power on"
    data = "PMON_ON#"
    svr_ret = net_send(data)
    print "wait until the lights off"
    time.sleep(20)
    print "power reset done"


def close_server() :
    print "closing server"
    data = "quit#"
    svr_ret = net_send(data)


def is_usb_on() :
    time.sleep(3)
    os.system("./relay8switch.sh lin")
    time.sleep(3)
    print "get usb state"
    adb_tool = os.popen("adb get-state")
    dev_state = adb_tool.read()
    if dev_state == "device\n" :
        print "[USB STATE] USB ON"
        return True
    else :
        print "[USB STATE] USB OFF"
        return False


def usb_on() :
    print "usb on"
    data = "USB_ON#"
    svr_ret = net_send(data)
    time.sleep(3)


def usb_off() :
    print "usb off"
    data = "USB_OFF#"
    svr_ret = net_send(data)
    time.sleep(3)


def new_test() :
    print "new test"
    data = "NEW_TEST#"
    svr_ret = net_send(data)


def mosoon_run(run_case_count, case_time, case_name, count, batch_index) :
    print "mosoon_run CASE_TIME=%d, batch=%s"%(case_time, batch_index)
    data = "MOSOON_RUN#%s#%s#%s#%s#%s#"%(case_time, case_name, count, run_case_count, batch_index)
    svr_ret = net_send(data)


def mosoon_stop() :
    print "mosoon_stop"
    data = "MOSOON_STOP#"
    svr_ret = net_send(data)


def kill_monsoon() :
    print "kill monsoon"
    data = "KILLALLTASK#"
    svr_ret = net_send(data)


def devboot_acs(acs_path, acs_cmd) :
    print "devboot_acs"
    print acs_path
    print acs_cmd

    os.system("cd %s"%acs_path)
    os.system("%s"%acs_cmd)


def devbtnpress(btn_id, press_time) :
    print "trigger button:%s press_time:%s"%(btn_id, press_time)
    os.system("./phonePower on %s"%btn_id)
    time.sleep(press_time)
    os.system("./phonePower off %s"%btn_id)


def dev_btn_powerup(btn_id, press_time) :
    print "dev_btn_powerup"

    devbtnpress(btn_id, press_time)
    time.sleep(5)


def dev_isonline() :
    print "dev is online ?"
    usb_on()
    time.sleep(3)
    print "Trying to get current dev state"
    adb_tool = os.popen("adb get-state")
    dev_state = adb_tool.read()
    print "Current dev state:%s"%dev_state
    if dev_state == "device\n" :
        print "yes"
        return True
    else :
        print "no"
        return False


def dev_isfastbootonline() :
    print "dev is fastboot online ?"
    usb_on()
    time.sleep(3)
    print "Trying to get current dev state"
    adb_tool = os.popen("fastboot devices")
    dev_state = adb_tool.read()
    print "Current dev state:%s"%dev_state
    if ( dev_state.find("fastboot") != -1 ) :
        print "yes"
        return True
    else :
        print "no"
        return False


def devboot_relay8(pw_btn_id, dev_boot_time, plat) :
    print "devboot_relay8"

    dev_heartbeat.heartbeat_set_sleep(True)

    adb_tool = os.popen("adb get-state")
    dev_state = adb_tool.read()
    print "Current dev state:%s"%dev_state
    while 1 :
        print "Current dev state:%s"%dev_state
        #print "ABD REBOOT -P"
        #os.system("adb reboot -p")
        time.sleep(5)

        pmon_reset()
        if( plat == 'BYT' ) :
            dev_btn_powerup(pw_btn_id, 5)
        else :
            dev_btn_powerup(pw_btn_id, 3)

        print "waiting for %ss for device boot"%dev_boot_time
        time.sleep(int(dev_boot_time))

        usb_toggle(True, 5, True)

        time.sleep(5)
        adb_tool = os.popen("adb get-state")
        time.sleep(2)
        dev_state = adb_tool.read()
        print "Current dev state OUTPUT:%s"%dev_state

        print "dev_state len %d" %len(dev_state)

        if dev_state == "device\n" :
            print " device break"
            break
        else:
            print "dev_state != deivce"

    dev_heartbeat.heartbeat_set_sleep(False)
    print "#####################################"
    print "device boot done"
    print "#####################################"


def devshutdown() :
    #this soft shutdown cause block sometimes.
    #print "ADB REBOOT -P"
    #os.system("adb root")
    #time.sleep(2)
    #os.system("adb reboot -p")
    #time.sleep(5)

    print "devshutdown"
    usb_off()
    data = "PMON_OFF#"
    svr_ret = net_send(data)
    time.sleep(20)


def devflashing() :
    print "devflashing"


def devsetup() :
    print "devsetup"


def socwatch_start(case_name, case_time, with_usb) :
    os.system("adb root")
    time.sleep(3)
    os.system("./socwatch/socwatch_start.sh %s %s &"%(case_name, case_time))


def post_process_cases(run_case_count, batch_index) :
    cur_time = time.strftime("%Y%m%d_%H_%M", time.localtime())
    base_dir = "data"
    if os.path.exists(base_dir) == False :
        os.makedirs(base_dir)

    tmp_dir = "data/log"
    if os.path.exists(tmp_dir) == False :
        os.makedirs(tmp_dir)

    path = "data/Batch_%s_%s_R%s"%(batch_index, cur_time, run_case_count)
    if os.path.exists(path) == False :
        os.makedirs(path)

    os.system('./socwatch/data_process.sh %s'%path)


def post_process_single_case() :
    print "post_process_single_case"


def devbootup(plat) :
    os.system("./relay8switch.sh win")
    #Boot up device.
    devboot_relay8(2, 40, plat)
    time.sleep(5)
    #Setup device param.
    devsetup()


def dev_reboot(plat = "MRFLD") :
    devshutdown()
    devbootup(plat)


def usb_toggle(dest_usb_state, try_time, need_reboot) :
    print "###################\tUSB TOGGLE %s\t%s\t%s"%(dest_usb_state, try_time, need_reboot)
    trytime = try_time

    os.system("./relay8switch.sh lin")
    while is_usb_on() != dest_usb_state :
        if(dest_usb_state == True) :
            usb_off()
            usb_on()
        else :
            usb_on()
            usb_off()
        if trytime > 0 :
            trytime -= 1
        elif trytime == 0 :
            if need_reboot == True :
                dev_reboot()
            break
        elif trytime == -1 :
            if (need_reboot == False) :
                continue
            else :
                dev_reboot()


def get_os_version_date() :
    print "GET SYSTEM VERSION"
    os.system("adb shell uname -v > test_case/os_version")


def run_single_case(run_case_count, case_path, count, case_time,
        delay_time, with_usb, with_monsoon, batch_index, img_dir, plat, dpst_on_off, media_file) :
    print "run_single_case"
    print "run_case_count = %s, casepath=%s, caseCount=%d, "\
        "socwatch_time = %d, delay_time = %d, usb = %s, monsoon = %s" \
        %(run_case_count, case_path, count, case_time, delay_time, with_usb, with_monsoon)

    usb_toggle(True, 5, True)
    os.system("./%s_setup %s"%(case_path, dpst_on_off))
    #dpst_on_off = DPSTON | DPSTOFF
    time.sleep(3)

    print "case [%s] setup done"%case_path
    print "case [%s] start"%case_path
    if( with_usb == 'True' ) :
        print "run case and waiting here until complete."

    case_info = case_path.split('/')
    case_name = case_info[1]
#    os.system("./%s_start %s %s %s"%(case_path, case_time, case_name, media_file))
    os.system("./%s_start %s %s"%(case_path, case_name, media_file))

    if( with_monsoon == 'True') :
        socwatch_start(case_name, case_time, with_usb)
    else:
        pass
    print "time sleep 12s after socwatch start"
    time.sleep(12)

    if ( with_usb == 'False' ) :
        usb_toggle(False, 5, True)
        time.sleep(3)

    start_time = datetime.datetime.now()
    if( with_monsoon == 'True') :
        mosoon_run(run_case_count, case_time+20, case_name, count, batch_index)
        print "[MOSOON START] %s"%time.strftime('%Y-%m-%d %H:%M:%S')
        cur_time = datetime.datetime.now()
        print "CASE NAME : %s"%case_name
        while (cur_time - start_time).seconds < case_time :
            if cam_hb_flag == '0' :
                time.sleep(5)
                cur_time = datetime.datetime.now()
                if (cur_time - start_time).seconds > case_time :
                    print "+----------------------+"
                    print "+    CAM HB TURN OFF   +"
                    print "+----------------------+"
                    return 'CAMHB TURN OFF'
                continue;

            if 'idle' in case_name :
                print "====================================== IDLE"
                ret = camhb.check_alive_case_running(True, 5, False, '/tmp/home.jpg' )
            elif 'play' in case_name :
                print "====================================== PLAY"
                ret = camhb.check_alive_case_running(False, 5, False )
            elif 'stream' in case_name :
                print "====================================== STREAM"
                ret = camhb.check_alive_case_running(False, 5, False )
            elif 'record' in case_name :
                print "====================================== RECORD"
                ret = camhb.check_alive_case_running(False, 5, True )

            if ret == 1 :
                print "+----------------------+"
                print "+         ALIVE        +"
                print "+----------------------+"
            elif ret == 2 :
                print "+----------------------+"
                print "+    CRASH NEED CHECK  +"
                print "+----------------------+"
                print "RECHECKING ..."
                if cam_hb_flag == '1' :
                    ret = camhb.crash_recheck(10) #RETURN VALUE 'CRASH' | 'ALIVE'
                if ret == 'CRASH' :
                    return ret
            elif ret == 0 :
                print "+----------------------+"
                print "+         CRASH        +"
                print "+----------------------+"
                return 'CRASH'

            cur_time = datetime.datetime.now()

#       #time.sleep(case_time + 30)
#        time.sleep(case_time/2 + 10)
#        print "get single image with flush buffer: %s.jpg"%case_name
#        if os.path.exists(plat) == False :
#            os.makedirs(plat)
#        camhb.get_single_image_flush_buffer("%s/%s_flush_buffer.jpg"%(plat, case_name))
#        time.sleep(case_time/2 + 20)
#        #mosoon_stop() #mosoon stop controlled by mosoon_run
        usb_toggle(True, 5, False)
        print "[USB ON] %s"%time.strftime('%Y-%m-%d %H:%M:%S')
    else :
#        time.sleep(case_time + 30)
        cur_time = datetime.datetime.now()
        print "CASE NAME : %s"%case_name
        while (cur_time - start_time).seconds < case_time :
            if cam_hb_flag == '0' :
                time.sleep(5)
                cur_time = datetime.datetime.now()
                if (cur_time - start_time).seconds > case_time :
                    print "+----------------------+"
                    print "+    CAM HB TURN OFF   +"
                    print "+----------------------+"
                    return 'CAMHB TURN OFF'
                continue;

            if 'idle' in case_name :
                print "====================================== IDLE"
                ret = camhb.check_alive_case_running(True, 5, False, '/tmp/home.jpg' )
            elif 'play' in case_name :
                print "====================================== PLAY"
                ret = camhb.check_alive_case_running(False, 5, False )
            elif 'stream' in case_name :
                print "====================================== STREAM"
                ret = camhb.check_alive_case_running(False, 5, False )
            elif 'record' in case_name :
                print "====================================== RECORD"
                ret = camhb.check_alive_case_running(False, 5, True )


            if ret == 1 :
                print "+----------------------+"
                print "+         ALIVE        +"
                print "+----------------------+"
            elif ret == 2 :
                print "+----------------------+"
                print "+    CRASH NEED CHECK  +"
                print "+----------------------+"
                print "RECHECKING ..."
                if cam_hb_flag == '1' :
                    ret = camhb.crash_recheck(10) #RETURN VALUE 'CRASH' | 'ALIVE'
                if ret == 'CRASH' :
                    return ret
            elif ret == 0 :
                print "+----------------------+"
                print "+         CRASH        +"
                print "+----------------------+"
                return 'CRASH'

            elif ret == 3 :
                pass

            cur_time = datetime.datetime.now()

#        time.sleep(case_time/2 + 10)
#        camhb.get_single_image_flush_buffer("%s/%s_flush_buffer.jpg"%(plat, case_name))
#        time.sleep(case_time/2 + 20)
#        #keep delay time when with_monsoon = False
#        print "There's no monsoon needed and ran."

    if(img_dir == "") :
        img_dir = get_os_version_date()


    print "case [%s] stop"%case_path
    os.system("./%s_stop %s_rcc_%s_c_%s_batind_%s_imgdir_%s" \
            %(case_path, case_name, run_case_count, count, batch_index, img_dir ))
    print "case [%s] done"%case_path
    return 'ALIVE'


def run_single_case_loop(rid, case_path, case_count, case_runtime,
    delay_time, heartbeat_enable, with_usb, with_monsoon, batch_index, img_dir, plat, dpst_on_off, media_file) :

    print "RUN SINGLECASE LOOP"
    loop = 0
    while True:
        print "WHILE LOOP = %s"%loop
        loop = loop + 1

        #Boot up device.
        os.system("./relay8switch.sh win")
        devbootup(plat)

        #Run single case.
        print "#########################################"
        print "Current case is : %s"%case_path
        #Run single case.

        ## UI state check with camera before case runing
        if cam_hb_flag == '1' :
            camhb.check_alive()
            ui_state = camhb.get_ui_state()

        if ( ( heartbeat_enable == True ) and
            ( dev_heartbeat.heartbeat_device_state() == False ) ) :
            print "There's_heartbeat, but failed..."
            continue
        elif cam_hb_flag == '1' and ui_state == False :
            print "Camera heartbeat enabled but It seems the ui_state crashed"
            continue
        else :
            ret = run_single_case(rid, case_path, case_count, case_runtime, \
                delay_time, with_usb, with_monsoon, batch_index, img_dir, plat, dpst_on_off, media_file)
        print "==="*10,"=>"
        print "ret=%s"%ret
        print "==="*10,"=>"
        if ret == 'CRASH' :
            kill_monsoon()
            continue
        #Generate report etc.
        post_process_single_case()

        ## UI state check with camera after case runing
        if cam_hb_flag == '1' :
            camhb.check_alive()
            ui_state = camhb.get_ui_state()
            if ui_state == True :
                print " CASE RUNNING OK, CONTINUE TO NEXT ...  "
                break
        elif cam_hb_flag == '0' :
            print " CAM HB TURNED OFF, CONTINUE TO NEXT ...  "
            break

## ERROR JUDGEMENT TO DELETE
#        if( heartbeat_enable == False ) :
#            print "There's_no_heartbeat..."
#            break

        if( dev_heartbeat.heartbeat_device_state() == True ) and (heartbeat_enable == True ):
            break

    #end While True


def voice2notice() :
    global voice_flag
    print '[THREAD CREATE] VOICE TO NOTICE'
    count = 3
    while (count > 0 and voice_flag == True) :
        print "count = %s voice_flag = %s"%(count, voice_flag)
        os.system('ffplay -nodisp post_flash/resource/mp3/caseDone.mp3 -autoexit >> voice_log')
        count = count - 1
        time.sleep(10)
    print '[THREAD EXIT] VOICE TO NOTICE'
    voice_flag = True
    thread.exit_thread()



#Run all case
def run_all_cases(heartbeat_enable, run_case_count, batch_index, img_dir, plat, dpst_on_off, auto_mode) :
    global voice_flag
    print "######################################################"
    print "run_all_cases"

    devshutdown()
    test_cases = []
    #Getting all the usecase from config file.
    file = open("test_cases.conf", "r")
    test_cases = file.readlines()

    print test_cases

    #Run all case
    rid = 1
    while rid <= run_case_count :
        for test_case in test_cases:
            key = test_case.split(":")
            if (key[0][0] == '#' or len(key) < 5) :
                continue
            print "###### key :%s" %key
            key_len = len(key)
            print "test case string lenth is %s" %(key_len)

            #Below 2 lines are for debug
            #for i in range(0, int(key_len)) :
            #   print key[i]

            case_path = key[0]
            case_count = 1
            case_name = key[0].split("/")

            delay_time = int(key[3]) - int(key[2])
            if (delay_time <= 0) :
                delay_time = 10
            print "USB off time is: %s"%delay_time
            case_runtime = int(key[3])
            print "Case running time is: %s"%case_runtime
            with_usb = key[4]
            print "Ruing with USB ? :%s "%with_usb
            with_monsoon = key[5]
            print "Ruing with MONSOON ? :%s "%with_monsoon
            media_file = key[6]
            print "Media File : %s"%media_file
            while True :
                flag_exit = True
                run_single_case_loop(rid, case_path, case_count, case_runtime,
                    delay_time, heartbeat_enable, with_usb, with_monsoon, batch_index, img_dir, plat, dpst_on_off, media_file)
                if auto_mode == 'True' :
                    break

                while True :
                    thread.start_new_thread(voice2notice, ())
                    operate = raw_input("Continue | Repeat | Get Data | Get data and exit?(c/r/g/ge):")
                    if operate == 'c' :
                        voice_flag = False
                        flag_exit = True
                        break
                    elif operate == 'r' :
                        voice_flag = False
                        flag_exit = False
                        break
                    elif operate == 'g' :
                        voice_flag = False
                        post_process_cases(rid, batch_index)
                    elif operate == 'ge' :
                        voice_flag = False
                        post_process_cases(rid, batch_index)
                        devshutdown()
                        return
                    else :
                        print "Error Input"
                        continue
                if flag_exit == True :
                    break
                else :
                    continue
        #end of for test_case in test_cases

        #Generate report etc.
        post_process_cases(rid, batch_index)

        #Shutdown device for next case.
        devshutdown()

        rid = rid + 1


def run_heartbeat(port, baudrate, heartbeat_cfg) :
    print "RUN HEARTBEAT"
    if( heartbeat_cfg == '1' ) :
        print "With heartbeat"
        thread.start_new_thread(dev_heartbeat.heartbeat_serial, (port, baudrate))
        return True
    print "Without heartbeat"
    return False


def thread_usb_switch() :
    print "thread usb switch"
    usb_off()
    pmpower_reset()
    time.sleep(7)
    usb_on()


def run_usb_switch() :
    print "run usb switch"


def init_power_states_for_win() :
    print "Init power states for win"
    os.system("./relay8switch.sh lin")
    devshutdown()


def run_usb_switch_win() :
    print "run usb switch win"
    os.system("./relay8switch.sh win")


def auto_flash_linux_recovery(cmd_wget_img, file_img, image_folder) :
    print "##########################################"
    print "AUTO FLASH Linux"

    os.system("./relay8switch.sh lin")
    time.sleep(5)
    img_file_path = "img/" + image_folder + "/" + file_img
    print "img file path:%s"%img_file_path
    if( os.path.exists(img_file_path) == False) :
        os.system(cmd_wget_img)
    else :
        print "img exist alreay."

    full_dir = "img/" + image_folder
    if os.path.exists(full_dir) == False :
        os.makedirs(full_dir)
        os.system("mv %s img/%s/"%(file_img, image_folder))
    else :
        print "Ignore downloading. File exists already."
    run_usb_switch()
    time.sleep(30)
    print "full dir:%s"%full_dir
    cur_dir = os.getcwd()
    print "old dir:%s"%cur_dir
    old_dir = cur_dir
    os.chdir(full_dir)
    cur_dir = os.getcwd()
    print "cur dir:%s"%cur_dir
    if( file_img.find("blankphone") != -1 ) :
        print "flashing blankphone"
        os.system("cflasher -f %s -x flash-EraseFactory.xml --reboot 1 -l 5"%(file_img))
    else :
        print "flashing fastboot"
        os.system("cflasher -f %s -x flash.xml"%(file_img))
        time.sleep(30)
    os.chdir(old_dir)
    cur_dir = os.getcwd()
    print "cur dir:%s"%cur_dir


def auto_flash_linux(cmd_wget_img, file_img, image_folder) :
    print "##########################################"
    print "AUTO FLASH Linux"

    os.system("./relay8switch.sh lin")
    time.sleep(5)
    img_file_path = "img/" + image_folder + "/" + file_img
    print "img file path:%s"%img_file_path
    if( os.path.exists(img_file_path) == False) :
        os.system(cmd_wget_img)
    else :
        print "img exist alreay."

    full_dir = "img/" + image_folder
    if os.path.exists(full_dir) == False :
        os.makedirs(full_dir)
        os.system("mv %s img/%s/"%(file_img, image_folder))
    else :
        print "Ignore downloading. File exists already."
    os.system("cflasher -f %s/%s"%(full_dir, file_img))


def auto_flash_windows(url, file_img, image_folder) :
    print "##########################################"
    print "AUTO FLASH Windows"

    print "[ WINDOWS AUTO FLASH START ] %s"%time.strftime('%Y-%m-%d %H:%M:%S')
    print "[ AUTO_FLASH SEND PARAMETERS ] #%s#%s#%s#"%(url, file_img, image_folder)

    data = "AUTO_FLASH#%s#%s#%s#"%(url, file_img, image_folder)
    svr_ret = net_send(data)
    print svr_ret
    ret_code = svr_ret.split('#')[1]
    if (ret_code == "OKAY") :
        return True
    elif (ret_code == "ERR") :
        return False


def switch_usb_win() :
    usb_off()
    os.system("./relay8switch.sh win")
    data = "CHECKDEVSTATE#"
    check_dev_state = net_send(data)
    dev_state = check_dev_state.split('#')[1]
    if (dev_state == "OKAY") :
        return True
    elif (dev_state == "ERR") :
        return False


def dev_reboot_for_flash_win(platform) :
    print "####################################"
    print "dev_reboot_for_flash_win %s"%platform

    if (platform == "BYT") :
        os.system("./relay8switch.sh win")
        usb_off()
        if ( switch_usb_win() == True ) :
            return True

        dev_boot_loop = 0

        while ( switch_usb_win() == False ) :

            print "Device is not online, trying to reboot."
            dev_reboot(platform)
            os.system("./relay8switch.sh win")
            usb_off()
            print "dev_reboot_for_flash_win %s, dev boot done."%platform
            if ( switch_usb_win() == True ) :
                break
            else :
                dev_boot_loop = dev_boot_loop + 1
                #os.system("./relay8switch.sh lin")
                #usb_on()
                if ( dev_boot_loop >= 5 ) :
                    print "dev_boot_loop >= 5 BYT"
                    return False

    elif (platform == "MRFLD") :
        if ( flash_by_linux == 'False' ) :
            init_power_states_for_win()

    return True


def auto_flash(heartbeat_enable, r_c_c, flash_by_linux, platform, dpst_on_off, auto_flash_count, flash_only, auto_mode) :
    print "##########################################"
    print "AUTO FLASH"
    image_cfg            = ConfigParser.ConfigParser()
    image_cfg.read('image.conf')
    image_number         = image_cfg.get('image_list', 'image_number')
    image_skip_number    = int(image_cfg.get('image_list', 'skip_number'))
    print "The number of images: %s, skip: %d"%(image_number, image_skip_number)


    for k in range(1, int(auto_flash_count) + 1) :
        print ">>>>>>>>>>>>>>>>>> loop k =%d/%d <<<<<<<<<<<<<<<<<<<<<<<<<<"%(k, int(auto_flash_count) )
        print "[AUTO FLASH TEST] %s"%time.strftime('%Y-%m-%d %H:%M:%S')
        k = k + 1
        for i in range(1, int(image_number) + 1) :
            print "i = %d"%i
            if ( i < (image_skip_number + 1) ) :
                continue

            if( dev_reboot_for_flash_win(platform) == False) :
                return

            for j in range(1, 3) :
                print "j = %d"%j

                print "AUTO FLASH, scan image..."
                image_m_n = "image_%d_0"%(i)
                image_folder = image_cfg.get('image_list', image_m_n)
                print "image folder:%s"%image_folder
                #
                image_m_n = "image_%d_%d"%(i, j)
                url_m_n = image_cfg.get('image_list', image_m_n)
                print "downloading :%s, %s"%(image_m_n, url_m_n)
                cmd_wget_img = "wget %s"%url_m_n
                print cmd_wget_img
                #
                index = url_m_n.rfind('/')
                file_img = url_m_n[index + 1 : len(url_m_n)]
                print "file img:%s"%file_img
                #
                flash_loop = 0
                ignore_flag = False
                if( flash_by_linux == 'True' ) :
                    auto_flash_linux_recovery(cmd_wget_img, file_img, image_folder)
                else :
                    run_usb_switch_win()
                    print "url_mn:%s"%url_m_n
                    print "file_img:%s"%file_img
                    print "image_folder:%s"%image_folder
                    while( auto_flash_windows(url_m_n, file_img, image_folder) == False ) :
                        print "Flashing err, redo reflash."
                        flash_loop = flash_loop + 1
                        if( flash_loop > 5 ) :
                            print "########################################"
                            print "fatel err with this version. ignore it."
                            print "########################################"
                            ignore_flag = True
                            break

                        if( platform == "BYT") :
                            print ">>>>>>>>>>>  BYT FLASH FAILED <<<<<<<<<<<"
                            return

                if( ignore_flag == True) :
                    print "image ignored"
                    break

            print "##########################################"
            print "flash done, right or wrong"
            print "##########################################"

            print "#### SWITCH USB TO WINDOWS BEFORE REBOOT ####"
            os.system("./relay8switch.sh win")
            dev_reboot(platform)
            os.system("./relay8switch.sh lin")
            usb_toggle(True, 5, True)

            if (flash_only == 'False') :
                cur_dir = os.getcwd()
                os.chdir("post_flash")
                os.system("./post_flash.sh %s"%platform)
                os.chdir(cur_dir)
                os.system("pwd")
                time.sleep(3)
                run_all_cases(heartbeat_enable, r_c_c, i, image_folder, platform, dpst_on_off, auto_mode)
                print "case done, pls pulling data first"
                time.sleep(10)
            else :
                print "FLash only Done"


# host = win or lin
def param_check_usb_switch(host) :
    if(host == "win") :
        os.system("./relay8switch.sh win")
    elif(host ==  "lin") :
        os.system("./relay8switch.sh lin")
    else:
        print "Error paramerter!"
    sys.exit(0)


def param_check_boot_up_only(platform) :
    print "[ POWER ON ONLY ]"
    pmpower_reset()
    devboot_relay8(2, 40, platform)
    print "[ POWER ON ONLY DONE ]"
    sys.exit(0)


def param_check(platform) :
    print "[ parameters check ]"
    if(len(sys.argv) == 2 ) :
        if(sys.argv[1] == "bootuponly") :
            param_check_boot_up_only(platform)
        elif(sys.argv[1] == "usb2win") :
            param_check_usb_switch("win")
        elif(sys.argv[1] == "usb2lin") :
            param_check_usb_switch("lin")
        else:
            print "PARAMETER UNDEFINED!"
            print "Usage: %s [bootuponly | usb2win | usb2lin]"%sys.argv[0]
            sys.exit(0)
    elif(len(sys.argv) == 1) :
        print "RUN PMBOT WITHOUT PARAMETER"
    else :
        print "Parameters Invalid!"
        sys.exit(0)


def ttyACM0_setup() :
    if os.path.exists('/dev/ttyUSB0') == False :
        print "=====" * 5
        print "   USB PLUGIN DISCONNECTED"
        print "=====" * 5
        sys.exit(0)
    else :
        if os.path.exists('/dev/ttyACM0') == False :
            print "Creating /dev/ttyACM0 ..."
            os.system("sudo ln -s /dev/ttyUSB0 /dev/ttyACM0")
            time.sleep(2)
            if os.path.exists('/dev/ttyACM0') == True :
                print "=====" * 5
                print "ttyACM0 CREATED!"
                print "=====" * 5
            else :
                print " TAT " * 5
                print "Failed to create ttyACM0, please check reason manually "
                print " TAT " * 5
                sys.exit(0)
        else:
            print "=====" * 5
            print "ttyACM0 SETUP ALREADY"
            print "=====" * 5


#### GLOBAL VARIBALE

voice_flag = True

##########################################################
# MAIN
##########################################################

if __name__ == '__main__' :

    if os.path.exists('/dev/ttyACM0') == False :
        ttyACM0_setup()
    config          = ConfigParser.ConfigParser()
    config.read('client.conf')

    server                  = config.get('config', 'server')
    port                    = config.get('config', 'port')
    r_c_c                   = int(config.get('config', 'run_case_count'))
    run_case_only           = config.get('config', 'run_case_only')
    flash_by_linux          = config.get('config', 'auto_flash_by_linux')
    platform                = config.get('config', 'platform')
    dpst_on_off             = config.get('config', 'dpst')
    auto_flash_count        = config.get('config', 'auto_flash_count')
    flash_only              = config.get('config', 'flash_only')
    auto_mode               = config.get('config', 'auto_mode')
    # HEARTBEAT SETTING
    s_hb_flag               = config.get('heartbeat', 'serial')
    cam_hb_flag             = config.get('heartbeat', 'camera')
    # SERIAL SETTING
    s_port                  = config.get('serial', 'port')
    s_baudrate              = config.get('serial', 'baudrate')
    # CAMEAR SETTING
    cam_dev                 = config.get('camera', 'device')
    cam_width               = int(config.get('camera', 'width'))
    cam_height              = int(config.get('camera', 'height'))



    print server

    print 'Waiting to connect to windows m/c..'
    # Blocks if lock is already acquired by some other process

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.settimeout(30000)
    client_socket.connect((server, int(port)))
    client_socket.settimeout(None)
    print "Connected to %s" %(server)


    # NET_TEST
    new_test()

    param_check(platform)

    # ENABLE SERIAL HAERTBEAT FOR KERNEL STATE CHECK
    heartbeat_enable = run_heartbeat(s_port, s_baudrate, s_hb_flag)
    # ENABLE CAMERA HEARTBEAT FOR UI STATE CHECK
    if cam_hb_flag == '1' :
        camhb = dev_camera_hb.cameraHB(cam_dev, cam_width, cam_height)


    # Run all cases.
    print "Run case only: %s"%run_case_only
    if ( run_case_only == 'False' ) :
        auto_flash(heartbeat_enable, r_c_c, flash_by_linux, platform, dpst_on_off, auto_flash_count, flash_only, auto_mode)
    else :
        run_all_cases(heartbeat_enable, r_c_c, 1, "", platform, dpst_on_off, auto_mode)

    # Quit
    time.sleep(5)
    close_server()

    print "all done"

    client_socket.shutdown(socket.SHUT_RDWR)
    client_socket.close()
    print "bye bye."
    sys.exit(0)
