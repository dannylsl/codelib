#!/bin/bash

import MySQLdb
import datetime

try:
    conn = MySQLdb.connect(host='vpnp-workstation1', user='root', passwd='123456', db='python_test',charset='utf8', port=3306)
    cur = conn.cursor()
    print ">>>>> Mysql Connected"

### READ DATA
    count = cur.execute('select * from table1')
    print  "count = %d" %count
    result = cur.fetchone()
    print "print one result"
    print "ID:%s data:%s date:%s"%result

### INSERT DATA
    dt = datetime.datetime.now().strftime("%Y-%m-%d")
    value = ['data', dt]
    print value
    cur.execute('insert into table1 values(NULL, %s, %s)', value)
    conn.commit() # Without conn.commit() the operation will be ignored

### UPDATE DATA
    cur.execute('update table1 set `data`=\'data_updated\' where `id`=1')

### READ DATAS
    print "FETCH 3 DATA"
    cur.execute('select * from table1')
    result = cur.fetchmany(3)
    print result

    print "==" * 10
    cur.scroll(0, mode='absolute')
    results = cur.fetchall()
    for r in results :
        print r

    cur.close()
    conn.close()
    print ">>>>> Mysql Closed"

except MySQLdb.Error, e:
    print "Mysql Error %d : %s"%( e.args[0], e.args[1])

