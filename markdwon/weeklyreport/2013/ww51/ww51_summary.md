##WW51 SUMMARY
#####DATE:2013-12-30    AUTHOR: Shaoling

### Weekly work
    Measure the ww51 build power consumption on VV Board and FFRD-PR2
    1. stream chrome crashed in build ww51
    2. VVBOARD need rework or upgrade. The CPU base does not work well. Waiting for Yingpu's support
        YingPu give us a new VV board which flash successfully but still have problem while boot
        It shows 'waiting for audio ...' in adb logcat and get stucked
        This problem start on build ww49
        2013-12-26 the problem located on Audio hardware or related software not exactly
        2013-12-30 This phenomenon disappeared on build ww52. It should be caused by the driver upgrade

    3. [WW52 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends

### AUTO VPNP TOOL
    __[ POST FLASH]__
        1. change `sleep` to `adb wait-for-device` to make sure that the `adb root` and `adb remount`
            is executed successfully
        2. turn on|off wifi with adb command
            `adb shell svc wifi enable`
            `adb shell svc wifi disable`
    __[ CAMERA HEARTBEAT ]__
        1. add comboBox on GUI for video device choosing function
        2. add function that drawing areas on the canvas
        3. add a config class `hb_camera_config.py` to process the areas


### MISC
    1. help Richard change the position of NI machine


### TO DO NEXT WEEK
    * [WEEKLY WORK]
        > Measure the ww51 build power consumption on VV Board and FFRD-PR2
        > Do the socwatch measurement and the analysis work && do powerbreakdown if possible
        > [WW01 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends

    * [AUTO VPNP TOOL]
        [HEARTBEAT WITH CAMERA]
        > Add camera heart during the case runing
        __[STATE - ONGOING]__
        > Speed up the image similarity calculation
        __[STATE - ONGOING]__
        [Camera heartbeat GUI]
            1. draw rect on image to specify section for image similarity calculation
            __[STATE ONGOING]__ hb_camera_config.py has finished the config class
                Integrate it into hb_camera.py

    * [AUTO VPNP DATA PROCESS]
        [DATA COMPARISON]
        > Display comparison data on web page
