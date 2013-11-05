import xlrd
data = xlrd.open_workbook('MRFLD_SOCWATCH_ANALYSIS_PR2_TEMPLATE.xlsx')

table = data.sheets()[0]

cell_B4 = table.cell(1,3).value
print cell_B4
