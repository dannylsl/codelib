import xlrd
import xlwt

from xlutils.copy import copy

data = xlrd.open_workbook('MRFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE.xlsx', formatting_info = True)

table = data.sheets()[0]

cell_B4 = table.cell(3,1)
cell_B4_value = table.cell(3,1).value

print cell_B4
print cell_B4_value

table.put_cell(3, 1, 2, 0.115, 0)
cell_B4 = table.cell(3,1)
print cell_B4  #xlrd can read data from xlsx, but failed to write data to xlsx

wb = copy(data)
ws = wb.get_sheet(0)

wb.save("out.xlsx")
