#!/usr/bin/python

import cgi

form = cgi.FieldStorage()

name = getvalue('name', 'world')

print 'Content-type: text/html'
print 
print 'Hello %s'%name
