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
    > camera heartbeat

### 2013-12-19
    > PHP analysis report display

### 2013-12-20
    > Android Framework
