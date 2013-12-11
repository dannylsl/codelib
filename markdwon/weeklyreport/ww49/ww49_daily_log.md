### WEEKLY WORK
    * Measure the ww48 build power consumption on VV Board and FFRD-PR2
        Wifi cannot be enabled:
            The Android Kitkat save wifi AP information into p2p_supplicant.conf and wpa_supplicant.conf
            Push the p2p_supplicant.conf.connected and wpa_supplicant.conf.connected before turn on WIFI
    * Do the socwatch measurement and the analysis work

### AUTO VPNP TOOL

    > [DATA PROCESS]
        1. Add new feature (retrieve fps from fps log file)
        2. README.md modified
        3. Upload to Gerrit Server

    > [DATA COMPARISON] 	
        1. Save data from xls to MySQL database
        _[STATE - DONE]_
        2. Display comparison data on web page

### MISC
    1. Help haiyang check the systrace analyze result of noaudio.wmv
       >  adb root
       >  sudo python systrace.py -t 60 gfx video -o test.html
