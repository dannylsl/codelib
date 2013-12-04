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
**Syntax** : analyze.py [platform = MRFLD | BYT] [csv_folder]

Example - 1:

	analyze.py MRFLD csv
Example - 2:

	python analyze.py BYT ww44


