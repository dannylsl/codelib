##WW50 SUMMARY
#####DATE:2013-12-23    AUTHOR: Shaoling
=======================

## Weekly work
    Measure the ww50 build power consumption on VV Board and FFRD-PR2
    1. FRC failed on Both VVBoard and FFRD with 29fps measured since the Merrifield MR1 upgrade
        Solution: http://android.intel.com:8080/#/c/151141/3
        However the patch cannot git into build ww50. the base code are quit different.
        Haiyang give me an new pre-intergrate build which works. FPS = 59.668938
        Thanks for Wang Kun K and Haiyang's help
    2. [BUG FIXED] post flash remove the SetupWizard which leads to a series crash
        Try to find a new way to skip SetupWizard
    3. [WW51 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends

### AUTO VPNP TOOL
   * DATA PROCESS
        1. Add new class mediafps to get frame rate from mediainfo log

   * CLIENT
        1. socwatch/data_process.sh: get record media information as file named "mediainfo_mp4_record"
            with mediainfo command
        2. basic camera heartbeat was added and tested
        [STATE ON GOING] A problem while get_single_image() in check_alive()
            we have to run three times get_single_image() to flush the camera buffer.
            The question was post to stackoverflow and waiting for answer

### Gerrit
    Gerrit upload xls_analyze and auto_vpnp client part to Gerrit Server
    Thanks for haiyang's code review

### MISC
    1. help haiyang check the BUG#157594. Power Comparison of 30fps and 60fps video playback between
    bypass build and non-bypass build
        More information refers to http://umgbugzilla.sh.intel.com:41006/show_bug.cgi?id=157594
    2. Retrieve Interrupt information with socwatch tools
       Command : ./socwatch -f intr -t 10   Version:1.2.1
    3. Read parts of Sensor code in Android Framework
    4. Help Wang kun check VPP optimazation on build 20131217_2078
    5. Help Haiyang retrieve ww50 FRC && ww50 stream_chrome && ww49 stream_chrome powerbreakdown data
    6. Thanks Jena, Preeti RanjanX for sharing "SPMaccelerometerControl.apk" to rotate chrome
        Usage:
            1. adb root
            2. adb shell
            3. am start -a android.intent.action.MAIN -n com.intel.spm.accelerometercontrol/.SPMaccelerometerControl --es accelerometer 0 --es user_rotation 1
        It helps the stream cases on VVBOARD
    7. Take part in the preparation conference for REPORT conference on 2013-12-20
    8. Help haiyang check Bug#159025 Power consumption in all video streaming cases has regressed on ww50
    9. Take part in and do support for the REPORT CONFERENCE OF wearable device

### TO DO NEXT WEEK

    * [WEEKLY WORK]
        > Measure the ww51 build power consumption on VV Board and FFRD-PR2
        > Do the socwatch measurement and the analysis work && do powerbreakdown if possible
        > [WW52 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends

    * [AUTO VPNP TOOL]
        [HEARTBEAT WITH CAMERA]
        > Add camera heart during the case runing
        > Speed up the image similarity calculation
        [Camera heartbeat GUI]
            1. select camera device function for camera device auto detection
                choosing /dev/video0 /dev/video1 etc
            2. draw rect on image to specify section for image similarity calculation

    * [AUTO VPNP DATA PROCESS]
        [DATA COMPARISON]
        > Display comparison data on web page

    * Reading Android code of Sensor Part
