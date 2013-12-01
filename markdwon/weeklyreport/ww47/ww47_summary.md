##WW47 SUMMARY
#####DATE:2013-11-30	AUTHOR: Shaoling

### WEEKLY WORK
	* build new libs for ww47 [AwesomePlayer.cpp | SensorSevice.cpp | Vpp_SETTING ]
		_[STATE-DONE]_
		Vpp setting was removed from SETTING GUI of build ww47, it is bug waiting for solution
		It seems there is no need to rebuild the AwesomePlayer.cpp
			> execute `adb shell set_prop dump.debug.log 2` to enable the FPS log out
			> execute `adb shell get_prop dump.debug.log 2` to check

	* Measure the ww47 build power consumption on VV Board and FFRD-PR2
		_[STATE-DONE]_ Most cases return Okay except stream_chrome & stream_stock
			* The com.android.settings crashed after I push the old wpa_supplicant.conf file to
				the device. Since the wpa_supplicant.conf has changed from Android 4.4(Kitkat)
			* The stream cases had been re-measured on 2013-11-26
				_[STATE - DONE]_
				The reason why the com.Android.settings crashed is that the post_flash.sh
				shell-scirpt remove the NFC, without which the com.Android.settings crashed

	* Do the socwatch and powerbreakdown measurement and the analysis work
		_[STATE-DONE]_
			* Socwatch cases has been measured and the analysis report had been done
			* The powerbreakdown measument was ignored. 
				*HAVE A TRY* 'Get powerbreakdown via VV BOARD of Camera team'

### AUTO VPNP TOOL 
	* [HEARTBEAT WITH CAMERA]
		[TASK-1] Optimize the image similarity comparsion
		_[STATE-NOT START]_
		[TASK-2] Design the basic GUI with python Tkinter module
		_[STATE-ON GOING]_ 
			1. basic GUI has been designed and implemented. GUI as below
			![Camera Heartbeat GUI](https://github.com/dannylsl/codelib/blob/66c291c2ffe67dc4298c05fd3383c2e1b1ff2f56/markdwon/weeklyreport/ww47/hbcamera.png)
			2. The functions is implementing, a problem about canvas blink was solve.
				More information: <http://stackoverflow.com/questions/20307718/python-tkinter-display-images-on-canvas-it-always-blink>
			
	* [CLIENT]
		1. add shell-script get_fps.sh as the common interface to get fps with libstagefright.so
		2. add timestamp to the 'adb logcat' in get_fps.sh
		3. increase the delay time to 1 minute in 'dumpsys.sh'
			[CHANGED] The delay time changed to 15 seconds. since the usb plugin will be disconnect	in 1 minute
		4. new cases add : video_playback_1080p_24fps | video_playback_1080p_24fps_fps_stagefright
		5. Modify vpnp.py that if the 'with_monsoon = False', do not call 'socwatch_start.sh' shell-scprit to run the socwatch tool
		6. The code has been update to Gerrit Server and thanks for haiyang's code review 

	* [AUTO BUILD] 
		1. add libscopy.sh to copy the libs rebuilt from /out/target/product/
		2. _[TO DO]_ write a shell-script to copy the source libs from device for backup. execute before post_flash

	* [AUTO DATA PROCESS]
		1. analyze.py output filename changed. adding the csv folder name as suffix 

### MISC
	* [WW48 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends
	* help Tianmi to get the power of HEVC 24fps clip and the fps it really take on Pre-intergration build #33883
		The result turns bad as below
			No.1	Power 2200mw or so & fps = 6.11
			No.2	Power 2500mw or so & fps = 5.33
	* help Tianmi to get the power of HEVC 24fps clip and the fps it really take on Pre-intergration build #33916
			No.1	Power 2391.68mw or so & fps = 5.58577:
			No.2	fps = 6.64
			No.3	fps = 5.61

### TO DO NEXT WEEK

	> [WEEKLY WORK]
		> build new libs for ww48 [AwesomePlayer.cpp | SensorSevice.cpp | Vpp_SETTING ]
		> Measure the ww48 build power consumption on VV Board and FFRD-PR2
		> Do the socwatch and powerbreakdown measurement and the analysis work
			*HAVE A TRY* 'Get powerbreakdown via VV BOARD of Camera team'

	> [AUTO VPNP TOOL]
		[HEARTBEAT WITH CAMERA]
		[TASK-1] Optimize the image similarity comparsion
		_[STATE-NOT START]_
		[TASK-2] Design the basic GUI with python Tkinter module
		_[STATE-ON GOING]_ 
			1. The functions is implementing, a problem about canvas blink was solve.
				More information: <http://stackoverflow.com/questions/20307718/python-tkinter-display-images-on-canvas-it-always-blink>

	> [MISC]
		> [ANDROID LEARNING] learning android app development

