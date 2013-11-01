##WW43 SUMMARY	
#####DATE:2013-11-01		AUTHOR: Shaoling

### WEEKLY WORK
	[FFRD-PR2]
		> Measure the power consumption, do the socwatch analyze report.
		> [AUTO-SHUTDOWN] when flashing build with 3.8V, the device is easily to shutdown itself.
			This issue is solved by increasing the flash voltage to 4.2V
		> [STOCK BROWSER] The stock browser cannot be launched when flashing with settings as below
			[Power Tool Setting -> Parameters] set all the limit to maximum
			change them as below, and the stock browser works well
			[Power Tool Setting -> Parameters] 'Power-up current limit' > 5A && keep others as default

	[VV BOARD]
		> Measure the power consumption, do the socwatch analyze report.
		> Measure the powerbreakdwon data and do the analyze report.
		> [STOCK BROWSER] The stock browser cannot be launched when flashing with settings as below
			[Power Tool Setting -> Parameters] 'Power-up current limit' > 5A && keep others as default
			change them as below, and the stock browser works well
			[Power Tool Setting -> Parameters] 'Power-up current limit' > 5A && set the run-time current limit to maximum

###  AUTO VPNP TOOL
	[Gerrit]
		> Finish the code review and push it to the Gerrit Server
		> remove the needless space and tab from the code and update it

	[HEARTBEAT WITH CAMERA]
		> [FINISHED] take a capture frome camera [FINISH with pygame module]
		> [NOT START] design the basic GUI with python Tkinter module

	[AUTO DATA PROCESS]
		[STATE - ON GOING] get stuck when getting exact data from csv

	[FPS-TAKEN SCRIPT]
		> [FINISHED] write the fps-taken shell-script and test it


### MSIC
	> Cut the media file to 3~4min time long with ffmpeg
	> modify the AwesomePlayer.cpp to build new lib for fps measurement


### TO DO NEXT WEEK
	> [WEEKLY WORK]
		> Measure the ww44 build power consumption on VV Board and FFRD-PR2
		> Do the socwatch and powerbreakdown measurement and the analysis work

	> [AUTO VPNP]
		[HEARTBEAT WITH CAMERA]
		> [CONTINUE WORK] design the basic GUI with python Tkinter module

	> [AUTO DATA PROCESS]
		[CONTINUE WORK] get stuck when getting exact data from csv

	> [MSIC] ask Haiqiang for help to check stock browser state on camera team VV Board 
		Our VV Board failed to lanuch stock browser with settings as below
			Power-up current limit > 5A
			the others keep default
		when set the Run-time current limit to Maximum, it works

