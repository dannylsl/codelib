### Weekly work
    Measure the ww51 build power consumption on VV Board and FFRD-PR2
    1. stream chrome crashed in build ww51

### AUTO VPNP TOOL
    _[ POST FLASH]_
        1. change `sleep` to `adb wait-for-device` to make sure that the `adb root` and `adb remount`
            is executed successfully
        2. turn on|off wifi with adb command
            `adb shell svc wifi enable`
            `adb shell svc wifi disable`

