
# XLS_ANALYZE TOOL
xls analyze tool is used to analyze the csv files, it will create Excel report from the data

### Installation
-----------

Before runing the script, you need install related python libs

* xlrd : read data from excel file

    `sudo apt-get install python-xlrd`

* xlwt : write data to excel file

    `sudo apt-get install python-xlwt`

* xlutils :Utilites for working with Excel files that required both xlrd and xlwt

    1. Download tar file from <https://pypi.python.org/pypi/xlutils>

    2. extract file from it, and execute command below

        `sudo python setup.py install`


### Usage

-------------
### analyze.py
**Syntax** : analyze.py [platform = MRFLD | BYT] [csv_folder]

**NOTE** : Please put the **Summary csv file** and **fps log file** in the csv_folder

Example - 1:
> ./analyze.py MRFLD csv

Example - 2:
> python analyze.py BYT ww44

### raw2db.py
**Syntax** : python raw2db.py [platform = MRFLD | BYT] [DEIVCE] [WEEK] [csv_folder]

Example - 1:
> ./raw2db.py MRFLD FFRD ww49 csv_folder

Example - 2:
> python raw2db.py BYT FFRD8 ww48 csv_folder

### analyze4cmp.py
**Syntax** : ./analyze4cmp.py [platform = MRFLD | BYT] [csv_file1] [csv_file2] ...

Example - 1:
> ./analyze4cmp.py MRFLD idle1.csv idle2.csv

Example - 2:
> python analyze4cmp.py BYT idle1.csv idle2.csv idle3.csv


### Change log
-------------
* 2014-03-07 **[NEW FEATURE]** retrieve fps from media_record_fps and store into database
* 2014-03-04 **[NEW FEATURE]** add support for MOOREFLD
* 2014-03-03 [csvr.py]change the way retrieve pstate for ANN-based socwatch analysis upgrade
* 2013-12-11 **[NEW FUNCTION]** add raw2db.py save summary csv data and fps data into MySQL database
* 2013-12-10 **[NEW FEATURE]** capture fps from fps_log_file
* 2013-12-04 **[NEW FUNCTION]** add analyze4cmp.py for two or more summary csv files's comparison
* 2013-12-03 Introduction file (README.md) added

### Related change
* 2014-03-03 **[SOCWATCH ANALYZER]** SOCWATCH V1.3 for ANN-based has no-aligning result in pstate
* 2014-02-19 **[SOCWATCH ANALYZER]** SOCWATCH V1.3 changed NC-State title.
    -> 'North Complex   ,Residency' to 'North Complex   ,Residency During S0i0'
        which lead to failure of creating csvReader Object
