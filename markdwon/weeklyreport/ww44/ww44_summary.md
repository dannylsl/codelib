##WW44 SUMMARY
#####DATE:2013-11-08		AUTHOR: Shaoling

### WEEKLY WORK
	[FFRD-2]
		> Measure the power consumption, do the socwatch analyze report
		> [RECORD-1080P-FPS] The fps of the record file from record social 1080p case, drop to
			24.25fps only, while HaiQiang measure it with 29.868fps. Try to find the reason or
			solution.
			ADD: This issue is talk about on the weekly sync. and richard say it is affected by 
			the light. I did a simple experiment as below
				* run record_social_1080p case under shadow, fps = 16.638
				* run record_social_1080p case under light, fps = 29.97
			It is the reason

	[VV BOARD]
		> Measure the power consumption, do the socwatch analyze report
		> Measure the power breakdown data and the analyze report

### AUTO VPNP TOOL
	> [FPS-TAKEN SCRIPT]
		[STATE - DONE] 2013-11-07
		It seems the fps-taken shell-script failed to take the fps. check it tomorrow 2012-11-07
		The reason why the fps-taken shell-script did not work is that the vpnp.py ignore the process
		when the feature "with_monsoon" = 'False'. The right way is keeping the time delay process. 
		The code is updated to gerrit server and have been code review by Haiyang, Thanks for Haiyang's 
		suggestion

	> [AUTO DATA PROCESS]
		[STATE DONE]
		Finish the csv analyze script which extract data needed from csv file and fill it into xls file

	> [AUTO VPNP]
		[STATE - ON GOING]
		[HEARTBEAT WITH CAMERA]
		> [TASK-1] images' similarity comparsion
			[STATE - ON GOING]
			Find some python code to do this, however, the time-consume is a little long. about 7 seconds
			while comparing two images with the size 640*480. *NEED SOME OPTIMIZATION*

		> [TASK-2] design the basic GUI with python Tkinter module
			[STATE - NOT START]
	
### MSIC
	> [STOCK BROWSER] ask Haiqiang for help to check stock browser state on camera team VV Board 
		Our VV Board failed to lanuch stock browser with settings as below
			Power-up current limit > 5A
			the others keep default
		when set the Run-time current limit to Maximum, it works
		[STATE DONE]
			The stock browser can be launched successfully on camera team VV Board with flashing setting 
			mentioned above
				Power-up current limit > 5A
				the others keep default
			As for the reason, I can not catch it, I will pay attention to it in the feature

	> [DEVICE] rework the USB-RLY08 board with adding eraser to fix the USB line
	> [samba] set up a samba server on vpnp-workstation1 to share the weekly data ( including raw data and anaylze report)
		windows access to \\vpnp-workstation1\vpnp_data
	> [NI DEVICE] contact NI Service Engineer for the noisy from our NI Device [PXI-1045]
		NI Service Engineer: Yu Liu  Email: Yu.liu@ni.com	Mobile: 15810676483	
		Yu Liu has helped us to replace the strainer of our NI Device, It sounds a little better from my point of view	
		As for the software license, Yu Liu promised he will ask his mate do us a favor next week. 
		*KEEP TRACKING THIS ISSUE*

	> [WW45 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends
	> [ANDROID LEARNING] start learning android app development

### TO DO NEXT WEEK
	> [WEEKLY WORK]
		> build new libs for ww45 [AwesomePlayer.cpp | SensorSevice.cpp]
		> Measure the ww45 build power consumption on VV Board and FFRD-PR2
		> Do the socwatch and powerbreakdown measurement and the analysis work

	> [AUTO VPNP TOOL] 
		[HEARTBEAT WITH CAMERA]
		[TASK-1] Optimize the image similarity comparsion
		[TASK-2] Design the basic GUI with python Tkinter module

	> [MISC]
		> [ANDROID LEARNING] start learning android app development
		> [NI DEVICE]
			[TASK-1] Noisy of device
			[TASK-2] license of software, waiting for Yu Liu's reply

