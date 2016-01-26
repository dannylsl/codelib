# -*- encoding: utf-8 -*-

import MySQLdb
import sys

if __name__ == "__main__" :

    try:
        conn = MySQLdb.connect(host='localhost', user='cupdata', passwd='cupdata',
                                db='cupdata',charset='utf8', port=3306)
        cur = conn.cursor()
    except MySQLdb.Error, e:
        print "Mysql Error %d : %s"%( e.args[0], e.args[1])
        sys.exit()

    cur.execute('select `id`,`code`, `desc`, `type`, `comment` from ds_content')
    results = cur.fetchall()
    for r in results :
        id = r[0]
        comment = r[4]
        if comment != "":
            new_comment = comment.replace('\n','<br>').strip()
            if new_comment != comment :
                sql = "update ds_content set `comment`='%s' where `id`=%d"%(new_comment, id)
                if cur.execute(sql) :
                    print "[OK ]",sql
                else :
                    print "[ERR]",sql
                conn.commit()

    cur.close()
    conn.close()
