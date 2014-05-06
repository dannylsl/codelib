import os
import time

print "ADB SHELL GETPROP RO.BOOTMODE"
adb_bootmode = os.popen("adb shell getprop ro.bootmode")
time.sleep(2)
bootmode = adb_bootmode.read()

print "BOOTMODE_DETECT=",bootmode
bootmode = bootmode.strip()

if bootmode == "charger":
    print "CHARGER WITH ENTER"
elif bootmode == "main":
    print "MAIN"
else :
    print "[%s]"%bootmode


