## Weekly work
    Measure the ww50 build power consumption on VV Board and FFRD-PR2
    1. FRC failed on Both VVBoard and FFRD with 29fps measured since the Merrifield MR1 upgrade
        Solution: http://android.intel.com:8080/#/c/151141/3
        However the patch cannot git into build ww50. the base code are quit different.
        Haiyang give me an new pre-intergrate build which works. FPS = 59.668938
        Thanks for Wang Kun K and Haiyang's help
    2. [BUG FIXED] post flash remove the SetupWizard which leads to a series crash
        Try to find a new way to skip SetupWizard

### MISC
    1. help haiyang check the BUG#157594. Power Comparison of 30fps and 60fps video playback between
    bypass build and non-bypass build
        More information refers to http://umgbugzilla.sh.intel.com:41006/show_bug.cgi?id=157594
    2. Retrieve Interrupt information with socwatch tools
       Command : ./socwatch -f intr -t 10   Version:1.2.1
    3. Read parts of Sensor code in Android Framework

### AUTO VPNP TOOL
   * DATA PROCESS
        1. Add new class mediafps to get frame rate from mediainfo log

   * CLIENT
        socwatch/data_process.sh: get record media information as file named "mediainfo_mp4_record"
        with mediainfo command

### 2013-12-18
    > camera heartbeat [STATE NOT START]
    > Gerrit upload xls_analyze and auto_vpnp client part to Gerrit Server
        Thanks for haiyang's code review
    > Help Wang kun check VPP optimazation on build 20131217_2078
    > Help Haiyang retrieve ww50 FRC && ww50 stream_chrome && ww49 stream_chrome powerbreakdown data
    > Thanks Jena, Preeti RanjanX for sharing "SPMaccelerometerControl.apk" to rotate chrome
        Usage:
            1. adb root
            2. adb shell
            3. am start 0a android.intent.action.MAIN -n com.intel.spm.accelerometercontrol/.SPMaccelerometerControl
                --es accelerometer 0 --es user_rotation 1

### 2013-12-19
    > PHP analysis report display

### 2013-12-20
    > Android Framework
