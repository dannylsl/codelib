### Weekly work
    Measure the ww51 build power consumption on VV Board and FFRD-PR2
    1. stream chrome crashed in build ww51
    2. VVBOARD need rework or upgrade. The CPU base does not work well. Waiting for Yingpu's support
        YingPu give us a new VV board which flash successfully but still have problem while boot
        It shows 'waiting for audio ...' in adb logcat and get stucked
        This problem start on build ww49
        2013-12-26 the problem located on Audio hardware or related software not exactly

### AUTO VPNP TOOL
    __[ POST FLASH]__
        1. change `sleep` to `adb wait-for-device` to make sure that the `adb root` and `adb remount`
            is executed successfully
        2. turn on|off wifi with adb command
            `adb shell svc wifi enable`
            `adb shell svc wifi disable`
    __[ CAMERA HEARTBEAT ]__
        1. add comboBox on GUI for video device choosing function

### MISC
    1. help Richard change the position of NI machine


### TO DO
    1. do analyze report
    2. camera heartbeat
    3. config class | client | camera HB etc
    4. Gerrit : reposition the comments
    5. download ww52 code

