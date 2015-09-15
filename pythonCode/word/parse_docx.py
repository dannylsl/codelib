import os
import sys
import win32com
from win32com.client import Dispatch, constants
from docx.api import Document
#import docx 


if __name__ == "__main__" :

#    w = win32com.client.Dispatch('Word.Application')
    print "main"
    filename = "test.docx"
    path = "C:\\Users\\dannylsl\\Documents\\"
    filepath = "%s%s"%(path, filename)
    print filepath

    #docx = w.Documents.Open( FileName = f )
    d = Document(filepath)
    t = d.tables[0]
    name = t.cell(0,1).text
    situation = t.cell(0,8).text
    people = t.cell(1,2).text
    title = t.cell(1,8).text
    print name, situation, people,title

    sys.exit()
