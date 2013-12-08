##WW48 SUMMARY
#####DATE:2013-12-08	AUTHOR: Shaoling


### WEEKLY WORK
	* build new libs for ww48 [AwesomePlayer.cpp | SensorSevice.cpp ]
		1. Since the stagefright log can be enabled and disabled with command, there is no need to rebuild the
			new lib for AwesomePlayer
		2. libsensorservices.so does not work because the new modification on the Android framework
			More information: http://android.intel.com:8080/#/c/146681/
			stream cases are ignored on **VVBOARD** because the we can not set screen in landscape mode

	* Measure the ww48 build power consumption on VVBOARD and FFRD-PR2
		The power measured with DPST feature enabled is about 50mw higher than it with DPST feature disabled
		The 'Intel Smart Video' is still disappeared on SETTINGS board of build ww48

	* Do the socwatch measurement and the analysis work
	* [WW49 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends

### AUTO VPNP TOOL
	* [CLIENT]
		add voice reminder in HALF-AUTO-MODE(auto_mode = False)
		It will make voice to remind user to make choice when each case is done

	* [AUTO VPNP DATA PROCESS]
		> xls_analyze function improvement
			1. improve the parameters check
			2. add analyze4cmp.py for two or more summary csv files comparison
			3. add README.md as introduction

		> Code for a data comparison tool
			_[STATE - ONGOING]_
			Save the xls report data into MySQL database and comparison data of weeks through web Browser

	* [HEARTBEAT WITH CAMERA]
		1. add new function to get a single image for comparison
		
### MISC
	1. Help Haiyang check the bug #155626
		It seem the time delay is in relationship with the Dalvikvm java virtual Machine. Not surely
	2. Wrote a article about 'How to use PhoneFlash Tool' on redmine
		http://autotest.bj.intel.com/redmine/projects/pnp-knowledge-base/wiki/%E5%A6%82%E4%BD%95%E4%BD%BF%E7%94%A8_phone_flash_tool/
	3. Help Bihuan using the 'xls_analyze' tool which helps creating excel report from csv files
	4. help binglin check wheather the two optimization works.Portrait mode FRC optimaziton
	5. Bugzilla account being actived, Thanks for Richard and Yanli
	6. Help bihuan and Tianyang Zhu measuring the power | socwatch | fps difference between Saltbay build 33883 and SaltBay build 33884
	7. take part in Intel Volunteers' Day


### TO DO NEXT WEEK

	> [WEEKLY WORK]
		> Measure the ww49 build power consumption on VV Board and FFRD-PR2
		> Do the socwatch and powerbreakdown measurement and the analysis work
		> [WW50 SOURCE CODE DOWNLOAD] set the auto-download and auto-build program prepared to work at weekends

	> [AUTO VPNP TOOL]
		[HEARTBEAT WITH CAMERA]
		> Basic Heartbeat for common case during setup and stop step

	* [AUTO VPNP DATA PROCESS]
		[DATA COMPARISON] 	
		> Save data from xls to MySQL database
		> Display comparison data on web page
