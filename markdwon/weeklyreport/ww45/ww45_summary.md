##WW45 SUMMARY
#####DATE:2013-11-15	AUTHOR: Shaoling

### WEEKLY WORK
	> build new libs for ww45 [AwesomePlayer.cpp | SensorSevice.cpp]
		[STATE DONE]
	> Measure the ww45 build power consumption on VV Board and FFRD-PR2
		[STATE DONE]
			* The video playback 1080p case has a power 1200mw or so, which is 200mw+ higher than it measured
			by team in Indian (970mw or so)
			GRSCD D0i3 always keep 0.00% ( Full state running)
			* New feature[DPST:] was added into the build ww45
			* Set the APMLatency to 5 [file:/etc/powervr.ini] saves about 100mw (1270mw -> 1168mw), comparing
			  with APMLatency = 500
	> Do the socwatch and powerbreakdown measurement and the analysis work
		[STATE DONE]
			* since the vpp errors, the video_playback_frc case was ignored on VV BOARD
			* stream_stock was ignored on FFRD-PR2
			* powerbreakdown was ignored this week
			* Do the socwatch analyze report

	> [GRSCD REGRESSION] flash daily build from 20131104 to 20131108 find the regression of GRSCD
		[STATE - DONE] find the regression was start 2013-11-04
			HaiYang has solved this regression. The video playback 1080p case power (DPST ON and APMLatency = 5) 890mw or so
			stream_chrome 720p power 950.67mw

### AUTO VPNP TOOL
	> [SOCWATCH TOOL UPDATE] The socwatch tool was updated to 1.2.1
		My accout can not access to http://socwatch.intel.com and can not download the SOCWATCH_INTERNAL_1.2.1
		Thanks for Bihuan's help
		I have applied for the access permission and thanks for Darell' access-granting

	> [AUTO VPNP DATA PROCESS]
		> [xls_analyze module] BUG in csver.py
			need adding exception process with case like csv file not exist
			[STATE - DONE]
			This bug is fixed in analyze.py, and I add exception process to csver.py when __init__
			with file not exist

	> [AUTO VPNP TOOL CLIENT]
		> Add new feature auto mode and new video playback case scripts including 1080
			User can make choice of 'Continue | Repeat | Get Data | Get Data And Exit' after each case
			while auto_mode = False

	> [AUTO VPNP TOOL SERVER]
		> Add 'echo.|' in bat files to avoid terminal getting stucked
			remove needless space and tab

	> [AUTO BUILD] update repo && reset the git environment
		[STATE - DONE]
			repo has been updated. however, there is no differences found
			git enviroment has been reseted and tested. It can download code successfully

	> [Gerrit]
		> [AUTO VPNP TOOL CLIENT]
			[STATE - DONE] The client code has been update to the Gerrit Server
				Thanks for haiyang's code review
		> [AUTO VPNP TOOL SERVER]
			[STATE - DONE] The server code has been update to the Gerrit Server
				Thanks for haiyang's code review

		> [PAY ATETTION] Before upload code to Gerrit server, use 'git diff' to check whether there is
			needless space or tabs. remove them before 'git push'


### MISC
	> [DEVICE] rework the USB-RLY08 board with adding eraser to fix the USB line
		[STATE - DONE] Replace eraser with stitching needle to fix the USB line.

	> [NI DEVICE]
		[TASK-1] Noisy of device
			[STATE - DONE] It seems that the case didn't improved, and it is defined as normal phenomenon
		[TASK-2] license of software, waiting for Yu Liu's reply
			[STATE - ON GOING] I contacted with Yu Liu and wait for his reply
				It seems Richard found the license and he is going to reinstall the Labview himself

	> [WW46 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends
	> [ANDROID LEARNING] learning android app development


### TO DO NEXT WEEK
	> [WEEKLY WORK]
		> build new libs for ww46 [AwesomePlayer.cpp | SensorSevice.cpp]
		> Measure the ww45 build power consumption on VV Board and FFRD-PR2
		> Do the socwatch and powerbreakdown measurement and the analysis work

	> [AUTO VPNP TOOL]
		[HEARTBEAT WITH CAMERA]
		[TASK-1] Optimize the image similarity comparsion
		[TASK-2] Design the basic GUI with python Tkinter module

	> [MISC]
		> [ANDROID LEARNING] learning android app development

