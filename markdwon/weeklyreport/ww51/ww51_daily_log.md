### Weekly work
    Measure the ww51 build power consumption on VV Board and FFRD-PR2
    1. stream chrome crashed in build ww51
    2. VVBOARD need rework or upgrade. The CPU base does not work well. Waiting for Yinpu's support

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
