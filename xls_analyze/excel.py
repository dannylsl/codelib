import xlrd
import xlwt
from xlutils.copy import copy

data = xlrd.open_workbook('MRFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE.xls', formatting_info = True)
#formatting_info = Ture support the xls only, Not xlsx

table = data.sheets()[0]

cell_B4 = table.cell(6,1)
cell_B4_value = table.cell(6,1).value

print cell_B4
print cell_B4_value

table.put_cell(6, 1, 1, 0.114, 0)
cell_B4 = table.cell(6,1)
print cell_B4  #xlrd can read data from excel, but failed to write data to excel

wb = copy(data)
ws = wb.get_sheet(0)
wb.save("MRFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE.xls")
