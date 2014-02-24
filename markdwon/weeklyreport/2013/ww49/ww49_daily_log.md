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

    > [POST FLASH]
        1. Add function to auto find SetupWizard location and remove them in Merrifield.sh
            Google has changed the SetupWizard location from /system/app to /system/priv-app
        2. Add a new parameter in test_cases.conf represents related media_file if needed
        3. Change the way to play a video using a absolute path with play a video by passing argument
         in video_playback cases
        4. Add new function in post_flash to push media file related with cases to be run, there is no
         need push all media file
            Note: Haiyang has found the tranform speed is extremely high in USB Storage Mode

### MISC
    1. Help haiyang check the systrace analyze result of noaudio.wmv
       >  adb root
       >  sudo python systrace.py -t 60 gfx video -o test.html
    2. Shell-learning sed | awk

