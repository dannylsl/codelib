import os
import sys
import win32com
#from win32com.client import Dispatch, constants
from docx.api import Document


if __name__ == "__main__" :

#    w = win32com.client.Dispatch('Word.Application')
    print "main"
    filename = "test.docx"
    path = "C:\\Users\\dannylsl\\Documents\\"
    filepath = "%s%s"%(path, filename)
    print filepath

    #docx = w.Documents.Open( FileName = f )
    d = Document(filepath)
    print "TABLE COUNTS:",len(d.tables)
    for i in range(0, len(d.tables)) :
        r_len = len(d.tables[i].rows)
        c_len = len(d.tables[i].columns)
        print "rows=%s  columns=%s"%(r_len, c_len)
        for r in range(0, r_len) :
            for c in range(0, c_len) :
                print "[%s, %s]%s"%(r,c, d.tables[i].cell(r,c).text)


    sys.exit()
