### WEEKLY WORK
    1. Measure the ww07 build power consumption on VV Board and FFRD-PR2
        > Since Haiyang using FFRD to check P1 high issue, the FFRD measure could be ignore
        > Our VV board still have "media audio_policy" problem while bootup in both mainline ww07 and r44b_ww07
        > borrow a vv board from video function team LiZhiyong and do rework on ww07.02 and finished the measurement
        > Haiyang finished the P1 high issue and give me the FFRD, the measurement of WW07 R44B finished
    2. Do the socwatch analysis report of VVBOARD and FFRD

### AUTO VPNP TOOL
    1. [BUG FIXED] program will crash if disable the camera heartbeat
        > since the object variable 'camhb' in vpnp.py will not be define while disable the camera heartbeat in client.conf

