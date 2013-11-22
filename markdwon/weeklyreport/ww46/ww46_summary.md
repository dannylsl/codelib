##WW46 SUMMARY
#####DATE:2013-11-22	AUTHOR: Shaoling

### WEEKLY WORK
	> build new libs for ww46 [AwesomePlayer.cpp | SensorSevice.cpp]
		[STATE - DONE]
	> Measure the ww46 build power consumption on VV Board and FFRD-PR2
		[STATE - DONE]
			* need to add new fps-taken case of stream and video playback 1080p 720p 60fps
			* It seems the VPP does not always take effect and we would better play the clip to the end
				while measuring a video playback case
				Haiyang recommands to open the log output, rebuild and replace libs to check whether VPP works
				[VPP SETTINGS LIBS BUILD ORDER]
					ORDER:
					1. modify /vendor/intel/hardware/libmedia_utils/VPP/VPPWorker.cpp [configFilter()] && VPPProcessor.cpp [constrution]
					2. compile vpp
					3. libstagefright
					4. libmediaplayerservice
					Here comes a new problem while executing the make command 'mm -B'	
					It works at the first time and failed at the second time, even though you remove the 
					related out files and folders
				
	> Do the socwatch and powerbreakdown measurement and the analysis work
		[STATE - DONE]
			* SOCWATCH measurement and analysis work have been done on both VV BOARD and FFRD-PR2.
			* powerbreakdown case was ignored on VV BOARD since the Labview license issue 
			* new cases [ video_playback_720p_60fps_fps_stagefright | video_playback_1080p_60fps_fps_stagefright ] added
			* add video_playback_common_setup | video_playback_common_start | video_playback_common_stop shell-scripts
			* change the time when execute the dumpsys command to catch the correct dumpsys

### AUTO VPNP TOOL
	[POST FLASH]
		> add 'socwacth_on_dev.sh' shell script as a common interface to run socwatch tool in different cases by pass parameters[ case_time | case name ]

	[CLIENT]
		> add 'socwatch_start.sh' shell script as a common interface to call the 'socwacth_on_dev.sh' shell script on device in different cases by passing parameters
		> add 'video_playback_common_setup | video_playback_common_start | video_playback_common_stop'  shell scripts  

### MISC
	* Help BiHuan measure power consumption of video playback case on two engineering builds of MRFLD

	* Help Richard take the DISP-BW of VIDEO_PLAYBACK_1080P | VIDEO_PLAYBACK_1080P_FRC | VIDEO_PLAYBACK_1080P_60FPS
		* It seems feature 'disp-ddr-bw' of SOCWATCH tool (1.2.1) does not work well on FFRD-PR2 [NOT TRIED ON VVBOARD]
		* The socwatch tool can runs less than 10s while FRC disabled
		* The socwatch tool can runs more than 50s while FRC enabled

	* [WW47 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends

	* [NI DEVICE]
		[TASK-2] license of software, waiting for Yu Liu's reply
			[STATE - DONE] Yu Liu has send me the license via email and Richard has install the License on Labview


### TRACKING
	* This weekly build [ww46] can not launch *STOCK BROWSER* on both VV BOARD and FFRD-PR2 with the 'Parameters Settings'
		archieved on ww43 as below
		> VV BOARD [Power Tool Setting -> Parameters] 'Power-up current limit' > 5A && set the run-time current limit to maximum
		> FFRD-PR2 [Power Tool Setting -> Parameters] 'Power-up current limit' > 5A && keep others as default
	Have check with camera team
	[STATE - DONE] CHECKED! camera team's VV BOARD can lunch STOCK BROWSER well

### TO DO NEXT WEEK
	> [WEEKLY WORK]
		> build new libs for ww47 [AwesomePlayer.cpp | SensorSevice.cpp | Vpp_SETTING ]
		> Measure the ww45 build power consumption on VV Board and FFRD-PR2
		> Do the socwatch and powerbreakdown measurement and the analysis work

	> [AUTO VPNP TOOL]
		[HEARTBEAT WITH CAMERA]
		[TASK-1] Optimize the image similarity comparsion
		[TASK-2] Design the basic GUI with python Tkinter module

	> [MISC]
		> [ANDROID LEARNING] learning android app development

