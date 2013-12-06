#!/bin/bash

import MySQLdb

try:
	conn = MySQLdb.connect(host='localhost', user='root', passwd='123456', db='python_test', port=3306)
	cur = conn.cursor()
	print ">>>>> Mysql Connected"
	count = cur.execute('select * from table1')
	print  "count = %d" %count
	result = cur.fetchone()
	print "print one result"
	print "ID:%s data:%s date:%s"%result
	cur.close()
	conn.close()
	print ">>>>> Mysql Closed"
except MySQLdb.Error, e:
	print "Mysql Error %d : %s"%( e.args[0], e.args[1])
