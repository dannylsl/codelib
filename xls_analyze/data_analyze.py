import os
import sys
import string
import xlrd
import csv
import xlwt

from xlrd import open_workbook
from xlutils.copy import copy

def write_result_xls(path_xls) :

	rb = open_workbook(path_xls, formatting_info = True)
	rs = rb.sheet_by_index(0)
 
	wb = copy(rb)
	ws = wb.get_sheet(0)
	ws.write(9, 4, 'changed!!!!!!!!')
 
	wb.save(path_xls)


def analyze_file_csv(path_csv, path_xls) :

	reader = csv.reader(file(path_csv, 'rb'))
	for line in reader :
		print "line: %s"%line

		for i in range(0, int(len(line))) :
			print "(%d, {%s})"%(i, line[i])

	write_result_xls(path_xls)


###############################
### main
###############################

#analyze_file_csv("record.csv", "ww37_merrifield_socwatch_analysis_.xlsx")
analyze_file_csv("record.csv", "demo.xlsx")


